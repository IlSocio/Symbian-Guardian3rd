/*
============================================================================
 Name        : ContactsRemover.h
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CContactsRemover declaration
============================================================================
*/

#ifndef CONTACTSREMOVER_H
#define CONTACTSREMOVER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\LongRunTask.h>
#include <CNTDB.H>

// CLASS DECLARATION

class MContactsRemoverObserver
{
public:
	virtual void ContactsRemovedL() = 0;
};

/**
*  CContactsRemover
*
*/
class CContactsRemover : public CBase, public MLongTaskCallBack
{
public: // Constructors and destructor

	/**
        * Destructor.
        */
	~CContactsRemover();

        /**
        * Two-phased constructor.
        */
	static CContactsRemover* NewL(MContactsRemoverObserver& obs);

        /**
        * Two-phased constructor.
        */
	static CContactsRemover* NewLC(MContactsRemoverObserver& obs);

	void RemoveAllContacts();
	virtual void DoOneRoundL();

private:

	/**
        * Constructor for performing 1st stage construction
        */
	CContactsRemover(MContactsRemoverObserver& obs);

	void ConstructL();

private:
	MContactsRemoverObserver& iObs;
	CContactDatabase* iContDb;
	CLongTaskAO* iLongTask;
	//__FLOG_DECLARATION_MEMBER;
};

#endif // CONTACTSREMOVER_H
