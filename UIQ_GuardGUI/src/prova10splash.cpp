// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 
//#include <e32std.h>

#include "prova10splash.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"

const TInt KMicorSecondsToWait = 3000000;

TInt CProva10Splash::RunDlgLD()
	{
	CProva10Splash* self = new (ELeave) CProva10Splash();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self->ExecuteLD(R_PROVA10SPLASH_UI_CONFIGURATIONS);
	self->DrawNow();
	}

CProva10Splash::CProva10Splash() 
	{
	}

CProva10Splash::~CProva10Splash()
	{	
	iTimer->Cancel();
	delete iTimer;
	}

void CProva10Splash::ConstructL()
	{
	//BaseConstructL();
	iTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	// Starts generating periodic events
	iTimer->Start(KMicorSecondsToWait, 0, TCallBack(StaticTimerCallBack, this));
	}
  
TInt CProva10Splash::StaticTimerCallBack(TAny* aThis)
	{
	CProva10Splash* self = static_cast<CProva10Splash*>(aThis);
	self->TimerCallBack();
	return KErrNone;
	}

/**
Callback method execution
*/
void CProva10Splash::TimerCallBack()
	{
	CloseDialog(KErrNone);
	CloseWindow();
	}

void CProva10Splash::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      case Eprova10Command1:
         break;
      default:
      CQikSimpleDialog::HandleCommandL(aCommand);
         break;
      }
   }
