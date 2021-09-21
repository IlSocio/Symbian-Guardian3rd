/*
* ==============================================================================
*  Name        : Pinview.h
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

#ifndef __PINVIEW_H__
#define __PINVIEW_H__

// INCLUDES
#include <coecntrl.h>
#include <aknscontrolcontext.h>
#include <aknsbasicbackgroundcontrolcontext.h>

#include "..\..\S60_Notifier\inc\AsyncQueryDialog.h"

// CLASS DECLARATION
class CPinView : public CCoeControl
    {
    public: // New methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CPinView object, which will draw itself to aRect.
        * @param aRect The rectangle this view will be drawn to.
        * @return a pointer to the created instance of CPinView.
        */
        static CPinView* NewL(MAsyncQueryObserver* aObserver);

        /**
        * NewLC.
        * Two-phased constructor.
        * Create a CPinView object, which will draw itself
        * to aRect.
        * @param aRect Rectangle this view will be drawn to.
        * @return A pointer to the created instance of CPinView.
        */
        static CPinView* NewLC(MAsyncQueryObserver* aObserver);

        /**
        * ~CPinView
        * Virtual Destructor.
        */
        virtual ~CPinView();

    	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    public:  // Functions from base classes

        /**
        * From CCoeControl, Draw
        * Draw this CPinView to the screen.
        * If the user has given a text, it is also printed to the center of
        * the screen.
        * @param aRect the rectangle of this view that needs updating
        */
        void Draw( const TRect& aRect ) const;

		virtual void HandleResourceChange(TInt aType);

    private: // Constructors
		TRect calculateFullscreenRect();
		
        /**
        * ConstructL
        * 2nd phase constructor.
        * Perform the second phase construction of a
        * CPinView object.
        * @param aRect The rectangle this view will be drawn to.
        */
        void ConstructL();

        /**
        * CPinView.
        * C++ default constructor.
        */
        CPinView(MAsyncQueryObserver* aObserver);

	private:
		CAknsBasicBackgroundControlContext* iBack;
		MAsyncQueryObserver* iObserver;
		TBool iIsTouch;
    };

#endif // __PinVIEW_H__

// End of File

