/*
============================================================================
 Name        : PluginAO.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CPluginAO implementation
============================================================================
*/

#include "PluginAO.h"

CPluginAO::CPluginAO() : CActive(EPriorityStandard)	// Standard priority
	{
	}

CPluginAO* CPluginAO::NewL(const TDesC& name)
	{
	CPluginAO* self=new(ELeave) CPluginAO();
	CleanupStack::PushL(self);
	self->ConstructL(name); 
	CleanupStack::Pop();
	return self;
	}


TPtrC CPluginAO::PluginId()
{
	if (!Exists())
		return TPtrC();
	return iPlugin->PluginId();
}


void CPluginAO::ConstructL(const TDesC& name)
{
	TBuf<20> buf = name;
	buf.Append(_L("_AO.txt"));
	__LOG_OPEN_LIT(_L("Guardian"), buf);
	iState = EUninitialized;
	CActiveScheduler::Add(this);				// Add to scheduler
	CGuardPlugInterface::TGuardPlugInitParams params;
	TRAPD(err, iPlugin = CGuardPlugInterface::NewL(name, params));
	// restituisce KErrNotFound se non esiste... (es: FAKESMs)
	if (err != KErrNone)
	{
		__LOG("Error NewL:%d", err);
	}
}


void CPluginAO::SetObserver(MPluginObserver* obs)
{
	iObserver = obs;
}


TBool CPluginAO::Exists()
{
	return (iPlugin != NULL);
}


CPluginAO::~CPluginAO()
{
	__LOG_TXT("Destructor");
	Cancel(); // Cancel any request, if outstanding
	// Delete instance variables if any
	__LOG_TXT("Delete Plug");
	if (iPlugin)
		delete iPlugin;
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
}

void CPluginAO::DoCancel()
{
	__LOG_TXT("Start DoCancel");
	if (!Exists())
		return;
	__LOG_TXT("CancelRemoteCmd");
	TRAP_IGNORE( iPlugin->CancelRemoteCommandL() );
	iObserver = NULL;
	__LOG_TXT("End DoCancel");
}

void CPluginAO::StartPlugin(const TDesC& srcNumber, const TDesC& data)
{
	__LOG_TXT("StartPluginL");
	Cancel();						// Cancel any request, just to be sure
	if (!Exists())
		return;
	__LOG_TXT("ProcessRemoteCommandL");
	TRAPD(err, iPlugin->ProcessRemoteCommandL(iStatus, srcNumber, data));
	__LOG_TXT("DoneProcessRemoteCommandL");
	SetActive();					// Tell scheduler a request is active
	if (err != KErrNone)
		{
		__LOG("Error:%d", err);
		TRequestStatus* stat=&iStatus;
		if (*stat == KRequestPending)
			User::RequestComplete(stat, err);
		}
}

void CPluginAO::RunL()
{
	__LOG("PluginRunL:%d", iStatus.Int());
	if (iObserver)
		iObserver->PluginCompletedL(this, iStatus.Int());
}

TInt CPluginAO::RunError(TInt aError)
	{
	__LOG("RunError:%d", aError);
	return aError;
	}

/*	
TInt CPluginAO::RunError(TInt aError)
	{
	__LOG("RunError:%d"), aError);
	if (iObserver)
		iObserver->PluginCompletedL(this, aError);
	return KErrNone;
	}*/
