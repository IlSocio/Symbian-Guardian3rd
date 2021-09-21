/*
============================================================================
 Name        : LogsRemover.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CLogsRemover implementation
============================================================================
*/

#include "LogsRemover.h"

#include <logcli.h>

#ifndef __SERIES60_3X__
#include <logwraplimits.h>
#endif

CLogsRemover::CLogsRemover(MLogsRemoverObserver& obs) : CActive(EPriorityStandard), iObs(obs)
{
CActiveScheduler::Add( this );
}


CLogsRemover::~CLogsRemover()
{
	__LOG_TXT("Destructor");
	Cancel();
	if (iLogClient)
		delete iLogClient;
	iFs.Close();
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
}

CLogsRemover* CLogsRemover::NewLC(MLogsRemoverObserver& obs)
{
	CLogsRemover* self = new (ELeave)CLogsRemover(obs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CLogsRemover* CLogsRemover::NewL(MLogsRemoverObserver& obs)
{
	CLogsRemover* self=CLogsRemover::NewLC(obs);
	CleanupStack::Pop(self); // self;
	return self;
}

void CLogsRemover::ConstructL()
{
	__LOG_OPEN("Guardian", "Logs.txt");
	User::LeaveIfError( iFs.Connect() );
	iLogClient = CLogClient::NewL(iFs);
}


void CLogsRemover::RemoveAllLogs()
{	
	__LOG_TXT("RemoveAllLogs");
	if (IsActive())
		Cancel();
	__LOG_TXT("ClearLogs");
	iLogClient->ClearLog( KLogNullRecentList, iStatus );
	__LOG_TXT("SetActive");
	SetActive();
}


void CLogsRemover::RunL()
	{
	iObs.LogsRemovedL();
	}


// How to cancel me
void CLogsRemover::DoCancel()
	{
	iLogClient->Cancel();
	}
	

