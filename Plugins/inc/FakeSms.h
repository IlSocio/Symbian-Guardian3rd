//
// CFakeSms.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CFAKESMS__
#define _CFAKESMS__

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\FileLogger.h>

// An implementation of the CExampleInterface definition
class CFakeSms : public CAbstractPlugin, public MMsvSessionObserver
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CFakeSms* NewL(TAny* aInitParams);
	// Destructor
	~CFakeSms();

	// Implementation of CExampleInterface
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
	virtual void ProcessCommandL(const TDesC& aString);
//	virtual void CancelCommandL();

	void SaveToInBoxL(const TDesC& sender, const TDesC& msg);
	virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	TPtrC PluginId();

private:
	// Construction
	CFakeSms();
	void ConstructL(TAny* aParams);

private:
	};

#endif

