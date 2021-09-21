/*
============================================================================
 Name        : CAboutContainer from GuardGUIContainer.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Container control implementation
============================================================================
*/

#include "AboutContainer.h"
#include "GuardSvg_200131CC.mbg"
#include "GuardGUIAppUi.h"

// INCLUDE FILES
#include <akniconutils.h> 
#include <eiklabel.h>  // for example label control
#include <lbs.h>  // for example label control
#include <akndef.H>
#include <eikdef.h>
#include <EIKENV.H>
#include <EIKAPPUI.H> 
#include <EIKAPP.H>


// ================= MEMBER FUNCTIONS =======================

//const TInt KMyIconMaxWidth(150);
//const TInt KMyIconMaxHeight(150);

//#ifdef __WINS__
//	_LIT(KImgLocation,"z:\\system\\apps\\Guardian2\\Guardian2.mbm");
//#else
//	_LIT(KMifFile,"\\resouce\\apps\\GuardSvg_20000BD8C.mif");
//#endif

// ---------------------------------------------------------
// CAboutContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CAboutContainer::ConstructL(MAboutObserver& aObserver, const TRect& aRect, TInt val)
	{
	iObserver = &aObserver;
	CreateWindowL();

	// CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);

	SetTypeSignatureL(val);

	/*
	if (iMyIcon) 
	{
		AknIconUtils::SetSize(iMyIcon, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		AknIconUtils::SetSize(iMyIconMask, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
	}*/

	_LIT(KMbmFile,"\\resource\\apps\\GuardSvg_200131CC.mbm");
    TParsePtrC parse((CEikonEnv::Static()->EikAppUi()->Application())->AppFullName());
	TFileName filePath;
	filePath = parse.Drive();
	filePath.Append(KMbmFile);

	iBackBitmap = AknIconUtils::CreateIconL(filePath, EMbmGuardsvg_200131ccSplashfull);			
	if (iBackBitmap)
		{
		CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);
		TSize scrSize = iPixRot.iPixelSize;

		TInt max = scrSize.iWidth;
		if (scrSize.iHeight > max)
			max = scrSize.iHeight;
		AknIconUtils::SetSize(iBackBitmap, TSize(max, max), EAspectRatioPreserved);
		}		
	
// ****************** ICONA

	SetRect(aRect);
	ActivateL();
	}


void CAboutContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
    // Remember to call base class implementation
    CCoeControl::HandlePointerEventL(aPointerEvent);
    
/*  	if (aPointerEvent.iType == TPointerEvent::ESwitchOn)
   	{
	if (iObserver)
		iObserver->HandleCentralKeyEventL();
    }*/
  	if (aPointerEvent.iType == TPointerEvent::EButton1Up)
   	{
	if (iObserver)
		iObserver->HandleCentralKeyEventL();
/*		ChangeApplicationStatusL( GetSelectedUidL() );
		TBool checked = IsSelectedMarkedL();
		iObserver->HandleItemChangeEventL( GetSelectedUidL() , checked);    */
    }
  	// Your additional code here
    // ...	
	}


TKeyResponse CAboutContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
    if ( aType != EEventKey )
        return EKeyWasNotConsumed;
    	switch ( aKeyEvent.iCode )
		{	case EKeyDevice3:	// Da gestire in maniera differente perche' di default viene mostrato il menu' delle opzioni
			{
			//CEikonEnv::Static()->AppUiFactory()->MenuBar()->TryDisplayMenuBarL();
			if (iObserver)
				iObserver->HandleCentralKeyEventL();
			return EKeyWasConsumed;
			}
		default:
			break;
		}
	return EKeyWasNotConsumed;
	}



void CAboutContainer::SetTypeSignatureL(TInt type) 
{
	_LIT(KMifFile,"\\resource\\apps\\GuardSvg_200131CC.mif");
    TParsePtrC parse((CEikonEnv::Static()->EikAppUi()->Application())->AppFullName());
	TFileName filePath;
	filePath.Append(parse.Drive());
	filePath.Append(KMifFile);/**/

	if (iScritta)
		delete iScritta;
	if (iScrittaMask)
		delete iScrittaMask;

	switch (type)
	{
	case 0:
		AknIconUtils::CreateIconL(iScritta, iScrittaMask, filePath, EMbmGuardsvg_200131ccInternofree, EMbmGuardsvg_200131ccInternofree_mask);
		break;
	case 1:
		AknIconUtils::CreateIconL(iScritta, iScrittaMask, filePath, EMbmGuardsvg_200131ccInternogold, EMbmGuardsvg_200131ccInternogold_mask);
		break;
	case 2:
//		AknIconUtils::CreateIconL(iScritta, iScrittaMask, filePath, EMbmGuardsvg_200131ccInternoiridium, EMbmGuardsvg_200131ccInternoiridium_mask);
		AknIconUtils::CreateIconL(iScritta, iScrittaMask, filePath, EMbmGuardsvg_200131ccInternoplatinum, EMbmGuardsvg_200131ccInternoplatinum_mask);
		break;
	case 3:
		AknIconUtils::CreateIconL(iScritta, iScrittaMask, filePath, EMbmGuardsvg_200131ccInternoiridium, EMbmGuardsvg_200131ccInternoiridium_mask);
		break;
	}

	if (iScritta)
	{
		AknIconUtils::SetSize(iScritta, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		AknIconUtils::SetSize(iScrittaMask, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
	}
}


// Destructor
CAboutContainer::~CAboutContainer()
	{
	if (iBackBitmap) 
		delete iBackBitmap;
	if (iScritta)
		delete iScritta;
	if (iScrittaMask)
		delete iScrittaMask;
	}

// ---------------------------------------------------------
// CAboutContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CAboutContainer::SizeChanged()
	{
/*	CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(iPixRot);
	TSize scrSize = iPixRot.iPixelSize;
    TInt w = scrSize.iWidth;
    TInt h = scrSize.iHeight;

	// Add here control resize code etc.
	iLabel->SetExtent( TPoint(10,10), iLabel->MinimumSize() );
	iToDoLabel->SetExtent( TPoint(10,150), iToDoLabel->MinimumSize() );*/

/*	if (iMyIcon) 
		{
		AknIconUtils::SetSize(iMyIcon, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		AknIconUtils::SetSize(iMyIconMask, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		}*/
	if (iScritta)
		{
		AknIconUtils::SetSize(iScritta, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
		AknIconUtils::SetSize(iScrittaMask, iSize, EAspectRatioPreservedAndUnusedSpaceRemoved);
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
	}

// ---------------------------------------------------------
// CAboutContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CAboutContainer::CountComponentControls() const
	{
	return 0; // return nbr of controls inside this container
	}

// ---------------------------------------------------------
// CAboutContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CAboutContainer::ComponentControl(TInt aIndex) const
	{
	return NULL;
/*	switch ( aIndex )
		{
		case 0:
			return iLabel;
		case 1:
			return iToDoLabel;
		default:
			return NULL;
		}*/
	}

// ---------------------------------------------------------
// CAboutContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CAboutContainer::Draw(const TRect& aRect) const
{
//	TInt w = aRect.Width();
//	TInt h = aRect.Height();
	CWindowGc& gc = SystemGc();

/*	gc.SetPenStyle( CGraphicsContext::ENullPen );
	gc.SetBrushColor( KRgbWhite );
	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	gc.DrawRect( aRect );*/

/*		TSize bmpSize = iScritta->SizeInPixels();
		TInt x = (scrSize.iWidth - bmpSize.iWidth)/2;   // sch320 imm200 ... 
		TInt y = (scrSize.iHeight - bmpSize.iHeight)/2;
		gc.BitBltMasked(TPoint(x, y), iScritta, bmpSize, iScrittaMask, ETrue);*/

	if (iBackBitmap)
		{
		// Crops iBackBitmap
		// First retrieve current size of the bitmap... it is a square currSize x currSize		
		TRect scrSize = iPixRot.iPixelSize;
		TInt currSize = scrSize.Width();
		if (scrSize.Height() > currSize)
			currSize = scrSize.Height();
				
		TRect mainPaneRect;
		AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, mainPaneRect);
 
		TInt offsetX = (currSize - scrSize.Width()) / 2 + mainPaneRect.iTl.iX;
		TInt offsetY = (currSize - scrSize.Height()) / 2 + mainPaneRect.iTl.iY;
			    
	    TRect sourceRect(TPoint(offsetX, offsetY), mainPaneRect.Size());
		gc.BitBlt(TPoint(0, 0), iBackBitmap, sourceRect);
		//gc.DrawBitmap(iSize, iBackBitmap, sourceRect);
		// Crop iBackBitmap 
		}
	
	if (iScritta)
	{  
		TSize scrSize = iSize;
		TSize bmpSize = iScritta->SizeInPixels();
		TInt x = (scrSize.iWidth - bmpSize.iWidth)/2;   // sch320 imm200 ... 
		TInt y = (scrSize.iHeight - bmpSize.iHeight)/2;
		gc.BitBltMasked(TPoint(x, y), iScritta, bmpSize, iScrittaMask, ETrue);/**/
	}
/*	if (iMyIcon)
	{
		TSize scrSize = iSize;
		TSize bmpSize = iMyIcon->SizeInPixels();
		TInt x = (scrSize.iWidth - bmpSize.iWidth)/2;   // sch320 imm200 ... 
		TInt y = (scrSize.iHeight - bmpSize.iHeight)/2;
		gc.BitBltMasked(TPoint(x, y), iMyIcon, bmpSize, iMyIconMask, ETrue);
	}*/
}

// ---------------------------------------------------------
// CAboutContainer::HandleControlEventL(
//    CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CAboutContainer::HandleControlEventL(
	CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
	{
	}
