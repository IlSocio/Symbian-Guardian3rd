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
#include <aknview.h>
#include <FuzzyByte\TimeOutTimer.h>


// CONSTANTS
// UID of view
 
// FORWARD DECLARATIONS
class CSplashContainer;

// CLASS DECLARATION

/**
*  CSplashView view class.
* 
*/
class CSplashView : public CAknView, MTimeOutNotifier
    {
    public: // Constructors and destructor

        static CSplashView* NewL(TTimeIntervalSeconds invervalSec);
        static CSplashView* NewLC(TTimeIntervalSeconds invervalSec);
        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        ~CSplashView();

    public: // Functions from base classes
        
        /**
        * From CAknView returns Uid of View
        * @return TUid uid of the view
        */
        TUid Id() const;

        /**
        * From MEikMenuObserver delegate commands from the menu
        * @param aCommand a command emitted by the menu 
        * @return void
        */
        void HandleCommandL(TInt aCommand);

        /**
        * From CAknView reaction if size change
        * @return void
        */
        void HandleClientRectChange();

    private:
        virtual void TimerExpiredL(TAny* src);
        
    private:
        CSplashView(TTimeIntervalSeconds invervalSec);
        
        /**
        * From CAknView activate the view
        * @param aPrevViewId 
        * @param aCustomMessageId 
        * @param aCustomMessage 
        * @return void
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
            const TDesC8& aCustomMessage);

        /**
        * From CAknView deactivate the view (free resources)
        * @return void
        */
        void DoDeactivate();

    private: // Data
        CSplashContainer* iContainer;
        TTimeIntervalSeconds iIntervalSec;
        CTimeOutTimer* iTimer;
    };

#endif

// End of File
