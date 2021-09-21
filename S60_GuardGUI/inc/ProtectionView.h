/*
============================================================================
 Name        : CProtectionView from GuardGUIView2.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares view for application.
============================================================================
*/

#ifndef ProtectionView_H
#define ProtectionView_H

// INCLUDES
#include <aknview.h>
#include <eiktxlbx.h>
#include <FuzzyByte\Guardian\client.h>
#include <FuzzyByte\FileLogger.h>
#include "protectioncontainer.h"
#include "GuiSettings.h"


// FORWARD DECLARATIONS
//class CProtectionContainer;

// CLASS DECLARATION

/**
*  CProtectionView view class.
* 
*/
class CProtectionView : public CAknView, public MMultiSelectionObserver
	{
	public: // Constructors and destructor

		/**
		* EPOC default constructor.
		*/
		void ConstructL();

		/**
		* Destructor.
		*/
		~CProtectionView();

	public: // Functions from base classes

		void HandleItemChangeEventL(const TInt32 uid, const TBool checked);

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
		void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );


//		void HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType);
		TBool AskSimNameL(TDes& text);
		TInt ShowItemPopupL();

	private:

		/**
		* From CAknView activate the view
		* @param aPrevViewId 
		* @param aCustomMessageId 
		* @param aCustomMessage 
		* @return void
		*/
		void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
			const TDesC8& aCustomMessage);

	//	void DeleteMenuItem(CEikMenuPane* menuPane, TInt aCommand);

		/**
		* From CAknView deactivate the view (free resources)
		* @return void
		*/
		void DoDeactivate();

		void MarkApplicationsL();

	private: // Data
		__LOG_DECLARATION_MEMBER
		CProtectionContainer* iContainer;
		RGuardian iGuardian;
		TBool iWasFindBoxVisible;
		CGuiSettings* iGuiSettings;
	};

#endif


