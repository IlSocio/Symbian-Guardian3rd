/*
============================================================================
 Name        : CGuardGUIAppUi from GuardGUIAppui.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares UI class for application.
============================================================================
*/

#ifndef GUARDGUIAPPUI_H
#define GUARDGUIAPPUI_H



// INCLUDES
#include <aknwaitdialog.h>
#include <aknprogressdialog.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>
#include <akntabobserver.h>
#include <browserlauncher.h>
//#include <DownloadedContentHandler.h>

#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\timeouttimer.h>
#include <FuzzyByte\phone.h>
#include <FuzzyByte\FuzWebRegister.h>
#include <FuzzyByte\Guardian\client.h>

#include "SplashView.h"
#include "AboutView.h"
#include "SimListView.h"
#include "SettingsView.h"
#include "ProtectionView.h"
//#include "pluginmanager.h"

#include "mmlist.h"
// FORWARD DECLARATIONS
//class CAboutContainer;

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
*
*/
/*#include <calsession.h>
#include <calentryview.h>
#include <calprogresscallback.h>*/
//#include "AsyncQueryDialog.h"

class CGuardGUIAppUi : public CAknViewAppUi, public MTimeOutNotifier, public MAknTabObserver, public MProgressDialogCallback // ,public MCalProgressCallBack //, public MDownloadedContentHandler
	{
	public: // // Constructors and destructor
	void DialogClosedL(TBool ok, const TDesC& code);
	/*void DeleteAgendaL();
	virtual void Progress(TInt aPercentageCompleted);
	virtual void Completed(TInt aError);
	virtual TBool NotifyProgress();*/
	
		/**
		* EPOC default constructor.
		*/ 
		void ConstructL();

//		TInt ShowItemPopupL(TInt resource);

		void TimerExpiredL(TAny* src);
		/**
		* Destructor.
		*/
		~CGuardGUIAppUi();

	public: // Functions from base classes
		//void HandlePointerEventL(const TPointerEvent& aPointerEvent);
		/**
		* From MAknTabObserver.
		* @param aIndex tab index
		*/
		void TabChangedL(TInt aIndex);
		void HandleResourceChangeL(TInt aType);
        void DialogDismissedL( TInt aButtonId );
		void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

        // reserved for future use
        TAny* DownloadedContentHandlerReserved1( TAny* /*aAnyParam*/ );
		//TBool HandleContentL(const TDesC& aFileName, const CAiwGenericParamList& aParamList, TBool& aContinue);
	private:
		TBool GotRegCodeL(const TDesC& regCode);
//		TBool Get_BT_IRDA_InboxFileL(const TDesC& path);
//		void SendFileUsingMtmL(TUid mtm, const TDesC& filename);
//		TUid AskMtmL();
//		TBool DBG_AskTimeOutL(TDes& timeout);
		void ReplaceTabL(TInt tabId, TInt svgId);
		TBool AskPasswordL(TDes& pass);

		void ShowWaitDialogL();
		void DismissWaitDialogL();
		void InitializeGuiViewsL();

	private:
		/**
		* From CEikAppUi, takes care of command handling.
		* @param aCommand command to be handled
		*/
		void HandleCommandL(TInt aCommand);

		/**
		* From CEikAppUi, handles key events.
		* @param aKeyEvent Event to handled.
		* @param aType Type of the key event.
		* @return Response code (EKeyWasConsumed, EKeyWasNotConsumed).
		*/
		virtual TKeyResponse HandleKeyEventL(
			const TKeyEvent& aKeyEvent,TEventCode aType);

		/**
		*  From CCoeAppUi, HelpContextL.
		*  Provides help context for the application.
		*  size is changed.
		*/
	 	CArrayFix<TCoeHelpContext>* HelpContextL() const;


		/**
		* Shows privacy statement if needed.
		*/
		void ShowLongTextFromFileL(const TDesC& fileName, const TDesC& title);

//		void DeleteMenuItem(CEikMenuPane* menuPane, TInt aCommand);
//		void DeleteMenuItemIfEmpty(CEikMenuPane* menuPane, TInt aCommand);
//		TBool SendFileViaSendUiL(const TDesC& filename);

	public:
		TInt iIsRegistered;

	private: //Data
		RBuf iMachineId;
		CFuzWebRegister* iWebReg;
		CAknNavigationControlContainer* iNaviPane;
		CAknTabGroup* iTabGroup;
		CAknNavigationDecorator* iDecoratedTabGroup;
		CAboutView* iView1;
		CSettingsView* iView2;
		CSimListView* iView3;
		CProtectionView* iView4;
		CSplashView* iSplashView;
		CTimeOutTimer* iTimer;
//		CPluginManager* iPluginManager;
		__LOG_DECLARATION_MEMBER

//		RGuardian iGuardian;
//		CPhone* iPhone;
		TBool iGuiActive;
        CAknWaitDialog*         iWaitDialog;
        TUint32					iBrandId;
    	TImei iImei;
//		CBrowserLauncher*		iBrowser;
	};

#endif

