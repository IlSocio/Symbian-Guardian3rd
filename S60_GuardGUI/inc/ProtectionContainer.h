/*
============================================================================
 Name        : CProtectionContainer from ProtectionContainer.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares container control for application.
============================================================================
*/

#ifndef ProtectionContainer_H
#define ProtectionContainer_H

// INCLUDES
#include "GuiSettings.h"
#include <aknutils.h>
#include <aknsfld.h>
#include <coecntrl.h>
#include <eiktxlbx.h>
#include <eiklbo.h>
#include <aknlists.h>
#include <FuzzyByte\FileLogger.h>
#include <eikedwob.h>

// FORWARD DECLARATIONS
class CEikLabel;        // for example labels


class MMultiSelectionObserver
{
public:
	virtual void HandleItemChangeEventL(const TInt32 uid, const TBool checked) = 0;
};
// CLASS DECLARATION

/**
*  CProtectionContainer  container control class.
*
*/
class CProtectionContainer : public CCoeControl, public MCoeControlObserver, public MEikListBoxObserver
	{
	public: // Constructors and destructor

		CProtectionContainer(CGuiSettings& aGuiSettings);
		/**
		* EPOC default constructor.
		* @param aRect Frame rectangle for container.
		*/
		void ConstructL(const TRect& aRect, TBool findBoxVisible);

		void SetObserver(MMultiSelectionObserver* observer);
		/**
		* Destructor.
		*/
		~CProtectionContainer();
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
		void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
		
	public: // New functions
		void ClearListBoxViewL();
			// Restituisce True se la sim selezionata e' la prima
		TInt32 GetSelectedUidL();
		TBool IsSelectedMarkedL();
		TBool ChangeApplicationStatusL(TInt32 uid);
		TBool IsFindBoxVisible();

	public: // Functions from base classes
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		
	private: // Functions from base classes
		TKeyResponse OfferKeyToFindBoxL(const TKeyEvent& aKeyEvent, TEventCode aType);
		void DeleteFindBox();
		HBufC* GetItemStringLC(const TDesC& name, const TUint icon);
		TInt GetOriginalIndexL();

		/**
		* From CoeControl,SizeChanged.
		*/
		void SizeChanged();

		/**
		* From CoeControl,CountComponentControls.
		*/
		TInt CountComponentControls() const;

		/**
		* From CCoeControl,ComponentControl.
		*/
		CCoeControl* ComponentControl(TInt aIndex) const;

		/**
		* From CCoeControl,Draw.
		*/
		void Draw(const TRect& aRect) const;

		/**
		* From MCoeControlObserver
		* Acts upon changes in the hosted control's state.
		*
		* @param aControl	The control changing its state
		* @param aEventType	The type of control event
		*/
		void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

		CArrayFixFlat<TApaAppInfo>* GetApplicationsLC(CArrayFixFlat<TApaAppInfo>* hiddenApps);
		CGulIcon* GetApplicationIconL(const TUid& aAppUID);
		//CAknSearchField* CreateFindBoxL(CEikListBox& aListBox, CAknSearchField::TSearchFieldStyle style);
		void CreateListBoxL(TBool large, TBool findBoxVisible);

	private:
		__LOG_DECLARATION_MEMBER
		CGuiSettings& iGuiSettings;		// Not Owned
		CEikColumnListBoxTypedef* iListBox;
//		CEikColumnListBox* iListBox;
//		CEikFormattedCellListBoxTypedef* iListBox;
		CArrayFixFlat<TApaAppInfo>* iVisibleAppList;
		CArrayFixFlat<TApaAppInfo>* iHiddenAppList;
		MMultiSelectionObserver* iObserver;
		RArray<TInt> iMarkers;

//		CAknSearchField::TSearchFieldStyle iStyle;
		TInt iStyle;
        //! the control used to display a search field.
        CAknSearchField* iFindBox;
		HBufC* iOldFilter;
		TBool iTouchSupported;
		TBool iAcceptTouchEvents;
		TInt iDBG_Down;
		TInt iDBG_Click;
	};

#endif


