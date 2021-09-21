// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 


#include "prova10warning.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"

//const TInt KMicorSecondsToWait = 3000000;

TInt CProva10warning::RunDlgLD()
	{
	CProva10warning* self = new (ELeave) CProva10warning();
/*	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();*/
	return self->ExecuteLD(R_EXIT_DIALOG);
	}

CProva10warning::CProva10warning() 
	{
	}

CProva10warning::~CProva10warning()
	{	
	}

void CProva10warning::ConstructL()
	{
	}

void CProva10warning::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      default:
      CQikSimpleDialog::HandleCommandL(aCommand);
         break;
      }
   }