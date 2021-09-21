/*
============================================================================
 Name        : CSimListContainer from SimListContainer.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Container control implementation
============================================================================
*/

// INCLUDE FILES
#include "SimListContainer.h"

#include <FuzzyByte\Guardian\settings_consts.h>

#include <eiklabel.h>  // for example label control


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSimListContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CSimListContainer::ConstructL(const TRect& aRect, MEikListBoxObserver& observer)
	{
	CreateWindowL();

	iListBox = new (ELeave) CAknDoubleStyleListBox();
	iListBox->ConstructL(this, EAknListBoxSelectionList);
	// Crea la scrollbar
	iListBox->CreateScrollBarFrameL(ETrue);
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	iListBox->SetRect( aRect );
	iListBox->SetContainerWindowL(*this);
	iListBox->Model()->SetOwnershipType(ELbmOwnsItemArray);
	iListBox->SetListBoxObserver(&observer);

/*  		CDesCArray* itemList = new (ELeave) CDesCArrayFlat(KMAX_SIMS);	
  		CleanupStack::PushL(itemList);
		itemList->AppendL( GetItemStringLC(_L("aaa"), _L("bbb"))->Des() );
		CleanupStack::PopAndDestroy();
		iListBox->Model()->SetItemTextArray(itemList);
		CleanupStack::Pop(); // itemList
	
	iListBox->HandleItemAdditionL();*/

    SetRect( aRect );
    ActivateL();
	}


void CSimListContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
    // Remember to call base class implementation
    CCoeControl::HandlePointerEventL(aPointerEvent);
    
    // Your additional code here
    // ...	
	}


// Destructor
CSimListContainer::~CSimListContainer()
	{
	if (iListBox)
		delete iListBox;
	}

_LIT(KTAB, "\t");

HBufC* CSimListContainer::GetItemStringLC(const TDesC& name, const TDesC& oper)
	{
	// Non si e' utilizzato realloc xche' il cleanupstack avrebbe puntato ancora
	// alla vecchia locazione della stringa

    HBufC* ris = HBufC::NewLC( name.Length() + oper.Length() + 10);
	TPtr ptr = ris->Des();
	ptr.Append( KTAB );
	ptr.Append( name );
	ptr.Append( KTAB );
	ptr.Append( oper );
	ptr.Append( KTAB );
	return ris;
	}


void CSimListContainer::GetSelectedNameAndOper(TDes& name, TDes& oper) 
	{
	TInt index = iListBox->CurrentItemIndex();
	if (index<0) 
		{
		name.Zero();
		oper.Zero();
		return;
		}
	TPtrC ptr = iListBox->Model()->ItemText(index);
	TPtrC name_tab_oper = ptr.Mid(1, ptr.Length()-2);
	// Split di NOME<KTAB>OPER
	TChar tab = '\t';
	TInt tab_pos = name_tab_oper.Locate(tab);
	TPtrC ptr_name = name_tab_oper.Left(tab_pos);
	TPtrC ptr_oper = name_tab_oper.Right(name_tab_oper.Length() - tab_pos - 1);
	name.Copy(ptr_name);
	oper.Copy(ptr_oper);
	}


void CSimListContainer::UpdateListBoxViewL(RArray<TImsiName>& nameList, RArray<TOperName>& operList)
	{
	CDesCArray* itemList = new (ELeave) CDesCArrayFlat(10);	
	CleanupStack::PushL(itemList);

		TInt i=0;
		while (i < nameList.Count())
			{
			TPtrC name = nameList[i];
			TPtrC oper = operList[i];
			itemList->AppendL( GetItemStringLC(name, oper)->Des() );
			CleanupStack::PopAndDestroy();
			i++;
			}

	iListBox->Model()->SetItemTextArray(itemList);
	CleanupStack::Pop(); // itemList
	
	iListBox->HandleItemAdditionL();
    iListBox->ActivateL();
    iListBox->DrawNow();																																																																																																								
	}

// ---------------------------------------------------------
// CSimListContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CSimListContainer::SizeChanged()
	{
    if(iListBox)
		iListBox->SetRect(Rect());
	}

// ---------------------------------------------------------
// CSimListContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CSimListContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iListBox) count++;
    return count;
	}

// ---------------------------------------------------------
// CSimListContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CSimListContainer::ComponentControl(TInt aIndex) const
	{
	 switch ( aIndex )
		{
		case 0:
			return iListBox;
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CSimListContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CSimListContainer::Draw(const TRect& aRect) const
	{
	}

// ---------------------------------------------------------
// CSimListContainer::HandleControlEventL(
//    CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CSimListContainer::HandleControlEventL(
	CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
	{
	}


TKeyResponse CSimListContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) 
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
