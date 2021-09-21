/*
============================================================================
 Name        : CAboutContainer from GuardGUIContainer.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares container control for application.
============================================================================
*/

#ifndef ABOUTCONTAINER_H
#define ABOUTCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <W32STD.H>
#include <FuzzyByte\phone.h>
#include <FuzzyByte\timeouttimer.h>



// FORWARD DECLARATIONS
class CEikLabel;        // for example labels

// CLASS DECLARATION

class MAboutObserver
{
public:
	virtual void HandleCentralKeyEventL() = 0;
};

/**
*  CAboutContainer  container control class.
*  
*/
class CAboutContainer : public CCoeControl, public MCoeControlObserver
	{
	public: // Constructors and destructor
		
		/**
		* EPOC default constructor.
		* @param aRect Frame rectangle for container.
		*/
		void ConstructL(MAboutObserver& aObserver, const TRect& aRect, TInt val);

		/**
		* Destructor.
		*/
		~CAboutContainer();
		void SetTypeSignatureL(TInt type);
		
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	private: // Functions from base classes
		
		void GetDegreesString(const TReal64& aDegrees, TDes& aDegreesString) const;

		/**
		* From CoeControl,SizeChanged.
		*/
		void SizeChanged();

		/**
		* From CoeControl,CountComponentControls
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
		* @param	aControl	The control changing its state
		* @param	aEventType	The type of control event 
		*/
		void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
		
	private: //data		
		MAboutObserver* iObserver;
		TPixelsTwipsAndRotation iPixRot;
		CFbsBitmap* iBackBitmap;
        CFbsBitmap* iScritta;
        CFbsBitmap* iScrittaMask;
	};

#endif
