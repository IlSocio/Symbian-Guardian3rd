/*
 ============================================================================
 Name        : CGuardGUIAppUi from GuardGUIAppui.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CGuardGUIAppUi implementation
 ============================================================================
 */
#include "GuardGUIApplication.h"
#include "GuardGUIAppui.h"
#include "GuardGUI.hrh" 
#include "SplashView.h"
#include "GuardGUIconsts.h" 
#include "GuardGUI.h05.hrh"
#include "guardsvg_200131CC.mbg"

#include <GuardGUI_200131CC.rsg>

#include <FuzzyByte\Notes.h>
#include <FuzzyByte\GuiUtils.H>
#include <FuzzyByte\FileUtils.H>
#include <FuzzyByte\FuzProducts.H>
#include <FuzzyByte\Queries.H>
#include <FuzzyByte\Guardian\srverr.h>
#include <FuzzyByte\Guardian\settings_consts.h>

#include <mmf/common/MMFCONTROLLERPLUGINRESOLVER.H>
#include <browseroverriddensettings.h>
#include <pathinfo.h> 
#include <f32file.h>
#include <hal.h>
#include <hal_data.h>
#include <CMessageData.h>
#include <stringloader.h>
#include <f32file.h>
#include <bautils.h>
#include <charconv.h>
#include <hlplch.h>
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknglobalnote.h>
#include <e32std.h>
#include <e32base.h>
#include <eiknotapi.h>
#include <W32STD.H>
#include <SENDUICONSTS.H>
#include <sendui.h>
#include <tsendingcapabilities.h>
#include <sendas2.h>
#include <TXTRICH.H>
#include <MMsvAttachmentManager.h>
#include <MSVAPI.H>


//#include "updatelock.h"
#define KSEC 1000000

_LIT(KBuyServerUrl, "http://www.Guardian-Mobile.com/Buy.aspx?");
 
_LIT(KRegServerUrl, "http://www.Guardian-Mobile.com/LicRequest.aspx?");

TBool CGuardGUIAppUi::AskPasswordL(TDes& pass)
	{
	for (;;)
		{
		if (!Queries::AskTextL(R_PASS_QUERY, pass, EFalse))
			return false;
		/****		CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( pass );
		 dlg->PrepareLC( R_PASS_QUERY );
		 dlg->SetMaxLength( KPASS_LEN ); // KPASS_LEN
		 if ( !dlg->RunLD() )
		 return false; // Pigiato Cancel*/

		// Pigiato OK
		pass.UpperCase();
		/*if (pass.Length()>=5)
		 return true;

		 Notes::WarningL(R_ERR_SHORT_PASS);*/
		return true;
		}
	}

void CGuardGUIAppUi::ReplaceTabL(TInt tabId, TInt svgId)
	{
	//	TFileName tmp = Application()->BitmapStoreName(); 
	//  z:\resource\apps\GuardGUI_200131CC.mbm
	_LIT(KMifFile,"\\resource\\apps\\GuardSvg_200131CC.mif");
	TFileName filePath = KMifFile();
	FileUtils::CompleteWithCurrentDrive(filePath);

	GuiUtils::StatusPaneReplaceNaviTabIconL(StatusPane(), iDecoratedTabGroup,
			tabId, filePath, svgId);
	/*	// AknsUtils: Skinned Icons
	 CFbsBitmap* bmp(NULL);
	 CFbsBitmap* mask(NULL);
	 AknIconUtils::CreateIconL(bmp, mask, filePath, svgId, svgId);
	 AknIconUtils::SetSize(bmp, TSize(5, 5));
	 AknIconUtils::SetSize(mask, TSize(5, 5));
	 iTabGroup->ReplaceTabL(tabId, bmp, mask);*/
	}

// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CGuardGUIAppUi::ConstructL()
//
// ----------------------------------------------------------
//
void CGuardGUIAppUi::ConstructL()
	{
	TUint32 EAknTouchCompatibleFlag = 0x00800000;
	TUint32 EAknSingleClickCompatibleFlag = 0x01000000;

	TUint32 flag = 0;
	if (GuiUtils::IsTouchSupportedL())
		flag = EAknTouchCompatibleFlag;

	BaseConstructL(EAknEnableSkin | flag);
	__LOG_OPEN("Guardian","GUI_AppUi.txt");

	/*	TBuf<255> pass;
	 CAknTextQueryDialog* dlg = new( ELeave ) CAsyncQueryDialog( pass );
	 dlg->SetPromptL(_L("Prov"));
	 dlg->ExecuteLD(R_PIN_QUERY_TEST, _L("Custom2:"));/**/

	//	DeleteAgendaL();
	// WLAN   = KFeatureIdProtocolWlan 
	// Europe - Look And Feel = KFeatureIdAvkonELaf
	// Asian  - Look And Feel = KFeatureIdAvkonApac


	__LOG_TXT("HAL Get Machine");
	iGuiActive = iIsRegistered = 0;
	iWebReg = NULL;
	TInt id;
	HAL::Get(HALData::EMachineUid, id);
	iMachineId.CreateL(16);
	iMachineId.AppendNum(id, EHex);
	__LOG_TXT("HAL Got Machine");

	//	iPluginManager = CPluginManager::NewL();

	// TimeOut per lo SplashScreen...
#ifdef __WINS__
	iSplashView = CSplashView::NewLC( TTimeIntervalSeconds(1) );
#else
	iSplashView = CSplashView::NewLC( TTimeIntervalSeconds(2) );
#endif
	AddViewL(iSplashView);
	CleanupStack::Pop();

	__LOG_TXT("StatusPane");
	// Show tabs for main views from resources
	CEikStatusPane* sp = StatusPane();

	// Fetch pointer to the default navi pane control
	iNaviPane = (CAknNavigationControlContainer*) sp->ControlL(TUid::Uid(
			EEikStatusPaneUidNavi));

	// Tabgroup has been read from resource and it were pushed to the navi pane.
	// Get pointer to the navigation decorator with the ResourceDecorator() function.
	// Application owns the decorator and it has responsibility to delete the object.
	iDecoratedTabGroup = iNaviPane->ResourceDecorator();
	if (iDecoratedTabGroup)
		{
		iTabGroup = (CAknTabGroup*) iDecoratedTabGroup->DecoratedControl();
		__LOG_TXT("Replace Tabs");
		ReplaceTabL(EGuardGUIView1Tab, EMbmGuardsvg_200131ccAbout);
		ReplaceTabL(EGuardGUIView2Tab, EMbmGuardsvg_200131ccSettings);
		ReplaceTabL(EGuardGUIView3Tab, EMbmGuardsvg_200131ccSim);
		ReplaceTabL(EGuardGUIView4Tab, EMbmGuardsvg_200131ccProt);
		iTabGroup->SetObserver(this);
		}
	__LOG_TXT("Replaced Tabs");

	// CActive::EPriorityStandard
	// EPriorityNormal
	iTimer = CTimeOutTimer::NewL(*this);
//	iTimer->AfterTime(timeoutSec);
	}

void CGuardGUIAppUi::DialogClosedL(TBool ok, const TDesC& code)
	{

	}

void CGuardGUIAppUi::InitializeGuiViewsL()
	{
	RFs &fs = iCoeEnv->FsSession();
	// VERIFICA EXPIRED...
	/*
#ifdef _DEBUG
	 TFileName fullFileName;
	 FileUtils::CompleteWithPrivatePathL(fs, _L("EXP"), fullFileName);
	 TBool exists = BaflUtils::FileExists(fs, fullFileName);
	 TTime time;
	 time.HomeTime();
	 // Gennaio = 0
	 if (time.DateTime().Day() >= 22 || exists || time.DateTime().Month() != ENovember || time.DateTime().Year() != 2009)
	 {
	 if (!exists)
	 {
	 RGuardian guard;
	 guard.Connect();
	 guard.SetEnabled(EFalse);
	 guard.Close();
	 FileUtils::DumpToFileL(fs, fullFileName, _L8("."));
	 }
	 WarnMsg(R_ERR_BETA_EXPIRED);
	 Exit();
	 }
	 // Verifica expired
#endif
	 */

	TMessage msg;
	RGuardian guard;
	__LOG_TXT("Connect");
	User::LeaveIfError(guard.Connect());
	CleanupClosePushL(guard);
	iBrandId = guard.GetBrandId();

	TBuf<20> version;
	guard.GetVersion(version);
 
	// NOME FILE DI REGISTRAZIONE...
	TFileName regName = iMachineId;
	FileUtils::CompleteWithPrivatePathL(fs, regName);
	
	// VERIFICA ESISTENZA CONFIGURAZIONE
	__LOG_TXT("GetMsg");
	guard.GetMessage(msg);
	if (msg.Length() == 0)
		{
		__LOG_TXT("ReadRes");
		iCoeEnv->ReadResourceL(msg, R_WARNING_SMS);
		guard.SetMessage(msg);

		//__LOG_TXT("Deleted"));
		// PrivacyStatementL();
		}

	TBuf<10> code;
	guard.GetRegCode(code);
	if (code.Length() < 2)
		{
		// IMPOSTA COME NON REGISTRATO NEL CASO IN CUI LA CONFIGURAZIONE E' ANDATA A PERDERSI...
		fs.Delete( regName );
		}

	// VERIFICA SE E' REGISTRATO...
	if (BaflUtils::FileExists(fs, regName))
		{
		TBuf8<10> buf;
		RFile file;
		User::LeaveIfError(file.Open(fs, regName, EFileShareReadersOrWriters
				| EFileRead));
		file.Read(buf);
		file.Close();
		TLex8 lex(buf);
		lex.Val(iIsRegistered);
		}

	__LOG_TXT("GetPass");
	TPassCode goodPass;
	guard.GetPassword(goodPass);
	goodPass.UpperCase();
	TBool enabled = guard.IsEnabled();
	CleanupStack::PopAndDestroy( &guard );


	/*TBuf<255> pass;
	 CAknTextQueryDialog* dlg = new( ELeave ) CAsyncQueryDialog( *this, pass );
	 //	CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( pass );
	 dlg->ExecuteLD(R_PIN_QUERY_TEST, _L("Pro:"));*/
	/*	__FLOG(_L("PrepareLC"));
	 dlg->SetPredictiveTextInputPermitted( EFalse );
	 dlg->PrepareLC( R_PIN_QUERY_TEST );
	 __FLOG(_L("SetMaxLen"));
	 dlg->SetMaxLength( 8 ); // KPASS_LEN
	 __FLOG(_L("RunLD"));
	 dlg->RunLD();*/

	/****************/
	/*	RNotifier notif;
	 notif.Connect();
	 TBuf8<8> pass8= _L8("12345");
	 TBuf8<8> resp8;
	 resp8.Zero();
	 //	const TUid KPinUid = {0x102826DC};
	 const TUid KPinUid = {0x200107B1};
	 TRequestStatus status;
	 notif.StartNotifierAndGetResponse(status, KPinUid, pass8, resp8);
	 User::WaitForRequest(status);
	 notif.Close();/**/

	// VERIFICA PASSWORD 
	//#ifndef  __WINS__
	//
	// Se e' necessario effettuare l'update non verra' richiesta la password
	// La nuova sim non sara' aggiunta alla lista di sim autorizzate
	// Perche' la Free funzia solo con la sim con cui e' stato installato.
	//
	//	enabled = ETrue;
	//	TBuf<20> aaa;
	//	Queries::AskTextL(R_SMS_QUERY, aaa, EFalse);

	if (enabled)
		{
		__LOG_TXT("IsEnabled");
		TBuf<KPASS_LEN> pass;
		TBool isValid = EFalse;
		TInt count = 0;
		do
			{
			pass.Zero();
			if (!AskPasswordL(pass))
				Exit(); // Pigiato Cancel
			count++;
			isValid = (pass.Compare(goodPass) == 0);
			if (!isValid)
				Notes::WarningL(R_ERR_BAD_PASS);
			}
		while (count < 3 && !isValid);
		if (!isValid)
			Exit();
		}/**/
	//#endif

	// __LOG_TXT("TabChanged(0)"));
	// TabChangedL(0);

	__LOG_TXT("View1");
	iView1 = new (ELeave) CAboutView;
	CleanupStack::PushL(iView1);
	iView1->ConstructL();
	AddViewL(iView1); // transfer ownership to CAknViewAppUi
	CleanupStack::Pop(); // view1

	__LOG_TXT("View2");
	iView2 = new (ELeave) CSettingsView;
	CleanupStack::PushL(iView2);
	iView2->ConstructL();
	AddViewL(iView2); // transfer ownership to CAknViewAppUi
	CleanupStack::Pop(); // view2

	__LOG_TXT("View3");
	iView3 = new (ELeave) CSimListView;
	CleanupStack::PushL(iView3);
	iView3->ConstructL();
	AddViewL(iView3); // transfer ownership to CAknViewAppUi
	CleanupStack::Pop(); // view3

	__LOG_TXT("View4");
	iView4 = new (ELeave) CProtectionView();
	CleanupStack::PushL(iView4);
	iView4->ConstructL();
	AddViewL(iView4); // transfer ownership to CAknViewAppUi
	CleanupStack::Pop(); // view4

	// Launch timer for showing the "Buy Editions Message" and initializes GUI
	iTimer->AfterTime(TTimeIntervalSeconds(1));
	
	__LOG_TXT("ActivateView");
	ActivateLocalViewL(iView1->Id());

	// Cosi' e' possibile cambiare subito schermata, senza attendere 1 secondo...
	iGuiActive = iIsRegistered;
	}

void CGuardGUIAppUi::TimerExpiredL(TAny* src)
	{
	__LOG_TXT("TimerExpired");
	/*		TBuf<10> pass;
	 pass.Zero();
	 // Questa dialog NON e' modale, sara' lanciata, presa in carico dal framework e l'esecuzione continuera'...
	 CAsyncQueryDialog* dlg = new( ELeave ) CAsyncQueryDialog( *this, pass );
	 //		CAknTextQueryDialog* dlg = new (ELeave) CAknTextQueryDialog(pass);
	 __FLOG(_L("PrepareLC"));
	 dlg->SetPredictiveTextInputPermitted( EFalse );
	 dlg->PrepareLC( R_PIN_QUERY_TEST );
	 __FLOG(_L("SetMaxLen"));
	 dlg->SetMaxLength( 8 ); // KPASS_LEN
	 __FLOG(_L("RunLD")); 
	 dlg->RunLD(); 
	 return;*/

	iGuiActive = ETrue;
	
	if (!iIsRegistered)
		{
		// Mostra box per comparativa delle versioni... Gold / Platinum
		HBufC* title = iCoeEnv->AllocReadResourceLC(R_EDITIONS_HEADER);
		ShowLongTextFromFileL(_L("editions.txt"), title->Des());
		CleanupStack::PopAndDestroy(title);
		
		// Check for updated version?
		if (Notes::QueryL(R_AVKON_SOFTKEYS_YES_NO, R_CHECK_FOR_UPDATES) == EAknSoftkeyYes)
			iView1->CheckForUpdatesL();
		}
	}
 
CGuardGUIAppUi::~CGuardGUIAppUi()
	{
	__LOG_TXT("Destructor");
	TRAP_IGNORE( DismissWaitDialogL() );
	iMachineId.Close();
	delete iWebReg;
	//	if (iPluginManager)
	//		delete iPluginManager;
	if (iTimer)
		delete iTimer;
	if (iDecoratedTabGroup)
		delete iDecoratedTabGroup;
	//	if (iPhone)
	//		delete iPhone;
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}

TKeyResponse CGuardGUIAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	if (iTabGroup == NULL)
		{
		return EKeyWasNotConsumed;
		}

	if (aKeyEvent.iCode == EKeyLeftArrow || aKeyEvent.iCode == EKeyRightArrow)
		{
		__LOG("GuiActive:%d", iGuiActive);
		if (!iGuiActive)
			return EKeyWasNotConsumed;
/*		if (iView1 && iView1->iForceUpdate)
			{
			Notes::InformationL(R_FORCE_UPDATE);
			CAknQueryDialog* dlg = CAknQueryDialog::NewL();
			if (dlg->ExecuteLD(R_CONFIRM_CHECK_UPDATES))
				{
				iView1->CheckForUpdatesL();
				}
			return EKeyWasNotConsumed;
			}*/
		delete iWebReg;
		iWebReg = NULL;
		return iTabGroup->OfferKeyEventL(aKeyEvent, aType);
		}
	else
		{
		return EKeyWasNotConsumed;
		}
	}

/*TBool CGuardGUIAppUi::DBG_AskTimeOutL(TDes& timeout)
 {
 CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( timeout );
 dlg->PrepareLC( R_DBG_LOCALIZE );
 dlg->SetMaxLength( 4 );
 return dlg->RunLD();
 }*/

void CGuardGUIAppUi::ShowWaitDialogL()
	{
	if (iWaitDialog)
		return;
	iWaitDialog = new (ELeave) CAknWaitDialog(
			reinterpret_cast<CEikDialog**> (&iWaitDialog), ETrue);
	// Set DialogDissmissed callback
	iWaitDialog->SetCallback(this);
	iWaitDialog->ExecuteLD(R_WEBCLIENT_DOWNLOAD_WAIT_NOTE);
	}

void CGuardGUIAppUi::DialogDismissedL(TInt aButtonId)
	{
	if (aButtonId == EAknSoftkeyCancel)
		{
		if (iWebReg)
			iWebReg->CancelRegistrationRequestL();
		}
	}

void CGuardGUIAppUi::DismissWaitDialogL()
	{
	if (!iWaitDialog)
		return;
	iWaitDialog->ProcessFinishedL(); // deletes the dialog
	delete iWaitDialog;
	iWaitDialog = NULL;
	}

/*void CGuardGUIAppUi::DeleteMenuItem(CEikMenuPane* menuPane, TInt aCommand)
 {
 TInt pos=0;
 TBool exists = menuPane->MenuItemExists(aCommand, pos);
 if (!exists)
 return;
 menuPane->DeleteMenuItem(aCommand);
 }


 void CGuardGUIAppUi::DeleteMenuItemIfEmpty(CEikMenuPane* menuPane, TInt aCommand)
 {
 TInt pos=0;
 TBool exists = menuPane->MenuItemExists(aCommand, pos);
 if (!exists)
 return;
 CEikMenuPaneItem::SData& data = menuPane->ItemData(aCommand);
 if (data.iText.Length() <= 0)
 GuiUtils::DeleteMenuItem(menuPane, aCommand);
 menuPane->DeleteMenuItem(aCommand);
 }*/

void CGuardGUIAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
	{
	//	__FLOG_1(_T8("DynInitMenu:%d"), aResourceId);

	// Nasconde Buy Gold se e' vuoto...

	// Dopo la registrazione nasconde Buy e Register
	//if (aResourceId != R_GUARDGUI_APP_MENU)
	//	return;
	
	if (iIsRegistered > 0)
		GuiUtils::DeleteMenuItem(aMenuPane, ERegister);

	if (iIsRegistered >= 1)
		GuiUtils::DeleteMenuItem(aMenuPane, EBuyGold);

	if (iIsRegistered >= 2)
		GuiUtils::DeleteMenuItem(aMenuPane, EBuyPlatinum);

	if (iIsRegistered >= 3)
		{
		GuiUtils::DeleteMenuItem(aMenuPane, EBuyIridium);
		GuiUtils::DeleteMenuItem(aMenuPane, EBuyCascade);
		}

	// ...ELEMENTI DELLA VISTA ABOUT...
	// ...ELEMENTI DELLA VISTA ABOUT...
	// ...ELEMENTI DELLA VISTA ABOUT...

	}

/*void CGuardGUIAppUi::HandlePointerEventL(const TPointerEvent& aPointerEvent)
 {
 // Remember to call base class implementation
 CCoeControl::HandlePointerEventL(aPointerEvent);
 
 // Your additional code here
 // ...	
 }*/

TAny* CGuardGUIAppUi::DownloadedContentHandlerReserved1(TAny* /*aAnyParam*/)
	{
	return NULL;
	}

/*
 TBool CGuardGUIAppUi::HandleContentL(const TDesC& aFileName, const CAiwGenericParamList& aParamList, TBool& aContinue)
 {
 for (TInt i=0; i<aParamList.Count(); i++)
 {
 TAiwGenericParam par = aParamList[i];
 TGenericParamId id = par.SemanticId();
 __LOG("ID:%d"), id);
 TAiwVariant val = par.Value();
 if (!val.IsEmpty())
 {
 TVariantTypeId type = val.TypeId();
 __LOG("Type:%d"), type);
 __FLOG(_L("Val:"));
 __FLOG(val.AsDes());
 }
 }
 __FLOG(_L("HandleContentL"));
 __FLOG(aFileName);
 aContinue = ETrue; // It must be ETrue if the caller wants Browser not to terminate after the content is handled.
 //  Il file contiene il codice di registrazione...
 return EFalse;       // ETrue if the implementer has processed the content. If it is EFalse, BrowserLauncher opens that content in an appropriate viewer application.
 }*/

/*enum TGenericParamId
 {
 EGenericParamUnspecified = 0,

 // General parameters
 EGenericParamError = 1,           // Any error parameter
 EGenericParamDir = 2,             // Any directory
 EGenericParamFile = 3,            // Any file
 EGenericParamURL = 4,             // Any URL
 EGenericParamApplication = 5,     // Application
 EGenericParamInstallPackage = 6,  // Install package
 EGenericParamDRMFile = 7,
 EGenericParamMIMEType = 8,
 EGenericParamCharSet = 9,

 // NOTE: Next id is a special semantic id reserved for AIW
 // framework. A consumer application should never
 // add it to parameter list.
 EGenericParamServiceCommand = 10,

 // NOTE: Next id is to be used only internally by DocumentHandler.
 // Do not not use it for anything else.
 EGenericParamInternalFile = 11,

 // Application services
 EGenericParamContactItem  = 20,
 EGenericParamCalendarItem  = 21,
 EGenericParamMessageItem  = 22,
 EGenericParamNoteItem  = 23,
 EGenericParamHelpItem  = 24,
 EGenericParamAlarmItem  = 25,
 EGenericParamLogItem  = 26,
 EGenericParamPhoneNumber = 27,
 EGenericParamAccessPoint = 28,
 EGenericParamSIPAddress = 29,

 EGenericParamMessageItemSMS = 30,
 EGenericParamMessageItemEMail = 31,
 EGenericParamMessageItemMMS = 32,

 EGenericParamEmailAddress = 33,
 EGenericParamWVID = 34,
 EGenericParamDateTime = 35,

 EGenericParamMessageItemMbox = 36,

 // SIM items
 EGenericParamSIMContactItem  = 40,
 EGenericParamSIMAppItem  = 41,

 // Browser items
 EGenericParamReferringURI  = 50,

 // Music Player items
 EGenericParamPlayerInitMode = 60,
 EGenericParamAlbumItems = 61,
 EGenericParamAlbumName = 62,

 // Print parameters
 EGenericParamPrintXMLFile = 70,

 // Call parameters
 EGenericParamCallDialDataV1 = 80,
 EGenericParamCallDialData   = 81,

 // Sprint media gallery provider specific
 EGenricParamMGItemType = 90,
 EGeneriParamMGMediaType = 91,
 EGeneriParamMGViewType = 92,
 EGenericParamMGSubviewtype = 93,
 EGenericParamMGMarked = 94,
 EGenericParamCdmaExtendedAMSData = 95,
 EGenericParamCdmaExtendedLightSurfData = 96,

 EGenericParamSilentDownload = 110,
 EGenericParamSuppressLaunch = 111,
 EGenericParamSuppressNextUrl = 112,

 EGenericParamPoCData = 120,
 EGenericParamPoCLaunchView = 121,

 EGenericParamAllowMove = 130,
 EGenericParamAllowSave = 131,

 EGenericParamFileSaved = 140,

 EGenericParamLocation = 150,

 EGenericParamFotaPkgId = 160,

 EGenericParamMMSSizeLimit = 170,
 EGenericParamResolution   = 171,

 EGenericParamSuppressDownloadConfirmation = 180,

 EGenericParamPassword     = 190,
 EGenericParamUserName     = 191,
 EGenericParamBookmarkName = 192,

 EGenericParamContactSelectionData = 200,
 EGenericParamContactLinkArray     = 201,
 EGenericParamContactStoreUriArray = 202,
 EGenericParamSelectedCount        = 203,
 EGenericParamContactAssignData    = 204,

 // In-device search parameters
 EGenericParamKeywords             = 240,
 EGenericParamCallAppLocName       = 241,
 EGenericParamStartOption          = 242
 }; */

/*enum TVariantTypeId
 {
 EVariantTypeAny = -1,   // Used only in searching
 EVariantTypeNull = 0,   // Null (empty) type

 EVariantTypeTInt32 = 1, // 32 bit Integer
 EVariantTypeTUid = 2,   // Globally unique UID
 EVariantTypeDesC = 3,   // Constant text literal
 EVariantTypeTTime = 4,   // Date and time
 EVariantTypeDesC8 = 5,     // 8-bit data buffer
 EVariantTypeFileHandle = 6 // File handle
 };*/

TBool CGuardGUIAppUi::GotRegCodeL(const TDesC& regCode)
	{
	__LOG_TXT("GotRegCodeL");
	__LOG_DES(regCode);
	RGuardian guard;
	User::LeaveIfError(guard.Connect());
	CleanupClosePushL(guard);
	TInt regResult = guard.Register(regCode);
	TBool isIridium = guard.IsIridium();
	CleanupStack::PopAndDestroy(&guard);
	if (!regResult)
		{
		Notes::ErrorL(R_ERR_CODE);
		return EFalse;
		}

	// regResult = 0 Free
	// regResult = 1 Platinum or Iridium
	// regResult = 2 Gold

	if (regResult == 2)
		{
		iIsRegistered++; // Gold ==> iIsRegistered = 1
		}
	else
		{
		// regResult = 1	// Platinum or Iridium ==> iIsRegistered = 2 or 3
		iIsRegistered = regResult + 1;
		iIsRegistered += isIridium;
		}
	TBuf8<10> data;
	data.AppendNum(iIsRegistered);

	Notes::ConfirmationL(R_OK_CODE);
	RFs &fs = iCoeEnv->FsSession();
	TFileName regName = iMachineId;
	FileUtils::CompleteWithPrivatePathL(fs, regName);
	RFile file;
	file.Create(fs, regName, EFileWrite);
	file.Write(data);
	file.Close();

	if (iTabGroup->ActiveTabId() == EGuardGUIView1Tab)
		{
		__LOG_TXT("UpdateContainerL");
		this->iView1->UpdateContainerL(iIsRegistered);
		}
	return ETrue;
	}

//void CGuardGUIAppUi::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3){}


void CGuardGUIAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case ESplashViewCmdBack:
			{
			this->InitializeGuiViewsL();
			break;
			}
			// VIENE VISUALIZZATO DOPO CHE SI SONO MOSTRATI I CREDITS????
			/*        case EAknSoftkeyBack:
			 {
			 if (iDecoratedTabGroup == NULL) break;
			 CAknTabGroup* tabGroup = static_cast<CAknTabGroup*> ( iDecoratedTabGroup->DecoratedControl() );
			 ActivateLocalViewL(  TUid::Uid(  tabGroup->ActiveTabId() ) );
			 break;
			 }*/
		case EEikCmdExit:
			{
			Exit();
			break;
			}

		case EAknSoftkeyExit:
			{
			CAknQueryDialog* dlg = CAknQueryDialog::NewL();
			if (!dlg->ExecuteLD(R_CONFIRM_EXIT))
				return;

			RFs& fs = iEikonEnv->FsSession();
			_LIT(KLogPath, "c:\\logs\\guardian\\");

			// Copy the logging files to a public directory
			RPointerArray<HBufC> array;
			CleanupResetAndDestroyPushL(array);
			FileUtils::ListFilesInDirectoryL(fs, KLogPath, array,
					KEntryAttMatchMask);
			if (array.Count() > 0)
				{
				__LOG("Wait. Count:%d", array.Count());
				User::After(5 * 1000000);
				}
			for (TInt i = 0; i < array.Count(); i++)
				{
				TParsePtrC parse(array[i]->Des());
				TBuf<50> newName;
				newName = PathInfo::PhoneMemoryRootPath();
				newName.Append(PathInfo::OthersPath());
				newName.Append(parse.NameAndExt());
				__LOG_TXT("NewName:");
				__LOG_DES(newName);
				TInt ris = BaflUtils::CopyFile(fs, array[i]->Des(), newName);
				__LOG("Ris:%d", ris);
				}
			CleanupStack::PopAndDestroy(); //array

			Exit();
			break;
			}

		case EBuyIridium:
			{
			/*#ifdef __WINSCW__
			 TBuf<300> url = _L("http://localhost:1105/GuardianMobile/Buy.aspx?");
			 #else
			 TBuf<300> url;
			 iEikonEnv->ReadResourceL(url, R_HTTP_BUY );
			 #endif*/
			FuzProducts::BuySoftwareL(KBuyServerUrl, EGuardianIridium);
			// TODO: Dopo l'acquisto acquisisce in Automatico il Codice e diventa Gold / Platinum
			break;
			}

		case EBuyGold:
			{
			FuzProducts::BuySoftwareL(KBuyServerUrl, EGuardianGold);
			// TODO: Dopo l'acquisto acquisisce in Automatico il Codice e diventa Gold / Platinum
			break;
			}

		case EBuyPlatinum:
			{
			FuzProducts::BuySoftwareL(KBuyServerUrl, EGuardianPlatinum);
			// TODO: Dopo l'acquisto acquisisce in Automatico il Codice e diventa Gold / Platinum
			break;
			}

		case ELicense:
			{
			HBufC* title = iCoeEnv->AllocReadResourceLC(R_LICENSE_HEADER);
			ShowLongTextFromFileL(_L("license.txt"), title->Des());
			CleanupStack::PopAndDestroy(title);
			break;
			}
			/*		case ECredits:
			 {
			 ActivateLocalViewL( KViewCreditsId );
			 break;
			 }
			 case EAknSoftkeyBack:
			 {
			 if (iDecoratedTabGroup == NULL) break;
			 CAknTabGroup* tabGroup = static_cast<CAknTabGroup*> ( iDecoratedTabGroup->DecoratedControl() );
			 ActivateLocalViewL(  TUid::Uid(  tabGroup->ActiveTabId() ) );
			 break;
			 }*/
			/*		case EGuardGUICmdAppTest:
			 {
			 iEikonEnv->InfoMsg(_L("test"));
			 break;
			 }*/
		case ESettings:
			{
			iTabGroup->SetActiveTabByIndex( 1 );
			ActivateLocalViewL( KView2Id );
			break;
			}
		case EHelp:
			{
			CArrayFix<TCoeHelpContext>* buf = CCoeAppUi::AppHelpContextL();
			HlpLauncher::LaunchHelpApplicationL(iEikonEnv->WsSession(), buf);/**/
			}
			break;
		case EAddSim:
			{
			// Mostra messaggio informativo...
			if (!iIsRegistered)
				{
				Notes::WarningL(R_ERR_UNAVAILINFREE);
				return;
				}
			HBufC* title = iCoeEnv->AllocReadResourceLC(R_ADDNEWSIM_HEADER);
			ShowLongTextFromFileL(_L("addnewsim.txt"), title->Des());
			CleanupStack::PopAndDestroy(title);
			break;
			}
		case ERegisterNet:
			{
			TBuf<8> parte1;
			TBuf<8> parte2;
			TBool good = EFalse;
			do
				{
				CAknMultiLineDataQueryDialog* dlg =
						CAknMultiLineDataQueryDialog::NewL(parte1, parte2);
				dlg->SetPredictiveTextInputPermitted(EFalse);
				if (!dlg->ExecuteLD(R_REGISTER_NET_DIALOG))
					return;
				good = FuzProducts::IsGoodLicenseID(parte1, parte2);
				if (!good)
					{
					Notes::ErrorL(R_ERR_LICNOTFOUND);
					}
				}
			while (!good);
			TBuf<16> licenseID = parte1;
			licenseID.Append(parte2);

			// Se e' il caso crea iWebReg
			if (iWebReg == NULL)
				{ 
				TRAPD(err, iWebReg = CFuzWebRegister::NewL(KRegServerUrl));
				if (err != KErrNone)
					return;
				}
			// Chiamata al server per effettuare la Registrazione...
			ShowWaitDialogL();
			TBuf<20> regCode;
			//			TBool abort;
			TResponseID resp;
			TInt ris = iWebReg->SendRegistrationRequestL(iBrandId, KGUIVERSION, licenseID, regCode, resp);
			DismissWaitDialogL();
			// delete iWebReg; iWebReg = NULL;
			if (ris == KErrCancel) // Cancelled
				return;
			if (resp == EErrNone)
				{
				GotRegCodeL(regCode);
				return;
				}
			TInt res = 0;
			switch (resp)
				{
				case ELicenseIDNotFound: // Da Gestire... "LicenseID non valido"
					res = R_ERR_LICNOTFOUND;
					break;
				case ELicenseIDHasDifferentIMEI: // Da Gestire... "LicenseID gia' registrato"
					res = R_ERR_LICDIFIMEI;
					break;
				case EBannedFor10Minutes: // Da Gestire... "Troppe richieste, riprovare piu' tardi"
					res = R_ERR_LICBANNED;
					break;
				case EUnknownDataReceived: // Da Gestire... "Errore nella risposta del server, riprovare piu' tardi"
					res = R_ERR_LICUNKDATA;
					break;
				case ETransmissionError: // Da Gestire... "Errore nella comunicazione, riprovare piu' tardi"
					res = R_ERR_LICTRANSMIS;
					break;
				default:
					res = R_ERR_LICGENERAL; // Da Gestire... "Errore Generico"
					break;
				}
			// Messaggio di errore: "Servizio Temporaneamente Non Disponibile: Riprovare Piu' Tardi"
			Notes::ErrorL(res);
			break;
			}
		case ERegisterCode:
			{
			TBuf<10> regCode64;
			do
				{
				CAknTextQueryDialog* dlg = new (ELeave) CAknTextQueryDialog(
						regCode64);
				dlg->SetPredictiveTextInputPermitted(EFalse);
				if (!dlg->ExecuteLD(R_REGISTER_DIALOG))
					return; // Pigiato Cancel
				}
			while (!GotRegCodeL(regCode64));
			break;
			}
		case EAbout:
			{
			/*		CAknMessageQueryDialog* dlg = new (ELeave)CAknMessageQueryDialog();
			 dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
			 HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			 dlg->QueryHeading()->SetTextL(*title);
			 CleanupStack::PopAndDestroy(); //title
			 HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			 dlg->SetMessageTextL(*msg);
			 CleanupStack::PopAndDestroy(msg); //msg
			 dlg->RunLD();*/
			}
			break;

		case EDBGPlugFake:
			{
			break;
			}

		case EDBGPlugAlar:
			{
			break;
			}

		case EDBGPlugConf:
			{
			break;
			}

		case EDBGPlugDele:
			{
			break;
			}
		default:
			CAknViewAppUi::HandleCommandL(aCommand);
			break;
		}
	}

void CGuardGUIAppUi::HandleResourceChangeL(TInt aType)
	{
	CAknAppUi::HandleResourceChangeL(aType);
	if (aType == KEikDynamicLayoutVariantSwitch)
		{
		if (iSplashView)
			iSplashView->HandleClientRectChange();
		if (iView1)
			iView1->HandleClientRectChange();
		if (iView2)
			iView2->HandleClientRectChange();
		if (iView3)
			iView3->HandleClientRectChange();
		if (iView4)
			iView4->HandleClientRectChange();
		}
	//Controls derived from CCoeControl, handled in a container class
	//iAppContainer->HandleResourceChange( aType );
	}

// ----------------------------------------------------
// CGuardGUIAppUi::TabChangedL(TInt aIndex)
// This method gets called when CAknTabGroup active
// tab has changed.
// ----------------------------------------------------
//
void CGuardGUIAppUi::TabChangedL(TInt aIndex)
	{
	ActivateLocalViewL(TUid::Uid(iTabGroup->TabIdFromIndex(aIndex)));
	}

CArrayFix<TCoeHelpContext>* CGuardGUIAppUi::HelpContextL() const
	{
	//		CCoeControl::GetHelpContext(TCoeHelpContext& cnt);
	CArrayFixFlat<TCoeHelpContext>* ctxs = new (ELeave) CArrayFixFlat<
			TCoeHelpContext> (1);
	CleanupStack::PushL(ctxs);
	// KHIntro
	// KHBuyAndReg
	// KHBuy
	// KHRegister
	// KHSettings
	// KHFastSettings
	// KHSimList
	// KHProtList

	const TUid KUid3 =
		{
		0x200112DD
		};
	switch (iTabGroup->ActiveTabId())
		{
		case EGuardGUIView1Tab:
			{
			if (!iIsRegistered)
				{
				ctxs->AppendL(TCoeHelpContext(KUid3, KHBuyAndReg));
				ctxs->AppendL(TCoeHelpContext(KUid3, KHBuy));
				ctxs->AppendL(TCoeHelpContext(KUid3, KHRegister));
				}
			else
				{
				ctxs->AppendL(TCoeHelpContext(KUid3, KHIntro));
				}
			break;
			}
		case EGuardGUIView2Tab:
			{
			ctxs->AppendL(TCoeHelpContext(KUid3, KHSettings));
			ctxs->AppendL(TCoeHelpContext(KUid3, KHFastSettings));
			break;
			}
		case EGuardGUIView3Tab:
			{
			ctxs->AppendL(TCoeHelpContext(KUid3, KHSimList));
			break;
			}
		case EGuardGUIView4Tab:
			{
			ctxs->AppendL(TCoeHelpContext(KUid3, KHProtList));
			break;
			}
		}
	CleanupStack::Pop(ctxs);
	return ctxs;
	}

void CGuardGUIAppUi::ShowLongTextFromFileL(const TDesC& fileName,
		const TDesC& title)
	{
	/* Note: to see privacy statement in emulator, copy
	 PrivacyStatement.txt from group/ directory to
	 %EPOCROOT%\Epoc32\release\winscw\udeb\z\private\E000BD8C
	 Also note that on emulator you can't modify files on Z: drive,
	 so even if you answer Yes to privacy statement, it will popup
	 dialog every time you launch application. But on device it will work
	 as expected.
	 */
	RFs &fs = iCoeEnv->FsSession();
	TFileName fullFileName = fileName;
	FileUtils::CompleteWithPrivatePathL(fs, fullFileName);

#ifdef __WINSCW__
	if (BaflUtils::FileExists(fs, fullFileName))
#endif		
		{
		RBuf text(FileUtils::ReadTextFileL(fs, fullFileName));
		text.CleanupClosePushL();
		CAknMessageQueryDialog *dialog = CAknMessageQueryDialog::NewL(text);
		dialog->PrepareLC(R_LONGTEXT_DIALOG);
		dialog->SetHeaderTextL(title);
		dialog->RunLD();
		CleanupStack::PopAndDestroy(); // text
		}
	}

// End of file


/*
 // Invece di questo dialog verifica esistenza degli MTM IR / OBEX / Email e inserisci le opzioni nel menu'...
 TUid CGuardGUIAppUi::AskMtmL()
 {
 CSendUi & sendUi = *CSendUi::NewLC() ;
 CArrayFixFlat<TUid> * dimmedMtms = new (ELeave) CArrayFixFlat<TUid>(2) ;
 CleanupStack::PushL(dimmedMtms) ;
 // you cannot send sis via MMS :(
 dimmedMtms->AppendL(TUid::Uid(KSenduiMtmMmsUidValue)) ;
 // OBEX + EMail
 TUid mtmUid = sendUi.ShowSendQueryL(NULL, TSendingCapabilities(0, 10000000, TSendingCapabilities::ESupportsAttachments), dimmedMtms);
 CleanupStack::PopAndDestroy(dimmedMtms) ;
 CleanupStack::PopAndDestroy(&sendUi) ;
 return mtmUid;
 }


 TBool CGuardGUIAppUi::SendFileViaSendUiL(const TDesC& filename)
 {
 TSendingCapabilities capabs( 0, 1024, TSendingCapabilities::ESupportsAttachments );

 RFs &fs= iCoeEnv->FsSession();

 TInt error( KErrNone );

 RFile temp;
 User::LeaveIfError( temp.Open( fs, filename, EFileShareReadersOnly | EFileRead ) );
 CleanupClosePushL(temp);

 CMessageData* messageData = CMessageData::NewL();
 CleanupStack::PushL(messageData);
 messageData->AppendAttachmentHandleL(temp);

 CSendUi* sendUi = CSendUi::NewLC();
 TRAPD(err, sendUi->ShowQueryAndSendL(messageData, capabs) );
 CleanupStack::PopAndDestroy(sendUi);
 TBool ris = (err == KErrNone);

 CleanupStack::PopAndDestroy(messageData);

 CleanupStack::PopAndDestroy(&temp);
 }
 // End of File



 // DOESN'T WORK ON N95 (3rd FP1)
 void CGuardGUIAppUi::SendFileUsingMtmL(TUid mtm, const TDesC& filename)
 {
 RSendAs sendas;

 // Connecting to the SendAs server
 User::LeaveIfError( sendas.Connect() );
 CleanupClosePushL(sendas);

 RSendAsMessage message;

 // Selecting the appropriate Bluetooth MTM / Infrared MTM UID
 TRAPD(res, message.CreateL(sendas, mtm));
 User::LeaveIfError(res);
 CleanupClosePushL(message);

 // Constructing the message
 TRequestStatus status;

 message.AddAttachment(filename, status);
 User::WaitForRequest(status);
 User::LeaveIfError( status.Int() );
 CleanupStack::Pop(1); // RMessage

 // Launch the dialog allowing us to choose a receiver
 // device and send the file
 TRAP(res, message.LaunchEditorAndCloseL());
 User::LeaveIfError(res);

 CleanupStack::PopAndDestroy(1); // RSendAs
 }*/

