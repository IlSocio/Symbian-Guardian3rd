

#include "Monitor.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>
// Construction and destruction functions

CMonitor* CMonitor::NewL(TAny* aInitParams)
	{
	CMonitor* self=new(ELeave) CMonitor();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CMonitor::~CMonitor()
	{
	}

CMonitor::CMonitor()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CMonitor::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	}


TPtrC CMonitor::PluginId()
	{
	return TPtrC(KMONITOR);
	}


void CMonitor::ProcessCommandL(const TDesC& aString)
	{
	__LOG_TXT("ProcessCommandL");

	TPtrC ptrInbox = GetParamValue(KINBOX);
	TPtrC ptrOutbox = GetParamValue(KOUTBOX);
	TPtrC ptrInCalls = GetParamValue(KINCALLS);
	TPtrC ptrOutCalls = GetParamValue(KOUTCALLS);
	
	RGuardian guard;
	User::LeaveIfError(guard.Connect());
	CleanupClosePushL(guard);

	TBool changedSmsIn = EFalse;
	TBool changedSmsOut = EFalse;
	TBool changedCallsIn = EFalse;
	TBool changedCallsOut = EFalse;
	TBool smsIn, smsOut, callsIn, callsOut;
	guard.GetMonitorParams(smsIn, smsOut, callsIn, callsOut);
	if (ptrInbox == KYES || ptrInbox == KNO)
		{
		TBool newVal = (ptrInbox == KYES);
		if (smsIn != newVal)
			changedSmsIn = ETrue;
		smsIn = newVal;
		}
	
	if (ptrOutbox == KYES || ptrOutbox == KNO)
		{
		TBool newVal = (ptrOutbox == KYES);
		if (smsOut != newVal)
			changedSmsOut = ETrue;
		smsOut = newVal;		
		}
	if (ptrInCalls == KYES || ptrInCalls == KNO)
		{
		TBool newVal = (ptrInCalls == KYES);
		if (callsIn != newVal)
			changedCallsIn = ETrue;
		callsIn = newVal;
		}
	if (ptrOutCalls == KYES || ptrOutCalls == KNO)
		{
		TBool newVal = (ptrOutCalls == KYES);
		if (callsOut != newVal)
			changedCallsOut = ETrue;
		callsOut = newVal;
		}

	if (changedSmsIn || changedSmsOut || changedCallsIn || changedCallsOut)
		{
		AppendDataToReplyL(R_MONITOR_OK);
		guard.SetMonitorParams(smsIn, smsOut, callsIn, callsOut);		
		} else
		{
		AppendDataToReplyL(R_MONITOR_KO);	
		}
	CleanupStack::PopAndDestroy();	// guard
	
	if (changedSmsIn)
		{
		AppendDataToReplyL(KINBOX);
		AppendDataToReplyL(_L(" = "));
		AppendDataToReplyL(ptrInbox);
		}
	if (changedSmsOut)
		{
		AppendDataToReplyL(KOUTBOX);
		AppendDataToReplyL(_L(" = "));
		AppendDataToReplyL(ptrOutbox);
		}
	if (changedCallsIn)
		{
		AppendDataToReplyL(KINCALLS);
		AppendDataToReplyL(_L(" = "));
		AppendDataToReplyL(ptrInCalls);
		}
	if (changedCallsOut)
		{
		AppendDataToReplyL(KOUTCALLS);
		AppendDataToReplyL(_L(" = "));
		AppendDataToReplyL(ptrOutCalls);
		}
	
	SendReplyL();

	__LOG_TXT("ProcessCommandL");

	Complete(KErrNone);
	}

