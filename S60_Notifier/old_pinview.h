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

#ifndef __PinVIEW_H__
#define __PinVIEW_H__

// INCLUDES
#include <coecntrl.h>

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
        static CPinView* NewL();

        /**
        * NewLC.
        * Two-phased constructor.
        * Create a CPinView object, which will draw itself
        * to aRect.
        * @param aRect Rectangle this view will be drawn to.
        * @return A pointer to the created instance of CPinView.
        */
        static CPinView* NewLC();

        /**
        * ~CPinView
        * Virtual Destructor.
        */
        virtual ~CPinView();

    public:  // Functions from base classes

        /**
        * From CCoeControl, Draw
        * Draw this CPinView to the screen.
        * If the user has given a text, it is also printed to the center of
        * the screen.
        * @param aRect the rectangle of this view that needs updating
        */
        void Draw( const TRect& aRect ) const;

        /**
        * From CoeControl, SizeChanged.
        * Called by framework when the view size is changed.
        */
        virtual void SizeChanged();

    private: // Constructors

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
        CPinView();
    };

#endif // __PinVIEW_H__

// End of File

