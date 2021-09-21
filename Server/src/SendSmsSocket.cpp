
#include "SendSmsSocket.h"
#include "splitManager.h"
#include "srverr.h"
#include "settings_consts.h"
//#include "PhoneInfo.h"

#include <smsuaddr.h>	// KSmsAddrFamily
#include <gsmubuf.h>	// CSmsBuffer
#include <smsustrm.h>	// RSmsSocketReadStream
#include <s32file.h>
#include <smutset.h>
#include <BAUTILS.H>
#include <smsclnt.h>

//#include <txtetext.h>
//#include <smuthdr.h>
//#include <gsmuset.h>
//#include <gsmuset.h>



//Constructor
CSmsSenderSocket::CSmsSenderSocket(RSocketServ& aSocketServer, RFs& fs, MSmsSendHandler* aHandler, const TDesC& outPath) : CActive(EPriorityStandard)
	{
	iFileName.Create(200);
	iOutBoxPath.Create(outPath);
	iHandler = aHandler;
	iFs = fs;
	iSocketServer = &aSocketServer;
	}

CSmsSenderSocket* CSmsSenderSocket::NewL(RSocketServ& aSocketServer, RFs& fs, MSmsSendHandler* aHandler, const TDesC& outPath)
	{
	CSmsSenderSocket* self = new (ELeave) CSmsSenderSocket(aSocketServer, fs, aHandler, outPath);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

void CSmsSenderSocket::ConstructL()
	{
	CActiveScheduler::Add( this );
	__LOG_OPEN("Guardian", "Sender.txt");
	iTimer = CTimeOutTimer::NewL(*this);
	
	iSca.Create(_L(""));

#ifndef __WINSCW__
	User::LeaveIfError(iSendSocket.Open(*iSocketServer, KSMSAddrFamily, KSockDatagram, KSMSDatagramProtocol));

	TSmsAddr smsAddr;
	smsAddr.SetSmsAddrFamily(ESmsAddrSendOnly);
	iSendSocket.Bind(smsAddr);
#endif

	iGoodQueue = CQueue::NewL();
	iBadQueue = CQueue::NewL();
	iSplitManager = CSplitManager::NewL( iFs );
	
	// Timer per i msg non inviati...
	iPeriodic = CPeriodic::NewL(EPriorityStandard);
	iStato = EIdle;

	ClearOutBox();
	}

CSmsSenderSocket::~CSmsSenderSocket()
	{
	__LOG_TXT("Destructor");
	Cancel();
	if (iTimer)
		delete iTimer;
	if (iPeriodic)
		delete iPeriodic;
	if (iSplitManager)
		delete iSplitManager;
	if (iGoodQueue)
		delete iGoodQueue;
	if (iBadQueue)
		delete iBadQueue;
	iSca.Close();
	iSendSocket.Close();
	iOutBoxPath.Close();
	iFileName.Close();
	__LOG_TXT("EndDestructor");
	__LOG_CLOSE;
	}



void CSmsSenderSocket::DoCancel()
	{
	__LOG_TXT("Cancel");
	if (iTimer)
		iTimer->Cancel();
	if (iPeriodic)
		iPeriodic->Cancel();
	if (iStato == ESending)
		iSendSocket.CancelIoctl();
	}


/*TBool CSmsSenderSocket::FindFirstFile(const TDesC& aPattern, TDes& aFileName)
	{
    TFindFile file_finder(iFs);
    CDir* file_list;

//	_L("*.$$$")  _L("*.err*")
	TInt ris = file_finder.FindWildByDir(iOutBoxPath, aPattern, file_list);
	if (ris != KErrNone) return EFalse;

	// ordina x data di ultima modifica (+vecchi in testa)
	file_list->Sort(ESortByDate);

	// Cerca nella lista il primo file saltando le directory
	TBool found = EFalse;
	TInt i=0;
	while ((i<file_list->Count()) && (!found))
		{
		if ((*file_list)[i].iAtt & KEntryAttDir) i++;
		else found = ETrue;
		}

	if (found)
	{
		// rileva il nome completo del file
		TParse fullentry;
		fullentry.Set((*file_list)[i].iName,& file_finder.File(),NULL);
		aFileName.Copy( fullentry.FullName() );
		__FLOG( fullentry.FullName() );
	}
	delete file_list;
	return found;
	}*/


TInt CSmsSenderSocket::CallBack_SendBadMessageL(TAny * pX)
	{
	return ((CSmsSenderSocket*)pX)->SendBadMessageL();
	}


TBool CSmsSenderSocket::SendGoodMessageL()
	{
	__LOG_TXT("Try SendGoodMessageL");
	if (IsActive())
		return ETrue;
	__LOG_TXT("SendGoodMessageL");	
	// Spedisce gli altri msg validi rimasti
	HBufC* fName = iGoodQueue->Dequeue();
	if (fName == NULL)
		return EFalse;
	iFileName.Copy( fName->Des() );
	delete fName;
	
	DoSendCurrentMessageL(); // Sending...
	return ETrue;
	}


TInt CSmsSenderSocket::SendBadMessageL()
	{
//	if (iStato != EIdle)
//		return ETrue;
	__LOG_TXT("TrySendBadMessageL");
	if (IsActive())
		return ETrue;
	__LOG_TXT("SendBadMessageL");

	HBufC* fName = iBadQueue->Dequeue();
	if (fName == NULL)
		{
		__LOG_TXT("Cancel Periodic");
		iPeriodic->Cancel();
		__LOG_TXT("Cancelled");
		if (iHandler)
			iHandler->AllSmsWereSentL();
		return EFalse;
		}
	iFileName.Copy( fName->Des() );
	delete fName;
	
	this->GetScaL(iSca);
	DoSendCurrentMessageL(); // Sending...
	return ETrue;
	}


void CSmsSenderSocket::DoSendCurrentMessageL()
	{
	__LOG_TXT("Try DoSendCurrentMessageL...");
//	if (iStato != EIdle)
//		return;
	if (IsActive())
		return;
	__LOG_TXT("DoSendCurrentMessageL:");
	__LOG_DES(iFileName);

	CSmsMessage* msg = CSmsMessage::NewL(iFs, CSmsPDU::ESmsSubmit, CSmsBuffer::NewL());
	CleanupStack::PushL(msg);

	RFileReadStream file;
	// apre il file e recupera il CSmsMessage
	file.Open(iFs, iFileName, EFileRead);
	CleanupClosePushL(file);
	file >> *(msg);
	CleanupStack::PopAndDestroy(); // aFile

	__LOG_TXT( "DEST:" );
	__LOG_DES( msg->ToFromAddress() );

/*********************
 
	// Impostazioni proprieta' del messaggio...
	CSmsSubmit& submit = (CSmsSubmit &) msg->SmsPDU();

	submit.SetRejectDuplicates(ETrue);
	submit.SetReplyPath(EFalse);
	submit.SetStatusReportRequest(EFalse);
	submit.SetValidityPeriod(ESmsVPWeek);

	// VP Assoluto... ESmsVPFSemiOctet
	// VP Relativo... ESmsVPFInteger
	submit.SetValidityPeriodFormat(TSmsFirstOctet::ESmsVPFInteger);
	submit.SetAlphabet( TSmsDataCodingScheme::ESmsAlphabet7Bit);
	if (submit.ProtocolIdentifierPresent())
		{
		__FLOG( _T8("PID Present") );
		submit.SetPIDType(TSmsProtocolIdentifier::ESmsPIDTelematicInterworking);
		submit.SetTelematicDeviceIndicator(TSmsProtocolIdentifier::ESmsNoTelematicDevice);
		}
*/

	// TTime aTime;
	// aTime.UniversalTime(); 	// Il cell. aggiunge in automatico il daylight saving per formare HomeTime() ???
	// msg->SetTime(aTime);
	
	__LOG_TXT("SetSCA...");
	msg->SetServiceCenterAddressL(iSca);
	//__LOG_TXT("SetOptimize..."));
	//msg->OptimizeSettingsL(CSmsMessage::ESmsFlagOptimizeAlphabet|CSmsMessage::ESmsFlagOptimizeConcatenation);
	//**** msg->OptimizeSettingsL(CSmsMessage::ESmsFlagOptimizeAlphabet);

	__LOG_TXT("SCA:");
	__LOG_DES( iSca );
	__LOG("MsgLen2:%d", msg->MessageLengthL() );
#ifndef __WINS__
	RSmsSocketWriteStream writeStream(iSendSocket);
	writeStream << *(msg);
	writeStream.CommitL();
	writeStream.Close();
#endif

	__LOG_TXT("Send - IOCTL");
	CleanupStack::PopAndDestroy();	// aMsg

	// Invia il messaggio
	iOctlWrite() = KSockSelectWrite;
	iSendSocket.Ioctl(KIoctlSendSmsMessage, iStatus, &iOctlWrite, KSolSmsProv);
	SetActive();
	iStato = ESending;
	}


void CSmsSenderSocket::ClearOutBox()
	{
	BaflUtils::DeleteFile(iFs, iOutBoxPath, CFileMan::ERecurse);
	iGoodQueue->Clear();
	iBadQueue->Clear();
	}


void CSmsSenderSocket::CleanNumber(TDes& aNumber)
{
	TInt i=0;
	while (i<aNumber.Length())
	{
		if ((aNumber[i] >= '0' && aNumber[i] <= '9') || aNumber[i] == '+')
			i++;
		else
			aNumber.Delete(i, 1);
	}
}


TInt CSmsSenderSocket::ScheduleSendingSmsL(const TDesC& aNumber, const TDesC& aMessage, TBool split)
	{
//	return KErrNone;
	if (aMessage.Length() <= 0)
	{
		__LOG_TXT("Len<0");
		return KErrMessageNotSet;
	}
	iSplitManager->SetBuffer( aMessage, split );
	TInt err = KErrNone;
	while ( iSplitManager->MoveNextL() )
		{
		TPtrC toSend;
		TSmsDataCodingScheme::TSmsAlphabet alphabet;
		iSplitManager->GetCurrent(toSend, alphabet);
		err |= DoScheduleSendingSmsL( aNumber, toSend, alphabet );
		}
	return err;
	}


TInt CSmsSenderSocket::DoScheduleSendingSmsL(const TDesC& aNumber, const TDesC& aMessage, TSmsDataCodingScheme::TSmsAlphabet aAlphabet)
	{
	__LOG_TXT("ScheduleSendingSmsL");
	if (aMessage.Length() <= 0)
	{
		__LOG_TXT("Len<0");
		return KErrMessageNotSet;
	}
	if (aNumber.Length() <= 0)
	{
		__LOG_TXT("Num<0");
		return KErrNumberNotSet;
	}

	// Check Free Space
	TVolumeInfo volumeInfo;
	User::LeaveIfError( iFs.Volume(volumeInfo, EDriveC) );
	if (volumeInfo.iFree < 10000) // 10Kb
		return KErrMessageNotSet;

	__LOG_TXT("...In Corso");
	iFs.MkDirAll(iOutBoxPath);

	RFileWriteStream file;
	TFullName fileName;
	TRAPD(err, file.Temp(iFs, iOutBoxPath, fileName, EFileWrite ));
	if (err != KErrNone)
		{
		return err;
		}
	if (fileName.Length() == 0)
		{
		return KErrPathNotFound;
		}
	CleanupClosePushL(file);
	
	__LOG_TXT("Schedule Sending:");
	__LOG_DES(aMessage);
	__LOG_DES(fileName);

	CSmsMessage* msg = CSmsMessage::NewL(iFs, CSmsPDU::ESmsSubmit, CSmsBuffer::NewL());
	CleanupStack::PushL(msg);

	__LOG_TXT("SetToFromAddr");
	msg->Buffer().InsertL(0, aMessage);

	TNumber cleanedNum = aNumber;
	CleanNumber(cleanedNum);
	__LOG_TXT("OrigNumber:");
	__LOG_DES(aNumber);
	__LOG_TXT("CleanNumber:");
	__LOG_DES(cleanedNum);
	msg->SetToFromAddressL(cleanedNum);
	
	 
	// Impostazioni proprieta' del messaggio...
	CSmsSubmit& submit = (CSmsSubmit &) msg->SmsPDU();
	
	submit.SetRejectDuplicates(ETrue);
	submit.SetReplyPath(EFalse);
	submit.SetStatusReportRequest(EFalse);
	submit.SetValidityPeriod(ESmsVPMaximum);

	// VP Assoluto... ESmsVPFSemiOctet
	// VP Relativo... ESmsVPFInteger
	submit.SetValidityPeriodFormat(TSmsFirstOctet::ESmsVPFInteger);	// TODO: Forse devo cambiare questo...
	submit.SetAlphabet( aAlphabet);
	
	if (submit.ProtocolIdentifierPresent())
		{
		__LOG_TXT("PID Present");
		submit.SetPIDType(TSmsProtocolIdentifier::ESmsPIDTelematicInterworking); // bit 7-6
		submit.SetTelematicDeviceIndicator(TSmsProtocolIdentifier::ESmsNoTelematicDevice); // bit 5
		
		// Forse e' possibile anche inviare cosi', ma per sicurezza, lasciamo invariato che sta funzionando...
		// submit.SetPIDType(TSmsProtocolIdentifier::ESmsPIDShortMessageType); // bit 7-6
		// submit.SetTelematicDeviceIndicator(TSmsProtocolIdentifier::ESmsNoTelematicDevice); // bit 5
		// sumbit.SetTelematicDeviceType(TSmsProtocolIdentifier::ESmsGsmMobileStation);
		}
	
/*
	TSmsUserDataSettings sett;
	sett.SetAlphabet( TSmsDataCodingScheme::ESmsAlphabet7Bit );
	sett.SetTextCompressed( EFalse );
	sett.SetTextConcatenated( EFalse );
	msg->SetUserDataSettingsL( sett );
	TInt totLen = msg->MaxMessageLength();
	__LOG("MsgLen1:%d"), msg->MessageLengthL() );
	__LOG("MaxLen1:"), totLen);
	msg->OptimizeSettingsL(CSmsMessage::ESmsFlagOptimizeAlphabet);
	totLen = msg->MaxMessageLength();
	__LOG("MsgLen2:%d"), msg->MessageLengthL() );
	__LOG("MaxLen2:"), totLen);
*/

	file << (*msg);
	__LOG_TXT("<< amsg");
	CleanupStack::PopAndDestroy(); // aMsg
	CleanupStack::PopAndDestroy(); // aFile
	iGoodQueue->EnqueueL( fileName );

	this->GetScaL(iSca);
	__LOG("Stato:%d", iStato);

	if (!IsActive())	// E' Idle...
		{
		SetActive();
		TRequestStatus* status=&iStatus;
		User::RequestComplete(status, KErrNone);
		__LOG("IsActive:%d", IsActive());
		}
	__LOG_TXT("Ends");
	return KErrNone;
	}


void CSmsSenderSocket::RunL()
	{
	__LOG_TXT("RunL");
	switch(iStato)
		{
		case EIdle:
		{
			__LOG_TXT("RunL.Idle.WakeUp!");
			break;
		}
		case ESending:
			{
			if (iStatus == KErrNone)
				{
				__LOG_TXT("RunL.Successful Sent");
				// Messaggio Inviato con Successo
				iFs.Delete(iFileName);
				if (iHandler)
					iHandler->SmsSentL();
				}
			else
				{
				__LOG("RunL.Error %d", iStatus.Int());
				// -4522 nel caso in cui si stia usando uno SCA di un'altro operatore... RILEVARE NUOVAMENTE SCA ???
				// -4550 nel caso in cui il TimeStamp abbia un valore errato (es. scadenza assoluta e data attuale impostata ad 1 anno prima)
				// -4550 nel caso in cui non ci sia credito a sufficienza (verificato con sim PosteMobile di papa')
				// -4562 ??? perche' ???  Boh, capita su RDA, ma neppure il cell riesce ad inviare...
				// -4623 evitato inserendo un ritardo di 5 secondi tra un invio e l'altro.
				RBuf newName;
				newName.CleanupClosePushL();
				newName.CreateL(iFileName.Length() + 10);
				newName.Copy(iFileName);
				TInt pos = newName.LocateReverse('.');
				TBuf<10> ext = newName.Right( newName.Length()-pos-1 );
				TUint val=0;
				TLex lex( ext ); //ext=$$$  ext=001
				lex.Val(val);	 // Converte lex in valore e
				if (val != 0)
					{	// *.$$$.001
					newName.SetLength(pos);
					}
				ext.Num(++val);

				newName.Append(_L("."));
				newName.Append(ext);

				__LOG_TXT("RunL.Rename");	
				__LOG_DES(iFileName);
				__LOG_DES(newName);
				iFs.Rename(iFileName, newName);
				iFileName.Copy(newName);
				CleanupStack::PopAndDestroy(); // newName
				if (val == MAX_SEND_RETRY)
					{
					__LOG_TXT("RunL.Abort Sending - Delete Message");
					__LOG_DES(iFileName);
					iFs.Delete(iFileName);
					} else
					{
					iBadQueue->EnqueueL( iFileName );	
					}
				}
			break;
			}
		}

	// Se non ha inviato un sms ma era semplicemente in Idle allora non attende per l'invio...
	TTimeIntervalSeconds waitTime = 5;
	if (iStato == EIdle)
		waitTime = 0;
	iStato = EIdle;
	
	// Aspetta 5 second prima di spedire il prossimo messaggio...
	if (!iTimer->IsActive())
		{
		__LOG_TXT("TimerAfter");
		iTimer->AfterTime(waitTime);
		}
	__LOG_TXT("End RunL");
	}


void CSmsSenderSocket::TimerExpiredL(TAny* src)
	{
	__LOG_TXT("TimerExpiderL");
	// Se ci sono dei messaggi buoni da inviare prova ad inviarli subito...
	if ( SendGoodMessageL() )
		return;
	
	// i messaggi buoni sono finiti
	// e' necessario controllare iStatus cosi' in caso di errore, si attende 2 minuti 
	if (iStatus != KErrNone)
		{
		if (!iPeriodic->IsActive())
			{
			__LOG_TXT("Start Periodic Timer");
			TTimeIntervalMicroSeconds32 interv(1000000*60*2); // 2 Minuti
			TCallBack call( CallBack_SendBadMessageL, this );
			iPeriodic->Start(interv, interv, call);
			}
		return;
		}
	
	// e' stato inviato con successo un messaggio che era corrotto
	SendBadMessageL();
	}


TInt CSmsSenderSocket::RunError(TInt aError)
	{
	__LOG("ERROR:%d", aError);
//	Cancel();
	return aError;
	}



void CSmsSenderSocket::HandleSessionEventL(TMsvSessionEvent aEvent, TAny *aArg1, TAny *aArg2, TAny *aArg3)
	{
	}


void CSmsSenderSocket::GetScaL(RBuf& aSCA)
	{
	__LOG_TXT("GetSCA:");
	aSCA.Close();
	CMsvSession* msvSession = CMsvSession::OpenSyncL(*this);
	CleanupStack::PushL(msvSession);

	CClientMtmRegistry* mtmReg = CClientMtmRegistry::NewL(*msvSession);
	CleanupStack::PushL(mtmReg);

	CSmsClientMtm* smsMtm = static_cast <CSmsClientMtm*> ( mtmReg->NewMtmL(KUidMsgTypeSMS) );
	CleanupStack::PushL(smsMtm);
	CSmsSettings& serviceSettings = smsMtm->ServiceSettings();

	if ( serviceSettings.ServiceCenterCount() > 0 )
	{
		CSmsServiceCenter& num = serviceSettings.GetServiceCenter( serviceSettings.DefaultServiceCenter() );
		aSCA.Create(num.Address());
	} else
	{
		aSCA.Create(_L(""));
		//aSCA.CreateL(30);
		//aSCA.Zero();
	}
	CleanupStack::PopAndDestroy(3, msvSession);
	__LOG_DES(aSCA);
	}


