
#include "ForegroundObserver.h"

#include <APGWGNAM.H>
#include <APGTASK.H>


CFgrObserver* CFgrObserver::NewL(MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = CFgrObserver::NewLC(aCallBack);
	CleanupStack::Pop(self);
	return self;
	}
 
 
CFgrObserver* CFgrObserver::NewLC(MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = new (ELeave) CFgrObserver(aCallBack);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
 
 
CFgrObserver::CFgrObserver(MFgrCallBack& aCallBack)
:CActive(EPriorityLow), iCallBack(aCallBack)
{
}



CFgrObserver::~CFgrObserver()
{
	Cancel();
	iWg.Close();
	iWsSession.Close();
	__LOG_TXT("Destructor");
	__LOG_CLOSE;
}
 
void CFgrObserver::ConstructL()
{
	User::LeaveIfError(iWsSession.Connect());

	CActiveScheduler::Add(this);
	__LOG_OPEN("Guardian", "FgrObserver.txt"); 
	
	iWg=RWindowGroup(iWsSession);
	User::LeaveIfError(iWg.Construct((TUint32)&iWg, EFalse));

	iWg.SetOrdinalPosition(-1);
	iWg.EnableReceiptOfFocus(EFalse);
 
	CApaWindowGroupName* wn=CApaWindowGroupName::NewLC(iWsSession);
	wn->SetHidden(ETrue);
//	wn->SetCaptionL(_L("FGR"));
	wn->SetWindowGroupName(iWg);
	CleanupStack::PopAndDestroy();/**/

	User::LeaveIfError(iWg.EnableFocusChangeEvents());
	User::LeaveIfError(iWg.EnableGroupChangeEvents());
//	User::LeaveIfError(iWg.EnableGroupListChangeEvents());
}
// 16:43

void CFgrObserver::RunL()
{
	TWsEvent e;
	if (iStatus == KErrNone) 
	{
		iWsSession.GetEvent(e);
	}
 
	if (iStatus == KErrCancel) 
	{
		return;
	}

	switch(e.Type()) 
	{
 		case EEventFocusGroupChanged :
			{
	        // __LOG_TXT("Event Focus"));
			break;
			}
 		case EEventWindowGroupsChanged:
			{
	        // __LOG_TXT("Event Group"));
			break;
			}
		default:
			__LOG("UNKNOWN EVENT:%d", e.Type());
			break;
	}

	TInt wgid = iWsSession.GetFocusWindowGroup();
	
//    iWsSession.SendEventToWindowGroup(wgid, e);	// SCHIANTA NGAGE... ED ERA PROPRIO UNA PORCATA... RALLENTAVA TUTTO...
	__LOG("WgId:%d", wgid);
	CApaWindowGroupName* gn = CApaWindowGroupName::NewLC(iWsSession, wgid);
	TUid uid = gn->AppUid();
	__LOG_DES(gn->WindowGroupName());
	CleanupStack::PopAndDestroy();
	// Menu', Idle, Telefono
	// uid.iUid != 0x101F4CD2 && uid.iUid != 0x101fd64c && uid.iUid != 0x100058b3

	iCurrUid = uid;
	if (uid.iUid != 0 && uid.iUid != iLastUid.iUid)
		iCallBack.ForegroundEventL(uid);
	iLastUid = uid;/**/

	StartObserver();
}
 
void CFgrObserver::DoCancel()
{
	iWsSession.EventReadyCancel();
}
 
void CFgrObserver::StartObserver()
{
	if(IsActive())
		{
		__LOG_TXT("Already Active");
		return;
		}
	iWsSession.EventReady(&iStatus);
	SetActive();
	__LOG_TXT("Listening...");
}

/*
void CFgrObserver::ChangeOwningWindowGroup(TInt owningWgId)
	{
	TInt wgid = iWsSession.GetFocusWindowGroup();
	TInt handle = iWsSession.GetWindowGroupHandle(wgid);
	RWindowGroup wg(iWsSession);
	wg.Construct(handle);
    wg.SetOwningWindowGroup( owningWgId );
    wg.Close();
	}*/
