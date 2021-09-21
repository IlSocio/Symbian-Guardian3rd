/*
 ============================================================================
 Name        : CSimListView from GuardGUIView2.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CSimListView implementation
 ============================================================================
 */
#include "GuardGUIconsts.h" 
#include "GuardGUI.hrh"
#include "SimListView.h"
#include "SimListContainer.h"
#include "guardguiappui.h"

#include <GuardGUI_200131CC.rsg>

#include <FuzzyByte\GuiUtils.h>
#include <FuzzyByte\Queries.h>
#include <FuzzyByte\Notes.h>
#include <FuzzyByte\Guardian\settings_consts.h>
#include <FuzzyByte\Guardian\srverr.h>

#include <akntitle.h>
#include <aknviewappui.h>
#include <avkon.hrh>
#include <aknview.h>
#include <eiktxlbx.h>
#include <aknlists.h>
#include <aknpopup.h>
#include <aknquerydialog.h>
#include <aknnotewrappers.h>
#include <aknmessagequerydialog.h>


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSimListView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CSimListView::ConstructL()
	{
	BaseConstructL(R_GUARDGUI_VIEW3);
	User::LeaveIfError(iGuardian.Connect());
	iTouchSupported = EFalse;
	iAcceptTouchEvents = EFalse;
	}

// ---------------------------------------------------------
// CSimListView::~CSimListView()
// destructor
// ---------------------------------------------------------
//
CSimListView::~CSimListView()
	{
	iGuardian.Close();
	if (iContainer)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		}

	delete iContainer;
	}

// ---------------------------------------------------------
// TUid CSimListView::Id()
//
// ---------------------------------------------------------
//
TUid CSimListView::Id() const
	{
	return KView3Id;
	}

TBool CSimListView::AskSimNameL(TDes& text)
	{
	return Queries::AskTextL(R_SIM_QUERY, text);
	/*	CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( text );
	 dlg->SetPredictiveTextInputPermitted( ETrue );
	 dlg->PrepareLC( R_SIM_QUERY );
	 dlg->SetMaxLength( KNAME_LEN );
	 return dlg->RunLD();*/
	}

void CSimListView::HandleListBoxEventL(CEikListBox* /*aListBox*/,
		TListBoxEvent aEventType)
	{
	if (aEventType == EEventPenDownOnItem) // 5th Ed.
		{
		iTouchSupported = ETrue;
		iAcceptTouchEvents = ETrue;
		}
	//	CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
	switch (aEventType)
		{
		case EEventEnterKeyPressed:
		case EEventItemClicked:
			//case EEventPenDownOnItem: // 5th Ed.
			//case EEventItemDoubleClicked: // 5th Ed.
			// Check se e' presente il supporto per il pennino...
/*			if (iTouchSupported)
				{
				if (!iAcceptTouchEvents)
					return;
				iAcceptTouchEvents = EFalse;
				if (iContainer->iListBox->CurrentItemIndex() != iOldIndex)
					{
					iOldIndex = iContainer->iListBox->CurrentItemIndex();
					return;
					}
				iOldIndex = iContainer->iListBox->CurrentItemIndex();
				}/**/

			switch (GuiUtils::ShowItemPopupL(R_CHANGE_SIM))
				{
				case 0:
					HandleCommandL(ERenameSim);
					break;
				case 1:
					HandleCommandL(ERemoveSim);
					break;
				case 2:
					HandleCommandL(EAddSim);
					break;
				}
			break;
		case EEventItemDraggingActioned: // 5th Ed.
			break;
		default:
			break;
		}
	}

void CSimListView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
	{
	AppUi()->DynInitMenuPaneL(aResourceId, aMenuPane);
	if (aResourceId == R_GUARDGUI_VIEW3_MENU)
		{
		// Nasconde il menu RemoveSim
		// aMenuPane->DeleteMenuItem(ERemoveSim);
		}
	}

void CSimListView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ERenameSim:
			{
			TImsiName name;
			TOperName oper;
			iContainer->GetSelectedNameAndOper(name, oper);
			if (name.Length() == 0)
				return;
			TImsiName oldName;
			oldName.Copy(name);
			if (!AskSimNameL(name))
				return;
			TInt ris = iGuardian.RenameSim(oldName, name);
			if (ris == KErrSimAlreadyExists)
				{
				// TODO: Messaggio di Warning: Questo nome e' gia' esistente.
				}
			UpdateViewL();
			break;
			}
		case ERemoveSim:
			{
			TImsiName name;
			TOperName oper;
			iContainer->GetSelectedNameAndOper(name, oper);
			if (name.Length() == 0)
				return;
			if (iGuardian.UnRegisterSim(name) == KErrSimOnlyAvail)
				{
				Notes::WarningL(R_ERR_SIM0);
				return;
				}
			UpdateViewL();
			break;
			}
			/*		case EAknSoftkeyOk:
			 {
			 iEikonEnv->InfoMsg( _L("view2 ok") );
			 break;
			 }
			 case EAknSoftkeyBack:
			 {
			 AppUi()->HandleCommandL(EEikCmdExit);
			 break;
			 }*/
		default:
			{
			AppUi()->HandleCommandL(aCommand);
			break;
			}
		}
	}

// ---------------------------------------------------------
// CSimListView::HandleClientRectChange()
// ---------------------------------------------------------
//
void CSimListView::HandleClientRectChange()
	{
	if (iContainer)
		{
		iContainer->SetRect(ClientRect());
		}
	}

void CSimListView::UpdateViewL()
	{
	RArray<TImsiName> nameList;
	CleanupClosePushL(nameList);
	RArray<TOperName> operList;
	CleanupClosePushL(operList);
	iGuardian.GetAuthorizedListL(nameList, operList);
	iContainer->UpdateListBoxViewL(nameList, operList);
	CleanupStack::PopAndDestroy(2); // nameList, operList
	}

// ---------------------------------------------------------
// CSimListView::DoActivateL(...)
//
// ---------------------------------------------------------
//
void CSimListView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (!iContainer)
		{
		iContainer = new (ELeave) CSimListContainer;
		iContainer->SetMopParent(this);
		iContainer->ConstructL(ClientRect(), *this);
		AppUi()->AddToStackL(*this, iContainer);
		UpdateViewL();

		// Imposta il titolo
		GuiUtils::StatusPaneSetupTitleL(StatusPane(), R_SIM_LIST_TITLE);
		/*		CEikStatusPane* sp=iEikonEnv->AppUiFactory()->StatusPane();
		 CAknTitlePane* tp=(CAknTitlePane*)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

		 HBufC* string = CCoeEnv::Static()->AllocReadResourceL(R_SIM_LIST);
		 tp->SetText( string );*/
		}
	iOldIndex = iContainer->iListBox->CurrentItemIndex();
	}

// ---------------------------------------------------------
// CSimListView::DoDeactivate()
//
// ---------------------------------------------------------
//
void CSimListView::DoDeactivate()
	{
	if (iContainer)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}

