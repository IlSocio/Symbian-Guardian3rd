// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 


#include "prova10info.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"


TInt CProva10info::RunDlgLD()
	{
	CProva10info* self = new (ELeave) CProva10info();
/*	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();*/
	return self->ExecuteLD(R_EXIT_DIALOG);
	}

CProva10info::CProva10info() 
	{
	}

CProva10info::~CProva10info()
	{	
	}

void CProva10info::ConstructL()
	{
	}

void CProva10info::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      default:
      CQikSimpleDialog::HandleCommandL(aCommand);
         break;
      }
   }