// INCLUDE FILES
#include "ProtectionContainer.h"
#include "guardgui_200131CC.mbg"
#include "guardsvg_200131CC.mbg"

#include <FuzzyByte\GuiUtils.H>
#include <FuzzyByte\Guardian\settings_consts.h>

#include <aknutils.h>
#include <aknsfld.h>
#include <eiklabel.h>  // for example label control
#include <APGCLI.H>
#include <GULICON.H>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akndef.H>
#include <eikdef.h>
#include <EIKENV.H>
#include <EIKAPPUI.H>
#include <EIKAPP.H>
#include <FRMTVIEW.H>
#include <avkon.rsg>
#include <avkon.mbg>
#include <aknconsts.h>
//#include <avkon.rh>


// ================= MEMBER FUNCTIONS =======================

CProtectionContainer::CProtectionContainer(CGuiSettings& aGuiSettings) : iGuiSettings(aGuiSettings)
	{	
	}

// ---------------------------------------------------------
// CProtectionContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CProtectionContainer::ConstructL(const TRect& aRect, TBool findBoxVisible)
	{
	__LOG_OPEN("Guardian", "GUI_ProtCont.txt")

	iTouchSupported = EFalse;
	iAcceptTouchEvents = EFalse;
	iDBG_Down = 0;
	iDBG_Click = 0;

	iFindBox = NULL;
	iListBox = NULL;

//	iStyle = 11; // 11 = CAknSearchField::EAdaptiveSearch;  12 = CAknSearchField::EAdaptive;
//	iStyle = 12;
	iStyle = CAknSearchField::ESearch;
//	iStyle = CAknSearchField::EPopup;

	CreateWindowL();
    SetRect( aRect );

	CreateListBoxL( iGuiSettings.iLargeIcons, findBoxVisible );

    ActivateL();
	DrawNow();
	}


void CProtectionContainer::HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)
	{
	if (aEventType == EEventEnterKeyPressed) // 5th Ed.
		{
		__LOG_TXT("EnterKeyPressed");
		}
	if (aEventType == EEventPenDownOnItem) // 5th Ed.
		{
		iDBG_Down++;
		TBuf<20> buf = _L("PenDown: ");
		buf.AppendNum(iDBG_Down);		
		__LOG_DES(buf);
		}
	if (aEventType == EEventItemClicked) // 5th Ed.
		{
		iDBG_Click++;
		TBuf<20> buf = _L("Item Clicked: ");
		buf.AppendNum(iDBG_Click);
		__LOG_DES(buf);
		}
	if (aEventType == EEventPenDownOnItem) // 5th Ed.
		{
		iTouchSupported = ETrue;
		iAcceptTouchEvents = ETrue;
		}
	switch (aEventType)
		{
		case EEventEnterKeyPressed:
		case EEventItemClicked:
			if (iTouchSupported)
				{ 
				if (!iAcceptTouchEvents)
					return;
				iAcceptTouchEvents = EFalse;
				}
			ChangeApplicationStatusL( GetSelectedUidL() );
			TBool checked = IsSelectedMarkedL();
			if (iObserver)
				{
				iObserver->HandleItemChangeEventL( GetSelectedUidL() , checked);    	
				}
			break;
		default:
			break;
		}
	}


void CProtectionContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
    // Remember to call base class implementation
    CCoeControl::HandlePointerEventL(aPointerEvent);


/*  
 *   Verifica se e' un evento nella listbox o nella findbox...  
  	if (aPointerEvent.iType == TPointerEvent::EButton1Up)
   	{
   		ChangeApplicationStatusL( GetSelectedUidL() );
		TBool checked = IsSelectedMarkedL();
		iObserver->HandleItemChangeEventL( GetSelectedUidL() , checked);    
    }*/
	
/*    if (IsFindBoxVisible())
    	{
    	iFindBox->HandlePointerEventL(aPointerEvent);
    	return;
    	}

    if (iListBox)
    	iListBox->HandlePointerEventL(aPointerEvent);*/
    // Your additional code here
    // ...	
	}


TBool CProtectionContainer::IsFindBoxVisible()
{
	return (iFindBox != NULL);
}


void CProtectionContainer::SetObserver(MMultiSelectionObserver* observer)
	{
	iObserver = observer;
	}


// Destructor
CProtectionContainer::~CProtectionContainer()
	{
	__LOG_TXT("Destructor");
	__LOG_TXT("FindBox");
	DeleteFindBox();
	__LOG_TXT("ListBox");
	if (iListBox)
	{
		delete iListBox;
		iListBox = NULL;
	}
	__LOG_TXT("AppList");
	delete iHiddenAppList;
	delete iVisibleAppList;
	__LOG_TXT("Markers");
	iMarkers.Reset();
	iMarkers.Close();
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}


HBufC* CProtectionContainer::GetItemStringLC(const TDesC& name, const TUint icon)
	{
	// Non si e' utilizzato realloc xche' il cleanupstack avrebbe puntato ancora
	// alla vecchia locazione della stringa

//	"0\tTESTO\t\t"

    HBufC* ris = HBufC::NewLC( name.Length() + 10 );
	TPtr ptr = ris->Des();
	
	_LIT(KListItemFormat, "%d\t%S\t\t0");
	ptr.Format(KListItemFormat, icon, &name);
	return ris;
	}


TInt32 CProtectionContainer::GetSelectedUidL()
	{
	if (iListBox == NULL)
		return 0;
	TInt index = GetOriginalIndexL();
	if (index<0)
		return 0;
	TApaAppInfo appInfo = (*iVisibleAppList)[index];
	return appInfo.iUid.iUid;
	}


void CProtectionContainer::ClearListBoxViewL()
	{
	iMarkers.Reset();
	CreateListBoxL( iGuiSettings.iLargeIcons, IsFindBoxVisible() );
    iListBox->DrawNow();
	}


TInt CProtectionContainer::GetOriginalIndexL()
{
	if (!iListBox)
		return -1;
	TInt indexFilt = iListBox->CurrentItemIndex();
	return GuiUtils::GetUnFilteredIndex(iListBox, indexFilt);
}


TBool CProtectionContainer::ChangeApplicationStatusL(TInt32 uid)
	{
	__LOG_TXT("ChangeApplicationStatusL");
	TInt i=0;
	while (i < iVisibleAppList->Count() && (*iVisibleAppList)[i].iUid.iUid != uid)
		i++;

	if (i == iVisibleAppList->Count())
		{
		// L'applicazione non esiste... oppure si trova tra le applicazioni non visibili...
		TInt i=0;
		while (i < iHiddenAppList->Count() && (*iHiddenAppList)[i].iUid.iUid != uid)
			i++;
		if (i == iHiddenAppList->Count())
			return EFalse;		// L'applicazione non esiste...
		return ETrue;			// L'applicazione esiste ma non e' visibile...				
		}

//	TInt indexFilt = GuiUtils::GetFilteredIndexL(i);	
//	if (indexFilt >= 0)
//		iListBox->View()->ToggleItemL(indexFilt);

	// Salva lo stato nell'array dei Markers...
	TInt pos = iMarkers.Find(i);
	if (pos >= 0) iMarkers.Remove(pos);
	else iMarkers.Append(i);
	
	
	// Refresh item...
	MDesCArray* textArray = iListBox->Model()->ItemTextArray();
	CDesCArray* listBoxItems = static_cast<CDesCArray*>( textArray );
	TBuf<512> listString = textArray->MdcaPoint(i);
	//Notes::Debug_InfoL(listString);

	TInt newIcon = 0;
	if (pos < 0)
		{
		newIcon = 1;
		}

	listString.Delete(listString.Length()-1, 1); // Removes last icon
	listString.AppendNum(newIcon);
	
	// update item
	listBoxItems->Delete( i );
	listBoxItems->InsertL( i, listString );
		
	// Update new item
	TInt indexFilt = GuiUtils::GetFilteredIndex(iListBox, i);
	if (indexFilt >= 0)
		{
		iListBox->DrawItem( indexFilt );
		}   
	
	return ETrue;
	}


TBool CProtectionContainer::IsSelectedMarkedL()
	{
		if (!iListBox)
			return EFalse;
		TInt indexOrig = GetOriginalIndexL();
		if (indexOrig < 0)
			return EFalse;
		return (iMarkers.Find(indexOrig) >= 0);
	}


// ---------------------------------------------------------
// CProtectionContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CProtectionContainer::SizeChanged()
	{
//    if (iListBox)
//		iListBox->SizeChanged();
	if (iListBox)
		iListBox->SetRect(Rect());
	if (!iFindBox)
		return;
	if (iStyle == CAknSearchField::EPopup)
		AknFind::HandlePopupFindSizeChanged( this, iListBox, iFindBox );
	else
		AknFind::HandleFixedFindSizeChanged( this, iListBox, iFindBox );
	}

// ---------------------------------------------------------
// CProtectionContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CProtectionContainer::CountComponentControls() const
	{
	TInt count(0);
	if (iListBox) count++;
	if (iFindBox) count++;
    return count;
	}


void CProtectionContainer::CreateListBoxL(TBool large, TBool findBoxVisible)
    {
	DeleteFindBox();

	__LOG_TXT("Delete ListBox");
	if (iListBox)
		delete iListBox;

	if (large)
		iListBox = new (ELeave) CAknSingleLargeStyleListBox();	 // Icone Grandi
	else
		iListBox = new (ELeave) CAknSingleGraphicStyleListBox(); // Icone Piccole

	iListBox->ConstructL(this, CEikListBox::ELoopScrolling);

	iListBox->SetContainerWindowL(*this);
	iListBox->Model()->SetOwnershipType(ELbmOwnsItemArray);
//	iListBox->SetListBoxObserver

	delete iVisibleAppList;
	delete iHiddenAppList;
	iHiddenAppList = new(ELeave)CArrayFixFlat<TApaAppInfo>(10);

	__LOG_TXT("GetAppList");
	iVisibleAppList = GetApplicationsLC( iHiddenAppList );
	CleanupStack::Pop( iVisibleAppList );

	CAknIconArray* iconList = new (ELeave) CAknIconArray(10);
	CleanupStack::PushL(iconList);

	CDesCArray* itemList = new (ELeave) CDesCArrayFlat(10);
	CleanupStack::PushL(itemList);

	CFbsBitmap*	myIcon(NULL);
	CFbsBitmap*	myIconMask(NULL);

//	AknIconUtils::CreateIconL(iMyIcon, iMyIconMask, KAvkonBitmapFile, EMbmAvkonQgn_indi_marked_add, EMbmAvkonQgn_indi_marked_add_mask);
	__LOG_TXT("GetMarkIcon");
    TRgb defaultColor;
    defaultColor = CEikonEnv::Static()->Color(EColorControlText);
        
    
       /*AknsUtils::CreateColorIconLC(AknsUtils::SkinInstance(),
        			KAknsIIDQgnIndiMarkedAdd,
        			KAknsIIDQsnIconColors,
        			EAknsCIQsnIconColorsCG13,
        			iMyIcon,
        			iMyIconMask,
        			KAvkonBitmapFile,
        			EMbmAvkonQgn_indi_checkbox_off,
        			EMbmAvkonQgn_indi_checkbox_off_mask,
        			defaultColor
        			);
		myIcon = new (ELeave) CFbsBitmap();
		myIcon->Create(TSize(10, 10), ENone);		
		myIconMask = new (ELeave) CFbsBitmap();
		myIconMask->Create(TSize(10, 10), ENone);
        CGulIcon* unmarkIcon = CGulIcon::NewL( myIcon, myIconMask );
    	CleanupStack::Pop(2);	// iMyIcon, iMyIconMask
    	CleanupStack::PushL(unmarkIcon);
    	iconList->AppendL(unmarkIcon);
    	CleanupStack::Pop(unmarkIcon);	// unmarkIcon*/ 
    CGulIcon* unmarkIcon = GuiUtils::LoadAndScaleIconL( _L("c:\\resource\\apps\\GuardSvg_200131CC.mbm"), EMbmGuardsvg_200131ccEmpty, EMbmGuardsvg_200131ccEmpty);
	CleanupStack::PushL(unmarkIcon);
	iconList->AppendL(unmarkIcon);
	CleanupStack::Pop(unmarkIcon);
    

        AknsUtils::CreateColorIconLC(AknsUtils::SkinInstance(),
         			KAknsIIDQgnIndiMarkedAdd,
         			KAknsIIDQsnIconColors,
         			EAknsCIQsnIconColorsCG13,
         			myIcon,
         			myIconMask,
         			KAvkonBitmapFile,
         			EMbmAvkonQgn_indi_marked_add,
         			EMbmAvkonQgn_indi_marked_add_mask,
         			defaultColor
         			);
        CGulIcon* markIcon = CGulIcon::NewL( myIcon, myIconMask );
     	CleanupStack::Pop(2);	// iMyIcon, iMyIconMask
     	CleanupStack::PushL(markIcon);
     	iconList->AppendL(markIcon);
     	CleanupStack::Pop(markIcon);	// markIcon

     	/*    AknsUtils::CreateColorIconLC(AknsUtils::SkinInstance(),
    			KAknsIIDQgnIndiMarkedAdd,
    			KAknsIIDQsnIconColors,
    			EAknsCIQsnIconColorsCG13,
    			iMyIcon,
    			iMyIconMask,
    			KAvkonBitmapFile,
    			EMbmAvkonQgn_indi_marked_add,
    			EMbmAvkonQgn_indi_marked_add_mask,
    			defaultColor
    			);
    CGulIcon* markIcon = CGulIcon::NewL( iMyIcon, iMyIconMask );
	CleanupStack::Pop(2);	// iMyIcon, iMyIconMask
	CleanupStack::PushL(markIcon);
	iconList->AppendL(markIcon);
	CleanupStack::Pop(markIcon);	// markIcon
*/

	__LOG_TXT("GetAppIconL loop");
	TInt i=0;
	
		while (i < iVisibleAppList->Count())
			{
			TApaAppInfo appInfo = (*iVisibleAppList)[i];
			// __FLOG(appInfo.iFullName);
			CGulIcon* icon = NULL;
			TRAPD(err, icon = GetApplicationIconL(appInfo.iUid));
			if (err != KErrNone)
			{
				const TUid KServerIcon = { 0x200107AB };
				TRAPD(err, icon = GetApplicationIconL( KServerIcon ));
			}
			CleanupStack::PushL(icon);
			iconList->AppendL( icon );
			CleanupStack::Pop(icon);
			// __FLOG(_T8("GetItemString"));
			itemList->AppendL( GetItemStringLC(appInfo.iShortCaption, i+2)->Des() );	// Cambiato nella 4.0
//			itemList->AppendL( GetItemStringLC(appInfo.iCaption, i+1)->Des() );
			CleanupStack::PopAndDestroy();
			i++;
			}/**/

	__LOG_TXT("SetItemTextArrayL");
	iListBox->Model()->SetItemTextArray( itemList );
	CleanupStack::Pop( itemList ); // itemList

	iListBox->ItemDrawer()->ColumnData()->SetIconArray( iconList );
	CleanupStack::Pop( iconList ); // iconList

	// Crea la scrollbar
	CEikScrollBarFrame* scrollBar = iListBox->CreateScrollBarFrameL(ETrue);
	scrollBar->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

	iListBox->SetRect( Rect() );

	// Se necessario crea FindBox
	if (findBoxVisible)
		iFindBox = GuiUtils::CreateSearchBoxL(*this, *iListBox, (CAknSearchField::TSearchFieldStyle)iStyle);
	
	iListBox->SetListBoxObserver(this);
	
	SizeChanged();

	ActivateL();
    }

/*
CAknSearchField* CProtectionContainer::CreateFindBoxL(CEikListBox& aListBox, CAknSearchField::TSearchFieldStyle style)
    {
	CAknFilteredTextListBoxModel* model = static_cast<CAknFilteredTextListBoxModel*>(aListBox.Model());
	if (!model)
		return NULL;
    // Creates FindBox.
	CAknSearchField* findbox = CAknSearchField::NewL(*this, style, NULL, 20);
	CleanupStack::PushL(findbox);
	if (style == CAknSearchField::EPopup)
		findbox->MakeVisible( EFalse );
	model->CreateFilterL(&aListBox, findbox);
//	CAknListBoxFilterItems* filter = model->Filter();
	CleanupStack::Pop( findbox ); // findbox
	return findbox;
    }*/


// ---------------------------------------------------------
// CProtectionContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CProtectionContainer::ComponentControl(TInt aIndex) const
	{
	 switch ( aIndex )
		{
		case 0:
			return iListBox;
		case 1:
			return iFindBox;
		default:
			return NULL;
		}
	}

// ---------------------------------------------------------
// CProtectionContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CProtectionContainer::Draw(const TRect& aRect) const
	{
	}


void CProtectionContainer::DeleteFindBox()
{
	if (iFindBox && iListBox)
	{		
		iFindBox->Editor().TextView()->SetCursorVisibilityL(TCursor::EFCursorInvisible, TCursor::EFCursorInvisible);
		CAknFilteredTextListBoxModel* model = static_cast<CAknFilteredTextListBoxModel*>(iListBox->Model());
		model->RemoveFilter();
		delete iFindBox;
		iFindBox = NULL;
	}
}


TKeyResponse CProtectionContainer::OfferKeyToFindBoxL(const TKeyEvent& aKeyEvent, TEventCode aType)
{
// Deseleziona tutti gli elementi che sono marcati
// Non e' possibile xche' la listbox ciuccia tutti gli eventi di keypress...
/*			CAknFilteredTextListBoxModel* model = STATIC_CAST(CAknFilteredTextListBoxModel*,iListBox->Model());
			TInt tot = model->Filter()->FilteredNumberOfItems();
			for (int i=0; i<tot; i++)
			{
				iListBox->View()->DeselectItem( i );
			}*/
/*			for (int i=0; i<iMarkers.Count(); i++)
			{
				TInt oriIndex = iMarkers[i];
				TInt filtIndex = GetFilteredIndexL(oriIndex);
				if (filtIndex >= 0)
					iListBox->View()->DeselectItem( filtIndex );
			}*/

            TBool needRefresh( EFalse );
            // Offers the key event to find box.
			TBool popup = (iStyle == CAknSearchField::EPopup);
			TKeyResponse ris = AknFind::HandleFindOfferKeyEventL(
  			   aKeyEvent, aType, this, iListBox, iFindBox, popup, needRefresh );

            if ( needRefresh )
                {
                SizeChanged();
                DrawNow();
                }
            if ( ris == EKeyWasConsumed )
                {
				__LOG_TXT("FindBox Key");
                } else
				{
				__LOG_TXT("FindBox NOKey");
				}

			__LOG("TxtLength:%d", iFindBox->TextLength());
//			iFindBox->GetSearchText(txt);
//			__FLOG(txt);

/*			// Riseleziona tutti gli elementi che erano marcati
			for (int i=0; i<iMarkers.Count(); i++)
			{
				TInt oriIndex = iMarkers[i];
				TInt filtIndex = GetFilteredIndexL(oriIndex);
				if (filtIndex >= 0)
					iListBox->View()->SelectItemL( filtIndex );
			}*/
			return ris;
}


TKeyResponse CProtectionContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
    if ( aType != EEventKey )
        return EKeyWasNotConsumed;

	if (!iListBox)
        return EKeyWasNotConsumed;

    switch ( aKeyEvent.iCode )
		{
        // Left Arrow pressed
		case EKeyBackspace:
		{
			if (!iFindBox)
				return EKeyWasNotConsumed;
			if (iFindBox->TextLength() == 0)
			{
				DeleteFindBox();
				SizeChanged();
				DrawNow();
				return EKeyWasConsumed;
			}
			return OfferKeyToFindBoxL(aKeyEvent, aType);
		}
		case EKeyLeftArrow:
		case EKeyRightArrow:
			return EKeyWasNotConsumed;
		case EKeyUpArrow:
		case EKeyDownArrow:
			return iListBox->OfferKeyEventL( aKeyEvent, aType );
		case EKeyDevice3:	// Da gestire in maniera differente perche' di default viene mostrato il menu' delle opzioni
			{
			__LOG_TXT("EKeyDevice3");
			if (iTouchSupported && !iAcceptTouchEvents)
				{
				__LOG_TXT("Touch event already dispatched");
				return EKeyWasConsumed;				
				}
			ChangeApplicationStatusL( GetSelectedUidL() );
			TBool checked = IsSelectedMarkedL();
			if (iObserver)
				iObserver->HandleItemChangeEventL( GetSelectedUidL() , checked);
			return EKeyWasConsumed;
			}
		default:
            {
			if (!iFindBox)
			{
			    iFindBox = GuiUtils::CreateSearchBoxL(*this, *iListBox, (CAknSearchField::TSearchFieldStyle)iStyle);
                SizeChanged();
				iFindBox->SetFocus(ETrue, EDrawNow);
				return EKeyWasNotConsumed;
				// Non e' possibile xche' viene inserito un numero invece di una lettera...
//				return OfferKeyEventL(aKeyEvent, aType);
			}
			return OfferKeyToFindBoxL(aKeyEvent, aType);
			}
		}
	return EKeyWasNotConsumed;
	}


CArrayFixFlat<TApaAppInfo>* CProtectionContainer::GetApplicationsLC(CArrayFixFlat<TApaAppInfo>* hiddenApps)
{
	CArrayFixFlat<TApaAppInfo>* userArray = new(ELeave)CArrayFixFlat<TApaAppInfo>(10);
	CleanupStack::PushL(userArray);

	CArrayFixFlat<TApaAppInfo>* romArray = new(ELeave)CArrayFixFlat<TApaAppInfo>(10);
	CleanupStack::PushL(romArray);

	CArrayFixFlat<TApaAppInfo>* systemArray = new(ELeave)CArrayFixFlat<TApaAppInfo>(10);
	CleanupStack::PushL(systemArray);

	RApaLsSession ls;
	User::LeaveIfError(ls.Connect());
	CleanupClosePushL(ls);
	
	User::LeaveIfError(ls.GetAllApps());

//	TInt ris(KErrNone);
	TApaAppInfo appInfo;
	TApaAppCapabilityBuf appCapab;

//	_LIT(KFAKEAPP, ".fakeapp");
	while (ls.GetNextApp(appInfo) == KErrNone)
	{
		// Cambiato nella 4.0
		appInfo.iCaption.Trim();
		appInfo.iShortCaption.Trim();
		
		if (appInfo.iShortCaption.Length() <= 0)
			appInfo.iShortCaption = appInfo.iCaption;
		
		if (appInfo.iShortCaption.Length() <= 0)
			continue;	// Deve avere un nome...

		/*AppInfo.iCaption.Trim();
		if (AppInfo.iCaption.Length() <= 0)
			continue;	// Deve avere un nome...*/

		if (appInfo.iUid.iUid == 0x101F4CD2)
			continue;	// Menu' S60

		if (appInfo.iUid.iUid == 0x200131CC ||
				appInfo.iUid.iUid == 0x200131C7 )
			continue;	// Guardian

		ls.GetAppCapability(appCapab, appInfo.iUid);
		
		//		if (AppInfo.iFullName.Right(8).MatchC(KFAKEAPP) == 0)
		//			continue;	// Applicazione java
		
		if (appCapab().iAppIsHidden)
			{
				systemArray->AppendL(appInfo);
			} else
			{
				appInfo.iFullName.LowerCase();
				if (appInfo.iFullName.Length() > 0 && appInfo.iFullName.Left(1) == _L("z"))
					romArray->AppendL(appInfo);				
				else
					userArray->AppendL(appInfo);				
			}
	}

	CleanupStack::PopAndDestroy(&ls);

/*	// Ordina array
	TKeyArrayFix captionKey(_FOFF(TApaAppInfo, iShortCaption), ECmpFolded);
	userArray->Sort(captionKey);
		
	romArray->Sort(captionKey);
	
	// Ordina array app di sistema
	//TKeyArrayFix captionKey(_FOFF(TApaAppInfo, iShortCaption), ECmpFolded);
	systemArray->Sort(captionKey);*/
	
	// Svuota Array User se e' il caso
	if (!iGuiSettings.iShowUserApps)
		{
		while (userArray->Count() > 0)
			{
			TApaAppInfo info = userArray->At(0);
			hiddenApps->AppendL(info);
			userArray->Delete(0);
			}		
		}
	
	// Processo array ROM -> in User o in Hidden
	while (romArray->Count() > 0)
		{
		TApaAppInfo info = romArray->At(0);
//		if (iGuiSettings.iShowRomApps)
		if (iGuiSettings.iShowUserApps)
			{
			userArray->AppendL(info);
			} else
			{
			hiddenApps->AppendL(info);				
			}
		romArray->Delete(0);
		}
	
	// Processo array System -> in User o in Hidden
	while (systemArray->Count() > 0)
		{
		TApaAppInfo info = systemArray->At(0);
		if (iGuiSettings.iShowSystemApps)
			{
			userArray->AppendL(info);
			} else
			{
			hiddenApps->AppendL(info);
			}
		systemArray->Delete(0);
		}
	CleanupStack::PopAndDestroy(systemArray); 
	CleanupStack::PopAndDestroy(romArray); 

	// Ordina array
	TKeyArrayFix captionKey(_FOFF(TApaAppInfo, iShortCaption), ECmpFolded);
	userArray->Sort(captionKey);

	return userArray;
}


CGulIcon* CProtectionContainer::GetApplicationIconL(const TUid& aAppUID)
{
	CFbsBitmap*	AppIcon(NULL);
	CFbsBitmap*	AppIconMsk(NULL);

	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
		// EAknsAppIconTypeList // EAknsAppIconTypeContext
	AknsUtils::CreateAppIconLC(skin, aAppUID,  EAknsAppIconTypeList, AppIcon, AppIconMsk);
//	__LOG_TXT("AknIconUtils");
//	AknIconUtils::CreateAppIconLC(skin, aAppUID,  EAknsAppIconTypeList, AppIcon, AppIconMsk);

	CGulIcon* ris = CGulIcon::NewL(AppIcon, AppIconMsk);

	CleanupStack::Pop(2);
	return ris;
}


void CProtectionContainer::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType)
{
}
