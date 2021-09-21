 /*
============================================================================
 Name        : ImeiEngine.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CSecurityCode declaration
============================================================================
*/

#ifndef SECURITYCODE_H
#define SECURITYCODE_H

#include <e32base.h>	
#include <e32std.h>
#include <w32std.h>	
#include <etel3rdparty.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\TimeOutTimer.h>



class MSecurityCodeNotifier
	{
public:
	virtual void GotSecurityCodeL(TInt error, TBool isValidCode) = 0;
	};


class CSecurityCode : public CActive, public MTimeOutNotifier
	{
	public:
		static CSecurityCode* NewL(RWsSession& aSession, MSecurityCodeNotifier& notifier);
		~CSecurityCode();

	public: // New functions
		void RequestCodeL(TUid aAppUid, const TDesC& aGoodCode);

	protected:
		void ConstructL();

	private:
        virtual void TimerExpiredL(TAny* src);

	private: // From CActive
		CSecurityCode(RWsSession& aSession, MSecurityCodeNotifier& notifier);
		void RunL();	
		void DoCancel();
		TInt RunError(TInt /*aError*/);

	private:
		TBuf8<20> iPass8;
		TBuf8<20> iResp8;
		TBuf<20> iGoodCode;
		TBuf<20> iRespCode;
		RNotifier iNotif;
		RWsSession& iSession;
		CTimeOutTimer* iTimer;
		TUid iAppUid;
		MSecurityCodeNotifier* iObs;
		__LOG_DECLARATION_MEMBER
	};

#endif

