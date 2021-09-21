/*
 ============================================================================
 Name        : Guardian.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : Your copyright notice
 Description : Exe source file
 ============================================================================
 */

#include "Guardian.h"

#include <Guardian_200131CB.rsg>

#include <FuzzyByte\Guardian\client.h> 
#include <FuzzyByte\Notes.h>
#include <FuzzyByte\resreader.h> 
#include <FuzzyByte\utils.h>
#include <FuzzyByte\phone.h>
#include <FuzzyByte\Processes.h>
#include <FuzzyByte\Contacts.h>

#include <etel3rdparty.h>
#include <e32base.h> 
#include <e32std.h>
#include <e32cons.h>            // Console
#include <e32property.h>
#include <COEMAIN.H>
#include <APGTASK.H> 
#include <eikENV.H> 
#include <bautils.h>
#include <SMUTHDR.H>
#include <txtrich.h> 

//#include <avkon.rsg>
//#include <avkon.hrh>
//#include <avkon.mbg>

_LIT(KResGuardian, "c:\\resource\\apps\\Guardian_200131CB.rsc");



CGuardian::CGuardian(TBool fromGui) :
	CBase(), iNetStatusPckg(iNetStatus), iFromGui(fromGui)
	{

	}



CGuardian* CGuardian::NewLC(TBool fromGui)
	{
	CGuardian* self = new (ELeave) CGuardian(fromGui);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CGuardian::~CGuardian()
	{
	__LOG_TXT("StartDestructor");
	delete iSimNotifier;
	
	if (iConfigObs) 
		delete iConfigObs;
	
	// Iridium
	delete iSmsMonitor;
	delete iCallsMonitor;
	// Iridium

	__LOG_TXT("Destructor");
	if (iTimer)
		delete iTimer;
	if (iProtApps)
		{
		iProtApps->Close();
		delete iProtApps;
		}
	if (iPhone)
		delete iPhone;
	if (iSmsLostPass)
		delete iSmsLostPass;
	if (iSmsPlugin)
		delete iSmsPlugin;
	if (iPluginManager)
		delete iPluginManager;
	if (iLogCleaner)
		delete iLogCleaner;
	if (iForegrObs)
		delete iForegrObs;
	delete iSecurityCode;
	iSession.Close();
	iSockServ.Close();
	iFs.Close();
	__LOG_TXT("EndDestructor");
	__LOG_CLOSE;
	}

void CGuardian::InitializeGoldAndPlatinumL(RGuardian& srv)
	{
	__LOG_TXT("GotRegCode");
	__LOG_DES(iRegCode);

	// iRegistered = srv.Register(iRegCode);  // 0 = NotReg  1 = Platinum  2 = Gold
	//__LOG("iRegistered:%d"), iRegistered);
	__LOG_TXT("Log Cleaner");

	for (TInt i = 0; i < ((srv.Register(iRegCode) + 1) >> 1); i++)
		{
		if (i % 2 == 0)
			{
			// *** GOOD
			TInt seconds = srv.GetInactivityDelay();
			iProtApps_Delay = seconds;
			iProtApps_Enabled = ETrue;
			iProtApps = new (ELeave) RArray<TInt32> ();
			srv.GetProtectedListL(*iProtApps);
			__LOG_TXT("Applications Locker");
			}
		else
			{
			// DUMMY ANTICRACK
			srv.GetProtectedListL(*iProtApps);
			iPluginManager = CPluginManager::NewL(iFs);
			iSmsPlugin = CSmsReceiverSocket::NewL(*this, iFs, iSockServ);
			iPassword = iRegCode;
			// DUMMY ANTICRACK 
			}
		}

	// *** START GOOD
	for (TInt i = 0; i < srv.Register(iRegCode); i++)
		{
		// i=0 Platin
		// i=1 Gold
		if (i % 2 == 0)
			{ // Platinum
			iPluginManager = CPluginManager::NewL(iFs);
			}
		else
			{
			// Gold
			delete iPluginManager;
			iPluginManager = NULL;
			iForegrObs = CFgrObserver::NewL(*this);
			}
		}
	// *** END GOOD

	// ANTICRACK -> Dovrebbe dare sempre 0 quindi non dovrebbe mai essere eseguito...
	for (TInt i = 0; i < srv.Register(iPassword); i++)
		{
		if (i % 2 == 0)
			{
			iPluginManager = CPluginManager::NewL(iFs);
			iSmsPlugin = CSmsReceiverSocket::NewL(*this, iFs, iSockServ);
			InitializeGoldAndPlatinumL(srv);
			}
		}
	// ANTICRACK

	for (TInt i = 0; i < srv.Register(iRegCode) % 2; i++)
		{
		if (i > 0)
			{ // ANTICRACK
			srv.GetProtectedListL(*iProtApps);
			// ANTICRACK
			}
		else
			{
			__LOG_TXT("ECOM Listener");
			// *** GOOD
			iForegrObs = CFgrObserver::NewL(*this);
			iSmsPlugin = CSmsReceiverSocket::NewL(*this, iFs, iSockServ);
			}
		}
	}


_LIT(KFORMAT_DATE, 	"%H:%T %D%M%*Y%/0%1%/1%2%/2%3%/3");


LOCAL_C TBool NumbersAreEquals(const TDesC& aNumber1, const TDesC& aNumber2)
	{
	TNumber num1_clean;
	for (TInt i=0; i<aNumber1.Length(); i++)
		{
		if (aNumber1[i] >= '0' && aNumber1[i] <= '9')
			num1_clean.Append( aNumber1[i] );
		}
	TNumber num2_clean;
	for (TInt i=0; i<aNumber2.Length(); i++)
		{
		if (aNumber2[i] >= '0' && aNumber2[i] <= '9')
			num2_clean.Append( aNumber2[i] );
		}
	TBool match = (num1_clean.Compare(num2_clean) == 0);
	if (num1_clean.Length() >= 7 && num2_clean.Length() >= 7)
		{
		match = (num1_clean.Right(7).Compare(num2_clean.Right(7)) == 0);
		}
	return match;
	}


void CGuardian::RealtimeSmsOrCallL(const TDesC& aDescription, const TDesC& aNumber, const TDesC& aText)
	{
/*  IRIDIUM
 
	il monitor non deve notificare sms in arrivo se il numero da cui proviene l'sms e' identico a quello del destinatario.
	altrimenti, se invio un sms a me stesso, poi ricevero' un sms di notifica che dara' luogo ad un'altra notifica ecc... ecc...
	  
	il monitor non deve notificare sms in uscita se il numero a cui e' destinato l'sms e' identico a quello del destinatario
	idem per le chiamate...
*/	  
	TBuf<30> date;
	TTime homeTime;
	homeTime.HomeTime();
	homeTime.FormatL(date, KFORMAT_DATE);
	
	RBuf msg;
	msg.CleanupClosePushL();
	msg.CreateL(200 + aDescription.Length() + aNumber.Length() + aText.Length());
	msg.Copy( aDescription );
	msg.Append(_L("<"));
	msg.Append(date);
	msg.Append(_L(" "));
	if (aNumber.Length() > 0)
		{
		msg.Append(aNumber);
		
		CContacts* cnt = CContacts::NewLC();	
		RBuf name( cnt->ResolveNumberL( aNumber ) ); name.CleanupClosePushL();
		if (name.Length() > 0)
			{
			msg.Append(_L(" "));
			msg.Append(name);
			}
		CleanupStack::PopAndDestroy( &name );
		CleanupStack::PopAndDestroy( cnt );
		} else
		{
		msg.Append(_L("N.Priv."));
		}
	msg.Append(_L(">\n"));
	msg.Append( aText );

	RGuardian srv;
	User::LeaveIfError(srv.Connect());
	CleanupClosePushL(srv);
	TNumber destNumber;
	srv.GetDestAddress(destNumber);
	__LOG_TXT("Sending SMS...");
	__LOG_DES(msg);

	// clean destNumber...
	TBool match = NumbersAreEquals(destNumber, aNumber);
	if (iRegCode.Length() <= 0)
		{
		match = EFalse;
		destNumber = aNumber;
		}
	if (!match)
		{
		srv.SendMessage(destNumber, msg);
		}
	CleanupStack::PopAndDestroy(&srv);
	
	CleanupStack::PopAndDestroy(&msg);
	}



void CGuardian::HandleNewMtmSmsL(const TDesC& aNumber, const TDesC& aText, TBool isIncoming)
	{
	if ((isIncoming) && (!iSmsIn)) return;
	if ((!isIncoming) && (!iSmsOut)) return;
		 
	if (isIncoming)
		{
		__LOG_TXT("*** Incoming Sms");
		__LOG_DES(aNumber);
		__LOG_DES(aText);
		RealtimeSmsOrCallL( _L("INBOX:\n"), aNumber, aText);
		} else
		{
		__LOG_TXT("*** Outgoing Sms");			
		__LOG_DES(aNumber);
		__LOG_DES(aText);
		RealtimeSmsOrCallL( _L("OUTBOX:\n"), aNumber, aText);
		}
	// send sms... Incoming SMS: +38282012929 data_e_ora skjdlaksjdlkjasdkjlkj
	}


void CGuardian::CallStatusChangedL(CTelephony::TCallStatus& aStatus,
		TInt aError)
	{
	if (aError != KErrNone)
		return;
	if ((aStatus == CTelephony::EStatusRinging) && (!iCallsIn))	return;
	if ((aStatus == CTelephony::EStatusDialling) && (!iCallsOut)) return;
	
	if (aStatus == CTelephony::EStatusRinging) 		// incoming
		{
		CTelephony::TTelNumber number;
		iCallsMonitor->GetPhoneNumber(ETrue, number);
		__LOG_TXT("*** Incoming Call");
		__LOG_DES(number);
		RealtimeSmsOrCallL( _L("INCALL:\n"), number, KNullDesC());
		}
	if (aStatus == CTelephony::EStatusDialling) 	// outgoing
		{
		CTelephony::TTelNumber number;
		iCallsMonitor->GetPhoneNumber(EFalse, number);
		__LOG_TXT("*** Outgoing Call");
		__LOG_DES(number);
		RealtimeSmsOrCallL( _L("OUTCALL:\n"), number, KNullDesC());
		}
	}

// si suppone che sia enabled...
void CGuardian::ConstructL()
	{
	__LOG_OPEN("Guardian","Guardian.txt");
	__LOG("From GUI: %d", iFromGui);

	__LOG_TXT("Create Timer");
	iTimer = CTimeOutTimer::NewL(*this, EPriorityHigh);
	User::LeaveIfError(iFs.Connect());
	User::LeaveIfError(iSockServ.Connect());

	__LOG_TXT("CPhone");
	iPhone = CPhone::NewL();
	iPhone->SetObserver(this);

	iSimNotifier = CSimNotifier::NewL( *this );
	
	__LOG_TXT("Detect Config Change");
	iConfigObs = CPubSubObserver::NewL(*this, KServerUid3, KPSChangeConfig);
	__LOG_TXT("StartMonitorProperty");
	iConfigObs->StartMonitorProperty();

	__LOG_TXT("LOSTPASS Listener");
	iSmsLostPass = CSmsReceiverSocket::NewL(*this, iFs, iSockServ);

	RGuardian srv;
	User::LeaveIfError(srv.Connect());
	CleanupClosePushL(srv);

	// Preleva la pass e la tiene in cache per ottimizzare la gestione di Uninstall-Protection
	srv.GetPassword(iPassword);
	__LOG_TXT("GotPassword");
	__LOG_DES( iPassword );

	srv.GetRegCode(iRegCode);
	iLogCleaner = CLogCleaner::NewL(iFs);
	InitializeGoldAndPlatinumL(srv);
	
	srv.GetMonitorParams(iSmsIn, iSmsOut, iCallsIn, iCallsOut);

	__LOG_TXT("Destroy Server");
	CleanupStack::PopAndDestroy(&srv); // srv

	__LOG_TXT("Connect WsSession");
	User::LeaveIfError(iSession.Connect());
	
	__LOG_TXT("AutoFlush");
	iSession.SetAutoFlush(ETrue);
		
	// Fallisce su N96 ???
	// Cambio per fare Lazy-Initialization... e via...
	// iSecurityCode = CSecurityCode::NewL(iSession, *this);

	/*	TBuf<20> buff;
	 TInt value;
	 TUid cat = {0x101F8789};

	 //	UID Idle Screen 101fd64c
	 RProperty::Get(cat, 2, value);
	 buff.AppendNum(value, EHex);
	 __FLOG(buff);
	 buff.Zero();

	 //	UID Telefono 100058b3
	 RProperty::Get(cat, 3, value);
	 buff.AppendNum(value, EHex);
	 __FLOG(buff);*/

	//	TInt err = BaflUtils::CopyFile( iFs, _L("c:\\tmp_reg.rsc"), _L("c:\\private\\10003a3f\\import\\apps\\GuardGUI_200131CC_reg.rsc"));
	//	__LOG("Err:%d"), err);
	__LOG_TXT("End ConstructL");
	}


void CGuardian::StartObserversAndWaitForSimL()
	{
	__LOG_TXT("BEGIN StartObserversAndWaitForSimL()");
	// Preleva numero... e se non e' attivo esce
	RGuardian srv;
	__LOG_TXT("Connect");
	User::LeaveIfError(srv.Connect());
	__LOG_TXT("Connected");
	CleanupClosePushL(srv);
	TNumber number;
	srv.GetDestAddress(number);
	__LOG_TXT("GotAddress");
	CleanupStack::PopAndDestroy(&srv);
	__LOG_TXT("Close Server");

	TBuf<15> intercept;
	intercept = KDELIMITER;
	intercept.Append(_L("LOSTCODE"));
	__LOG_TXT("StartReceivingL");
	iSmsLostPass->StartReceivingL(intercept);

	// Fa partire subito il cleaner senza aspettare la rete... Cosi' sicuram. il numero del plugin in ingresso sara' cancellato...
	__LOG_TXT("LogClenaer");
	if (iLogCleaner)
		iLogCleaner->StartCleaner(number);

	__LOG_TXT("ForegrObserver");
	if (iForegrObs) // GOLD...
		{
		__LOG_TXT("Ok");
		// TODO: Arriva qui solo se e' stato gia' registrato... Fare controlli anticrack...
		iForegrObs->StartObserver();
		}

	__LOG_TXT("SmsPlugins");
	if (iSmsPlugin) // PLATINUM... 
		{
		__LOG_TXT("Ok");
		// Arriva qui solo se e' stato gia' registrato... Fare controlli anticrack...
		intercept = KDELIMITER; 
		intercept.Append(iPassword);
		iSmsPlugin->StartReceivingL(intercept); 
		}

	// Attenda che arrivi la notifica se la SIM è presente oppure no
	iSimNotifier->WaitForSimL( iFs );

	//LockScreenDialogL();
	// TRAPD(err, iPluginManager->ProcessSmsPluginL(_L("32827123232"), _L("*DELETE*SMS")));

	__LOG_TXT("END StartObserversAndWaitForSimL()");
	}
 

void CGuardian::SimNotifyL(TBool isPresentAndReady)
	{
	CheckAndLockPhoneIfNeededL();
	
	delete iSimNotifier;
	iSimNotifier = NULL;

	// Se la SIM è presente attende che sia connessa alla rete
	// Attende il segnale di rete anche se non viene rilevata una SIM (chissà, magari verrà inserita più tardi)
	// if (isPresentAndReady)
		{
		// Serve per verificare se il cell. si trova gia' connesso alla rete
		iPhone->GetNetworkStatus(iNetStatus.iRegStatus);
		// Attende la rete...
		HandlePhoneEventL(ENotifyNetworkStatusChange);		
		}
	}


void CGuardian::HandlePhoneEventL(TPhoneFunctions event)
	{
	__LOG("HandlePhoneEvent:%d", iNetStatus.iRegStatus)
			
	if (event != ENotifyNetworkStatusChange)
		{
		return;
		}
	// Se non e' connesso alla rete aspetta di esserlo...
	if (iNetStatus.iRegStatus != CTelephony::ERegisteredOnHomeNetwork
			&& iNetStatus.iRegStatus != CTelephony::ERegisteredRoaming)
		{
		iPhone->NotifyNetworkStatusChange(iNetStatusPckg);
		return;
		}
	CheckSimAndSendSmsL();
	}


void CGuardian::CheckAndLockPhoneIfNeededL()
	{
	// il codice imsi non viene rilevato correttamente, quindi si attende prima di verificare che la sim sia inserita e pronta
	RGuardian srv;
	User::LeaveIfError( srv.Connect() );
	CleanupClosePushL( srv );
	TLockBehaviour behaviour = srv.GetLockBehaviour();

	// 0=Installer  1=GUI  2=ExtendedNotifier  3=Autostart
	if ((behaviour == ELockOnStartup) && (iFromGui >= 2))
		{
		__LOG_TXT("Lock On Startup");
		iIsLocked = ETrue;
		srv.SetLocked(ETrue);
		}
	
	if (behaviour == ELockOnSimChange) 
		{
		if (!srv.IsValidSim())
			{
			__LOG_TXT("Invalid IMSI");
			iIsLocked = ETrue;
			srv.SetLocked(ETrue);
			} 
		}
	
	iIsLocked = srv.IsLocked();
	CleanupStack::PopAndDestroy( &srv );
	
	if (iIsLocked)
		{
		__LOG_TXT("Launch GuardLock");
		Processes::Launch(_L("GuardLock_200131C8.exe"), 0x200131C8, ETrue);
		__LOG_TXT("Launched!");
		}
		// iSecurityCode->RequestCodeL(TUid::Uid(0x666), iIsLocked, iPassword);	
	}

    	
void CGuardian::StartL()
	{
	iDoneInitialization = EFalse;
	iTimer->AfterTime( TTimeIntervalSeconds(0) );
	}


void CGuardian::TimerExpiredL(TAny* src)
	{
	if (!iDoneInitialization)
		{
		StartObserversAndWaitForSimL();
		iDoneInitialization = ETrue;
		return;
		}
	
	TInt inact = User::InactivityTime().Int();
	__LOG("Inactivity Event:%d:%d", inact, iProtApps_Delay.Int());
	if (inact < iProtApps_Delay.Int())
		{
		__LOG("Wait More:%d", iProtApps_Delay.Int());
		iTimer->AfterInactivity(iProtApps_Delay);
		}
	else
		{
		__LOG_TXT("Lock Apps!");
		iProtApps_Enabled = ETrue;
		}
	}

// Deve per forza di cose girare in Background per fornire la protezione contro la disinstallazione non autorizzata...
// Anche la versione Free va tenuta aperta cosi' si puo' recuperare la password...
void CGuardian::CheckSimAndSendSmsL()
	{
	// Guardian e' per forza attivo altrimenti non sarebbe stato avviato...
	RGuardian srv;
	User::LeaveIfError(srv.Connect());
	CleanupClosePushL(srv);

	if (srv.IsIridium())
		{
		iSmsMonitor = CSmsMtmMonitor::NewL(*this);
		iCallsMonitor = CCallsMonitor::NewL(*this);
		iCallsMonitor->StartListening();
		}

	// Verifica cosa accade se viene acceso senza sim inserita... oppure Offline...
	if (!srv.IsValidSim())
		{
		__LOG_TXT("Invalid IMSI");

		RBuf msg;
		msg.CleanupClosePushL();
		msg.CreateL(180);
		srv.GetMessage(msg);
		TTime time;
		time.HomeTime();
		_LIT(KFORMAT_DATE, "%D%M%*Y%/0%1%/1%2%/2%3%/3 %H:%T");
		TBuf<30> tmp;
		time.FormatL(tmp, KFORMAT_DATE);
		tmp.Append(_L("\n"));

		//*** Qui ci sono 53 caratteri		
		msg.Insert(0, tmp);
		/*
		 01/01/07 23:19
		 // 38 caratteri per il testo
		 // 15 caratteri per data e ora
		 */
		if (iForegrObs)
			{
			TUint cell;
			TUint lac;
			TNetwork network;
			TCountry country;
			TOperName oper;
			iPhone->GetCellID(cell, lac, network, country, oper);

			CResReader* rdr = CResReader::NewLC(iFs, KResGuardian);

			TBuf<200> txt;
			//*** Qui ci sono 59 caratteri + 14 di MNC
			msg.Append(_L("\n"));
			rdr->ReadL(txt, R_LOCALIZE_CELL);
			msg.Append(txt);
			msg.AppendNum(cell); // 7+8

			rdr->ReadL(txt, R_LOCALIZE_AREA);
			msg.Append(txt);
			msg.AppendNum(lac); // 6+8

			rdr->ReadL(txt, R_LOCALIZE_NETWORK);
			msg.Append(txt);
			msg.Append(network); // 6+8 = 14 il codice MNC in realta' e' solo di 3 quindi occupa in tutto 9

			rdr->ReadL(txt, R_LOCALIZE_COUNTRY);
			msg.Append(txt);
			msg.Append(country); // 6+4 "\nMCC: "

			//			rdr->ReadL(R_LOCALIZE_OPERATOR, txt);
			//			msg.Append(txt);	msg.Append(oper.Left(10));	// 10+10
			CleanupStack::PopAndDestroy(rdr);

			// 59 caratteri per i dati + (9)
			// TODO: ...

			//*** Qui ci sono 43 caratteri
			TImsi imsi;
			TImei imei;
			iPhone->GetImsi(imsi);
			srv.GetImei(imei);
			msg.Append(_L("\n\nIMEI:"));
			msg.Append(imei); // 7+20
			msg.Append(_L("\nIMSI:"));
			msg.Append(imsi); // 6+15
			// 48 (43 perche' imei e' di 15 non di 20) caratteri per imsi ed imei
			// Per un TOT.MAX di 159...
			}
		TNumber number;
		srv.GetDestAddress(number);
		srv.SendMessage(number, msg);
		CleanupStack::PopAndDestroy(&msg); // msg
		}
	else
		{
		__LOG_TXT("Valid IMSI");
		// RILEVA IL NOME DELLA SIM...
		TImsiName name;
		srv.RegisterSim(name);
		__LOG_DES(name);
		}
	//	this->IncomingSmsL(this->iSmsPlugin, _L("+393282740578"), _L("*retrieve*contacts=999*incalls=999*outcalls=999*misscalls=999*inbox=999*outbox=999"));
	//	this->IncomingSmsL(this->iSmsPlugin, _L("+393282740578"), _L("*retrieve*contacts=999"));
	//	this->IncomingSmsL(this->iSmsPlugin, _L("+393282740578"), _L("*delete*calendar"));

	CleanupStack::PopAndDestroy(&srv); // srv
	__LOG_TXT("Closed");
	}


void CGuardian::IncomingSmsL(const TAny* src, const TDesC& aFromNumber,
		const TDesC& aData)
	{
#ifndef _DEBUG
	__LOG_TXT("BEGIN IncomingSmsL");
	__LOG_DES(aData);
	if (src == iSmsPlugin) // Da un Plugin
		{
		// TODO: Arriva qui solo se e' stato gia' registrato... Fare controlli anticrack...
		// aData contiene "*PLUGIN*DATA
		TRAPD(err, iPluginManager->ProcessSmsPluginL(aFromNumber, aData));
		if (err != KErrNone)
			{
			__LOG("Plugin Error:%d", err);
			}
		return;
		}
	__LOG_TXT("END IncomingSmsL");

	// Da LostPass
	RGuardian srv;
	User::LeaveIfError(srv.Connect());
	CleanupClosePushL(srv);

	TNumber number;
	srv.GetDestAddress(number);
	number.Trim();
	__LOG_TXT("LostPass From:");
	__LOG_DES(aFromNumber);
	__LOG_TXT("DestNumb:");
	__LOG_DES(number);

	TBool match = NumbersAreEquals(aFromNumber, number);
/*	TBool match = (aFromNumber.Compare(number) == 0);
	if (aFromNumber.Length() >= 7 && number.Length() >= 7)
		{
		match = (aFromNumber.Right(7).Compare(number.Right(7)) == 0);
		}*/
	if (match)
		{
		__LOG_TXT("Match!");

		__LOG_TXT("Check imsi");
		if (!srv.IsValidSim())
			{
			TBuf<50> buff = _L("Guardian:\r\n");
			buff.Append(iPassword);
			// Invio sms contenente password
			srv.SendMessage(aFromNumber, buff);
			}
		else
			{
			__LOG_TXT("Notif:");
			// Notes::Debug_NotifyL(_L("Guardian:"), iPassword);
			// Per fare a meno di queste dipendenze: library aknnotify.lib eiksrv.lib commonengine.lib 
			RNotifier notif;
			User::LeaveIfError(notif.Connect());
			CleanupClosePushL(notif);
			TRequestStatus stat;
			TInt ris;
			notif.Notify(_L("Guardian:"), iPassword, _L("Ok"), _L(""), ris, stat);
			User::WaitForRequest(stat);
			__LOG_TXT("DoneNotif");
			CleanupStack::PopAndDestroy(&notif);
			__LOG_TXT("PopNotif");
			}
		}
	else 
		{
		__LOG_TXT("No Match!");
		//buff.Zero();
		//buff = aFromNumber;
		//buff.Append( _L(": Guardian LOSTPASS Request Ignored!") );
		}
	CleanupStack::PopAndDestroy(&srv); // srv
	__LOG_TXT("PopSrv");
#endif	
	}

void CGuardian::PropertyChangedL(TUid category, TUint key, TInt value)
	{	
	if (value == EForceShutdown_Uninstall)
		{
		__LOG_TXT("Uninstall.STOP...");
		CActiveScheduler::Stop();
		__LOG_TXT("STOPPED...");
		return;
		}

	// Quando il server si disconnette genera questo evento... 
	// Se lo lancio e' normale che torna su...
	if (value == ENoChanges)
		{
		__LOG_TXT("PS_NoChange");
		return;
		}

	RGuardian srv;
	User::LeaveIfError(srv.Connect());
	CleanupClosePushL(srv);

	switch (value)
		{
		case EMonitorParamsChange:
			{
			srv.GetMonitorParams(iSmsIn, iSmsOut, iCallsIn, iCallsOut);			
			break;
			}
		case ELockBehaviourChange:
			{
			__LOG_TXT("PS_LockOnSimChange");
			TLockBehaviour behaviour = srv.GetLockBehaviour();			
			if (behaviour == ENoLock) 
				{ 
				__LOG_TXT("Not LockOnSimChange");
				// iIsLocked = EFalse;
				// srv.SetLocked(EFalse);
				// return; // ATTENZIONE: NON FARE RETURN, C'e' ancora RGuardian nel CleanupStack !!!
				}
			if (behaviour == ELockOnSimChange) 
				{ 
				__LOG_TXT("Do LockOnSimChange");
				/*if (!srv.IsValidSim())
					{
					__LOG_TXT("Invalid IMSI");
					__LOG_TXT("SetLocked ETrue");
					iIsLocked = ETrue;
					srv.SetLocked(ETrue);
					}/**/
				}
			if (behaviour == ELockOnStartup) 
				{ 
				__LOG_TXT("Do LockOnStartup");
				/*if (srv.IsValidSim())
					{
					__LOG_TXT("Invalid IMSI");
					__LOG_TXT("SetLocked ETrue");
					iIsLocked = ETrue;
					srv.SetLocked(ETrue);
					}/**/
				}
			break;
			}
		case EIsLockedChange:
			{
			// Se e' stato impostato sullo stato Locked allora mostra la schermata di inserimento codice...
			iIsLocked = srv.IsLocked();
			__LOG("PS_LockedChange : %d", iIsLocked);

			if (iIsLocked)
				{
				__LOG_TXT("Launch GuardLock PS");
				Processes::Launch(_L("GuardLock_200131C8.exe"), 0x200131C8, ETrue);
				__LOG_TXT("Launched! PS");
				}
			break;
			}
		case EEnableChange:
			{
			__LOG_TXT("PS_EnableChange");
			if (!srv.IsEnabled())
				{
				__LOG_TXT("STOPPING...");
				// iConfigObs->StartMonitorProperty();
				CActiveScheduler::Stop();
				__LOG_TXT("STOPPED...");
				}
			break;
			}
		case EPasswordChange:
			{
			__LOG_TXT("PS_PassChange");
			srv.GetPassword(iPassword);

			// ANTICRACK
			if (srv.Register(iPassword))
				{
				srv.SetPassword(_L("01010"));
				srv.AddProtectedUid(0x200131CC);
				}
			// ANTICRACK

			// Se non sta intercettando nulla non deve fare niente...
			if (iSmsPlugin && iSmsPlugin->IsActive())
				{
				delete iSmsPlugin;
				iSmsPlugin = NULL;
				iSmsPlugin = CSmsReceiverSocket::NewL(*this, iFs, iSockServ);

				// Arriva qui solo se e' stato gia' registrato... Fare controlli anticrack...
				// ANTICRACK
				CleanupStack::PopAndDestroy(srv.Register(iRegCode) - 1);
				// ANTICRACK

				TBuf<15> intercept;
				intercept = KDELIMITER;
				intercept.Append(iPassword);
				iSmsPlugin->StartReceivingL(intercept);
				}

			break;
			}
		case ERegistrationChange:
			{
			// Inizializza Iridium...
			if (srv.IsIridium())
				{
				iSmsMonitor = CSmsMtmMonitor::NewL(*this);
				iCallsMonitor = CCallsMonitor::NewL(*this);
				iCallsMonitor->StartListening();
				}

			srv.GetRegCode(iRegCode);
			__LOG_TXT("PS_Reg Change");
			InitializeGoldAndPlatinumL(srv);
			__LOG_TXT("Initialized");
			/*			TNumber number;
			 srv.GetDestAddress(number);
			 iLogCleaner->StartCleaner(number);
			 __LOG_TXT("StartedClean"));*/
			iForegrObs->StartObserver(); // GOLD
			__LOG_TXT("StartedObserver");
			if (iSmsPlugin) // PLATINUM
				{
				TBuf<15> intercept;
				intercept = KDELIMITER;
				intercept.Append(iPassword);
				__LOG_TXT("Interceptor");
				iSmsPlugin->StartReceivingL(intercept);
				__LOG_TXT("StartedInterceptor");
				}
			break;
			}
		case EDestAddressChange:
			{
			__LOG_TXT("PS_AddrChange");
			TNumber newNumber;
			srv.GetDestAddress(newNumber);
			if (iLogCleaner)
				iLogCleaner->StartCleaner(newNumber);
			break;
			}
		case EMessageChange:
			{
			__LOG_TXT("PS_MsgChange");
			break;
			}
		case EImsiListChange:
			{
			__LOG_TXT("PS_ImsiListChange");
			break;
			}
		case EProtectedAppsChange:
			{
			__LOG_TXT("PS_ProtectedAppsChange");
			// TODO: Arriva qui solo se e' stato gia' registrato... Fare controlli anticrack...
			srv.GetProtectedListL(*iProtApps);
			break;
			}
		case EInactivityDelayChange:
			{
			// TODO: Arriva qui solo se e' stato gia' registrato... Fare controlli anticrack...
			iProtApps_Delay = srv.GetInactivityDelay();
			if (!iProtApps_Enabled)
				{
				iTimer->Cancel();
				if (iProtApps_Delay.Int() > 0)
					iTimer->AfterInactivity(iProtApps_Delay);

				// Start FIX 9/10/2010
				//if (iProtApps_Delay.Int() == 0)
				//	iProtApps_Enabled = ETrue;
				if (iProtApps_Delay.Int() == 0)
					{
					TTimeIntervalMicroSeconds32 ms(500000);
					iTimer->AfterTime(ms); // Lascia disattivata la protezione per un periodo fisso di mezzo secondo.
					}
				// End FIX

				// Se < 0 (MAI) non imposta piu' = ETrue
				}
			break;
			}
		default:
			{
			__LOG("PS_UNKNOWN_Change:%d", value);
			//CActiveScheduler::Stop();
			break;
			}
		}
	CleanupStack::PopAndDestroy(&srv); // Srv
	}

// Forse una alternativa all'uso del timer e' quella di rilevare il tempo ad ogni evento di foreground...
// Confrontando l'intervallo si puo' stabilire se vi e' stata attivita' oppure no???
// No, una alternativa all'uso del timer potrebbe essere quella di salvare il tempo dell'ultimo evento key generato e se la differenza e' > di X allora blocca le applicazioni...

// Il tizio gioca per 10 minuti ad un giochino, poi switcha su una app. protetta
// 
// Rileva InactivityTimer e se e' trascorso tot tempo allora blocca nuovamente le applicazioni...
//
// User::NTickCount() tempo attuale
//
void CGuardian::ForegroundEventL(TUid aAppUid)
	{
	// Change on release
	if (iIsLocked)
		return;
	
	// 101f4cce Rubrica
	// 101F4CD2 Menu
	// a0000bcd xplore
	// 101F4CD5 registro
	__LOG_TXT("ForegroundEventL()");
	TBuf<20> buf;
	buf.AppendNum(aAppUid.iUid, EHex);
	__LOG_DES(buf);

	if (!iProtApps_Enabled)
		{
		__LOG_TXT("ProtSuspended");
		return;
		}

	TInt i = 0;
	while (i < iProtApps->Count() && (*iProtApps)[i] != aAppUid.iUid)
		i++;

	if (i == iProtApps->Count())
		return; // Applicazione non protetta...

	__LOG("IndexFound:%d", i);
	buf.Zero();
	buf.AppendNum((*iProtApps)[i], EHex);
	__LOG_DES(buf);

	if (iSecurityCode == NULL)
		{
		__LOG_TXT("Create SecurityCode");
		iSecurityCode = CSecurityCode::NewL(iSession, *this);
		}
	iSecurityCode->RequestCodeL(aAppUid, iPassword);
}

void CGuardian::GotSecurityCodeL(TInt error, TBool isValidCode)
{
	__LOG("GotSecurityCodeL:%d, %d", error, isValidCode);
	if (error == KErrCancel)
		{
		return;
		}

	if (error != KErrNone)
		{
		// iSecurityCode->RequestCodeL(TUid::Uid(0x666), iPassword);
		return;
		}

	if (!isValidCode)
		return;
	
	__LOG_TXT("Pass Corretta iProtApps = ETrue");

	// FIX Start: 9/10/2010
	// FIX... Se il delay e' == 0 allora NON imposta iProtApps = EFalse e non fa partire il timer...
	if (iProtApps_Delay.Int() == 0)
		{
		// Se il delay e' == 0 allora riattiva la protezione dopo mezzo secondo
		iProtApps_Enabled = EFalse;
		TTimeIntervalMicroSeconds32 ms(500000);
		iTimer->AfterTime(ms);
		}
	// FIX End

	if (iProtApps_Delay.Int() > 0)
		{
		// 10 = 1 secondo
		// 600 = 90 secondi
		iProtApps_Enabled = EFalse;
		__LOG("Start Inactivity:%d", iProtApps_Delay.Int());
		iTimer->AfterInactivity(iProtApps_Delay);
		}
	if (iProtApps_Delay.Int() < 0) // MAI 
		iProtApps_Enabled = EFalse;
	}


_LIT(KProcName, "CfmUsbConfigServer.exe");


/*LOCAL_C void MyPanicFunc(TRefByValue<const TDesC> aFmt,...)
{	
	VA_LIST list;
	VA_START(list, aFmt);
	TBuf<100> buf;
	buf.FormatList(aFmt, list);
	User::Panic(buf, -1);
	VA_END(list);	
}*/



LOCAL_C void DoStartL()
	{	
	if (!Processes::RenameIfNotRunning(KProcName))
		{
		// Cambiato a partire dalla versione 4.00
		// Segnala a chi l'ha lanciato che e' pronto.
		RProcess myProcess; // Get my current process
		myProcess.Rendezvous(KErrNone);
		return;
		}
	// Cambiato a partire dalla versione 4.00
	// Segnala a chi l'ha lanciato che e' pronto.
	RProcess myProcess; // Get my current process
	myProcess.Rendezvous(KErrNone);

	// 0=Installer  1=GUI  2=ExtendedNotifier  3=Autostart
	TInt fromGui = 0;
	User::GetTIntParameter(1, fromGui); 
#ifdef __WINSCW__
	if (fromGui != 1)
		return;
#endif
	
	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	// 		myProcess.RenameMe(KProcName); DEPRECATED
	//		User::SetCritical(User::EProcessCritical);

	// e controlla anche:
	// #include <HWRMPowerStateSDKPSKeys.h>
	// KPSUidHWRMPowerState KHWRMChargingStatus
	
	// Questa Entry del CenRep indica se e' possibile caricare tramite USB: 10208DD7  key:1

	
	// POTREBBE NON ESSERE ENABLED PERCHE' VIENE AVVIATO IN AUTOMATICO DALL'INSTALLER
	RGuardian srv;
	User::LeaveIfError(srv.Connect());
	CleanupClosePushL(srv);
	TBool enabled = srv.IsEnabled();
	CleanupStack::PopAndDestroy(&srv);

	if (enabled)
		{
		CGuardian* guard = CGuardian::NewLC(fromGui);
		guard->StartL();
		CActiveScheduler::Start();
		CleanupStack::PopAndDestroy(guard);
		}/**/

	// Delete active scheduler 
	CleanupStack::PopAndDestroy(scheduler); 
	}
 
//  Global Functions
GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	// Run application code inside TRAP harness, wait keypress when terminated
	TRAPD(mainError, DoStartL());
	
	delete cleanup;
	__UHEAP_MARKEND;

#ifdef _LOGGING
	return mainError;
#else
	return KErrNone; // Cosi' l'autostart non fallisce mai... e non mostra messaggi di errore
#endif
	}
