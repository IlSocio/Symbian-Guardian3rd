
#include "activitymanager.h"

CActivityManager* CActivityManager::NewL(MActivityManagerObserver* aObserver, TInt aTimeout)
{
	CActivityManager* self = new (ELeave) CActivityManager(aObserver, aTimeout);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}

 
CActivityManager::CActivityManager(MActivityManagerObserver* aObserver, TInt aTimeout)
: CActive(CActive::EPriorityHigh), iObserver(aObserver), iTimeout(aTimeout)
{
	CActiveScheduler::Add(this);
}


CActivityManager::~CActivityManager()
{
	Cancel();
	iTimer.Close();
}


void CActivityManager::ConstructL()
{
	iTimer.CreateLocal();
}


void CActivityManager::SetTimeout(TInt aTimeout)
{
	iTimeout = aTimeout;
	Reset();
}
 

void CActivityManager::Reset()
{
	Cancel();
	Start();
}
 

void CActivityManager::DoCancel()
{
	iTimer.Cancel();
	iWatch = ENone;
}


void CActivityManager::Start()
{
	if (IsActive())
		return;
	iWatch = EWaitingForInactivity;
	iTimer.Inactivity(iStatus, iTimeout);
	SetActive();
}


void CActivityManager::RunL()
{
	if (iStatus != KErrNone)
	{
		iWatch = ENone;
		return;
	}
	if (iWatch == EWaitingForInactivity)
	{
		TInt inactivity = User::InactivityTime().Int();
		if (inactivity >= iTimeout)
		{
			if (iObserver)
				iObserver->InactivityDetected();
			if (!IsActive()) //observer might have called a Reset()
			{
				iTimer.Inactivity(iStatus, 0);
				iWatch = EWaitingForActivity;
			}
		}
		else
		{
			iTimer.Inactivity(iStatus, iTimeout);
		}
	}
	if (iWatch == EWaitingForActivity)
	{
		if (iObserver)
			iObserver->ActivityDetected();
		if (!IsActive()) //observer might have called a Reset()
		{
			iTimer.Inactivity(iStatus, iTimeout);
			iWatch = EWaitingForInactivity;
		}
	}
	if (!IsActive()) //observer might have called a Reset()
	{
		SetActive();
	}
}
