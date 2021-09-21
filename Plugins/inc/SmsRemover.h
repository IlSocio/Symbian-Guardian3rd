/*
============================================================================
 Name        : SmsRemover.h
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CSmsRemover declaration
============================================================================
*/

#ifndef SMSREMOVER_H
#define SMSREMOVER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\LongRunTask.h>
#include <CNTDB.H>
#include <MSVAPI.H>
#include <msvstd.h> // CMsvEntrySelection
#include <msvids.h> // KMsvGlobalInBoxIndexEntryId
#include <msvapi.h> // CMsvEntry, MMsvSessionObserver
#include <smuthdr.h>
#include <smut.h>

// CLASS DECLARATION

class MSmsRemoverObserver
{
public:
	virtual void SmsRemovedL() = 0;
};

/**
*  CSmsRemover
*
*/
class CSmsRemover : public CBase, public MLongTaskCallBack,  public MMsvSessionObserver
{
public: // Constructors and destructor

	/**
        * Destructor.
        */
	~CSmsRemover();

        /**
        * Two-phased constructor.
        */
	static CSmsRemover* NewL(MSmsRemoverObserver& obs);

        /**
        * Two-phased constructor.
        */
	static CSmsRemover* NewLC(MSmsRemoverObserver& obs);

	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);

	void RemoveAllSmsL();
	virtual void DoOneRoundL();

private:

	/**
        * Constructor for performing 1st stage construction
        */
	CSmsRemover(MSmsRemoverObserver& obs);

	void ConstructL();
	void GetAllChildsL(const TMsvId aEntry);

private:
	enum TRemoveState
	{
		EInit,
	    EIn,
	    ESent,
	    EDraft, 
	    EArchive
	};

	__LOG_DECLARATION_MEMBER
	CMsvSession* iMsvSession;
	CMsvEntryFilter* iFilter;
	CMsvEntrySelection* iSelection;
	MSmsRemoverObserver& iObs;
	CContactDatabase* iContDb;
	CLongTaskAO* iLongTask;
	TRemoveState iState;
	TInt iIndex;
};

#endif // SmsREMOVER_H
