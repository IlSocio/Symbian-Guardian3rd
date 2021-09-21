/*
============================================================================
 Name        : CAboutView from GuardGUIView.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares view for application.
============================================================================
*/

#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

// INCLUDES
#include <e32base.h>
#include <FuzzyByte\MyObexClient.h>
#include <FuzzyByte\timeouttimer.h>
#include <COEMAIN.H> 
#include <aknview.h>
#include <aknwaitdialog.h> 
#include <MSVAPI.H>
#include <FuzzyByte\Guardian\settings_consts.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\FuzWebUpdate.h>

#include "aboutcontainer.h"

//#include "..\..\S60_Notifier\inc\PinView.h"


// FORWARD DECLARATIONS
class CAboutContainer;

// CLASS DECLARATION

/**
*  CAboutView view class.
*/
class CAboutView : public CAknView, public MTimeOutNotifier, public MProgressDialogCallback, public MMsvSessionObserver, public MAboutObserver
	{
	public: // Constructors and destructor

		/**
		* EPOC default constructor.
		*/
		void ConstructL();

		/**
		* Destructor.
		*/
		~CAboutView();

	public: // Functions from base classes
		void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
		void HandleCentralKeyEventL();
		void UpdateContainerL(TInt val);
		void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );
		
		void TimerExpiredL(TAny* src);

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

 //       virtual void ClientEventL( const TWebClientEvents event, const TDesC& descr ); 
//		virtual void ClientErrorL( const TInt error, const TDesC& aErrorData );
//        virtual void ClientBodyReceivedL( const TDesC8& aBodyData );

		TInt LaunchDialog(TAny* aPtr);
		void CheckForUpdatesL();
		
	//	virtual void OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType);
	private:

		void DeleteMenuItem(CEikMenuPane* menuPane, TInt aCommand);
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

		void ShowWaitDialogL();
		void DismissWaitDialogL();
		void DialogDismissedL( TInt aButtonId );
		void WriteLastUpdateDayL(TInt day);
		TInt32 ReadLastUpdateDayL();


//	public:
		//TBool iForceUpdate;

	private: // Data
		HBufC* iFileRedist;
		TInt iFileSize1;
//		TInt iFileSize2;
		CAboutContainer* iContainer;
//		CPinView* iContainer;
		CTimeOutTimer* iTimer;
		TBool iHasBT;
		TBool iHasIR;
		CMyObexClient* iBtIr;
		CFuzWebUpdate* iWebUpd;
		CAknWaitDialog* iWaitDialog;
		TUint32	iBrandId; 
		TImei iImei;
		__LOG_DECLARATION_MEMBER
	};

#endif


