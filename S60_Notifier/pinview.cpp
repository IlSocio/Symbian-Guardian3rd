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

// INCLUDE FILES
#include <coemain.h>
#include <aknutils.h>
#include "PinView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CPinView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPinView* CPinView::NewL()
    {
    CPinView* self = CPinView::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CPinView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPinView* CPinView::NewLC()
    {
    CPinView* self = new ( ELeave ) CPinView;
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
	TPixelsTwipsAndRotation pixRot;
	CCoeEnv::Static()->ScreenDevice()->GetDefaultScreenSizeAndRotation(pixRot);
	TSize scrSize = pixRot.iPixelSize;

    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( scrSize );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CPinView::CPinView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPinView::CPinView()
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
    // No implementation required
    }


// -----------------------------------------------------------------------------
// CPinView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CPinView::Draw( const TRect& /*aRect*/ ) const
    {
    // note that the whole screen is drawn everytime, so aRect-parameter
    // is ignored

    // Get the standard graphics context
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbWhite);
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );

    // Gets the control's extent
    TRect rect( Rect());
    gc.Clear( rect );
    }

// -----------------------------------------------------------------------------
// CPinView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CPinView::SizeChanged()
    {
    // @note is this right?
    // DrawNow();
    }


