
// Transient server example - client interface implementation

#include "client.h"
#include "clientserver.h"
#include "srverr.h"
//#include "license.h"

#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\utils.h>
#include <FuzzyByte\processes.h>
#include <FuzzyByte\Guardian\settings_consts.h>

#include <badesca.h>
#include <S32MEM.H> 


const TInt KServerDefaultMessageSlots = 1; //Number of message slots available per session.

LOCAL_C TInt CreateServerProcess(RSemaphore& sem)
	{
	__LOG_DECLARATION_MEMBER
	__LOG_OPEN("Guardian", "_CreateServerProcess.txt");
	const TUidType serverUid(KNullUid, KNullUid, KServerUid3);

	RProcess server;
	TInt err = server.Create(KMyServerImg, KNullDesC, serverUid);
	if(err != KErrNone)
		{
		__LOG("Create Err: %d", err);
		__LOG_CLOSE
		return err;
		}

	server.Resume();	
#ifdef __WINSCW__
	sem.Wait();
	err = KErrNone;
#else
	err = sem.Wait(5000000);
#endif
	__LOG("Wait Err: %d", err);				// -33 KErrTimeOut
	TInt res=KErrNone;
	if (server.ExitType()==EExitPanic) 
		res = KErrGeneral;					// res = KErrGeneral
	else
		res = err;
	server.Close();
	__LOG("Res: %d", res);
	__LOG_CLOSE
	return res;
	}
/*
// Sostituito con il semaforo perche' cosi' va bene anche in caso di Processi multipli...
// La chiamata del client alla CreateGlobal fallira', in questo modo non si verranno a creare piu' processi del server...

 	TRequestStatus stat;
	server.Rendezvous(stat);
	if (stat != KRequestPending)
		server.Kill(0);		// abort startup
	else
		server.Resume();	// logon OK - start the server
	User::WaitForRequest(stat);		// wait for start or death
*/
	// we can't use the 'exit reason' if the server panicked as this
	// is the panic 'reason' and may be '0' which cannot be distinguished
	// from KErrNone




LOCAL_C TInt StartServer()
	{
	__LOG_DECLARATION_MEMBER
	__LOG_OPEN("Guardian", "_StartServer.txt");
	// Il FindServer non e' suffic. perche' il nome del server sara' assegnato diverso tempo dopo la creazione del processo... 

	/* QUESTI CONTROLLI DOVREBBERO ESSERE SUPERFLUI PERCHE' IL RENDEZVOUS DOVREBBE GIA' BASTARE...
 	if (Utils::ProcessIsRunningL( KMyServerName ))
		return KErrNone;
	if (Utils::ProcessIsRunningL( KMyServerImg ))
		return KErrNone;*/
	
	TBool exists = Processes::IsRunning(KMyServerName);
	if (exists)
		{
    	__LOG_TXT("IsRunning");
    	__LOG_CLOSE
		return KErrNone;
		}
	
	// Probably the Server is not Running
	RSemaphore sem;
    TInt err = sem.CreateGlobal( KMyServerImg, 0 );
    if ( err != KErrNone )
        {
        // Server is already Running...
    	__LOG("AlreadyRunning: %d", err);
    	__LOG_CLOSE
        return KErrNone;
        }
	// Server not Running		
	err = CreateServerProcess(sem);
	__LOG("CreateServerProcess: %d", err);	// -2 KErrGeneral
	sem.Close();
	__LOG_TXT("Sem.Closed");
	__LOG_CLOSE
	return err;
	
/*	TFindServer find(KMyServerName);
	TFullName name;	
	TInt err = find.Next(name);	// KErrNone if a matching server is found, KErrNotFound otherwise. 
	if (err != KErrNone)
		{
		// Probably the Server is not Running
		RSemaphore sem;
	    err = sem.CreateGlobal( KMyServerImg, 0 );
	    if ( err != KErrNone )
	        {
	        // Server is already Running...
	        return KErrNone;
	        }
		// Server not Running		
		err = CreateServerProcess(sem);
		sem.Close();
		}
	return err;*/
	}


/*
const TInt KServerRetryCount = 3;

static TInt StartServer()
//
// Start the server process. Simultaneous launching
// of two such processes should be detected when the second one attempts to
// create the server object, failing with KErrAlreadyExists.
//
	{
	const TUidType serverUid(KNullUid,KNullUid,KServerUid3);
	RProcess server;
	TInt r=server.Create(KMyServerImg,KNullDesC,serverUid);
	if (r!=KErrNone)
		return r;
	TRequestStatus stat;
	server.Rendezvous(stat);
	if (stat!=KRequestPending)
		server.Kill(0);		// abort startup
	else
		server.Resume();	// logon OK - start the server
	User::WaitForRequest(stat);		// wait for start or death
	// we can't use the 'exit reason' if the server panicked as this
	// is the panic 'reason' and may be '0' which cannot be distinguished
	// from KErrNone
	r=(server.ExitType()==EExitPanic) ? KErrGeneral : stat.Int();
	server.Close();

	return r;
	}

EXPORT_C TInt RGuardian::Connect()
//
// Connect to the server, attempting to start it if necessary
//
	{
#ifndef __SERIES60_3X__
	TInt r=StartThread();
	if (r!=KErrNone)
		return r;
#endif
	TInt retry=KServerRetryCount;
	for (;;)
		{
		TInt r=CreateSession(KMyServerName,TVersion(0,0,0),KServerDefaultMessageSlots);
		if (r!=KErrNotFound && r!=KErrServerTerminated)
			return r;
		if (--retry==0)
			return r;
		r=StartServer();
		if (r!=KErrNone && r!=KErrAlreadyExists)
			return r;
		}
	}
*/

/*EXPORT_C TInt RGuardian::StoreL(const CLicense& aLicense)
	{
//	if (rawLicenseData.Length()>KMaxMyMessage)
//		return KErrArgument;
	HBufC8* buff = aLicense.BufferLC();
    TInt ris = SendReceive(EStoreLicense,  TIpcArgs(&buff));
	CleanupStack::PopAndDestroy(); // buff;
	return ris;
	}*/


EXPORT_C TBool RGuardian::IsEnabled()
	{
    TBool exists=EFalse;
    TPckgBuf<TBool> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EIsEnabled, args);
    exists = pckg();
    return exists;
	}


EXPORT_C TInt RGuardian::SetMonitorParams(TBool smsIn, TBool smsOut, TBool callIn, TBool callOut)
	{
    TPckgBuf<TBool> pckgSmsIn(smsIn);  // Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgSmsOut(smsOut);  // Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgCallIn(callIn);  // Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgCallOut(callOut);  // Questo e' di tipo TDes8
    TIpcArgs args(&pckgSmsIn, &pckgSmsOut, &pckgCallIn, &pckgCallOut);    
	return SendReceive(ESetMonitorParams, args);
	}


EXPORT_C void RGuardian::GetMonitorParams(TBool& smsIn, TBool& smsOut, TBool& callIn, TBool& callOut)
	{
    TPckgBuf<TBool> pckgSmsIn;  // Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgSmsOut;  // Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgCallIn;  // Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgCallOut;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckgSmsIn, &pckgSmsOut, &pckgCallIn, &pckgCallOut);
    SendReceive(EGetMonitorParams, args);
    smsIn = pckgSmsIn();
    smsOut = pckgSmsOut();
    callIn = pckgCallIn();
    callOut = pckgCallOut();
	}


EXPORT_C TBool RGuardian::IsLocked()
	{
    TBool exists=EFalse;
    TPckgBuf<TBool> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EIsLocked, args);
    exists = pckg();
    return exists;
	}

EXPORT_C TBool RGuardian::IsIridium()
	{	
    TBool exists=EFalse;
    TPckgBuf<TBool> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EIsIridium, args);
    exists = pckg();
    return exists;
	}


EXPORT_C TInt RGuardian::SetLockDelay(TUint32 aDelay)
	{
    TPckgBuf<TUint32> pckg(aDelay);
    TIpcArgs args(&pckg);
    return SendReceive(ESetLockDelay, args);
	}


EXPORT_C TUint32 RGuardian::GetLockDelay()
	{
	TUint32 delay=0;
    TPckgBuf<TUint32> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EGetLockDelay, args);
    delay = pckg();
    return delay;
	}


EXPORT_C TLockBehaviour RGuardian::GetLockBehaviour()
	{	
	TLockBehaviour behaviour=ENoLock;
    TPckgBuf<TUint32> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EGetLockBehaviour, args);
    behaviour = (TLockBehaviour) pckg();
    return behaviour;
	}


EXPORT_C TInt RGuardian::Connect()
	{
	__LOG_DECLARATION_MEMBER 
	__LOG_OPEN_ID("Guardian","_Connect.txt");
	TInt i=0;
	TInt errno;
	do {
		errno = StartServer();
		if (errno != KErrNone)
			{ 
			__LOG("Err: %d Count: %d", errno, i);
			}
		i++;
	} while (errno != KErrNone && i < 5);
	__LOG("errno: %d", errno);
	if(errno == KErrNone)
		{
		errno = CreateSession(KMyServerName,
			TVersion(KServMajorVersionNumber,KServMinorVersionNumber,KServBuildVersionNumber),
			KServerDefaultMessageSlots);
		__LOG("CreateSession: %d", errno);
		}
	__LOG_CLOSE
	return errno;
	}



/*EXPORT_C TBool RGuardian::GetInterceptAlways()
	{
    TBool exists=EFalse;
    TPckgBuf<TBool> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EGetInterceptAlways, args);
    exists = pckg();
    return exists;
	}*/


EXPORT_C TUint32 RGuardian::GetBrandId() 
	{
    TUint32 delay = 0;
	TPckgBuf<TUint32> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EBrandId, args);
    delay = pckg();
    return delay;	
	}

EXPORT_C TInt RGuardian::GetInactivityDelay()
	{
    TInt delay = 0;
	TPckgBuf<TInt> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EGetInactivityDelay, args);
    delay = pckg();
    return delay;
	}


EXPORT_C TInt RGuardian::Register(const TDesC& regCode)
	{
    TInt regged=0;
    TPckgBuf<TInt> pckg;
    TIpcArgs args(&pckg, &regCode);
    SendReceive(ERegister, args); // restituisce KErrSame value nel caso in cui si tenti di chiamare la routine di registrazione per 2 volte con il codice corretto...
    regged = pckg();
	return regged;
	}


// Il buffer di ricezione deve essere abbastanza grande da contenere i dati...
EXPORT_C TInt RGuardian::GetPassword(TDes& pass)
	{
//	RDebug::Print(_L("### Log %d %08x"), 5, 0xABCDEF12);
    TIpcArgs args(&pass);
    return SendReceive(EPassword, args);
// KErrNone, if the send operation is successful; KErrServerTerminated, if the server no longer present; KErrServerBusy, if there are no message slots available; KErrNoMemory, if there is insufficient memory available.
// ??? Restituire messaggi di errore differenti??? Licenza non trovata / non valida / ecc...
//	return KErrNone;
	}


// Il buffer di ricezione deve essere abbastanza grande da contenere i dati...
EXPORT_C TInt RGuardian::GetDestAddress(TDes& dest)
	{
    TIpcArgs args(&dest);
    return SendReceive(EDestAddress, args);
	}


EXPORT_C TInt RGuardian::GetRegCode(TDes& dest)
	{
    TIpcArgs args(&dest);
    return SendReceive(EGetRegCode, args);
	}


EXPORT_C TBool RGuardian::IsLargeIconsGUI()
	{
    TBool large=EFalse;
    TPckgBuf<TBool> pckg;  // Questo e' di tipo TDes8
    TIpcArgs args(&pckg);
    SendReceive(EIsLargeIconsGUI, args);
    large = pckg();
    return large;
	}

EXPORT_C TInt RGuardian::SendMessage(const TDesC& dest, const TDesC& msg, TBool split)
	{
	TPckgBuf<TBool> pckg(split);
    TIpcArgs args(&dest, &msg, &pckg);
    return SendReceive(ESendMessage, args);
	}


EXPORT_C TInt RGuardian::SetPassword(const TDesC& pass)
	{
    TIpcArgs args(&pass);
    return SendReceive(ESetPassword, args);
	}


EXPORT_C TInt RGuardian::SetLargeIconsGUI(TBool large)
	{
    TPckgBuf<TBool> pckg(large);
    TIpcArgs args(&pckg);
    return SendReceive(ESetLargeIconsGUI, args);
	}


EXPORT_C TInt RGuardian::SetEnabled(TBool enabled)
	{
    TPckgBuf<TBool> pckg(enabled);
    TIpcArgs args(&pckg);
    return SendReceive(ESetEnabled, args);
	}

EXPORT_C TInt RGuardian::SetLocked(TBool locked)
	{
    TPckgBuf<TBool> pckg(locked);
    TIpcArgs args(&pckg);
    return SendReceive(ESetLocked, args);
	}

EXPORT_C TInt RGuardian::SetLockBehaviour(TLockBehaviour locked)
	{
    TPckgBuf<TUint32> pckg(locked);
    TIpcArgs args(&pckg);
    return SendReceive(ESetLockBehaviour, args);	
	}

EXPORT_C TInt RGuardian::GetImei(TDes& imei)
	{
    TIpcArgs args(&imei);
    return SendReceive(EGetImei, args);	
	}

// Il buffer di ricezione deve essere abbastanza grande da contenere i dati...
EXPORT_C TInt RGuardian::GetMessage(TDes& msg)
	{
    TIpcArgs args(&msg);
    return SendReceive(EMessage, args);
	}


EXPORT_C TInt RGuardian::GetVersion(TDes& msg)
	{
    TIpcArgs args(&msg);
    return SendReceive(EGetVersion, args);
	}


EXPORT_C TBool RGuardian::IsValidSim()
	{
    TBool valid=EFalse;
    TPckgBuf<TBool> pckg;
    TIpcArgs args(&pckg);
    SendReceive(EIsValidImsi, args);
    valid = pckg();
    return valid;
	}



/*EXPORT_C TInt RGuardian::SetInterceptAlways(TBool interc)
	{
    TPckgBuf<TBool> pckg(interc);
    TIpcArgs args(&pckg);
    return SendReceive(ESetInterceptAlways, args);
	}*/


EXPORT_C TInt RGuardian::SetInactivityDelay(TInt delay)
	{
    TPckgBuf<TInt> pckg(delay);
    TIpcArgs args(&pckg);
    return SendReceive(ESetInactivityDelay, args);
	}


EXPORT_C TInt RGuardian::SetDestAddress(const TDesC& dest)
	{
    TIpcArgs args(&dest);
    return SendReceive(ESetDestAddress, args);
	}

EXPORT_C TInt RGuardian::RegisterSim(TDes& name)
	{
    TIpcArgs args(&name);
    return SendReceive(ERegisterImsi, args);
	}


EXPORT_C TInt RGuardian::RenameSim(const TDesC& oldName, const TDesC& newName)
	{
    TIpcArgs args(&oldName, &newName);
    return SendReceive(ERenameImsi, args);
	}


EXPORT_C TInt RGuardian::UnRegisterSim(const TDesC& simName)
	{
    TIpcArgs args(&simName);
    return SendReceive(EUnRegisterImsi, args);
	}


EXPORT_C TInt RGuardian::AddProtectedUid(const TInt32& uid)
	{
	TPckgBuf<TInt32> pckg(uid);
    TIpcArgs args(&pckg);
    return SendReceive(EAddProtectedUid, args);
	}


EXPORT_C TInt RGuardian::SetMessage(const TDesC& message)
	{
    TIpcArgs args(&message);
    return SendReceive(ESetMessage, args);
	}



EXPORT_C TInt RGuardian::RemProtectedUid(const TInt32& uid)
	{
	TPckgBuf<TInt32> pckg(uid);
    TIpcArgs args(&pckg);
    return SendReceive(ERemProtectedUid, args);
	}


EXPORT_C TInt RGuardian::GetProtectedListL(RArray<TInt32>& uidList)
	{
    TInt totQty=0;
    TPckgBuf<TInt> pckg;
	HBufC8* buffer = HBufC8::NewLC( 4 * 10 ); // Legge 10 uid alla volta
	TPtr8 ptr = buffer->Des();
	TIpcArgs args(&ptr, &pckg);

	uidList.Reset();
	TInt ris = 0;
	do {
		ptr.Zero();
		ris = SendReceive(EGetProtectedList, args);
		if (ris != KErrNone && ris != KErrCompletion)
		{
			CleanupStack::PopAndDestroy(buffer);	// buffer
			return ris;
		}
		totQty = pckg();	// Quantita' di uid prelevati...
		const TUint8* memPtr = ptr.Ptr();
		for (TInt i=0; i<totQty; i++)
		{
			TInt32* uid = (TInt32*) memPtr;
			uidList.AppendL(*uid);
			memPtr += 4;
		}
	} while (ris != KErrCompletion);

	CleanupStack::PopAndDestroy(buffer);

	return KErrNone;
	}


EXPORT_C TInt RGuardian::GetAuthorizedListL(RArray<TImsiName>& nameList, RArray<TOperName>& operList)
	{
    TInt totQty=0;
    TPckgBuf<TInt> pckg;
	HBufC* buffer = HBufC::NewLC( 3 * (KNAME_LEN + KOPER_LEN) ); // Legge un minimo di 3 sim alla volta
	TPtr ptr = buffer->Des();
	TIpcArgs args(&ptr, &pckg);

	nameList.Reset();
	operList.Reset();
	TInt ris = 0;

	do {
		ptr.Zero();
		ris = SendReceive(EGetImsiList, args);
		if (ris != KErrNone && ris != KErrCompletion)
		{
			CleanupStack::PopAndDestroy(buffer);	// buffer
			return ris;
		}
		totQty = pckg();	// Quantita' di sim prelevate...

		TInt tabPos = -1;
		TPtrC s = buffer->Des();
		for (TInt i=0; i<totQty; i++)
		{
			// NOME...
			s.Set( s.Mid(tabPos + 1) );
			tabPos = s.Locate( TChar('\t') );
			TPtrC name(s.Left(tabPos));

			// OPERATORE...
			s.Set( s.Mid(tabPos + 1) );
			tabPos = s.Locate( TChar('\t') );
			TPtrC oper(s.Left(tabPos));

			nameList.AppendL(name);
			operList.AppendL(oper);

			tabPos = s.Locate( TChar('\t') );
		}
	} while (ris != KErrCompletion);

	CleanupStack::PopAndDestroy(buffer);	// buffer
	return KErrNone;
	}


/*EXPORT_C TInt RGuardian::GetAuthorizedListL(RArray<TImsiName>& nameList, RArray<TOperName>& operList)
	{
    TInt totQty=0;
    TPckgBuf<TInt> pckg;
	RBuf buffer;
	buffer.CleanupClosePushL();
	buffer.CreateL(3 * (KNAME_LEN + KOPER_LEN) ); // Legge un minimo di 3 sim alla volta
	TIpcArgs args(&buffer, &pckg);

	nameList.Reset();
	operList.Reset();
	TInt ris = 0;

	RFileLogger f;
	f.Connect();
	f.CreateLog(_L("Guardian"), _L("test.txt"), EFileLoggingModeAppend);
	f.SetDateAndTime(ETrue, ETrue);
	CleanupClosePushL(f);

	do {
		buffer.Zero();
		f.WriteFormat(_L("SendReceive:%d"), 0);
		ris = SendReceive(EGetImsiList, args);
		f.WriteFormat(_L("SendReceive:%d"), ris);
		if (ris != KErrNone && ris != KErrCompletion)
		{
			CleanupStack::PopAndDestroy();	// buffer
			return ris;
		}
		totQty = pckg();	// Quantita' di sim prelevate...
		f.WriteFormat(_L("qty:%d"), totQty);

		RDesReadStream strm(buffer);
		CleanupClosePushL(strm);
		TInt strmSize = strm.Source()->SizeL();
		f.WriteFormat(_L("StreamSize:%d"), strmSize);

		for (TInt i=0; i<totQty; i++)
		{
			f.WriteFormat(_L("DoName:%d"), i);
			// NOME...
			TBuf<KNAME_LEN+2> name;
			strm.ReadL(name, TChar('\t'));

			f.WriteFormat(_L("DoSetLen:%d"), i);
			name.SetLength(name.Length()-1);
			f.Write(name);
			nameList.AppendL(name);

			f.WriteFormat(_L("DoOper:%d"), i);
			// OPER...
			TBuf<KOPER_LEN+2> oper;
			strm.ReadL(oper, TChar('\t'));

			f.WriteFormat(_L("DoSetLen:%d"), i);
			oper.SetLength(oper.Length()-1);
			f.Write(oper);
			operList.AppendL(oper);

			f.WriteFormat(_L("Done:%d"), i);
		}
		CleanupStack::PopAndDestroy();	// strm
	} while (ris != KErrCompletion);

	CleanupStack::PopAndDestroy(&f);
	CleanupStack::PopAndDestroy();	// buffer
	return KErrNone;
	}*/


EXPORT_C TInt RGuardian::ClearOutBox()
	{
	return SendReceive(EClearOutBox);
	}


/*EXPORT_C void RGuardian::CancelNotifyConfigChange()
	{
	SendReceive(ECancelNotifyConfigChange);
	}*/


EXPORT_C void RGuardian::Uninstall()
	{
    SendReceive(EUninstall);
	}


/*EXPORT_C void RGuardian::NotifyConfigChange(TRequestStatus& aStatus, TDes8& aChangePckg)
	{
// Vedi gestione asincrona...
	SendReceive(ENotifyConfigChange, TIpcArgs(&aChangePckg), aStatus);
	}*/



/*#ifndef __SERIES60_3X__
	GLDEF_C TInt E32Dll(TDllReason )
	// DLL entry point
	{
	return(KErrNone);
	}
#endif*/

