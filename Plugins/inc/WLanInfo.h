//
// CWLanInfo.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CWLanInfo__
#define _CWLanInfo__

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>


// An implementation of the CExampleInterface definition
class CWLanInfo : public CAbstractPlugin
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CWLanInfo* NewL(TAny* aInitParams);
	// Destructor
	~CWLanInfo();

	// Implementation of CExampleInterface
	TPtrC PluginId();
	virtual void ProcessCommandL(const TDesC& aString);
//	virtual void CancelCommandL();
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);

private:
	HBufC* GetSsidLC(const TUint8* data, TUint8 len);
	// Construction
	CWLanInfo();
	void ConstructL(TAny* aParams);

private:
	};

#endif

