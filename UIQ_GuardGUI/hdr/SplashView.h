/*
============================================================================
 Name        : CSplashView from SplashView.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CSplashView declaration
============================================================================
*/

#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

// INCLUDES
#include <COEVIEW.H>
//#include <aknview.h>
#include "guardguiexternalinterface.h"
#include <QikAppUi.h>
#include <COECNTRL.H> 
#include <QikViewBase.h>
#include <FBS.H>
#include <GULICON.H>

/**
*  CSplashView view class.
* 
*/
// CQikViewBase
class CSplashView : public CQikViewBase
    {
    public: // Constructors and destructor

        static CSplashView* NewLC(CQikAppUi& appUi, const TVwsViewId aParentViewId);
        /**
        * EPOC default constructor.
        */
        void ConstructL();

		CSplashView(CQikAppUi& appUi, const TVwsViewId &aParentViewId);
        /**
        * Destructor.
        */
        ~CSplashView();

    public: // Functions from base classes
		void ViewConstructL();
		void Draw(const TRect& aRect) const;

        /**
        * From CAknView returns Uid of View
        * @return TUid uid of the view
        */
		TVwsViewId ViewId() const;
//        TUid Id() const;

        /**
        * From CAknView reaction if size change
        * @return void
        */
        void HandleClientRectChange();

    private:

        /**
        * From CAknView activate the view
        * @param aPrevViewId 
        * @param aCustomMessageId 
        * @param aCustomMessage 
        * @return void
        */
//        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
//            const TDesC8& aCustomMessage);
		void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
              const TDesC8& aCustomMessage);

        /**
        * From CAknView deactivate the view (free resources)
        * @return void
        */
//        void DoDeactivate();
		void ViewDeactivated();

	private:
		CFbsBitmap* iBitmap;
		CFbsBitmap* iScritta;
		CFbsBitmap* iScrittaMask;
    };

#endif

// End of File
