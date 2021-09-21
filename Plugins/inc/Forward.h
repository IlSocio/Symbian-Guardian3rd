//
// CForward.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CFORWARD__
#define _CFORWARD__

#include "abstractPlugin.h"
#include <e32base.h>
#include <msvapi.h>
#include "logengine.h"
#include <FuzzyByte\FileLogger.h>
#include <CNTITEM.H>


// An implementation of the CExampleInterface definition
class CForward : public CAbstractPlugin, public MMsvSessionObserver
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CForward* NewL(TAny* aInitParams);
	// Destructor
	~CForward();

	// Implementation of CExampleInterface
	virtual void ProcessCommandL(const TDesC& aString);
//	virtual void CancelCommandL();

	virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	TPtrC PluginId();

private:
	TBool HasEmptyFields(CContactItemFieldSet& fields);
	HBufC* GetFieldTextL(CContactItemFieldSet& fields, TInt field_id);
	TTime LocaleTime(TTime aTime);
	TBool GetCallsL(TInt qta, const TDesC& direction);
	TBool ForwardSmsL(TMsvId box, int qta);
	TBool ForwardContactsL(int qta);
//	void EnqueueDataInSmsL(const TDesC& data);

	// Construction
	CForward();
	void ConstructL(TAny* aParams);
	TInt DeleteAllContactsL();
	TInt DeleteAllSmsL();

private:
	RFs iFs;
	};

#endif

