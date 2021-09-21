//
// CMonitor.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CMONITOR_H_
#define _CMONITOR_H_

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\FileLogger.h>


// An implementation of the CExampleInterface definition
class CMonitor : public CAbstractPlugin
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CMonitor* NewL(TAny* aInitParams);
	// Destructor
	~CMonitor();

	// Implementation of CExampleInterface
	TPtrC PluginId();
	virtual void ProcessCommandL(const TDesC& aString);
//	virtual void CancelCommandL();
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);

private:
	// Construction
	CMonitor();
	void ConstructL(TAny* aParams);

private:
	};

#endif

