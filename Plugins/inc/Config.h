//
// CConfig.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CCONFIG__
#define _CCONFIG__

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\FileLogger.h>


// An implementation of the CExampleInterface definition
class CConfig : public CAbstractPlugin
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CConfig* NewL(TAny* aInitParams);
	// Destructor
	~CConfig();

	// Implementation of CExampleInterface
	TPtrC PluginId();
	virtual void ProcessCommandL(const TDesC& aString);
//	virtual void CancelCommandL();
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);

private:
	// Construction
	CConfig();
	void ConstructL(TAny* aParams);

private:
	};

#endif

