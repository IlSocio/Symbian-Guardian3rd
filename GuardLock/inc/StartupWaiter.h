#ifndef __STARTUPWAITER_H
#define __STARTUPWAITER_H

#include <FuzzyByte\FileLogger.H>
#include <FuzzyByte\PubSubObserver.H>
#include <FuzzyByte\TimeOutTimer.H>
#include <FuzzyByte\Processes.H>
#include <e32base.h>
#include <e32cons.h>            // Console


class CStartupWaiter : CBase, public MPubSubNotifier, public MTimeOutNotifier
	{
public:
	static CStartupWaiter* NewLC();
	void StartMonitorL(RFs& fs);

private:	
	virtual ~CStartupWaiter();
	CStartupWaiter();
	void ConstructL();
	
private:
    virtual void TimerExpiredL(TAny* src);
	virtual void PropertyReadyL(TAny* src);

private:
	CPubSubWaiter* iPubSubWaiter;
	CTimeOutTimer* iTimer;
	TBool iMenuIsReady;
	TUint32 iLockDelay;
	__LOG_DECLARATION_MEMBER
	};

#endif
