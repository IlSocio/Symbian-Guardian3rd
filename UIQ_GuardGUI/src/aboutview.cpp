

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 
#include <GULICON.H>
#include "NumericDialog.h"
#include "settings_consts.h"
#include "aboutview.h"
#include "guardguiExternalInterface.h"
#include "client.h"

#include <GuardGUI_200107AF.rsg>
#include <GuardBMP_200107AF.mbg>
#include "settview.hrh"
#include "guardguiappui.h"
#include "common.hrh"
#include "infodialog.h"


CAboutView* CAboutView::NewLC(CQikAppUi& aAppUi, const TVwsViewId aParentViewId)
	{
	CAboutView* self = new (ELeave) CAboutView(aAppUi, aParentViewId);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CAboutView::CAboutView(CQikAppUi& aAppUi,const TVwsViewId aParentViewId) 
: CQikViewBase(aAppUi, aParentViewId)
	{
	}

void CAboutView::ConstructL()
	{
	BaseConstructL();
	iTimer = CTimeOutTimer::NewL( *this );
// TODO:	TBool iHasBT = CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdBt);
// TODO:	TBool iHasIR = CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdIrda);
	
	RFs &fs= iCoeEnv->FsSession();
	_LIT(KFileName, "\\resource\\apps\\GuardBMP_200107AF.mbm");
	iBitmap = iEikonEnv->CreateBitmapL(KFileName, EMbmGuardbmp_200107afBackground2);
	

	/* TODO:
	// Mese * 30 + Giorno
	CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
 	if (!appui->iIsRegistered)
		{
		iForceUpdate = UpdateLock::NeedsUpdateL();
		}

 	HBufC* sisFile = iEikonEnv->AllocReadResourceLC( R_GUARDIAN_SISX );
	iFileRedist = Utils::CompleteWithPrivatePathL( iEikonEnv->FsSession(), sisFile->Des());
	CleanupStack::PopAndDestroy(sisFile);
	
 	if (Utils::GetFileSize( iEikonEnv->FsSession(), KFileTmpInst ) > 0)
 		{
 		BaflUtils::RenameFile( iEikonEnv->FsSession(), KFileTmpInst, iFileRedist->Des() );
 		}
 	*/
 	}

CAboutView::~CAboutView()
	{	
	if (iBitmap) 
		delete iBitmap;
	if (iTimer)
		delete iTimer;
	}


void CAboutView::ViewConstructL()
	{
       ViewConstructFromResourceL(R_INFO_VIEW_UI_CONFIGURATIONS);

	   CGulIcon* myIcon = NULL;
       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afAbout, EMbmGuardbmp_200107afAbout_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(1, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();

       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afSettings, EMbmGuardbmp_200107afSettings_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(2, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();

       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afSim, EMbmGuardbmp_200107afSim_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(3, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();

       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afSim, EMbmGuardbmp_200107afSim_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(4, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();
	   
       CQikCommandManager& man = CQikCommandManager::Static(*iEikonEnv);
       man.InsertIntoCommandListL(*this, *this, R_COMMON_COMMANDS);
	}


void CAboutView::ViewActivatedL(const TVwsViewId &aPrevViewId,
							  const TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage)
	{
	if (this->ActiveTabId()!= 1)
		ActivateTabL(1);
	SetAppTitleNameL(_L("Info"));
	if (iTimer && !iTimer->IsActive()) 
		{
		// Mostra il Messaggio SIM Registrata dopo 1 secondo...
		TTimeIntervalMicroSeconds32 timeout(1000000 * 1);
		iTimer->After(timeout);
		}
	}


void CAboutView::TimerExpiredL(TAny* src)
	{
		TImsiName sim_name;
		// Se la sim non e' ancora registrata allora la registra...
		// Se invece e' gia' registrata la sposta in alto nella lista...
		RGuardian guard;
		User::LeaveIfError( guard.Connect() );
		CleanupClosePushL(guard);
		if (guard.RegisterSim(sim_name) == KErrNone) 
			{
			TBuf<200> buff;
//			iCoeEnv->ReadResource( buff, R_SIM_ADDED );
			buff = _L("This SIM has been Registered using name:");
			buff.Append(TChar('"'));
			buff.Append( sim_name );
			buff.Append(TChar('"'));
			// TODO: Messaggio Informativo Sim Aggiunta... OK!
			// CAknQueryDialog* dlg = CAknQueryDialog::NewL();
			// dlg->ExecuteLD(R_QUERY_SIM_ADDED, buff);
			}
		CleanupStack::PopAndDestroy(); // Guard

		delete iTimer;
		iTimer = NULL;
	}


void CAboutView::TabActivatedL(TInt aTabId)
	{
	if (aTabId == 1) return;
	CGuardGUIAppUi& appUi = (CGuardGUIAppUi &) iQikAppUi;
	appUi.MainTabActivatedL(aTabId);	
	}


TVwsViewId CAboutView::ViewId()const
	{
	return TVwsViewId(KUidGuardGUIApp, KUidAboutView);
	}


void CAboutView::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
/*      case EInfoViewSettings:
    	 {
		 CGuardGUIAppUi& appUi = (CGuardGUIAppUi &) iQikAppUi;
		 appUi.MainTabActivatedL(2);
		break;
    	 }*/
      default:
         CQikViewBase::HandleCommandL(aCommand);
         break;
      }
   }


void CAboutView::Draw(const TRect &aRect) const
	{
    CWindowGc& gc = SystemGc();
//	TPoint p1 = PositionRelativeToScreen();
//	TPoint p2 = Position();
//	TRect r1 = Rect();
//	TRect r2 = ClientRect();
//	TRect r3 = ApplicationRect();
//	TSize s1 = MinimumSize();
//	TSize s2 = Size();
/*    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );*/
	// Disegna immagine di sfondo...
	if (iBitmap)
		gc.DrawBitmap(iSize, iBitmap);
	}

