/*
============================================================================
 Name        : CSimListContainer from SimListContainer.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares container control for application.
============================================================================
*/

#ifndef SimListContainer_H
#define SimListContainer_H

// INCLUDES
#include <coecntrl.h>
#include <eiktxlbx.h>
#include <eiklbo.h>
#include <aknlists.h> 
#include <FuzzyByte\Guardian\settings_consts.h>

// FORWARD DECLARATIONS
class CEikLabel;        // for example labels

// CLASS DECLARATION

/**
*  CSimListContainer  container control class.
*  
*/
class CSimListContainer : public CCoeControl, MCoeControlObserver
	{
	public: // Constructors and destructor
		
		/**
		* EPOC default constructor.
		* @param aRect Frame rectangle for container.
		*/
		void ConstructL(const TRect& aRect, MEikListBoxObserver& observer);

		/**
		* Destructor.
		*/
		~CSimListContainer();
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	public: // New functions
		void UpdateListBoxViewL(RArray<TImsiName>& nameList, RArray<TOperName>& operList);
			// Restituisce True se la sim selezionata e' la prima
		void GetSelectedNameAndOper(TDes& name, TDes& oper);

	public: // Functions from base classes
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	private: // Functions from base classes
		HBufC* GetItemStringLC(const TDesC& name, const TDesC& imsi);

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
		void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	
	public:
		CAknDoubleStyleListBox* iListBox;
	};

#endif


