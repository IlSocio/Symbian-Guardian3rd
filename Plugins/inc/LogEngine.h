#ifndef __LOGENGINE_H__
#define __LOGENGINE_H__

// INCLUDE FILES
#include <e32base.h>
#include <f32file.h>        // RFs
#include <logcli.h>			// CLogClient
#include <logview.h>		// CLogViewEvent
#include <FuzzyByte\FileLogger.h>


enum
	{
	ELogNone=0,
	EGetEvent
	};


//CLASS DECLARATION
class CLogEngine : public CActive
	{

public:

	/**
	* Symbian OS default constructor
	*/
	CLogEngine(RFs& fs);

	/**
	* Two-phased constructor.
	*/
	static CLogEngine* NewL(RFs& fs);

	/**
	* Two-phased constructor.
	*/
	static CLogEngine* NewLC(RFs& fs);

	/**
	* Destructor
	*/
	virtual ~CLogEngine();

	/**
	* Reads events from the main event database
	*/
	TBool ReadEventsL(const CLogEvent* &event);

	/**
	* Convenience methods for filtering events, only
	* one filter at time can be active. When none set
	* no filtering, all will be shown
	*/
	/**
	* Sets incoming events filtering
	*/
	void SetEventFilterDirectionIncoming();

	/**
	* Sets outgoing events filtering
	*/
	void SetEventFilterDirectionOutgoing();
	
	
	void SetEventFilterDirectionMissed();

	/**
	* Sets voice type events filtering
	*/
	void SetEventFilterEventTypeVoice();

	/**
	* Sets sms events filtering
	*/
	void SetEventFilterEventTypeSMS();

	/**
	* Clears filters
	*/
	void ClearEventFilterL();

private:
	void StartWait( );

	/**
	* Symbian 2-phase constructor
	*/
	void ConstructL();

	/**
	* From CActive
	*/
	void RunL();

	/**
	* From CAktive
	*/
	TInt RunError(TInt anError);

	/**
	* From CActive
	*/
	void DoCancel();

private: // Data Members
	RFs& iFs;

	CLogClient* iLogClient;
	CLogViewEvent* iLogViewEvent;

	// Filters for event log
	CLogFilter* iLogFilter;

	TInt iTask; // task for RunL

	CActiveSchedulerWait* iWait;
	__LOG_DECLARATION_MEMBER
	};

#endif

// End of file
