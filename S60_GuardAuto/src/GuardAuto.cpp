/*
============================================================================
 Name        : Guardian.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Exe source file
============================================================================
*/

//  Include Files  

#include <FuzzyByte\Guardian\client.h>
//#include "client.h"
#include "GuardAuto.h"
#include <e32base.h>
#include <e32std.h>
#include <e32cons.h>            // Console
#include <f32file.h>
#include <APGCLI.H> 
#include <S32STRM.H>
#include <S32FILE.H> 
#include <bautils.H>
#include <hal.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\Processes.H>

 
_LIT(KAutoStartName, "Guard_AutoStart_200107AD");



LOCAL_C void DoStartL()
    { 
	__LOG_DECLARATION_MEMBER
	__LOG_OPEN("Guardian", "AutoStart.txt")

	if (!Processes::RenameIfNotRunning( KAutoStartName ))
		{
		__LOG_TXT("Already Running")
		__LOG_CLOSE
		return;
		}
	
    // Create active scheduler (to run active objects)
    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
    CleanupStack::PushL(scheduler);
    CActiveScheduler::Install(scheduler);

	// Controlla se Guardian e' abilitato e se lo e' allora lancia l'eseguibile apposito...
	RGuardian srv;
	__LOG_TXT("Connect")
	User::LeaveIfError( srv.Connect() );
	CleanupClosePushL(srv);
	__LOG_TXT("CheckEnabled")
	TBool enabled = srv.IsEnabled();
	CleanupStack::PopAndDestroy(); // srv 
 
	if (enabled)
		__LOG_TXT("Enabled")
	else 
		__LOG_TXT("Disabled")
	
/*	RFs fs;
	fs.Connect();
	TInt err = BaflUtils::CopyFile( fs, _L("c:\\tmp_reg.rsc"), _L("c:\\private\\10003a3f\\import\\apps\\GuardGUI_200131CC_reg.rsc"));
	__FLOG_1(_T8("Err:%d"), err);
	fs.Close();*/

	if ( enabled )
	{
		__LOG_TXT("ReadUid")
		// Prepare to Launch Guardian...	
		TUid uid3 = {0x200131CB};
		const TUidType guardUid(KNullUid, KNullUid, uid3);
		RProcess guardian;
		__LOG_TXT("Create")
		TInt r=guardian.Create(_L("Guardian_200131CB"), KNullDesC, guardUid);
		if (r!=KErrNone) 
			{
			__LOG_CLOSE
			return;
			}
		__LOG_TXT("Rendez")
		TRequestStatus stat;
		guardian.Rendezvous(stat);
		if (stat != KRequestPending)
		{
			__LOG_TXT("Kill")		// NECESSARIO POWERMNGMT
			guardian.Kill(0);		// abort startup
		}
		else
		{
			__LOG_TXT("Resume")
			guardian.SetParameter(1, 3);	// Avvio da Autostart.
			guardian.Resume();	// logon OK - start the server
		}
		__LOG_TXT("Wait")
		User::WaitForRequest(stat);		// wait for start or death
		// we can't use the 'exit reason' if the server panicked as this
		// is the panic 'reason' and may be '0' which cannot be distinguished
		// from KErrNone
		r=(guardian.ExitType()==EExitPanic) ? KErrGeneral : stat.Int();
		__LOG("Ris:%d", r)
		__LOG_TXT("Close")
		guardian.Close();
	}/**/
	
	// Il Delay e' necessario per il 5500 perche' se si chiude troppo presto non rileva che il programma e' stato avviato e mostra un errore.
	// Ad ogni modo, il processo Guardian va avanti... e' solo lo starter che attende
	User::After(5*1000000);
	// Cerca una alternativa ad User::After perche' con un secondo programma che la usa il cell. si "posa"
	
// Nel Samsung SGH i450 forse il delay crea dei problemi?!?


    // Delete active scheduler
    CleanupStack::PopAndDestroy(scheduler);
	__LOG_TXT("DESCTRUCTOR")
	__LOG_CLOSE
    }



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



