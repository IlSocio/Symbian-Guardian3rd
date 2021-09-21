/*
============================================================================
 Name        : CSimListView from GuardGUIView2.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares view for application.
============================================================================
*/

#ifndef SimListView_H
#define SimListView_H

// INCLUDES
#include <aknview.h>
#include <eiktxlbx.h>
#include <FuzzyByte\Guardian\client.h>


// CONSTANTS
// UID of view

// FORWARD DECLARATIONS
class CSimListContainer;

// CLASS DECLARATION

/**
*  CSimListView view class.
* 
*/
class CSimListView : public CAknView, public MEikListBoxObserver
	{
	public: // Constructors and destructor

		/**
		* EPOC default constructor.
		*/
		void ConstructL();

		/**
		* Destructor.
		*/
		~CSimListView();

	public: // Functions from base classes

		TUid Id() const;

		void HandleCommandL(TInt aCommand);

		void HandleClientRectChange();
		void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );
		void HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType);
		TBool AskSimNameL(TDes& text);

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

		/**
		* From CAknView deactivate the view (free resources)
		* @return void
		*/
		void DoDeactivate();

		void UpdateViewL();

	private: // Data
		CSimListContainer* iContainer;
		RGuardian iGuardian;
		TInt iOldIndex;
		TBool iTouchSupported;
		TBool iAcceptTouchEvents;
	};

#endif


