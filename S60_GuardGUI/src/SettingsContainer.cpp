/*
============================================================================
 Name        : CSettingsContainer from SettingsContainer.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Container control implementation
============================================================================
*/
#include "SettingsContainer.h"

#include <GuardGUI_200131CC.rsg>

#include <eiklabel.h>  // for example label control
#include <AknLists.h>
#include <barsread.h>

_LIT(KTAB, "\t");
  
// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSettingsContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CSettingsContainer::ConstructL(const TRect& aRect, MEikListBoxObserver& observer)
	{
	CreateWindowL();

	iListBox = new (ELeave) CAknSettingStyleListBox();
	iListBox->ConstructL(this, EAknListBoxSelectionList);
	// Crea la scrollbar
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
//	iListBox->SetRect( aRect );
	iListBox->SetContainerWindowL(*this);
	iListBox->Model()->SetOwnershipType(ELbmOwnsItemArray);
	iListBox->SetListBoxObserver(&observer);

	SetRect(aRect);
	ActivateL();

//	UpdateListBoxViewL(EFalse, _L(""), _L(""), _L(""), _L(""));
	}


void CSettingsContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
    // Remember to call base class implementation
    CCoeControl::HandlePointerEventL(aPointerEvent);
    
    //if (iListBox)
    //	iListBox->HandlePointerEventL(aPointerEvent);
    // Your additional code here
    // ...	
	}


HBufC* CSettingsContainer::GetItemStringLC(TInt resourceID, const TDesC& value)
	{
	// iCoeEnv->ReadResourceL();
	HBufC* string = CCoeEnv::Static()->AllocReadResourceLC(resourceID);

/*	Stranamente non funzia
    E' colpa di ReAllocL() !!!! Non aumenta la dimensione...
	string->ReAllocL(string->Length() + value.Length());
	CleanupStack::Pop();
	CleanupStack::PushL(string);
	string->Des().Append(value);
	return string;*/

	// Non si e' utilizzato realloc xche' il cleanupstack avrebbe puntato ancora
	// alla vecchia locazione della stringa
	HBufC* ris = HBufC::NewL(string->Length() + value.Length() + 6);
	TPtr ptr = ris->Des();
	ptr.Append(KTAB);
	ptr.Append( string->Des() );
	ptr.Append(KTAB);
	ptr.Append(KTAB);
	ptr.Append( value );
	CleanupStack::PopAndDestroy(string);
	CleanupStack::PushL(ris);
	return ris;/**/
	}


void CSettingsContainer::UpdateListBoxViewL(const TBool isEnabled, const TDesC& number, const TDesC& message, const TDesC& password, const TDesC& delay, const TLockBehaviour lockBehaviour, const TDesC& monitor)
	{
	CDesCArray* itemList = new (ELeave) CDesCArrayFlat(1);
	TBuf<20> enab;

	if (isEnabled)
	{
		iCoeEnv->ReadResourceL(enab, R_ACTIVE );
	} else {
		iCoeEnv->ReadResourceL(enab, R_INACTIVE );
	}
	
	TBuf<32> lockBehaviour_txt;
	switch (lockBehaviour)
		{
		case ENoLock:
			iCoeEnv->ReadResourceL(lockBehaviour_txt, R_NO );
			break;
		case ELockOnSimChange:
			iCoeEnv->ReadResourceL(lockBehaviour_txt, R_ON_SIM_CHANGE );
			break;
		case ELockOnStartup:
			iCoeEnv->ReadResourceL(lockBehaviour_txt, R_ON_STARTUP );
			break;
		}	

/*	TBuf<20> number;
	TBuf<20> password;
	TBuf<200> message;
	iGuardian.GetDestAddress(number);
	iGuardian.GetMessage(message);
	iGuardian.GetPassword(password);*/

	itemList->AppendL( GetItemStringLC( R_STATUS, enab )->Des() );	CleanupStack::PopAndDestroy();
	itemList->AppendL( GetItemStringLC( R_PHONE_NUMBER, number )->Des() ); CleanupStack::PopAndDestroy();
	itemList->AppendL( GetItemStringLC( R_TEXT_SMS, message )->Des() );	CleanupStack::PopAndDestroy();

	TBuf<8> pass;
	for (TInt i=0; i<password.Length(); i++)
	{
		pass.Append('*');
	}
	itemList->AppendL( GetItemStringLC( R_PASSWORD, pass )->Des() );	CleanupStack::PopAndDestroy();
	itemList->AppendL( GetItemStringLC( R_LOCK_PHONE, lockBehaviour_txt )->Des() );	CleanupStack::PopAndDestroy();
	itemList->AppendL( GetItemStringLC( R_MONITOR, monitor )->Des() );	CleanupStack::PopAndDestroy();
	itemList->AppendL( GetItemStringLC( R_PROTECT_APP, delay )->Des() );	CleanupStack::PopAndDestroy();
	iListBox->Model()->SetItemTextArray(itemList);

	iListBox->HandleItemAdditionL();
//    iListBox->ActivateL();
    iListBox->DrawNow();
	}

// Destructor
CSettingsContainer::~CSettingsContainer()
	{
	if (iListBox)
		delete iListBox;
	}

// ---------------------------------------------------------
// CSettingsContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CSettingsContainer::SizeChanged()
	{
    if(iListBox)
		iListBox->SetExtent(TPoint(0,0), iListBox->MinimumSize());
	}

// ---------------------------------------------------------
// CSettingsContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CSettingsContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iListBox) count++;
    return count;
	}

// ---------------------------------------------------------
// CSettingsContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CSettingsContainer::ComponentControl(TInt aIndex) const
	{
	 switch ( aIndex )
		{
		case 0:
			return iListBox;
		default:
			return NULL;
		}
	}

	TKeyResponse CSettingsContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
    if ( aType != EEventKey )
        return EKeyWasNotConsumed;

	//
	// Pass any key event to the listbox
	// (this is required if you want to move the cursor through the list)
	//
	if(!iListBox)
		return EKeyWasNotConsumed;

    switch ( aKeyEvent.iCode )
		{
        // Left Arrow pressed
		case EKeyUpArrow:
		case EKeyDownArrow:
		case EKeyDevice3:
			return iListBox->OfferKeyEventL( aKeyEvent, aType );
		break;
		}
	return EKeyWasNotConsumed;
	}

// ---------------------------------------------------------
// CSettingsContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CSettingsContainer::Draw(const TRect& aRect) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetPenStyle( CGraphicsContext::ENullPen );
	gc.SetBrushColor( KRgbGray );
	gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
	gc.DrawRect( aRect );
	}

// ---------------------------------------------------------
// CSettingsContainer::HandleControlEventL(
//    CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CSettingsContainer::HandleControlEventL(
	CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
	{
	}
