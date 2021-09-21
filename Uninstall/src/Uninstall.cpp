/*
============================================================================
 Name        : Uninstall.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : Your copyright notice
 Description : Exe source file
============================================================================
*/

//  Include Files  

#include "Uninstall.h"
#include <e32base.h>
#include <e32cons.h>            // Console
//#include "SecurityCode.h"
#include <FuzzyByte\Guardian\client.h>
#include <f32file.h>


_LIT(KFileRedist, "c:\\system\\data\\200131CC\\guardian.sisx");


LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	// Segnala al server di chiudersi... (Il quale lo segnalera' ai client...)
	// Il Server e' gia' stato chiuso dall'installer
/*	RGuardian guard;
	CleanupClosePushL(guard);
	guard.Connect();
	guard.Uninstall();
	CleanupStack::PopAndDestroy();*/

/*	// Fa si che il notifier liberi le risorse...
	CSecurityCode* secCode = CSecurityCode::NewL();
	CleanupStack::PushL(secCode);
	TBuf<20> res;
	secCode->RequestCodeL(_L("KILL"), res);
	CleanupStack::PopAndDestroy();*/

	// Rimuove il file usato per l'invio di Guardian
	RFs fs;
	User::LeaveIfError( fs.Connect() );
	CleanupClosePushL(fs);
	fs.Delete(KFileRedist);
	CleanupStack::PopAndDestroy(&fs);

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
	return KErrNone;
	}
