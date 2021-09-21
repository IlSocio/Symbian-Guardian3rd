//
// CDelete.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CDELETE__
#define _CDELETE__

#include "Interface.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\LongRunTask.h>
#include <calsession.h>
#include <calentryview.h>
#include <calprogresscallback.h>
#include "contactsremover.h"
#include "smsremover.h"
#include "abstractplugin.h"
#include "logsremover.h"


// An implementation of the CExampleInterface definition
class CDelete : public CAbstractPlugin, public MLogsRemoverObserver, public MCalProgressCallBack, public MContactsRemoverObserver, public MSmsRemoverObserver,  public MMsvSessionObserver, MLongTaskCallBack
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CDelete* NewL(TAny* aInitParams);
	// Destructor
	~CDelete();

	void RemoveDirL(RFs& fs, const TDesC& path);

	// Implementation of CExampleInterface
//	void CancelRemoteCommand();
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
	virtual void ProcessCommandL(const TDesC& aString);
	virtual void CancelCommandL();

	void SaveToInBoxL(const TDesC& sender, const TDesC& msg);
	virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	TPtrC PluginId();

	virtual void LogsRemovedL();
	virtual void ContactsRemovedL();
	virtual void SmsRemovedL();
	virtual void Progress(TInt aPercentageCompleted);
	virtual void Completed(TInt aError);
	virtual TBool NotifyProgress();

private:
	virtual void DoOneRoundL();
	// Construction
	CDelete();
	void ConstructL(TAny* aParams);
	void DeleteEmailAccountsL();
	TInt DeleteAllContactsL();
	TInt DeleteAllSmsL();
	TInt DeleteAllCalendarEntriesL(CCalSession* iSession);
	void CheckAndCompleteL();
	void DeleteCalEntriesL();
	
	void ProcessNextStateL();
	
private:
	enum TState 
	{
		EUninitialized,
		EContacts,
		ECalendar,
		EHistory,
		ESms,
		EComplete
	};

	TState iState;
	RFs iFs;
	CLogsRemover* iLogsRemover;
	CCalSession* iCalSession;
	CCalEntryView* iCalView;
	CSmsRemover* iSmsRemover;
	CContactsRemover* iContRemover;
	TBool iDoSomething;
	TBool iDoSms;
	TBool iDoCalendar;
	TBool iDoContacts;
	TBool iDoHistory;
	CLongTaskAO* iLongTask;
	CDesCArray* iListCalFiles;
	TInt iCurrCalFileIdx;
	};

#endif

