

#include "Empty1.h"


// Construction and destruction functions

CEmpty1* CEmpty1::NewL(TAny* aInitParams)
	{
	CEmpty1* self=new(ELeave) CEmpty1();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CEmpty1::~CEmpty1()
	{
	}


TPtrC CEmpty1::PluginId()
	{
	return TPtrC(KEmpty1);
	}


CEmpty1::CEmpty1()
// Store input/output parameters
	{
	}

void CEmpty1::ConstructL(TAny* aInitParams)
	{
	}


void CEmpty1::CancelRemoteCommandL()
	{
	// TODO: Add code if you need to cancel any pending async requests.
	if (iStatus == NULL)
		return;
	if (*iStatus == KRequestPending)
		{
		Complete(KErrCancel);
		}
	}


void CEmpty1::Complete(TInt code)
	{
	if (iStatus == NULL)
		return;
	if (*iStatus == KRequestPending)
		{
		User::RequestComplete(iStatus, code);
		}	
	}


void CEmpty1::ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString)
	{
	iStatus = &aCompletionStatus;
	CancelRemoteCommandL();
	*iStatus = KRequestPending;

	// TODO: Add your code here...
	
	
	
	// TODO: Remove the code below if the request has not been completed yet...
	Complete(KErrNone);
	}

