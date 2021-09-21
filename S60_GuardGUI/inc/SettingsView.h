/*
============================================================================
 Name        : CSettingsView from GuardGUIView2.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares view for application.
============================================================================
*/

#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

// INCLUDES
#include <aknview.h>
#include <eiktxlbx.h>
#include <FuzzyByte\Guardian\client.h>
#include <AknSettingPage.h>
#include <AknCheckBoxSettingPage.h>

// CONSTANTS
// UID of view

// FORWARD DECLARATIONS
class CSettingsContainer;

// CLASS DECLARATION

/**
*  CSettingsView view class.
*
*/
class CSettingsView : public CAknView, public MEikListBoxObserver
	{
	public: // Constructors and destructor

		/**
		* EPOC default constructor.
		*/
		void ConstructL();

		/**
		* Destructor.
		*/
		~CSettingsView();

	public: // Functions from base classes

		void DynInitMenuPaneL( TInt aResourceId,	CEikMenuPane* aMenuPane );
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
		void HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType);
		
		void GetItemDescriptionL(TInt index, TDes& descr);
		CDesCArray* CreateRadioButtonArrayLC();
		CDesCArray* CreateRadioArrayForLockPhoneLC();
		CSelectionItemList* CreateCheckBoxArrayL(TBool smsIn, TBool smsOut, TBool callIn, TBool callOut);
		void UpdateViewL();
		TInt Index2Seconds(TInt index);
		TInt Seconds2Index(TInt seconds);
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

		TBool AskNumberL(TDes& number);
		TBool AskTextL(TDes& text);
		TBool AskPasswordL(TDes& pass);
	private: // Data
		TBool iAcceptTouchEvents;
		TBool iTouchSupported;
		TInt iOldIndex;
		RGuardian iGuardian;
		CSettingsContainer* iContainer;
		CSelectionItemList* iMonitorList;
	};

#endif


