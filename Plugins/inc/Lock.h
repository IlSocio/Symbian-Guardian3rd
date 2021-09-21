//
// CLock.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CLock__
#define _CLock__

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>


// An implementation of the CExampleInterface definition
class CLock : public CAbstractPlugin
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CLock* NewL(TAny* aInitParams);
	// Destructor
	~CLock();

	// Implementation of CExampleInterface
	TPtrC PluginId();
	virtual void ProcessCommandL(const TDesC& aString);
//	virtual void CancelCommandL();
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);

private:
	// Construction
	CLock();
	void ConstructL(TAny* aParams);

private:
	};

#endif

