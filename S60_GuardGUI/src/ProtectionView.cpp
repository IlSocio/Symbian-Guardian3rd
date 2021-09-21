/*
 ============================================================================
 Name        : CProtectionView from GuardGUIView2.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CProtectionView implementation
 ============================================================================
 */
#include "GuardGUIconsts.h"
#include "GuardGUIAppUi.h"
#include "GuardGUI.hrh"
#include "ProtectionView.h"
#include "ProtectionContainer.h"

#include <GuardGUI_200131CC.rsg>

#include <FuzzyByte\Guardian\settings_consts.h>
#include <FuzzyByte\Guardian\srverr.h>
#include <FuzzyByte\Notes.h>
#include <FuzzyByte\GuiUtils.h>

// INCLUDE FILES
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
// CProtectionView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
// 
void CProtectionView::ConstructL()
	{
	BaseConstructL(R_GUARDGUI_VIEW4);
	__LOG_OPEN("Guardian", "GUI_ProtView.txt")
	User::LeaveIfError(iGuardian.Connect());

	iGuiSettings = CGuiSettings::NewL(iEikonEnv->FsSession());
	
	// All'avvio, forza questi valori a True perche' 
	// se l'utente si e' dimenticato di quell'impostazione non vede le app e contatta il supporto tecnico
	iGuiSettings->iShowUserApps = ETrue;
	iGuiSettings->iShowRomApps = ETrue;
	iGuiSettings->iShowSystemApps = ETrue;
	
	if (GuiUtils::IsTouchSupportedL())
		iWasFindBoxVisible = EFalse;
	else
		iWasFindBoxVisible = ETrue;
	}

// ---------------------------------------------------------
// CProtectionView::~CProtectionView()
// destructor
// ---------------------------------------------------------
//
CProtectionView::~CProtectionView()
	{
	__LOG_TXT("Destuctor");
	delete iGuiSettings;
	iGuardian.Close();
	if (iContainer)
		{
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	__LOG_TXT("End Destuctor");
	__LOG_CLOSE;
	}

// ---------------------------------------------------------
// TUid CProtectionView::Id()
//
// ---------------------------------------------------------
//
TUid CProtectionView::Id() const
	{
	return KView4Id;
	}

void CProtectionView::HandleItemChangeEventL(const TInt32 uid,
		const TBool checked)
	{
	CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
	if (!appui->iIsRegistered)
		{
		Notes::WarningL(R_ERR_UNAVAILINFREE);
		return;
		}

	if (checked)
		iGuardian.AddProtectedUid(uid);
	else
		iGuardian.RemProtectedUid(uid);
	/*	TBuf<20> buf;
	 buf.AppendNum(uid, EHex);
	 if (checked)
	 iEikonEnv->InfoMsg( buf );*/
	}

/*
 void CProtectionView::DeleteMenuItem(CEikMenuPane* menuPane, TInt aCommand)
 {
 TInt pos=0;
 TBool exists = menuPane->MenuItemExists(aCommand, pos);
 if (exists)
 menuPane->DeleteMenuItem(aCommand);
 }
 */

void CProtectionView::DynInitMenuPaneL(TInt aResourceId,
		CEikMenuPane* aMenuPane)
	{
	AppUi()->DynInitMenuPaneL(aResourceId, aMenuPane);

	if (aResourceId == R_VIEWAPPS_CASCADE)
	// if (aResourceId == R_GUARDGUI_VIEW4_MENU) 
		{
		if (iGuiSettings->iShowUserApps && iGuiSettings->iShowSystemApps
				&& iGuiSettings->iShowRomApps)
			aMenuPane->SetItemButtonState(EViewAllApps, EEikMenuItemSymbolOn);
		else
			{
			if (iGuiSettings->iShowUserApps)
				aMenuPane->SetItemButtonState(EViewUserOnlyApps,
						EEikMenuItemSymbolOn);

			if (iGuiSettings->iShowSystemApps)
				aMenuPane->SetItemButtonState(EViewSystemOnlyApps,
						EEikMenuItemSymbolOn);

			if (iGuiSettings->iShowRomApps)
				aMenuPane->SetItemButtonState(EViewRomOnlyApps,
						EEikMenuItemSymbolOn);
			}
		/*		if (iGuiSettings->iShowRomApps)
		 aMenuPane->SetItemButtonState(EViewRomApps, EEikMenuItemSymbolOn);
		 else
		 aMenuPane->SetItemButtonState(EViewRomApps, EEikMenuItemSymbolIndeterminate);
		 
		 if (iGuiSettings->iShowSystemApps)
		 aMenuPane->SetItemButtonState(EViewSystemApps, EEikMenuItemSymbolOn);
		 else
		 aMenuPane->SetItemButtonState(EViewSystemApps, EEikMenuItemSymbolIndeterminate);/**/
		}

	if (aResourceId == R_GUARDGUI_VIEW4_MENU)
		{
		// Nasconde il menu RemoveSim
		if (iContainer->IsSelectedMarkedL())
			{
			GuiUtils::DeleteMenuItem(aMenuPane, EAddApp);
			}
		else
			{
			GuiUtils::DeleteMenuItem(aMenuPane, ERemoveApp);
			//				aMenuPane->DeleteMenuItem(ERemoveApp);
			}

		// Gestione di Icone Piccole Grandi
		if (iGuiSettings->iLargeIcons)
			{
			GuiUtils::DeleteMenuItem(aMenuPane, ELargeIco);
			//				aMenuPane->DeleteMenuItem(ELargeIco);
			}
		else
			{
			GuiUtils::DeleteMenuItem(aMenuPane, ESmallIco);
			//				aMenuPane->DeleteMenuItem(ESmallIco);
			}

		}
	}

void CProtectionView::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case EAddApp:
		case ERemoveApp:
			{
			TInt32 uid = iContainer->GetSelectedUidL();
			if (uid <= 0)
				return;
			iContainer->ChangeApplicationStatusL(uid);
			TBool isMarked = iContainer->IsSelectedMarkedL();
			HandleItemChangeEventL(uid, isMarked);
			break;
			}

		case EViewAllApps:
			{
			iGuiSettings->iShowUserApps = ETrue;
			iGuiSettings->iShowRomApps = ETrue;
			iGuiSettings->iShowSystemApps = ETrue;
			iGuiSettings->SaveL();
			iContainer->ClearListBoxViewL();
			MarkApplicationsL();
			break;
			}
		case EViewUserOnlyApps:
			{
			iGuiSettings->iShowUserApps = ETrue;
			iGuiSettings->iShowRomApps = EFalse;
			iGuiSettings->iShowSystemApps = EFalse;
			iGuiSettings->SaveL();
			iContainer->ClearListBoxViewL();
			MarkApplicationsL();
			break;
			}
		case EViewRomOnlyApps:
			{
			iGuiSettings->iShowRomApps = ETrue;
			iGuiSettings->iShowUserApps = EFalse;
			iGuiSettings->iShowSystemApps = EFalse;
			iGuiSettings->SaveL();
			iContainer->ClearListBoxViewL();
			MarkApplicationsL();
			break;
			}
		case EViewSystemOnlyApps:
			{
			iGuiSettings->iShowSystemApps = ETrue;
			iGuiSettings->iShowUserApps = EFalse;
			iGuiSettings->iShowRomApps = EFalse;
			iGuiSettings->SaveL();
			iContainer->ClearListBoxViewL();
			MarkApplicationsL();
			break;
			}

		case ELargeIco:
		case ESmallIco:
			{
			iGuiSettings->iLargeIcons = (aCommand == ELargeIco);
			iGuiSettings->SaveL();
			iContainer->ClearListBoxViewL();
			MarkApplicationsL();
			break;
			}
		default:
			{
			AppUi()->HandleCommandL(aCommand);
			break;
			}
		}
	}

// ---------------------------------------------------------
// CProtectionView::HandleClientRectChange()
// ---------------------------------------------------------
//
void CProtectionView::HandleClientRectChange()
	{
	if (iContainer)
		{
		iContainer->SetRect(ClientRect());
		}
	}

void CProtectionView::MarkApplicationsL()
	{
	CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
	if (!appui->iIsRegistered)
		{
		return;
		}
	RArray<TInt32> uidList;
	CleanupClosePushL(uidList);
	__LOG_TXT("GetProtList");
	iGuardian.GetProtectedListL(uidList);

	__LOG_TXT("ChangeAppStatus");
	// Cicla ed imposta tutti i marker delle varie applicazioni protette...
	for (TInt i = 0; i < uidList.Count(); i++)
		{
		TInt32 uid = uidList[i]; // In base al valore restituito puo' rimuovere l'applicazione dalla lista di quelle protette...
		TBool exists = iContainer->ChangeApplicationStatusL(uid);
		if (!exists)
			iGuardian.RemProtectedUid(uid);
		}
	CleanupStack::PopAndDestroy(&uidList); // uidList
	__LOG_TXT("END UpdateViewL");
	}

// ---------------------------------------------------------
// CProtectionView::DoActivateL(...)
//
// ---------------------------------------------------------
//
void CProtectionView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
	{
	if (!iContainer)
		{
		iContainer = new (ELeave) CProtectionContainer(*iGuiSettings);
		iContainer->SetMopParent(this);
		iContainer->ConstructL(ClientRect(), iWasFindBoxVisible);
		iContainer->SetObserver(this);
		AppUi()->AddToStackL(*this, iContainer);
		MarkApplicationsL();

		// Imposta il titolo
		GuiUtils::StatusPaneSetupTitleL(StatusPane(), R_PROTECTED_APPS_TITLE);
		/*
		 CEikStatusPane* sp=iEikonEnv->AppUiFactory()->StatusPane();
		 CAknTitlePane* tp=(CAknTitlePane*)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

		 __FLOG(_T8("ReadRes"));
		 HBufC* string = CCoeEnv::Static()->AllocReadResourceL(R_PROTECTED_APPS);
		 __FLOG(_T8("SetText"));
		 tp->SetText( string );
		 __FLOG(_T8("END Activate"));*/
		}
	}

// ---------------------------------------------------------
// CProtectionView::DoDeactivate()
//
// ---------------------------------------------------------
//
void CProtectionView::DoDeactivate()
	{
	if (iContainer)
		{
		iWasFindBoxVisible = iContainer->IsFindBoxVisible();
		AppUi()->RemoveFromViewStack(*this, iContainer);
		delete iContainer;
		iContainer = NULL;
		}
	}

