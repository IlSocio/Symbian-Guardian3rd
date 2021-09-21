/*
============================================================================
 Name        : CAboutView from GuardGUIView.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CAboutView implementation
============================================================================
*/

#include "AboutView.h"
#include "AboutContainer.h"
#include "GuardGUIAppUi.h"
#include "guardgui.hrh"
#include "GuardGUIconsts.h"
#include "webupdate.h"
#include "updatelock.h"

#include <FuzzyByte\utils.h>
#include <FuzzyByte\iapmanager.rsg>
#include <FuzzyByte\Notes.h>
#include <FuzzyByte\iapManager.h>
#include <FuzzyByte\Utils.h>
#include <FuzzyByte\ResReader.h>
#include <FuzzyByte\GuiUtils.h>
#include <FuzzyByte\FileUtils.h>
#include <FuzzyByte\InboxAttachment.h>
#include <FuzzyByte\Guardian\client.h>
#include <FuzzyByte\Guardian\settings_consts.h>

//#include <SWInstDefs.h>
#include <mmf\common\mmfcontrollerpluginresolver.h>
#include <S32STRM.H>
#include <akntitle.h>
#include <aknviewappui.h>
#include <avkon.hrh>
#include <aknglobalnote.h>
#include <aknnotewrappers.h>
#include <aknmessagequerydialog.h>
#include <FeatDiscovery.h>
#include <Featureinfo.h>
#include <BaUtils.h>



// Invia al server kversion e UID3 per verificare aggiornamenti...
// Server risponde con 0 oppure con file:urlcompleto \n descrizione
// _UID3_
#include <GuardGUI_200131CC.rsg>

// E' Installer a piazzarlo li con quel nome...
_LIT(KFileTmpInst, "c:\\system\\data\\200131CC\\guardian.sisx");			// Pacchetto per la redistribuzione

_LIT(KUpdServerUrl, "http://www.Guardian-Mobile.com/CheckUpdates.aspx?");
 


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAboutView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CAboutView::ConstructL()
	{
	BaseConstructL( R_GUARDGUI_VIEW1 );
	__LOG_OPEN("Guardian", "GUI_AboutView.txt");
	iTimer = CTimeOutTimer::NewL( *this );
	iHasBT = CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdBt);
	iHasIR = CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdIrda);
	iBtIr = CMyObexClient::NewL();

 	TFileName sisFile;
 	iEikonEnv->ReadResourceL(sisFile, R_GUARDIAN_SISX );
 	
 	FileUtils::CompleteWithPrivatePathL(iEikonEnv->FsSession(), sisFile );
	iFileRedist = sisFile.Alloc();
	
 	if (FileUtils::GetFileSize( iEikonEnv->FsSession(), KFileTmpInst ) > 0)
 		{
 		BaflUtils::RenameFile( iEikonEnv->FsSession(), KFileTmpInst, iFileRedist->Des() );
 		}
 	}


// ---------------------------------------------------------
// CAboutView::~CAboutView()
// destructor
// ---------------------------------------------------------
//
CAboutView::~CAboutView()
	{
	__LOG_TXT("Destructor");
	if (iFileRedist)
		{
		delete iFileRedist; 
		iFileRedist = NULL;
		}
	if (iWebUpd)
	{
		delete iWebUpd;
		iWebUpd = NULL; 
	}
	if (iBtIr)
	{
		delete iBtIr;
		iBtIr = NULL;
	}
	if ( iContainer )
		{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
		}
	if (iTimer)
		{
		delete iTimer;
		}
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}


void CAboutView::ShowWaitDialogL()
{
	if (iWaitDialog)
		return;
    iWaitDialog = new (ELeave) CAknWaitDialog(
        reinterpret_cast<CEikDialog**>( &iWaitDialog ), ETrue );
    // Set DialogDissmissed callback
    iWaitDialog->SetCallback( this );
    iWaitDialog->ExecuteLD( R_WEBCLIENT_DOWNLOAD_WAIT_NOTE );
}


void CAboutView::DialogDismissedL( TInt aButtonId )
    {
    if ( aButtonId == EAknSoftkeyCancel )
        {
		if (iWebUpd)
			iWebUpd->CancelDownloadL();
        }
    }



void CAboutView::DismissWaitDialogL()
{
    if ( !iWaitDialog )
		return;
	iWaitDialog->ProcessFinishedL();    // deletes the dialog
	delete iWaitDialog;
	iWaitDialog = NULL;
}



void CAboutView::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3){}


// ---------------------------------------------------------
// TUid CAboutView::Id()
//
// ---------------------------------------------------------
//
TUid CAboutView::Id() const
	{
	return KViewId;
	}


void CAboutView::HandleCentralKeyEventL()
	{
	MenuBar()->TryDisplayMenuBarL();
	}


void CAboutView::CheckForUpdatesL()
	{
	if (iWebUpd == NULL)
		iWebUpd = CFuzWebUpdate::NewL( KUpdServerUrl );

	ShowWaitDialogL();
	TBuf8<100> url;
	TBool hasUpdates;
	CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();	
	TInt ris = iWebUpd->IsThereAnUpdatedVersionL( appui->iIsRegistered, KGUIVERSION, iBrandId, url, hasUpdates);
	DismissWaitDialogL();

	if (ris == KErrCancel)
	{ 
		delete iWebUpd;	iWebUpd = NULL;
		return;
	}

	if (ris != KErrNone)
		{
		// Questo check e' stato aggiunto nella 1.03 prima non era presente.
		// Obbliga ad aggiornare trascorsi 15 gg. non e' sufficiente uno IAP non valido
		delete iWebUpd;	iWebUpd = NULL;
		// es. kerrtimedout
		Notes::ErrorL(R_ERR_LICTRANSMIS);
		return;
		}

	if (!hasUpdates)
	{
		Notes::InformationL(R_NO_UPDATE);
		delete iWebUpd; iWebUpd = NULL;
		return;
	}

	// Dialog di conferma download aggiornamento...
	CAknQueryDialog* dlg = CAknQueryDialog::NewL();
	if ( !dlg->ExecuteLD(R_CONFIRM_DOWNLOAD) )
	{
		delete iWebUpd; iWebUpd = NULL;
		return;
	}

	// Read the TmpDownload filename
	TBuf<100> tmpDL;
	iEikonEnv->ReadResourceL(tmpDL, R_GUARDIAN_SISX);
	tmpDL.Insert(0, _L("c:\\system\\data\\200131CC\\"));
	iCoeEnv->FsSession().MkDirAll( tmpDL );
	
	// Show Progress...
	ShowWaitDialogL();
	ris = iWebUpd->DownloadUpdatedVersionL(url, iCoeEnv->FsSession(), tmpDL);
	DismissWaitDialogL();
	delete iWebUpd;	iWebUpd = NULL;
	// Hide Progress...

	if (ris == KErrCancel)
	{
		return;
	}
	if (ris != KErrNone)
	{
		Notes::ErrorL(R_ERR_LICTRANSMIS);
		return;
	}

	Notes::ConfirmationL(R_DOWN_COMPLETED);

	// Salva il file nell'InBox...
	RFs &fs= iCoeEnv->FsSession();
	
	CInboxAttachment* saver = CInboxAttachment::NewLC();
	HBufC* details = iCoeEnv->AllocReadResourceLC( R_WEB_NAME );
	saver->BT_IRDA_SaveFileToInboxL( fs, details->Des(), tmpDL );
	CleanupStack::PopAndDestroy(2);

	fs.Delete( tmpDL );
	// Elimina il file che e' gia' stato scaricato e salvato nell'inbox.

	// Refresh di File1 e File2
	// iFileSize1 = GetFileSize(KFileRedist);
	// iFileSize2 = GetFileSize(KFileEmb);

	// Parte Installazione di KFileTmp
	//  In alternativa all'installazione diretta, piazza il file nell'inbox... In questo caso non e' necessario il KFileRestore
	//
	//  Attenzione... Sara' lanciato l'uninstaller che andra' a rimuovere KFileRedist
	//  Quindi e' bene tenere una copia del pacchetto scaricato che sara' poi ripristinata dal mio installer
	//  Non e' piu' necessario mettendo l'update nell'inbox.
	//

//	AppUi()->Exit();
	}


// ---------------------------------------------------------
// CAboutView::HandleCommandL(TInt aCommand)
// takes care of view command handling
// ---------------------------------------------------------
//
void CAboutView::HandleCommandL(TInt aCommand)
	{
	switch ( aCommand )
		{
/*		case ESettings:
			{
			AppUi()->ActivateLocalViewL( KView2Id );
			break;		
			}*/
		case ECheckUpdates:
			{
				CheckForUpdatesL();
				break;  
			}
		case ESendBT:
			{
				if (iFileSize1) 
				{
					TRAP_IGNORE( iBtIr->ShowQueryAndSendFileL(iFileRedist->Des(), R_WEBCLIENT_DOWNLOAD_WAIT_NOTE, ETrue, iFileSize1) );
				}
				break;
			}
		case ESendIR:
			{
				if (iFileSize1)
				{
					TRAP_IGNORE( iBtIr->ShowQueryAndSendFileL(iFileRedist->Des(), R_WEBCLIENT_DOWNLOAD_WAIT_NOTE, EFalse, iFileSize1) );
				}
				break;
			}
		case EAknSoftkeyBack:
			{
			AppUi()->HandleCommandL(EEikCmdExit);
			break;
			}
		default:
			{
			AppUi()->HandleCommandL( aCommand );
			break;
			}
		}
	}

// ---------------------------------------------------------
// CAboutView::HandleClientRectChange()
// ---------------------------------------------------------
//
void CAboutView::HandleClientRectChange()
	{
	if ( iContainer )
		{
		iContainer->SetRect( ClientRect() );
		}
	}

// ---------------------------------------------------------
// CAboutView::DoActivateL(...)
//
// ---------------------------------------------------------
//
void CAboutView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
	{
	if (!iContainer)
		{
		CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
/*		iContainer = CPinView::NewL();
		iContainer->SetMopParent(this);/**/
		
		iContainer = new (ELeave) CAboutContainer;
		iContainer->SetMopParent(this);
		iContainer->ConstructL( *this, ClientRect(), appui->iIsRegistered );/**/
		AppUi()->AddToStackL( *this, iContainer );

		// Imposta il titolo
		GuiUtils::StatusPaneSetupTitleL(StatusPane(), R_ABOUT_TITLE);
/*		CEikStatusPane* sp=iEikonEnv->AppUiFactory()->StatusPane();
		CAknTitlePane* tp=(CAknTitlePane*)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

		HBufC* string = CCoeEnv::Static()->AllocReadResourceL(R_ABOUT);
		tp->SetText( string );*/

		if (iTimer && !iTimer->IsActive())
			{
			// Mostra il Messaggio SIM Registrata dopo 1 secondo...
			//TTimeIntervalMicroSeconds32 timeout(1000000 * 1);
			iTimer->AfterTime( TTimeIntervalSeconds(1) );
			}
		}
		iFileSize1 = FileUtils::GetFileSize(iEikonEnv->FsSession(), iFileRedist->Des());
   }




LOCAL_C void GetMatchingConfigFilesL(RFs& fs, RPointerArray<HBufC>& array)
	{
	CPhone* phone = CPhone::NewL();
	CleanupStack::PushL(phone);
	TOperName oper;
	TCountry mcc;
	TUint lac;
	TNetwork mnc;
	TUint cellId;
	phone->GetCellID(cellId, lac, mnc, mcc, oper);
	CleanupStack::PopAndDestroy(phone);
	if (mnc.Length() == 0)
		return;
	TInt num_mnc=0;
	TInt num_mcc=0;
	TLex lex(mnc);
	lex.Val(num_mnc);
	lex.Assign(mcc);
	lex.Val(num_mcc);
	
	TFileName mcc_mnc;
	mcc_mnc.AppendNum(num_mcc);
	mcc_mnc.Append(_L("_"));
	mcc_mnc.AppendNum(num_mnc);
	mcc_mnc.Append(_L("\\"));
	FileUtils::CompleteWithPrivatePathL(fs, mcc_mnc);
	array.ResetAndDestroy();
	FileUtils::ListFilesInDirectoryL(fs, mcc_mnc, array, KEntryAttMatchMask);
	}


LOCAL_C void CreateNewIapsL(RFs& fs)
	{
	RPointerArray<HBufC> array;
	CleanupResetAndDestroyPushL(array);
	GetMatchingConfigFilesL(fs, array);

	if (array.Count() > 0)
		{
		CMDBSession* db = CMDBSession::NewLC( KCDVersion1_1 );
		for (TInt i=0; i<array.Count(); i++)
			{
			HBufC* rscFile = (HBufC*) array[i];
			TParsePtrC parse(rscFile->Des());
			
			CResReader* resReader = CResReader::NewLC(fs, rscFile->Des());
			TBuf<30> apn;
			TBuf<20> user;
			TBuf<20> pass;
			resReader->ReadL(apn, R_APN);
			resReader->ReadL(user, R_USER);
			resReader->ReadL(pass, R_PASS);
			CleanupStack::PopAndDestroy(resReader);
			
			TRAPD(err, IapManager::CreateNewIAPL(fs, *db, parse.Name(), apn, user, pass));
			/*if (err != KErrNone)
				{
				TBuf<20> buf = _L("Error: ");
				buf.AppendNum(err);
				CAknInformationNote* dialog = new ( ELeave ) CAknInformationNote(ETrue);
				dialog->ExecuteLD( buf );
				}*/
			}
		CleanupStack::PopAndDestroy(db);
		}
	CleanupStack::PopAndDestroy(); // array	
	}


void CAboutView::TimerExpiredL(TAny* src)
	{
	__LOG_TXT("TimerExpired");		
		TImsiName sim_name;
		// Se la sim non e' ancora registrata allora la registra...
		// Se invece e' gia' registrata la sposta in alto nella lista...
		RGuardian guard;
		User::LeaveIfError( guard.Connect() );
		CleanupClosePushL(guard);
		guard.GetImei(iImei);
		iBrandId = guard.GetBrandId();
		if (guard.RegisterSim(sim_name) == KErrNone)
			{	
			RBuf buff;
			buff.CleanupClosePushL();
			buff.Create(200);
			iCoeEnv->ReadResourceL( buff, R_SIM_ADDED );
			buff.Append(TChar('"'));
			buff.Append( sim_name);
			buff.Append(TChar('"'));
			CAknQueryDialog* dlg = CAknQueryDialog::NewL();
			dlg->ExecuteLD(R_QUERY_SIM_ADDED, buff);
			CleanupStack::PopAndDestroy(&buff);
			}
		CleanupStack::PopAndDestroy(&guard);		

		// Add IAP...
		CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
		if (appui->iIsRegistered == 0)
			{
			RFs& fs = iEikonEnv->FsSession();
			TRAPD(err, CreateNewIapsL( fs ) );		
			}
		// Add IAP...
				
		delete iTimer;
		iTimer = NULL;
		__LOG_TXT("End TimerExpired");
	}


void CAboutView::UpdateContainerL(TInt val)
{
	if (iContainer)
	{
		iContainer->SetTypeSignatureL(val);
		iContainer->DrawNow();
	}
}


// ---------------------------------------------------------
// CAboutView::DoDeactivate()
//
// ---------------------------------------------------------
//
void CAboutView::DoDeactivate()
	{
	if ( iContainer )
		{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		delete iContainer;
		iContainer = NULL;
		}
	}



void CAboutView::DeleteMenuItem(CEikMenuPane* menuPane, TInt aCommand)
{
	TInt pos=0;
	TBool exists = menuPane->MenuItemExists(aCommand, pos);
	if (exists)
		menuPane->DeleteMenuItem(aCommand);
}



void CAboutView::DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane )
{
	AppUi()->DynInitMenuPaneL(aResourceId, aMenuPane);

	// Invia Guardian -> via BT / via IR
	if (aResourceId == R_GUARDGUI_VIEW1_MENU)
		{
			// Check Esistenza file da inviare...
			if ((!iHasIR && !iHasBT) || iBtIr->IsBusy() || iFileSize1 == 0)
			{
				DeleteMenuItem(aMenuPane, ESendObex);
//				aMenuPane->DeleteMenuItem(ESendObex);
			} else
			{
				if (!iHasIR)
					DeleteMenuItem(aMenuPane, ESendIR);
//					aMenuPane->DeleteMenuItem(ESendIR);
				if (!iHasBT)
					DeleteMenuItem(aMenuPane, ESendBT);
//					aMenuPane->DeleteMenuItem(ESendBT);
			}
		}
}


