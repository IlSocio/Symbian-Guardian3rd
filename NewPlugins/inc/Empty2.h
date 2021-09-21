//
// CEmpty2.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CEmpty2__
#define _CEmpty2__

#include "Interface.h"
#include <e32base.h>
#include <msvapi.h>


_LIT(KEmpty2, "EMPTY2");

// An implementation of the CExampleInterface definition
class CEmpty2 : public CGuardPlugInterface
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CEmpty2* NewL(TAny* aInitParams);
	// Destructor
	~CEmpty2();

	// Implementation of CExampleInterface
	virtual void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
	virtual void CancelRemoteCommandL();

	TPtrC PluginId();

private:
	// Construction
	CEmpty2();
	void ConstructL(TAny* aParams);
	void Complete(TInt code);

private:
	TRequestStatus* iStatus;
	};

#endif

