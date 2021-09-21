#ifndef __FOREGROUNDOBSERVER_H
#define __FOREGROUNDOBSERVER_H

#include <e32cmn.h>
#include <e32base.h>
#include <W32STD.H>
#include <FuzzyByte\FileLogger.h>


class MFgrCallBack 
{
public:
	virtual void ForegroundEventL(TUid aAppUid) = 0;
};
 
class CFgrObserver : public CActive 
{
public:
	static CFgrObserver* NewL(MFgrCallBack& aCallBack);
	static CFgrObserver* NewLC(MFgrCallBack& aCallBack);
	virtual ~CFgrObserver();
	void StartObserver();
	
//	void ChangeOwningWindowGroup(TInt wgId);
private:
	CFgrObserver(MFgrCallBack& aCallBack);
	void ConstructL();
	void RunL();
	void DoCancel();
private:
	TUid			iCurrUid;
	TUid			iLastUid;
	MFgrCallBack& 	iCallBack;
	RWsSession      iWsSession;
	RWindowGroup    iWg; 
	__LOG_DECLARATION_MEMBER
};

#endif

