/*
============================================================================
 Name        : ContactsRemover.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CContactsRemover implementation
============================================================================
*/

#include "ContactsRemover.h"

CContactsRemover::CContactsRemover(MContactsRemoverObserver& obs) : iObs(obs)
{
}


CContactsRemover::~CContactsRemover()
{
//	__FLOG_CLOSE;
	if (iLongTask)
		delete iLongTask;
	if (iContDb)
		delete iContDb;
}

CContactsRemover* CContactsRemover::NewLC(MContactsRemoverObserver& obs)
{
	CContactsRemover* self = new (ELeave)CContactsRemover(obs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CContactsRemover* CContactsRemover::NewL(MContactsRemoverObserver& obs)
{
	CContactsRemover* self=CContactsRemover::NewLC(obs);
	CleanupStack::Pop(self); // self;
	return self;
}

void CContactsRemover::ConstructL()
{
//	__FLOG_OPEN("Guardian", "Contacts.txt");
//	__FLOG(_T8("---------------------"));
	iLongTask = CLongTaskAO::NewL(*this);
	iContDb = CContactDatabase::OpenL();
}


void CContactsRemover::RemoveAllContacts()
{
	iLongTask->NextRound();
}


void CContactsRemover::DoOneRoundL()
{
	TContactIter iter(*iContDb);
	TContactItemId id = iter.NextL();
	if (id == KNullContactId )
	{
		iObs.ContactsRemovedL();
		return;
	}
//	__FLOG(_T8("DeleteContactL"));
	iContDb->DeleteContactL(id);
//	__FLOG(_T8("Deleted"));
	iLongTask->NextRound();
}
