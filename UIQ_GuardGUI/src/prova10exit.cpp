// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 


#include "prova10exit.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"

//const TInt KMicorSecondsToWait = 3000000;

TInt CProva10exit::RunDlgLD()
	{
	CProva10exit* self = new (ELeave) CProva10exit();
/*	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();*/
	return self->ExecuteLD(R_EXIT_DIALOG);
	}

CProva10exit::CProva10exit() 
	{
	}

CProva10exit::~CProva10exit()
	{	
	}

void CProva10exit::ConstructL()
	{
	}

void CProva10exit::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      default:
      CQikSimpleDialog::HandleCommandL(aCommand);
         break;
      }
   }
