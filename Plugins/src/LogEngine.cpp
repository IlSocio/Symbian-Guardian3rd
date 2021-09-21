/*
* ============================================================================
*  Name     : CLogEngine from LogExEngine.h
*  Part of  : LogExample
*  Created  : 26.05.2005 by Forum Nokia
*  Implementation notes:
*  Version  : 1.0
*  Copyright: Nokia Corporation
* ============================================================================*/

#include "LogEngine.h"

#include <e32cons.h>
#include <e32math.h>	// Random()
#include <eikenv.h>
#include <logwrap.h>
#include <logwrap.hrh>

#ifndef __SERIES60_3X__
#include <logwraplimits.h>
#endif




// ----------------------------------------------------------
// CLogEngine::CLogEngine():CActive(EPriorityStandard)
// Defines priority for object
// ----------------------------------------------------------
//
CLogEngine::CLogEngine(RFs& fs):CActive(EPriorityStandard), iFs(fs)
	{
	iTask = ELogNone;
	}

// ----------------------------------------------------
// CLogEngine::~CLogEngine()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
//
CLogEngine::~CLogEngine()
	{
	__LOG_TXT("Destructor");
	Cancel();

	if (iLogViewEvent)
		delete iLogViewEvent;
	if (iLogClient)
		delete iLogClient;
	if (iLogFilter)
		delete iLogFilter;

	if ( iWait )
	{
		delete iWait;
		iWait = NULL;
	}
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}


// ----------------------------------------------------
// CLogEngine::NewL()
// Symbian 2-phase constructor
// ----------------------------------------------------
//
CLogEngine* CLogEngine::NewL(RFs& fs)
	{
	CLogEngine* self = CLogEngine::NewLC(fs);
	CleanupStack::Pop(self);
	return self;
	}

// ----------------------------------------------------
// CLogEngine::NewLC()
// Symbian 2-phase constructor
// ----------------------------------------------------
//
CLogEngine* CLogEngine::NewLC(RFs& fs)
	{
	CLogEngine* self = new (ELeave) CLogEngine(fs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// ================= PRIVATE =======================

// ----------------------------------------------------
// CLogEngine::ConstructL()
// Symbian 2-phase constructor
// ----------------------------------------------------
//
void CLogEngine::ConstructL()
	{
	__LOG_OPEN("Guardian", "LogEngine.txt");
	iWait = new (ELeave) CActiveSchedulerWait();

	// Establish connection to log engine
	iLogClient = CLogClient::NewL(iFs);

	// Log view and view for recent events events with standard priority
	iLogViewEvent = CLogViewEvent::NewL(*iLogClient);

	// Filter for events
	iLogFilter = CLogFilter::NewL();

	iTask = ELogNone; // Default task for RunL

	CActiveScheduler::Add(this);
	}


// ----------------------------------------------------
// CLogEngine::RunL()
// RunL
// ----------------------------------------------------
//
void CLogEngine::RunL()
	{
	if ( iWait->IsStarted() )
		iWait->AsyncStop();
	TInt completed = iTask;
//	iTask = ELogNone;
	// NOTA: Impostando iTask su None e' possibile richiamare Cancel senza problemi...
	// Inoltre, bisogna impostarlo prima di chiamare una eventuale CallBack altrim.
	// Una successiva chiamata Asincrona fatta dalla CallBack non servita' a nulla
	// perche' subito dopo viene impostato iFunc a None.
	if(iStatus.Int() != KErrNone) // ERRORE
	{
		return;
	}
	switch (completed)
		{
		case EGetEvent:
			{
			break;
			}
		default:
			{
			break;
			}
		}
	}


void CLogEngine::StartWait( )
    {
	if ( iWait->IsStarted() != (TInt)ETrue )
        {
        iWait->Start();
        }
    }


// ----------------------------------------------------
// CLogEngine::RunError()
// RunL can leave so we need to implement RunError method
// ----------------------------------------------------
//
TInt CLogEngine::RunError(TInt anError)
	{
	return anError;
	}

// ----------------------------------------------------
// CLogEngine::DoCancel()
// Method to cancel outstanding request
// ----------------------------------------------------
//
void CLogEngine::DoCancel()
	{
	__LOG_TXT("DoCancel");
	if ( iWait->IsStarted() )	// ***
		iWait->AsyncStop();		// ***

	//Cancel appropriate request
	switch ( iTask )
		{
		case EGetEvent:
			{
			iLogViewEvent->Cancel();
			break;
			}
		default:
			break;
		}
	iTask = ELogNone;
	}


void CLogEngine::SetEventFilterDirectionMissed()
	{
	TBuf<KLogMaxDirectionLength> direction;
	iLogClient->GetString(direction, R_LOG_DIR_MISSED);
	iLogFilter->SetDirection(direction);
	}

// ----------------------------------------------------
// CLogEngine::SetEventFilterDirectionIncoming()
// Sets incoming events filtering
// ----------------------------------------------------
//
void CLogEngine::SetEventFilterDirectionIncoming()
	{
	TBuf<KLogMaxDirectionLength> direction;
	iLogClient->GetString(direction, R_LOG_DIR_IN);
	iLogFilter->SetDirection(direction);
	}

// ----------------------------------------------------
// CLogEngine::SetEventFilterDirectionOutgoing()
// Sets outgoing events filtering
// ----------------------------------------------------
//
void CLogEngine::SetEventFilterDirectionOutgoing()
	{
	TBuf<KLogMaxDirectionLength> direction;
	iLogClient->GetString(direction, R_LOG_DIR_OUT);
	iLogFilter->SetDirection(direction);
	}

// ----------------------------------------------------
// CLogEngine::SetEventFilterEventTypeVoice()
// Sets voice type events filtering
// ----------------------------------------------------
//
void CLogEngine::SetEventFilterEventTypeVoice()
	{
	iLogFilter->SetEventType(KLogCallEventTypeUid);
	}

// ----------------------------------------------------
// CLogEngine::SetEventFilterEventTypeSMS()
// Sets sms events filtering
// ----------------------------------------------------
//
void CLogEngine::SetEventFilterEventTypeSMS()
	{
	iLogFilter->SetEventType(KLogShortMessageEventTypeUid);
	}

// ----------------------------------------------------
// CLogEngine::ClearEventFilter()
// Clears filter
// ----------------------------------------------------
//
void CLogEngine::ClearEventFilterL()
	{
	// Empty the active filter copying empty filter to it
	if (iLogFilter)
		{
		delete iLogFilter;
		iLogFilter = NULL;
		}
	iLogFilter = CLogFilter::NewL();
	}

// ----------------------------------------------------
// CLogEngine::ReadEventsL()
// Reads events from main event database
// ----------------------------------------------------
//
TBool CLogEngine::ReadEventsL(const CLogEvent* &event) // puntatore ad una costante event
	{
	__LOG_TXT("ReadEvents");
	if ( IsActive() )
		{
		Cancel();
		}

	if (iTask == EGetEvent)
	{
		__LOG_TXT("Task = GetEvent");
		TBool hasNext = iLogViewEvent->NextL(iStatus);
		if(!hasNext)
		{
			__LOG_TXT("HasNext = False");
			event = NULL;
			iTask = ELogNone;
			return EFalse;
		}
		SetActive();
		StartWait();
		event = &iLogViewEvent->Event();
		return ETrue;
	}
	__LOG_TXT("SetFilter");
	TBool hasEvents = iLogViewEvent->SetFilterL(*iLogFilter, iStatus);
	// ETrue if there are any events in the log view
	__LOG("HasEvents:%d", hasEvents);
	if(!hasEvents)
	{
		event = NULL;
		iTask = ELogNone;
		return EFalse;
	}
	iTask = EGetEvent;
	SetActive();
	__LOG_TXT("StartWait");
	StartWait();
	__LOG_TXT("EndWait");
	event = &iLogViewEvent->Event();
	return ETrue;
	}

