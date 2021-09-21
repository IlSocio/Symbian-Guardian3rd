/*
============================================================================
 Name        : ProcMonitor.cpp
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CProcMonitor implementation
============================================================================
*/

#include "ProcMonitor.h"



CProcMonitor::CProcMonitor(MProcObserver& observer) : CActive(EPriorityStandard), iObserver(observer)	// Standard priority
{
}


void CProcMonitor::ConstructL(const TDesC& process)
{
	CActiveScheduler::Add(this);				// Add to scheduler
	TFindProcess findProc(process);
	if (findProc.Next(iProcName) != KErrNotFound)
	{
		User::LeaveIfError(iSysStartProcess.Open(findProc));
		iSysStartProcess.Logon(iStatus);
		SetActive();
	} else 
	{	// Il processo e' gia' stato chiuso...
		SetActive();
		TRequestStatus* status=&iStatus;
		User::RequestComplete(status, KErrNone);
	}
}

CProcMonitor::~CProcMonitor()
{
	Cancel(); // Cancel any request, if outstanding
	iSysStartProcess.Close();
}

void CProcMonitor::DoCancel()
{
	iSysStartProcess.LogonCancel(iStatus);
}

void CProcMonitor::RunL()
{
	User::LeaveIfError(iStatus.Int());

	iObserver.NotifyProcTerminated(iProcName);
}
