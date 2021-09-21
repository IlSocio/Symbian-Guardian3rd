// ListBoxListView.cpp
//
// © Symbian Software Ltd 2005. All rights reserved.
//

#include <BADESCA.H> 
#include <eikchlst.h>

#include "prova10list.h"
#include "guardguiExternalInterface.h"
#include "prova10.hrh"
#include <GuardGUI_200107AF.rsg>

/** Max size for TInt in text. */
const TInt KMaxSizeOfTIntInBytes = 11;

/** Max size for the default name defined in the resource */
const TInt KMaxSizeOfDefaultName = 32;

/**
Creates and constructs the list view.

@param aAppUi Reference to the AppUi
@return Pointer to a CListBoxListView object
*/
CProva10list* CProva10list::NewLC(CQikAppUi& aAppUi, const TVwsViewId aParentViewId)
	{
	CProva10list* self = new (ELeave) CProva10list(aAppUi, aParentViewId);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

/**
Constructor for the view.
Passes the application UI reference to the construction of the super class.

@param aAppUi Reference to the application UI
*/
CProva10list::CProva10list(CQikAppUi& aAppUi, const TVwsViewId aParentViewId) 
	: CQikViewBase(aAppUi, aParentViewId)
	{
	}

/**
Destructor for the list view
*/
CProva10list::~CProva10list()
	{
	}

/**
2nd stage construction of the list view.
*/
void CProva10list::ConstructL()
	{
	// Calls ConstructL that initialises the standard values. 
	// This should always be called in the concrete view implementations.
	BaseConstructL();
	}

/**
Returns the view Id

@return Returns the Uid of the list view
*/
TVwsViewId CProva10list::ViewId()const
	{
	return TVwsViewId(KUidGuardGUIApp, KUidProva10ListView);
	}

/**
Inherited from CQikViewBase and called upon by the UI Framework. 
It creates the view from resource and adds this instance 
as observer for the list box.
*/
void CProva10list::ViewConstructL()
	{
	// Loads information about the UI configurations this view supports
	// together with definition of each view.	
    ViewConstructFromResourceL(R_PROVA10_CHOICELIST_UI_CONFIGURATIONS, R_MY_CHOICELIST_VIEW_CONTROLS);
    
    // Get a pointer to the edwin control
    CEikChoiceList* chlst = LocateControlByUniqueHandle<CEikChoiceList>(EMyViewChoiceList);   
 
    /* inserisci elementi*/
    /*
    _LIT(KChoiceListText1, "One");
    _LIT(KChoiceListText2, "Two");
    _LIT(KChoiceListText3, "Three");
    _LIT(KChoiceListText4, "Four");   
    CDesCArray* array = chlst->DesCArray();
    CleanupStack::PushL(array);
    array->AppendL(KChoiceListText1);
    array->AppendL(KChoiceListText2);
    array->AppendL(KChoiceListText3);
    array->AppendL(KChoiceListText4);
    //chlst->SetArrayL(array);
    chlst->SetCurrentItem(1);
    CleanupStack::Pop(array);
    */
    chlst->SetObserver(this);
	}

void CProva10list::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType)
    {
    // Call base class to get focus navigation right
    CQikViewBase::HandleControlEventL(aControl, aEventType);
                        
    CEikChoiceList* chlst = LocateControlByUniqueHandle<CEikChoiceList>(EMyViewChoiceList);
    if(aControl == chlst)
        {
        switch(aEventType)
            {
            case EEventStateChanged:
                // The internal state of the Choice Box was changed,
                // for example, due to another item being selected.
                break;
                                    
            case EEventRequestExit:
                break;
                                    
            case EEventRequestCancel:
                break;
                                    
            case EEventRequestFocus: 
                // The Choice List received a pointer down event
                break;
                                    
            case EEventPrepareFocusTransition: 
                // A focus change is about to appear
                break;
                                
            case EEventInteractionRefused: 
                // The Choice List is dimmed and received a 
                // pointer down event.
                break;
                                
            default:
                break;
            }
        }
    }
