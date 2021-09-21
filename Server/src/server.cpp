#include "server.h"
#include "session.h"
#include "srverr.h"

#include <FuzzyByte\utils.h>
#include <FuzzyByte\Processes.h>
#include <FuzzyByte\FileUtils.h>

#include <e32des8.h>
#include <f32file.h>
#include <COEMAIN.H>
#include <e32property.h>


const TTimeIntervalSeconds KMyShutdownDelaySec(5);

//enum {KMyShutdownDelay=0x2000000};	// approx 20s
/*inline CShutdown::CShutdown()
	:CTimer(-1)
	{CActiveScheduler::Add(this);}
inline void CShutdown::ConstructL()  
	{CTimer::ConstructL();}
inline void CShutdown::Start()
	{After(KMyShutdownDelay);}

void CShutdown::RunL()
//
// Initiate server exit when the timer expires
//
	{
	CActiveScheduler::Stop();
	}*/


CMyServer* CMyServer::NewLC()
	{
	CMyServer* server = new(ELeave) CMyServer(EPriorityNormal);
	CleanupStack::PushL(server);
	server->ConstructL();
	return server;
	}

CMyServer::CMyServer(TInt aPriority) : CServer2(aPriority)
	{
	}

void CMyServer::TimerExpiredL(TAny* src)
	{
	// Rinomina il processo prima di terminarlo perche' puo' accadere che il processo morto resti ancora visibile nella lista dei processi.
	// (Almeno questo accade nell'emulatore)
	RProcess::RenameMe(_L("GfxLayerSrv"));
	CActiveScheduler::Stop();
	}


TUint32 CMyServer::LoadBrandTxtL()
	{
	TFileName brandFile = KBrandFile();
	FileUtils::CompleteWithPrivatePathL( iFs, brandFile );
	RFileReadStream strm;
	strm.PushL();
	TUint32 val = 0;
	TInt err = strm.Open( iFs, brandFile, EFileShareReadersOrWriters|EFileRead);
	if (err == KErrNone)
		{
		val = strm.ReadUint32L();
		val = val ^ 0xAB;
		
		if (val > 0)
			{
			if (val % 3 != 0)
				val = 0;
			if (val % 2 == 0)
				val = 0;
			if (val % 5 == 0)
				val = 0;
			// 3 9 21 27
			// TODO: Set fake flag...
			}
		}
	strm.Pop();
	strm.Close();
	return val;
	}


void CMyServer::ConstructL()
	{
	__LOG_OPEN("Guardian", "Server.txt");
	TInt err = Start(KMyServerName);
	__LOG_DES(KMyServerName);
	if (err != KErrNone)
		{
		__LOG("ERRORE STARTL SERVER : %d", err);
		User::Leave(err);
		}
	
	/*	TInt err = KErrNone;
		TInt i=0;
		do {
			TRAP(err, StartL(KMyServerName));
			if (err > 0)
				{
				__LOG("Err: %d Count: %d", err, i);
				}
			i++;
		} while (err != KErrNone && i < 5);
		
		if (err != KErrNone)
			{
			__LOG("ERRORE STARTL SERVER : %d", err);
			User::Leave(err);
			}*/

	
	//RProcess::RenameMe(KMyServerName);
	//TInt err= RProcess::RenameMe(KMyServerName); 
	//__FLOG_1(_L("err:%d"), err);

//	TUint32 sid = User::CreatorSecureId().iId; 
	iPhone = CPhone::NewL();
	TInt FIVE = 5;
	TUint32 sid = RProcess().SecureId().iId ^ 0x3660;
	// > 200131CB
	__LOG("SID:%d", sid);

	iUninstall = EFalse;
	
	iShutdown = CTimeOutTimer::NewL(*this);
	iShutdown->AfterTime(KMyShutdownDelaySec);

	User::LeaveIfError( iFs.Connect() );
	TFileName fname = KNewConfigFile();
	FileUtils::CompleteWithPrivatePathL(iFs, fname);
	iConfigFile.Create( fname );
// ANTICRACK //
	TInt punti = iConfigFile[1];
// ANTICRACK //

	iSettings = CSettings::NewL(iFs);
	//iSettings = CSettingsOld::NewL();
	
// ANTICRACK 
	__LOG("Punti:%d", punti);
	if (punti == 0)				// Dummy, just for confusing the cracker
		User::Leave(punti);
	// punti = 58
	punti ^= 49;
// ANTICRACK //

	// ANTICRACK //
	punti += (sid % FIVE);
	// ANTICRACK //

	TFileName outBoxPath;
	TInt fake8 = 0x60;
	iPhone->GetImei( iSettings->imeiOnMemory );
	
// ANTICRACK //
	if (iSettings->imeiOnMemory == KMyServerImg)
		{
		// QUESTO CODICE NON DOVREBBE ESSERE MAI ESEGUITO
		RProcess::RenameMe(KMyServerName);
		fake8 = FIVE;
		} else 
		{
		User::LeaveIfError( iSocketServ.Connect() );
		iImei = iSettings->imeiOnMemory;
		fake8 = 2;
		}
// ANTICRACK //
	
	outBoxPath = KOutBoxDir();
	FileUtils::CompleteWithPrivatePathL(iFs, outBoxPath);
	
// ANTICRACK //
	__LOG("Punti2:%d", punti); // 11
	outBoxPath[ punti ] = punti ^ 57;
	punti ^= 11;
// ANTICRACK //

	iSmsSender = CSmsSenderSocket::NewL(iSocketServ, iFs, this, outBoxPath);
	iMsgToSend = EFalse;
	

	iHasChanged = EFalse;
	TInt ris = KErrNone; 
	{
		TEntry entry;
		TFileName oldConfigFile = _L("guardian.dat");
		FileUtils::CompleteWithPrivatePathL(iFs, oldConfigFile); 
		ris = iFs.Entry(oldConfigFile, entry);
		if (ris == KErrNone)
			{
			ris = iSettings->ImportDictionary(KServerUid3, oldConfigFile, iConfigFile, KSETTINGS_VERSION);
			iFs.Delete( oldConfigFile );
			iHasChanged = ETrue;
			} else
			{ 
			ris = iSettings->Load(iConfigFile, KSETTINGS_VERSION);
			}
	}
	
	/*TInt ris = KErrNone;
	TRAPD(error, ris = 	LoadSettingsL() );		
	__LOG("ris: %d", ris);/**/
	
	__LOG("f6: %d", iSettings->fakeRegistration6);
	__LOG("f7: %d", iSettings->fakeRegistration7);
	__LOG("f8: %d", iSettings->fakeRegistration8);	// 2
	__LOG("f: %d", iSettings->fakeRegistration);	// 1
	__LOG("f2: %d", iSettings->fakeRegistration2);
	__LOG("f5: %d", iSettings->fakeRegistration5);
	__LOG("f4: %d", iSettings->fakeRegistration4);
	__LOG("f3: %d", iSettings->fakeRegistration3);
	__LOG("f9: %d", iSettings->fakeRegistration9);
	__LOG("cF: %d", iSettings->countFail);			// 3
	__LOG("iI: %d", iSettings->isIridium);
	__LOG("fI: %d", iSettings->fakeIridium);
	
// ANTICRACK //
	iSettings->fakeRegistration8 = fake8;
	punti += iSettings->fakeRegistration7;
	__LOG("Punti3:%d", punti);
	CleanupStack::PopAndDestroy(punti);
// ANTICRACK //

	if (ris != KErrNone)
		// Il file di configurazione ha un formato non valido
		// Oppure il file di configurazione non esiste...
		{
		__LOG_TXT("!!Reset Settings!!");
		
//		TBuf<20> buf;
//		buf.AppendNum(sid, EHex);
//		__FLOG(buf);

		iSettings->key = sid;
		__LOG("key1:%d", iSettings->key);
		iSettings->fakeRegistration8 = fake8;

		// Read the brand.txt file
		TRAPD(errBrand, iSettings->brandId = LoadBrandTxtL() );
		__LOG("BrandId:%d", iSettings->brandId);
		__LOG("ErrBrand:%d", errBrand);

		// ANTICRACK //
		iSettings->fakeRegistration5 = iSettings->IsValidRegCodeL();
		__LOG("F5:%d", iSettings->fakeRegistration5);
		// ANTICRACK //

		iHasChanged = ETrue;
		TRAPD(err, SaveSettingsL());
		}

	static _LIT_SECURITY_POLICY_PASS(KAllowAllPolicy);
	ris = RProperty::Define(KPSChangeConfig, RProperty::EInt, KAllowAllPolicy, KAllowAllPolicy);
	__LOG("PS_Define:%d", ris);
	}



TInt CMyServer::LoadSettingsL()
	{
	return KErrNone;
/*	__LOG_TXT("LoadSettingsL");
	iHasChanged = EFalse;
	TEntry entry;

	TInt ris = iFs.Entry(iConfigFile, entry);
	if (ris != KErrNone)
	{
		__LOG_TXT("Default");
		iSettings->Default();
		return ris;
	}

	CDictionaryStore* dictstore = CDictionaryFileStore::OpenLC (iFs, iConfigFile, KServerUid3 );

	RDictionaryReadStream in;
	in.OpenLC(*dictstore, KServerUid3);

	in >> *(iSettings);

	in.Close();
	CleanupStack::PopAndDestroy(2); // in dictstore
	__LOG_TXT("End LoadSettingsL");
	return ris;/**/
	}



void CMyServer::SaveSettingsL()
	{
	if (!iHasChanged) return;
	__LOG_TXT("SaveSettingsL");
	__LOG("F5:%d", iSettings->fakeRegistration5);
	iSettings->SaveL();
	iHasChanged = EFalse;
	__LOG_TXT("End SaveSettingsL");/**/
	}
/*


void CMyServer::SaveSettingsL()
	{
	if (!iHasChanged) return;
	__LOG_TXT("SaveSettingsL");
	__LOG("F5:%d", iSettings->fakeRegistration5);
	iFs.Delete( iConfigFile );
	iFs.MkDirAll( iConfigFile );
	CDictionaryStore* dictstore = CDictionaryFileStore::OpenLC (iFs, iConfigFile, KServerUid3 );

	RDictionaryWriteStream out;
	out.AssignLC(*dictstore, KServerUid3);

	out << *(iSettings);

	out.CommitL();            // Commit changes to the stream
	dictstore->CommitL();

	out.Close();
	CleanupStack::PopAndDestroy(2); // out dictstore
	iHasChanged = EFalse;
	__LOG_TXT("End SaveSettingsL");
	}
*/

void CMyServer::SmsSentL()
	{
	__LOG_TXT("SmsSent");
	}


void CMyServer::AllSmsWereSentL()
	{
	__LOG_TXT("AllSmsSent");
	iMsgToSend = EFalse;
    if (iSessionCount <= 0 && !iShutdown->IsActive())
    	iShutdown->AfterTime(KMyShutdownDelaySec);
    }


CSession2* CMyServer::NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const
//
// Cretae a new client session. This should really check the version number.
//
	{
//	__LOG_TXT("NewSessionL"));
	// Check we're the right version
	if (!User::QueryVersionSupported(TVersion(KServMajorVersionNumber,
                                              KServMinorVersionNumber,
                                              KServBuildVersionNumber), aVersion))
        {
    //	__LOG_TXT("Version NOT Supported"));
		User::Leave(KErrNotSupported);
        }

	return new(ELeave) CMySession();
	}


void CMyServer::AddSession()
	{
    iSessionCount++; // se PosE = 9 tutto ok!
	__LOG("AddSession: %d", iSessionCount);
	// ANTICRACK
	iSettings->fakeRegistration6 |= (iConfigFile.LocateReverse(TChar('e')) % 3);
	__LOG("Fake6:%d", iSettings->fakeRegistration6);
	// ANTICRACK
	
	iShutdown->Cancel();
	// ANTICRACK //
	__LOG("Fake2:%d", iSettings->fakeRegistration2);
	iSmsSender += iSettings->fakeRegistration2;
	// ANTICRACK //
	}


void CMyServer::DropSession()
	{
	__LOG("DropSession: %d", iSessionCount);
	TRAPD(err, SaveSettingsL());
    iSessionCount--;
    if (iSessionCount <= 0 && iMsgToSend == EFalse && !iShutdown->IsActive())
    	iShutdown->AfterTime(KMyShutdownDelaySec);
	if (iSessionCount <= 0 && iUninstall)
		TimerExpiredL(NULL);
	}



// *****************************************
// INVIO DI SMS

TInt CMyServer::SendMessageL(const TDesC& aNumber, const TDesC& aMessage, TBool split)
	{
	__LOG_TXT("SendMessage");
	iMsgToSend = ETrue;
	// ANTICRACK... se iImei non e' impostato non invia nulla
	if (iImei.Length() <= 0)
		return KErrMessageNotSet;
	// ANTICRACK
	iSmsSender += iSettings->fakeIridium;
	// ANTICRACK
	if (aMessage.Length() <= 0)
		return KErrMessageNotSet;
	return iSmsSender->ScheduleSendingSmsL(aNumber, aMessage, split);
	}


void CMyServer::ClearOutBox()
	{
	__LOG_TXT("ClearOutBox");
	iSmsSender->ClearOutBox();
	}

	// *****************************************
	// PARAMETRI DI CONFIGURAZIONE

/*void CPubSubAppUi::SetPropertyValueL()
  {
  RProperty myName;
  CleanupClosePushL(myName);

  // attach to the  property
  TInt r=myName.Attach(KMyPropertyCat,KMyPropertyName,EOwnerThread);
  User::LeaveIfError(r);

  // publish a new name value
  TFileName myFile;
  myFile = RProcess().FileName();
  User::LeaveIfError(RProperty::Set(KMyPropertyCat,KMyPropertyName,myFile));
  CleanupStack::PopAndDestroy(&myName);
  }*/

// Notifica l'avvenuto cambiamento della configurazione a tutti quanti i Client che sono in attesa di cambiamenti...
void CMyServer::NotifyChange(TAny* aSource, const TConfigChangeEvent aChangeCode)
	{
	// C:\privatE\ => posizione 9
	// ANTICRACK
	// Cracked...   privatE\20..  // private/E0..
	// ANTICRACK
	__LOG("Fake6:%d", iSettings->fakeRegistration6);
	__LOG("PS_Set:%d", aChangeCode);
	TInt value = static_cast<TInt>(aChangeCode + iSettings->fakeRegistration6);
	TInt ris = RProperty::Set(KServerUid3, KPSChangeConfig, value);
	if (aChangeCode == EForceShutdown_Uninstall)
	{
		iUninstall = ETrue;
	}
	ris = 0;
	iHasChanged = ETrue;
	}



CMyServer::~CMyServer()
	{
	__LOG("Destructor:%d", iSessionCount );
	TInt ris = RProperty::Delete(KPSChangeConfig); // Quando fa il delete viene segnalato il cambio ai Subscriber... Ai quali viene riportato il valore 0
	__LOG("PS_Delete:%d", ris);	ris = 0;
	if (iSettings)
		delete iSettings;
	if (iSmsSender)
		delete iSmsSender;
	if (iPhone)
		delete iPhone;
	iSocketServ.Close();
	iConfigFile.Close();
	iFs.Close();
	__LOG("EndDestructor:%d", iSessionCount );
	__LOG_CLOSE;
	}


/*static void RunServerL()
//
// Perform all server initialisation, in particular creation of the
// scheduler and server and then run the scheduler
//
	{
	// naming the server thread after the server helps to debug panics
#ifndef __SERIES60_3X__
	RThread trd = RThread();
	User::LeaveIfError(trd.Rename(KMyServerName));
#else
	User::LeaveIfError(RThread::RenameMe(KMyServerName));
#endif
	//
	// create and install the active scheduler we need
	CActiveScheduler* s=new(ELeave) CActiveScheduler;
	CleanupStack::PushL(s);
	CActiveScheduler::Install(s);
	//
	// create the server (leave it on the cleanup stack)
	CMyServer::NewLC();
	//
	// Initialisation complete, now signal the client
	RProcess::Rendezvous(KErrNone);
	//
	// Ready to run
	CActiveScheduler::Start();
	//
	// Cleanup the server and scheduler
	CleanupStack::PopAndDestroy(2);
	}


TInt E32Main()
//
// Server process entry-point
//
	{
	__UHEAP_MARK;
	//
	CTrapCleanup* cleanup=CTrapCleanup::New();
	TInt r=KErrNoMemory;
	if (cleanup)
		{
		TRAP(r,RunServerL());
		delete cleanup;
		}
	//
	__UHEAP_MARKEND;
	return r;
	}*/


TInt E32Main()
	{
	return CMyServer::EntryPoint(NULL);
	}

TInt CMyServer::EntryPoint(TAny* /*aNone*/)
	{
	CTrapCleanup* cleanupStack = CTrapCleanup::New();
	if(!cleanupStack)
		{
		User::Panic(KMyServerName, ECreateTrapCleanup);
		}

	TRAPD(leave, ThreadMainL());
	if(leave)
		{
		TBuf<30> buf = _L("appregserver");
		buf.AppendNum(leave);
		User::Panic(buf, ESrvCreateServer);
		}

	delete cleanupStack;
	cleanupStack = NULL;

	return KErrNone;
	}


void CMyServer::ThreadMainL()
	{
	// Puo' essere richiamato appena il server e' stato distrutto... ed il sistema non ha ancora rimosso il Server dall'elenco dei server disponibili.
	// In questo caso la StartL() presente dentro la CMyServer::ConstructL() fallira' con KErrAlreadyExists.
	
	__LOG_DECLARATION_MEMBER
	__LOG_OPEN("Guardian","_ThreadMainL.txt");

	if (!Processes::RenameIfNotRunning( KMyServerName ))
		{
		__LOG_TXT("Unexpected situation");
		// non dovrebbe mai accadere perche' il client non dovrebbe lanciarlo se c'e' gia' un server in esecuzione...
	    RSemaphore semaphore;
	    TInt err = semaphore.OpenGlobal( KMyServerImg );
		__LOG("Err: %d", err);
	    User::LeaveIfError( err );
	    semaphore.Signal();
	    semaphore.Close(); 
		__LOG_TXT("Closing Log");
		__LOG_CLOSE;
		return;
		}
	CActiveScheduler* activeScheduler = new(ELeave) CActiveScheduler();
	CleanupStack::PushL(activeScheduler);

	CActiveScheduler::Install(activeScheduler);

	__LOG_TXT("Create srv");
	CMyServer* srv = CMyServer::NewLC();	// -11 KErrAlreadyExists
	//
	// Initialisation complete, now signal the client
//	RProcess::Rendezvous(KErrNone);
// Sostituito con il semaforo perche' cosi' va bene anche in caso di Processi multipli...
// La chiamata del client alla CreateGlobal fallira', in questo modo non si verranno a creare piu' processi del server...
    RSemaphore semaphore;
	__LOG_TXT("OpenGlobal");
    TInt err = semaphore.OpenGlobal( KMyServerImg );
	__LOG("Err: %d", err);
    User::LeaveIfError( err ); 
    semaphore.Signal();
    semaphore.Close();
	__LOG_TXT("Closing Log");
	__LOG_CLOSE;

	CActiveScheduler::Start();

	CleanupStack::PopAndDestroy(srv);
	CleanupStack::PopAndDestroy(activeScheduler);
	}
