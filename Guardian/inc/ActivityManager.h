#ifndef __ACTIVITYMANAGER_H
#define __ACTIVITYMANAGER_H

#include <e32cmn.h>
#include <e32base.h>
#include <W32STD.H>


class MActivityManagerObserver
{
public :
	virtual void ActivityDetected() = 0;
	virtual void InactivityDetected() = 0;
};



class CActivityManager : public CActive
{
public:
	static CActivityManager* NewL(MActivityManagerObserver* aObserver, TInt aTimeout = 60);
	~CActivityManager();
	void SetTimeout(TInt aTimeout);
	void Start();
	void Reset();
 
protected: // from CActive
	void DoCancel();
	void RunL();
 
protected:
	CActivityManager(MActivityManagerObserver* aObserver, TInt aTimeout);
	void ConstructL();
 
protected:
	enum TWatch { ENone = 0, EWaitingForInactivity, EWaitingForActivity };

protected:
	RTimer iTimer;
	TWatch iWatch;
	MActivityManagerObserver* iObserver; ///The observer of activity status
	TInt iTimeout; ///Current inactivity period
};

#endif
