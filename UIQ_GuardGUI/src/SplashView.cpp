/*
============================================================================
 Name        : CSplashView from SplashView.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CSplashView implementation
============================================================================
*/

// INCLUDE FILES
#include <GuardBMP_200107AF.mbg>
#include  "SplashView.h"
#include <bautils.h>
#include <COEMAIN.H>
#include <COEAUI.H> 
#include <EIKAPPUI.H>


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSplashView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
//
CSplashView::CSplashView(CQikAppUi& appUi, const TVwsViewId &aParentViewId) : CQikViewBase(appUi, aParentViewId)
{
}


CSplashView* CSplashView::NewLC(CQikAppUi& appUi, const TVwsViewId aParentViewId)
    {
    CSplashView* self = new ( ELeave ) CSplashView(appUi, aParentViewId);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CSplashView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSplashView::ConstructL()
    {
	BaseConstructL();
//	CQikViewBase::ConstructL();
	CreateWindowL();
	SetExtentToWholeScreen();
	SetLayoutManagerL(NULL);
	
	TQikViewMode NewMode;
	NewMode.SetAppTitleBar(false);
	NewMode.SetButtonOrSoftkeyBar(false);
	NewMode.SetStatusBar(false);
	NewMode.SetToolbar(false);
	NewMode.SetFullscreen();
	SetViewModeL(NewMode);


	RFs &fs= iCoeEnv->FsSession();
	_LIT(KFileName, "\\resource\\apps\\GuardBMP_200107AF.mbm");
	iBitmap = iEikonEnv->CreateBitmapL(KFileName, EMbmGuardbmp_200107afBackground);
//	iBitmap = iEikonEnv->CreateBitmapL(KFileName, EMbmGuardbmp_200107afBackground);
	iScritta = iEikonEnv->CreateBitmapL(KFileName, EMbmGuardbmp_200107afScritta);
//	iScrittaMask = iEikonEnv->CreateBitmapL(KFileName, EMbmGuardbmp_200107afScritta);
	iScrittaMask = iEikonEnv->CreateBitmapL(KFileName, EMbmGuardbmp_200107afScritta_mask);
	}


void CSplashView::ViewConstructL()
	{
	}


CSplashView::~CSplashView()
    {
	if (iBitmap) delete iBitmap;
	if (iScritta) delete iScritta;
	if (iScrittaMask) delete iScrittaMask;
    }

TVwsViewId CSplashView::ViewId() const
    {
	return TVwsViewId(KUidGuardGUIApp, KUidSplashView);
    }


// ---------------------------------------------------------
// CSplashView::HandleClientRectChange()
// ---------------------------------------------------------
//
void CSplashView::HandleClientRectChange()
    {
    }


	void CSplashView::ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
              const TDesC8& aCustomMessage)
   {
   }


void CSplashView::ViewDeactivated()
    {
    }


void CSplashView::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    // TODO: Add your drawing code here
    // example code...
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbRed );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
	if (iBitmap)
		gc.DrawBitmap(iSize, iBitmap);
	if (iScritta)
	{
		// Se InvertedMask = EFalse saranno trasferiti i pixel che hanno il nero nella mask 
		// Se la bitmap e' > di 256 viene ignorato e fa AplhaBlending 
//		gc.DrawBitmapMasked(iSize, iScritta, iScritta->SizeInPixels(), iScrittaMask, ETrue);

		TSize scrSize = iSize;
		TSize bmpSize = iScritta->SizeInPixels();
		TInt x = (scrSize.iWidth - bmpSize.iWidth)/2;   // sch320 imm200 ... 
		TInt y = (scrSize.iHeight - bmpSize.iHeight)/2;
//		gc.BitBltMasked(TPoint(x, y), iScritta, bmpSize, iScrittaMask, EFalse);
		TRect testR(TPoint(x, y), TSize(bmpSize.iWidth, bmpSize.iHeight));
		gc.DrawBitmapMasked(testR, iScritta, bmpSize, iScrittaMask, ETrue);
	}

    }

