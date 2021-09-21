

#include "Lock.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>
// Construction and destruction functions

CLock* CLock::NewL(TAny* aInitParams)
	{
	CLock* self=new(ELeave) CLock();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CLock::~CLock()
	{
	}

CLock::CLock()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CLock::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	}


TPtrC CLock::PluginId()
	{
	return TPtrC(KLOCK);
	}


void CLock::ProcessCommandL(const TDesC& aString)
	{
	__LOG_TXT("ProcessCommandL");

	TBool off = ( iDataUpper.Find( KOFF ) >= 0 );

	RGuardian guard;
	User::LeaveIfError(guard.Connect());
	CleanupClosePushL(guard);
	
	guard.SetLocked(!off);
	if (off)
		AppendDataToReplyL(R_LOCK_OFF);
	else 
		AppendDataToReplyL(R_LOCK_ON);
	
	CleanupStack::PopAndDestroy(&guard);
	
	SendReplyL();
/**/
	__LOG_TXT("ProcessCommandL");

	Complete(KErrNone);
	}

