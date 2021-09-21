// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
//

///////////////////////////////////////////////////////////////////////
//
// EXAMPLE RECOGNIZER 
// ------------------
//  This example code demonstrates how to write a simple data recognizer.
//
////////////////////////////////////////////////////////////////////////


#include <eikenv.h>
#include <ImplementationProxy.h> 

// User include
#include "guardauto.h"
#include "logging.h"
#include "client.h"

const TUid KExampleDllUid = {0x200107AD};
const TInt KImplementationUid = 0x200107B3;


/*
Constructor - sets the number of supported mime types, 
the recognizer's priority and its UID.
*/
CGuardAuto::CGuardAuto():CApaDataRecognizerType(KExampleDllUid, CApaDataRecognizerType::EHigh)
	{
    iCountDataTypes = 1;
	}


_LIT(KSysStartProcessMatch, "SysStart*");

void CGuardAuto::ConstructL()
	{
	iMonitor = new (ELeave) CProcMonitor(*this);
	iMonitor->ConstructL(KSysStartProcessMatch);
	}


const TUid KGuardianUid3={0x200131CB};
_LIT(KGuardianImage, "Guardian_200131CB");

void CGuardAuto::NotifyProcTerminated(const TDesC& procName)
	{
	__FLOG_DECLARATION_MEMBER;
	__FLOG_OPEN("Guardian", "AutoStart.txt");
	__FLOG(_T8("------------"));

// Controlla se Guardian e' abilitato e se lo e' allora lancia l'eseguibile apposito...
	RGuardian srv;
	__FLOG(_T8("Connect"));
	User::LeaveIfError( srv.Connect() );
	__FLOG(_T8("Enable"));
	TBool enabled = srv.IsEnabled();
	__FLOG(_T8("Srv_Close"));
	srv.Close();

//	if ( enabled )
//	{
		const TUidType serverUid(KNullUid, KNullUid, KGuardianUid3);
		RProcess guardian;
		__FLOG(_T8("Create"));
		TInt r=guardian.Create(KGuardianImage, KNullDesC, serverUid);
		if (r!=KErrNone) 
			return;
		__FLOG(_T8("Rendez"));
		TRequestStatus stat;
		guardian.Rendezvous(stat);
		if (stat != KRequestPending)
		{
			__FLOG(_T8("Kill"));
			guardian.Kill(0);		// abort startup
		}
		else
		{
			__FLOG(_T8("Resume"));
			guardian.Resume();	// logon OK - start the server
		}
		__FLOG(_T8("Wait"));
		User::WaitForRequest(stat);		// wait for start or death
		// we can't use the 'exit reason' if the server panicked as this
		// is the panic 'reason' and may be '0' which cannot be distinguished
		// from KErrNone
		r=(guardian.ExitType()==EExitPanic) ? KErrGeneral : stat.Int();
		__FLOG(_T8("Close"));
		guardian.Close();
//	}
	__FLOG_CLOSE;
	}


/*
Specifies this recognizer's preferred data buffer size passed to DoRecognizeL().
The actual value used will be the maximum of all recognizers.
*/
TUint CGuardAuto::PreferredBufSize()
	{
    return 0;
	}


/*
Returns the indexed data type that the recognizer can recognize. 
In this case, only 1 is supported. 
*/
TDataType CGuardAuto::SupportedDataTypeL(TInt /*aIndex*/) const
	{
	return TDataType();
	}

/*
Attempts to recognize the data type, given the filename and data buffer.
*/
void CGuardAuto::DoRecognizeL(const TDesC& aName, const TDesC8& aBuffer)
	{
	// this function is never called
    }


/*
The ECom implementation creation function.
*/
CApaDataRecognizerType* CGuardAuto::CreateRecognizerL()
	{
	CGuardAuto* thing = new (ELeave) CGuardAuto;
	CleanupStack::PushL(thing);
	thing->ConstructL();
	CleanupStack::Pop();
	return thing;
	}


/*
Standard ECom framework code 
*/
const TImplementationProxy ImplementationTable[] = 
    {
	IMPLEMENTATION_PROXY_ENTRY(KImplementationUid,CGuardAuto::CreateRecognizerL)
	};

/*
Standard ECom framework code 
*/
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }
