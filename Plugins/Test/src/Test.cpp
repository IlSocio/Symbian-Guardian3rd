/*
============================================================================
 Name        : Test.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Exe source file
============================================================================
*/

//  Include Files  

#include "Test.h"
#include <e32base.h>
#include <e32std.h>
#include <e32cons.h>            // Console
#include "interface.h"
#include "PluginAO.h"
#include "pluginmanager.h"
#include <Plugins_200112df.rsg>

//  Constants

_LIT(KTextConsoleTitle, "Console");
_LIT(KTextFailed, " failed, leave code = %d");
_LIT(KTextPressAnyKey, " [press any key]\n");


//  Global Variables

LOCAL_D CConsoleBase* console;  // write all messages to this



//  Local Functions
LOCAL_C void MainL(const TDesC& aArgs)
    {
    //
    // add your program code here, example code below
    //

	TBuf<20> buf;
	buf = _L("11111");
	CGuardPlugInterface::TGuardPlugInitParams params;
//	params.number = &buf;

	CPluginManager* manager = CPluginManager::NewLC();
	manager->ProcessSmsPluginL(_L("3271828283"), _L("FAKESMS*mitt;te*a*sto"));
//	RBuf prova;
//	manager->ProcessSmsPluginL(prova, _L("FAKESMS*mitt;te*a*sto"));

// Verifica se la gestione di TRequestStatus e' stata fatta bene...
// Come mai non viene mai chiamato il CompleteL del plugin???

	CleanupStack::PopAndDestroy();
    console->Write(_L("Hello, world!\n"));
    console->Printf(_L("Command line args: \"%S\"\n"), &aArgs);
    }


LOCAL_C void DoStartL()
    {
    // Create active scheduler (to run active objects)
    CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
    CleanupStack::PushL(scheduler);
    CActiveScheduler::Install(scheduler);

    // Call main function with command line
    TBuf<256> cmdLine;
    User().CommandLine(cmdLine);
    MainL(cmdLine);

    // Delete active scheduler
    CleanupStack::PopAndDestroy(scheduler);
    }


//  Global Functions
GLDEF_C TInt E32Main()
    {
    // Create cleanup stack
    __UHEAP_MARK;
    CTrapCleanup* cleanup = CTrapCleanup::New();

    // Create output console
    TRAPD(createError, console = Console::NewL(KTextConsoleTitle, TSize(KConsFullScreen,KConsFullScreen)));
    if (createError)
        return createError;

    // Run application code inside TRAP harness, wait keypress when terminated
    TRAPD(mainError, DoStartL());
    if (mainError)
        console->Printf(KTextFailed, mainError);
    console->Printf(KTextPressAnyKey);
    console->Getch();
    
    delete console;
    delete cleanup;
    __UHEAP_MARKEND;
    return KErrNone;
    }



