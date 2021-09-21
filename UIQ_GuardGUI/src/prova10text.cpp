// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 


#include "prova10text.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"

//const TInt KMicorSecondsToWait = 3000000;

TInt CProva10text::RunDlgLD()
	{
	CProva10text* self = new (ELeave) CProva10text();
/*	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();*/
	return self->ExecuteLD(R_TEXT_DIALOG);
	}

CProva10text::CProva10text() 
	{
	}

CProva10text::~CProva10text()
	{	
	}

void CProva10text::ConstructL()
	{
	}

void CProva10text::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      default:
      CQikSimpleDialog::HandleCommandL(aCommand);
         break;
      }
   }