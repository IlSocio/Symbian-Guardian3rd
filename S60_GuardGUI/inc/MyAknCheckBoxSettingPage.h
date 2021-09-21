/*
 ============================================================================
 Name		: CMyAknCheckBoxSettingPage.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMyAknCheckBoxSettingPage declaration
 ============================================================================
 */

#ifndef CMYAKNCHECKBOXSETTINGPAGE_H
#define CMYAKNCHECKBOXSETTINGPAGE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <AknCheckBoxSettingPage.h>

// CLASS DECLARATION

/**
 *  CMyAknCheckBoxSettingPage
 * 
 */
class CMyAknCheckBoxSettingPage : public CAknCheckBoxSettingPage
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CMyAknCheckBoxSettingPage();

	/**
	 * Two-phased constructor.
	 */
	static CMyAknCheckBoxSettingPage* NewL(TInt aResourceID, CSelectionItemList* aItemArray);

	/**
	 * Two-phased constructor.
	 */
	static CMyAknCheckBoxSettingPage* NewLC(TInt aResourceID, CSelectionItemList* aItemArray);

	void ConstructL();
	CMyAknCheckBoxSettingPage(TInt aResourceID, CSelectionItemList* aItemArray);
	
private:
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
	/**
	 * Constructor for performing 1st stage construction
	 */

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */

	};

#endif // CMYAKNCHECKBOXSETTINGPAGE_H
