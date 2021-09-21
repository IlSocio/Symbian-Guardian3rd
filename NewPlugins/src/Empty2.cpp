

#include "Empty2.h"


// Construction and destruction functions

CEmpty2* CEmpty2::NewL(TAny* aInitParams)
	{
	CEmpty2* self=new(ELeave) CEmpty2();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CEmpty2::~CEmpty2()
	{
	}


TPtrC CEmpty2::PluginId()
	{
	return TPtrC(KEmpty2);
	}


CEmpty2::CEmpty2()
// Store input/output parameters
	{
	}

void CEmpty2::ConstructL(TAny* aInitParams)
	{
	}


void CEmpty2::CancelRemoteCommandL()
	{
	// TODO: Add code if you need to cancel any pending async requests.
	if (iStatus == NULL)
		return;
	if (*iStatus == KRequestPending)
		{
		Complete(KErrCancel);
		}
	}


void CEmpty2::Complete(TInt code)
	{
	if (iStatus == NULL)
		return;
	if (*iStatus == KRequestPending)
		{
		User::RequestComplete(iStatus, code);
		}	
	}


void CEmpty2::ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString)
	{
	iStatus = &aCompletionStatus;
	CancelRemoteCommandL();
	*iStatus = KRequestPending;

	// TODO: Add your code here...
	
	
	
	// TODO: Remove the code below if the request has not been completed yet...
	Complete(KErrNone);
	}

