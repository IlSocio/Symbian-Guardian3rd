/*
============================================================================
 Name        : CSplashContainer from SplashContainer.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CSplashContainer implementation
============================================================================
*/

// INCLUDE FILES
#include "SplashContainer.h"
#include "GuardSvg_200131CC.mbg" // Contiene i numeri delle icone di Guardian2.mbm

#include <FuzzyByte\FileUtils.h>

#include <AknLists.h>
#include <barsread.h> 
#include <eiklabel.h>  // for example label control
#include <EIKENV.H>
#include <EIKAPPUI.H> 
#include <EIKAPP.H>


//#ifdef __WINS__
//	_LIT(KImgLocation,"z:\\system\\apps\\Guardian2\\Guardian2.mbm");
//#else
//	_LIT(KImgLocation,"\\resouce\\apps\\GuardSvg_20000BD8C.mif");
//#endif


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSplashContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CSplashContainer::ConstructL(const TRect& aRect)
    {
	__LOG_OPEN("Guardian", "GUI_SplashCont.txt");
    CreateWindowL();
	CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);
//	SetExtentToWholeScreen();     
	__LOG("PixRot: %d %d", iPixRot.iPixelSize.iWidth, iPixRot.iPixelSize.iHeight); // 360 x 640
	__LOG("iSize: %d %d", iSize.iWidth, iSize.iHeight );

	__LOG_TXT("GetMifFilePath");
	_LIT(KMifFile,"\\resource\\apps\\GuardSvg_200131CC.mif");
	TFileName filePath;
	
//    TParsePtrC parse((CEikonEnv::Static()->EikAppUi()->Application())->AppFullName());
//	filePath.Append(parse.Drive());
	filePath = KMifFile;
	FileUtils::CompleteWithCurrentDrive(filePath);
	__LOG_DES(filePath);

/*	if (iPixRot.iPixelSize.iWidth != 360 || iPixRot.iPixelSize.iHeight != 640 )
		{
		}*/
	AknIconUtils::CreateIconL(iEye, iEyeMask, filePath, EMbmGuardsvg_200131ccSplash, EMbmGuardsvg_200131ccSplash_mask);
	if (iEye)
		{
		AknIconUtils::SetSize(iEye, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		AknIconUtils::SetSize(iEyeMask, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		}

	__LOG_TXT("GetMbmFilePath");
	_LIT(KMbmFile,"\\resource\\apps\\GuardSvg_200131CC.mbm");
//	filePath = parse.Drive();
	filePath = KMbmFile;
	FileUtils::CompleteWithCurrentDrive(filePath);
	__LOG_DES(filePath);

	iBackBitmap = AknIconUtils::CreateIconL(filePath, EMbmGuardsvg_200131ccSplashfull);
	if (iBackBitmap)
		{
		CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);
		TSize scrSize = iPixRot.iPixelSize;

		TInt max = scrSize.iWidth;
		if (scrSize.iHeight > max)
			max = scrSize.iHeight;
		AknIconUtils::SetSize(iBackBitmap, iSize, EAspectRatioPreserved);
		}
	
//	if (iBackBitmap)
//		AknIconUtils::SetSize(iBackBitmap, iSize, EAspectRatioNotPreserved);/**/
	if (iSplashBitmap)
		AknIconUtils::SetSize(iSplashBitmap, iSize, EAspectRatioPreserved);/**/

	
/*	static const TAknsItemID KMyItemID = { 0x200131CC, 0x1000 };
	
	MAknsSkinInstance* pSkin = AknsUtils::SkinInstance();
	const TAknsItemID elementID = KMyItemID;
	CAknsItemDef* itemCBA = AknsUtils::CreateBitmapItemDefL( elementID, filePath, EMbmGuardsvg_200131ccSplash);
	if ( itemCBA )
	  {
	  TRAPD( err_skin, pSkin->SetLocalItemDefL( itemCBA) );
	  }*/
	 
	
	__LOG_TXT("CreatedIcon");
    SetRect(aRect);
    ActivateL();
    }


void CSplashContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
    // Remember to call base class implementation
    CCoeControl::HandlePointerEventL(aPointerEvent);
    
    // Your additional code here
    // ...	
	}


// Destructor
CSplashContainer::~CSplashContainer()
    {
	__LOG_TXT("Destructor");
	if (iBackBitmap) 
		delete iBackBitmap;
	if (iSplashBitmap) 
		delete iSplashBitmap;
	if (iEye) 
	{
		delete iEye;
		iEye = NULL;
	}
	if (iEyeMask) 
		delete iEyeMask;
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
    }

// ---------------------------------------------------------
// CSplashContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CSplashContainer::SizeChanged()
    {
	CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);
    // TSize scrSize = iPixRot.iPixelSize;
    // TInt w = scrSize.iWidth;
    // TInt h = scrSize.iHeight;
	if (iEye) 
		{
		AknIconUtils::SetSize(iEye, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		AknIconUtils::SetSize(iEyeMask, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		}
	
	if (iBackBitmap)
		{
		CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);
		TSize scrSize = iPixRot.iPixelSize;

		TInt max = scrSize.iWidth;
		if (scrSize.iHeight > max)
			max = scrSize.iHeight;
		AknIconUtils::SetSize(iBackBitmap, TSize(max, max), EAspectRatioPreserved);
		}
//	if (iBackBitmap)
//		AknIconUtils::SetSize(iBackBitmap, iSize, EAspectRatioNotPreserved);
	if (iSplashBitmap)
		AknIconUtils::SetSize(iSplashBitmap, iSize, EAspectRatioPreserved);
    }

// ---------------------------------------------------------
// CSplashContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CSplashContainer::CountComponentControls() const
    {
    return 0;
	}

// ---------------------------------------------------------
// CSplashContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CSplashContainer::ComponentControl(TInt aIndex) const
    {
    return NULL;
    }

// ---------------------------------------------------------
// CSplashContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CSplashContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
/*    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbWhite );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );*/

	if (iSplashBitmap)
		{
		gc.DrawBitmap(iSize, iSplashBitmap);
		return;
		}
	
	if (iBackBitmap)
		{
		// Crops iBackBitmap
		// First retrieve current size of the bitmap... it is a square currSize x currSize
		TRect scrSize = iPixRot.iPixelSize;
		TInt currSize = scrSize.Width();
		if (scrSize.Height() > currSize)
			currSize = scrSize.Height();
		
		TInt offsetX = (currSize - scrSize.Width()) / 2;
		TInt offsetY = (currSize - scrSize.Height()) / 2;
		
		TRect sourceRect(TPoint(offsetX, offsetY), iSize);
		gc.BitBlt(TPoint(0, 0), iBackBitmap, sourceRect);
		// gc.DrawBitmap(iSize, iBackBitmap);
		}

	if (iEye) 
		{
		TSize scrSize = iSize;
		TSize bmpSize = iEye->SizeInPixels();
		TInt x = (scrSize.iWidth - bmpSize.iWidth)/2;   // sch320 imm200 ... 
		TInt y = (scrSize.iHeight - bmpSize.iHeight)/2;
		gc.BitBltMasked(TPoint(x, y), iEye, bmpSize, iEyeMask, ETrue);
		}/**/
    }
 
// ---------------------------------------------------------
// CSplashContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CSplashContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }


// End of File  
