/*
* ==============================================================================
*  Name        : Pinview.cpp
*  Part of     : Helloworldbasic
*  Interface   :
*  Description :
*  Version     :
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation.
* ==============================================================================
*/

#include "PinView.h"
//#include "..\..\S60_GuardGUI\inc\GuardSvg_200131CC.mbg"

#include <coemain.h>
#include <aknsutils.h>  
#include <aknutils.h>
#include <aknsdrawutils.h> 
#include <aknsbasicbackgroundcontrolcontext.h> 
// #include <FuzzyByte\GuiUtils.h>

// ============================ MEMBER FUNCTIONS ===============================

#define PEN_ENABLED_ORDINAL_WINS 3184
#define PEN_ENABLED_ORDINAL_ARM 4251

LOCAL_C TBool IsTouchSupportedL()
{
	TBool isPenEnabled = EFalse;

	RLibrary avkonDll;
	if ( avkonDll.Load( _L( "avkon.dll" ) ) != KErrNone)
		return EFalse;

	#ifdef __WINSCW__
	TLibraryFunction PenEnabled = avkonDll.Lookup( 3184 );
	#else
	TLibraryFunction PenEnabled = avkonDll.Lookup( 4251 );
	#endif

	if ( PenEnabled != NULL )
		isPenEnabled = PenEnabled();

	avkonDll.Close();
	return isPenEnabled;
}

// -----------------------------------------------------------------------------
// CPinView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPinView* CPinView::NewL(MAsyncQueryObserver* aObserver)
    {
    CPinView* self = CPinView::NewLC(aObserver);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CPinView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPinView* CPinView::NewLC(MAsyncQueryObserver* aObserver)
    {
    CPinView* self = new ( ELeave ) CPinView(aObserver);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CPinView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPinView::ConstructL()
    {
	iIsTouch = IsTouchSupportedL();
/*	TPixelsTwipsAndRotation pixRot;
	CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(pixRot);
	TSize scrSize = pixRot.iPixelSize;*/
	TRect scrSize = calculateFullscreenRect();
	
/*
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	CAknsItemData* item = skin->GetCachedItemData(KAknsIIDQsnBgAreaControl);
	if(item==NULL)
		{
		item = skin->CreateUncachedItemDataL(KAknsIIDQsnBgAreaControl);
		}
	if(item->Type()==EAknsITMaskedBitmap)
		{
		CAknsItemDef* def = AknsUtils::CreateMaskedBitmapItemDefL(KAknsIIDQsnBgAreaControl, KMbmFile, EMbmIndianeyeStatusskin, EMbmIndianeyeStatusskin);
		skin->SetLocalItemDefL(def);
		}
	else
		{
		CAknsItemDef* def = AknsUtils::CreateBitmapItemDefL(KAknsIIDQsnBgAreaControl, KMbmFile, EMbmIndianeyeStatusskin);
		skin->SetLocalItemDefL(def);
		}
*/

/*    MAknsSkinInstance* skin = AknsUtils::SkinInstance();    
    if (skin)
    	{
    	_LIT(KMbmFile,"z:\\resource\\apps\\GuardSvg_200131CC.mbm");
		CAknsItemDef * itemCBA = AknsUtils::CreateBitmapItemDefL(KAknsIIDQsnBgAreaControl, KMbmFile, EMbmGuardsvg_200131ccSplash);
		if (itemCBA)
			{
			  TRAPD(err_skin, skin->SetLocalItemDefL( itemCBA ) );
			  // use err_skin here to check the result of operation
			}
		CAknsItemDef * itemBack = AknsUtils::CreateBitmapItemDefL(KAknsIIDQsnBgScreen, KMbmFile, EMbmGuardsvg_200131ccSplash);
		if (itemBack)
			{
			  TRAPD(err_skin, skin->SetLocalItemDefL( itemBack ) );
			  // use err_skin here to check the result of operation
			}
    	}*/

    // Create a window for this application view
    CreateWindowL();
    Window().SetNonFading(ETrue);

    SetRect( scrSize );

    
/*	_LIT(KMbmFile,"z:\\resource\\apps\\GuardSvg_200131CC.mbm");
	static const TAknsItemID KMyItemID = { 0x200131CC, 0x1000 };
    	
    	MAknsSkinInstance* pSkin = AknsUtils::SkinInstance();
    	const TAknsItemID elementID = KMyItemID;
    	CAknsItemDef* itemCBA = AknsUtils::CreateBitmapItemDefL( elementID, KMbmFile, EMbmGuardsvg_200131ccSplash);
    	if ( itemCBA )
    	  {
    	  TRAPD( err_skin, pSkin->SetLocalItemDefL( itemCBA) );
    	  }/**/
    	
//	static const TAknsItemID KMyItemID = { 0x200131CC, 0x1000 };
//	iBack = CAknsBasicBackgroundControlContext::NewL(KMyItemID, Rect(), EFalse);

 	iBack = CAknsBasicBackgroundControlContext::NewL(KAknsIIDQsnBgScreen, Rect(), EFalse);//KAknsIIDQsnBgScreenIdle
	// Activate the window, which makes it ready to be drawn


    ActivateL();
    }


void CPinView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
    CCoeControl::HandlePointerEventL(aPointerEvent);
    
    if (aPointerEvent.iType != TPointerEvent::EButton1Down)
    	return;
    if (aPointerEvent.iPosition.iX < 100 || aPointerEvent.iPosition.iY < 100)
    	return;
    
//	iObserver->DialogClosedL(ETrue, _L("12345"));
	}


TRect CPinView::calculateFullscreenRect()
{
/*		TPixelsTwipsAndRotation pixRot;
		CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(pixRot);
		TSize scrSize = pixRot.iPixelSize;*/

   // Window that fills the entire screen
   TRect fullRect;
   AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, fullRect);
 
   //if (!iIsTouch)
	   return fullRect;
   
   // Rect that occupied by control pane (i.e. CBA)
   TRect cba_rect;
   AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane, cba_rect);
 
   // Calculate final rect which depends on CBA location
   AknLayoutUtils::TAknCbaLocation cba_location = AknLayoutUtils::CbaLocation();
 
   switch(cba_location) {
      case AknLayoutUtils::EAknCbaLocationBottom:
    	  fullRect.iBr.iY -= cba_rect.Height();
      break;
 
      case AknLayoutUtils::EAknCbaLocationLeft:
    	  fullRect.iTl.iX += cba_rect.Width();
      break;
 
      case AknLayoutUtils::EAknCbaLocationRight:
    	  fullRect.iBr.iX -= cba_rect.Width();
      break;
 
      default:
      break;
   }
   return fullRect;
}


// -----------------------------------------------------------------------------
// CPinView::CPinView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPinView::CPinView(MAsyncQueryObserver* aObserver) : iObserver(aObserver)
    {
    // No implementation required
    }


// -----------------------------------------------------------------------------
// CPinView::~CPinView()
// Destructor.
// -----------------------------------------------------------------------------
//
CPinView::~CPinView()
    {
	if (iBack)
		delete iBack;
    // No implementation required
    }


TTypeUid::Ptr CPinView::MopSupplyObject(TTypeUid aId)
    {
    if (aId.iUid == MAknsControlContext::ETypeId)
        {
// TODO: Forse da sistemare cosi'...
//    	if (iBack == NULL)
//        	return TTypeUid::Null();
        return MAknsControlContext::SupplyMopObject( aId, iBack );
        }

    return CCoeControl::MopSupplyObject(aId);
    }


// -----------------------------------------------------------------------------
// CPinView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CPinView::Draw( const TRect& aRect ) const
    {
    // note that the whole screen is drawn everytime, so aRect-parameter
    // is ignored

    // Get the standard graphics context
   	CWindowGc& gc = SystemGc();

	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* context = AknsDrawUtils::ControlContext(this);

	// Determina l'area da disegnare...
    AknsDrawUtils::Background(skin, context, this, gc, iSize);
}

 

void CPinView::HandleResourceChange(TInt aType)
    {	
	CCoeControl::HandleResourceChange(aType);
    	// Set the windows size

	if ( aType==KEikDynamicLayoutVariantSwitch )
		{
			/*TPixelsTwipsAndRotation pixRot;
			CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(pixRot);
			TSize scrSize = pixRot.iPixelSize;*/			

/*			TPixelsTwipsAndRotation pixRot;
			CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(pixRot);
			TSize scrSize = pixRot.iPixelSize;
			TRect scrSize = iPixRot.iPixelSize;
			TInt currSize = scrSize.Width();
			if (scrSize.Height() > currSize)
				currSize = scrSize.Height(); 
					
			TRect mainPaneRect;
			AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, mainPaneRect);

			TInt offsetX = (currSize - scrSize.Width()) / 2 + mainPaneRect.iTl.iX;
			TInt offsetY = (currSize - scrSize.Height()) / 2 + mainPaneRect.iTl.iY;
				    
		    TRect sourceRect(TPoint(offsetX, offsetY), mainPaneRect.Size());
		    AknsUtils::RegisterControlPosition()*/
		    
			TRect rect = calculateFullscreenRect();
/*			TRect rect;
	        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, rect );*/
			        
/*			if (iBack)
				delete iBack;
		 	iBack = CAknsBasicBackgroundControlContext::NewL(KAknsIIDQsnBgScreen, rect, EFalse);/**/
			if (iBack)
				iBack->SetRect(rect);
			SetRect(rect);
		}
    }


