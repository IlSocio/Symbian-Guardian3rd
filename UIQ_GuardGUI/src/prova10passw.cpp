// prova10passw.cpp
//
// © Symbian Software Ltd 2006. All rights reserved.
//

#include <QikCommand.h>
#include <eikedwin.h>
#include <eikseced.h>

#include "prova10passw.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include "prova10.hrh"

/**
Creates, constructs, execute and destroys the dialog.
*/
TInt CProva10Passw::RunDlgLD(TDes& aPassword)
	{
	CProva10Passw* self = new (ELeave) CProva10Passw(aPassword);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self->ExecuteLD(R_DIALOGS_USER_PASSWORD_DIALOG);
	}

/**
Constructor for the dialog.
*/
CProva10Passw::CProva10Passw(TDes& aPassword) 
	: iCmdManager(CQikCommandManager::Static(*iCoeEnv)), iPassword(aPassword)
	{
	}

/**
Destructor for the dialog
*/
CProva10Passw::~CProva10Passw()
	{
	}

/**
2nd stage construction of the dialog.
*/
void CProva10Passw::ConstructL()
	{
	}

/**
Handles all commands in the dialog.
Called by the UI framework when a command has been issued.
The command Ids are defined in the .hrh file.

@param aCommand The command to be executed
*/
void CProva10Passw::HandleCommandL(CQikCommand& aCommand)
	{
	switch(aCommand.Id())
		{
		case EPasswDialogLoginCmd:
		case EPasswDialogCancelCmd:
			{
			// Signals that the dialog should close with the command id as value

			const CEikSecretEditor* secretEditor = LocateControlByUniqueHandle<const CEikSecretEditor>(EPasswDialogSecretEditor);
			secretEditor->GetText(iPassword);

			CloseDialog(aCommand.Id());
			break;
			}
		default:
			{
			CQikSimpleDialog::HandleCommandL(aCommand);
			break;
			}
		}
	}

/**
Handles an event from an observed control. Used to get event when the edwin 
has been changed. If the edwin contains any text the login command shall be
available.
*/
void CProva10Passw::HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType)
	{
	    switch(aEventType)
	    {
	    	case EEventStateChanged:
			{
			switch(aControl->UniqueHandle())
				{
				case EPasswDialogSecretEditor:
					{
					// Locate the edwin
					const CEikSecretEditor* edwinsec = LocateControlByUniqueHandle<const CEikSecretEditor >(EPasswDialogSecretEditor);
	            	// Sets the login command to available if the edwin contains any text
					TBuf<50> text;
					edwinsec->GetText(text);
					if (text.Length()> 4)
	            		iCmdManager.SetAvailable(*this, EPasswDialogLoginCmd, ETrue);				
					break;
					}							
				}
			break;
			}
	        case EEventRequestExit:
	    	{
	    	CloseDialog(EPasswDialogLoginCmd);
	    	break;
	    	}		
	        case EEventRequestCancel:
	    	{
	    	CloseDialog(EPasswDialogCancelCmd);
	    	break;
	    	}
	        default:
	        break;
	    }
	CQikSimpleDialog::HandleControlEventL(aControl, aEventType);
	}
