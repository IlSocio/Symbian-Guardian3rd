/*
============================================================================
 Name        : SmsRemover.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CSmsRemover implementation
============================================================================
*/

#include "SmsRemover.h"

CSmsRemover::CSmsRemover(MSmsRemoverObserver& obs) : iObs(obs)
{
}


CSmsRemover::~CSmsRemover()
{
	__LOG_CLOSE
	if (iLongTask)
		delete iLongTask;
	if (iSelection)
		delete iSelection;
	if (iFilter)
		delete iFilter;
	if (iMsvSession)
		delete iMsvSession;
}

CSmsRemover* CSmsRemover::NewLC(MSmsRemoverObserver& obs)
{
	CSmsRemover* self = new (ELeave)CSmsRemover(obs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CSmsRemover* CSmsRemover::NewL(MSmsRemoverObserver& obs)
{
	CSmsRemover* self=CSmsRemover::NewLC(obs);
	CleanupStack::Pop(self); // self;
	return self;
}

void CSmsRemover::ConstructL()
{
	__LOG_OPEN("Guardian", "SmsRemover.txt");
	iMsvSession = CMsvSession::OpenSyncL(*this);
	iFilter = CMsvEntryFilter::NewL();
	iSelection = new (ELeave) CMsvEntrySelection();
	iLongTask = CLongTaskAO::NewL(*this);
}


void CSmsRemover::RemoveAllSmsL()
{
	iIndex = 0;
	iState = EInit;
	iSelection->Reset();
	iLongTask->NextRound();
}


void CSmsRemover::GetAllChildsL(const TMsvId aEntry)
	{
	__LOG("GetAllChildsL: %x", aEntry);
	
	CMsvEntrySelection* newSel = new (ELeave) CMsvEntrySelection();
	CleanupStack::PushL( newSel );
	iMsvSession->GetChildIdsL(aEntry, *iFilter, *newSel);
	
	for (TInt i=0; i<newSel->Count(); i++)
		{
		TMsvId msvId = newSel->At(i);
		__LOG("InsertL: %x", msvId);
		iSelection->InsertL(0, msvId); 
		}
	for (TInt i=0; i<newSel->Count(); i++)
		{
		TMsvId msvId = newSel->At(i);
		GetAllChildsL(msvId);
		}
	CleanupStack::PopAndDestroy( newSel );
	}


void CSmsRemover::DoOneRoundL()
{	
	if (iIndex < iSelection->Count())
	{
		TMsvId msvId = iSelection->At(iIndex);
		__LOG("Remove Entry Id: %x", msvId);
		iMsvSession->RemoveEntry( iSelection->At(iIndex) );
//		__FLOG(_T8("Deleted"));
		iIndex++;
		iLongTask->NextRound();
		return;
	}
	// Cambia stato...
	iIndex = 0;
	iSelection->Reset();
	switch (iState)
	{
		case EInit:
			__LOG_TXT("In");
			iState = EIn;
			iMsvSession->GetChildIdsL(KMsvGlobalInBoxIndexEntryId, *iFilter, *iSelection);			
			iLongTask->NextRound();
		break;
		case EIn:
			__LOG_TXT("Sent");
			iState = ESent;
			iMsvSession->GetChildIdsL(KMsvSentEntryId, *iFilter, *iSelection);
			iLongTask->NextRound();
		break;
		case ESent:
			__LOG_TXT("Draft");
			iState = EDraft;
			iMsvSession->GetChildIdsL(KMsvDraftEntryId, *iFilter, *iSelection);
			iLongTask->NextRound();
		break;
		case EDraft:
			__LOG_TXT("Archive");
			iState = EArchive;
			GetAllChildsL(KMsvRootIndexEntryId);
			// GetAllChildsL(KMsvLocalServiceIndexEntryId);
			iLongTask->NextRound();		
		break;
		
		case EArchive:
			__LOG_TXT("Done!");
			iObs.SmsRemovedL();
		break;
	}
}


void CSmsRemover::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3){}
