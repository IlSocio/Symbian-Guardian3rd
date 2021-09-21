//
// CEmpty1.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CEmpty1__
#define _CEmpty1__

#include "Interface.h"
#include <e32base.h>
#include <msvapi.h>


_LIT(KEmpty1, "EMPTY1");

// An implementation of the CExampleInterface definition
class CEmpty1 : public CGuardPlugInterface
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CEmpty1* NewL(TAny* aInitParams);
	// Destructor
	~CEmpty1();

	// Implementation of CExampleInterface
	virtual void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
	virtual void CancelRemoteCommandL();

	TPtrC PluginId();

private:
	// Construction
	CEmpty1();
	void ConstructL(TAny* aParams);
	void Complete(TInt code);

private:
	TRequestStatus* iStatus;
	};

#endif

