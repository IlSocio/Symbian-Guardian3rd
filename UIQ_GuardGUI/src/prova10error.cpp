// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 


#include "prova10error.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"

//const TInt KMicorSecondsToWait = 3000000;

TInt CProva10error::RunDlgLD()
	{
	CProva10error* self = new (ELeave) CProva10error();
/*	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();*/
	return self->ExecuteLD(R_EXIT_DIALOG);
	}

CProva10error::CProva10error() 
	{
	}

CProva10error::~CProva10error()
	{	
	}

void CProva10error::ConstructL()
	{
	}

void CProva10error::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      default:
      CQikSimpleDialog::HandleCommandL(aCommand);
         break;
      }
   }