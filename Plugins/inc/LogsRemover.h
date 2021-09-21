/*
============================================================================
 Name        : LogsRemover.h
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CLogsRemover declaration
============================================================================
*/

#ifndef LOGSREMOVER_H
#define LOGSREMOVER_H
#include <FuzzyByte\FileLogger.h>

// INCLUDES
#include <e32std.h>
#include <e32base.h>
//#include <FuzzyByte\LongRunTask.h>
#include <CNTDB.H>

class CLogClient;

// CLASS DECLARATION

class MLogsRemoverObserver
{
public:
	virtual void LogsRemovedL() = 0;
};

/**
*  CLogsRemover
*
*/
class CLogsRemover : public CActive
{
public: // Constructors and destructor

	/**
        * Destructor.
        */
	~CLogsRemover();

        /**
        * Two-phased constructor.
        */
	static CLogsRemover* NewL(MLogsRemoverObserver& obs);

        /**
        * Two-phased constructor.
        */
	static CLogsRemover* NewLC(MLogsRemoverObserver& obs);

	void RemoveAllLogs();

private:
	void RunL();

	// How to cancel me
	void DoCancel();
	
	/**
        * Constructor for performing 1st stage construction
        */
	CLogsRemover(MLogsRemoverObserver& obs);

	void ConstructL();

private:
	RFs iFs;
	MLogsRemoverObserver& iObs;
	CLogClient* iLogClient;
//	CLongTaskAO* iLongTask;
	__LOG_DECLARATION_MEMBER;
};

#endif // LogsREMOVER_H
