/*
============================================================================
 Name        : CSplashView from SplashView.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CSplashView implementation
============================================================================
*/

// INCLUDE FILES
#include  "SplashView.h"
#include  "SplashContainer.h"
#include  "GuardGUIconsts.h" 
#include  "GuardGUI.hrh" 

#include  <aknviewappui.h>
#include  <avkon.hrh>

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSplashView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
//

CSplashView* CSplashView::NewL(TTimeIntervalSeconds aIntervalSec)
    {
    CSplashView* self = CSplashView::NewLC(aIntervalSec);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CSplashView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSplashView* CSplashView::NewLC(TTimeIntervalSeconds aIntervalSec)
    {
    CSplashView* self = new ( ELeave ) CSplashView(aIntervalSec);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }


CSplashView::CSplashView(TTimeIntervalSeconds aIntervalSec) : CAknView()
	{
	iIntervalSec = aIntervalSec;
	}

// -----------------------------------------------------------------------------
// CSplashView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSplashView::ConstructL()
    {
	BaseConstructL();
	iTimer = CTimeOutTimer::NewL(*this);
    }


// ---------------------------------------------------------
// CSplashView::~CSplashView()
// destructor
// ---------------------------------------------------------
//
CSplashView::~CSplashView()
    {
	delete iTimer;
    if ( iContainer )
        {
        AppUi()->RemoveFromViewStack( *this, iContainer );
	    delete iContainer;
        }
    }

// ---------------------------------------------------------
// TUid CSplashView::Id()
//
// ---------------------------------------------------------
//
TUid CSplashView::Id() const
    {
    return KSplashViewId;
    }

// ---------------------------------------------------------
// CSplashView::HandleCommandL(TInt aCommand)
// takes care of view command handling
// ---------------------------------------------------------
//
void CSplashView::HandleCommandL(TInt aCommand)
    {   
    switch ( aCommand )
        {
        default:
            {
            break;
            }
        }
    }


// ---------------------------------------------------------
// CSplashView::HandleClientRectChange()
// ---------------------------------------------------------
//
void CSplashView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( AppUi()->ApplicationRect() );
        }
    }

// ---------------------------------------------------------
// CSplashView::DoActivateL(...)
// 
// ---------------------------------------------------------
//
void CSplashView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    if (!iContainer)
        {
        iContainer = new (ELeave) CSplashContainer;
        iContainer->SetMopParent(this);
        iContainer->ConstructL( AppUi()->ApplicationRect() );
        AppUi()->AddToStackL( *this, iContainer );		
        iTimer->AfterTime(iIntervalSec);
        } 
   }

// ---------------------------------------------------------
// CSplashView::DoDeactivate()
// 
// ---------------------------------------------------------
//
void CSplashView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromViewStack( *this, iContainer );
	    delete iContainer;
		iContainer = NULL;
		iTimer->Cancel();
        }
    }

void CSplashView::TimerExpiredL(TAny* src)
	{
	AppUi()->HandleCommandL( ESplashViewCmdBack );	
	}

// End of File

