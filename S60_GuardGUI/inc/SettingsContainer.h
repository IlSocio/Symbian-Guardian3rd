/*
============================================================================
 Name        : CSettingsContainer from SettingsContainer.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares container control for application.
============================================================================
*/

#ifndef SettingsContainer_H
#define SettingsContainer_H

// INCLUDES
#include <coecntrl.h>
#include <eiktxlbx.h>
#include <eiklbo.h>
#include <FuzzyByte\Guardian\client.h>

// FORWARD DECLARATIONS
class CEikLabel;        // for example labels

// CLASS DECLARATION

/**
*  CSettingsContainer  container control class.
*  
*/
class CSettingsContainer : public CCoeControl, MCoeControlObserver
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
		~CSettingsContainer();
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	public: // New functions
		void UpdateListBoxViewL(const TBool isEnabled, const TDesC& number, const TDesC& message, const TDesC& password, const TDesC& delay, const TLockBehaviour lockBehaviour, const TDesC& monitor);

	private:
		HBufC* GetItemStringLC(TInt resourceID, const TDesC& value);

	private: // Functions from base classes

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
		CEikTextListBox *iListBox;		

	private: //data
	};

#endif


