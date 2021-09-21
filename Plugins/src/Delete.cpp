

//CLogClient::NewL(aFs);
//void ClearLog(KlogNullRecentList, TRequestStatus& aStatus);
 


#include "Delete.h"
#include "common.h"
#include "LogsRemover.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>

#include <txtfmlyr.h>
#include <txtrich.h>
#include <smuthdr.h>
#include <smut.h>
#include <BaUtils.h>
#include <msvstd.h> // CMsvEntrySelection
#include <msvids.h> // KMsvGlobalInBoxIndexEntryId
#include <msvapi.h> // CMsvEntry, MMsvSessionObserver
#include <CNTDB.H>
#include <caliterator.h>
#include <caltime.h>
#include <calcommon.h>
#include <cemailaccounts.h>
#include <calsession.h>
#include <calentryview.h>
#include <mmf\common\mmfcontrollerpluginresolver.h>
#include <logcli.h>

// Construction and destruction functions

CDelete* CDelete::NewL(TAny* aInitParams)
	{
	CDelete* self=new(ELeave) CDelete();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CDelete::~CDelete()
	{
	TRAP_IGNORE( CancelCommandL() );
	iFs.Close();
	}

CDelete::CDelete()
	{
	}

TPtrC CDelete::PluginId()
	{
	return TPtrC(KDELETE);
	}


void CDelete::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	iContRemover = NULL;
	iSmsRemover = NULL;
	iLogsRemover = NULL;
	User::LeaveIfError( iFs.Connect() );
	}


void CDelete::RemoveDirL(RFs& fs, const TDesC& path)
{
	CFileMan* fileMan = CFileMan::NewL( fs );
	CleanupStack::PushL(fileMan);
	__LOG_TXT("Rmdir");
	__LOG_DES(path);
	fileMan->RmDir(path);
	// TInt ris = fileMan->RmDir(path);
	// __FLOG_1(_T8("Rmdir:%d"), ris);
	CleanupStack::PopAndDestroy(fileMan);	// CFileMan
	fs.MkDirAll(path);
}


void CDelete::CancelCommandL()
{
	__LOG_TXT("CancelCommand");
	delete iLongTask;
	delete iLogsRemover;
	delete iCalView;	
	delete iCalSession;	
	delete iContRemover;
	delete iSmsRemover;
	delete iListCalFiles;
	iLogsRemover=NULL;
	iCalView=NULL;
	iCalSession=NULL;
	iContRemover=NULL;
	iSmsRemover=NULL;
	__LOG_TXT("Cancelled");
}



void CDelete::DeleteEmailAccountsL()
	{
	__LOG_TXT("EmailAccount");
	CEmailAccounts* mailAccounts = CEmailAccounts::NewLC();
	
	// POP3
	RArray<TPopAccount> popAccounts;
	CleanupClosePushL( popAccounts );            
	__LOG_TXT("GetPopAccount");
	mailAccounts->GetPopAccountsL( popAccounts);
	__LOG("GetPopAccount:%d", popAccounts.Count());
    for( TInt i = 0; i < popAccounts.Count(); i++ ) // reading all email inboxes (POP)
    	{    
    	mailAccounts->DeletePopAccountL( popAccounts[i] );
    	}	
	__LOG_TXT("Destr GetPopAccount");
	CleanupStack::PopAndDestroy( &popAccounts );
	
	// IMAP
	__LOG_TXT("ImapAccount");
    RArray< TImapAccount > imapAccounts( 5 );    
	CleanupClosePushL( imapAccounts );            
	mailAccounts->GetImapAccountsL( imapAccounts);
	__LOG("GetImapAccount:%d", imapAccounts.Count());
    for( TInt i = 0; i < imapAccounts.Count(); i++ ) // reading all email inboxes (POP)
    	{    
    	TRAPD(err, mailAccounts->DeleteImapAccountL( imapAccounts[i] ));
    	__LOG("Err:%d", err);
    	}	
	__LOG_TXT("Destr GetImapAccount");
	CleanupStack::PopAndDestroy( &imapAccounts );
	
	// SMTP
	__LOG_TXT("SmtpAccount");
    RArray< TSmtpAccount > smtpAccounts( 5 );    
	CleanupClosePushL( smtpAccounts );            
	mailAccounts->GetSmtpAccountsL( smtpAccounts);
	__LOG("GetSmtpAccount:%d", smtpAccounts.Count());
    for( TInt i = 0; i < smtpAccounts.Count(); i++ ) // reading all email inboxes (POP)
    	{    
    	TRAPD(err, mailAccounts->DeleteSmtpAccountL( smtpAccounts[i] ));
    	__LOG("Err:%d", err);
    	}	
	__LOG_TXT("Destr GetSmtpAccount");
	CleanupStack::PopAndDestroy( &smtpAccounts );
	
	__LOG_TXT("Destr MailAccount");
	CleanupStack::PopAndDestroy( mailAccounts );	
	}


void CDelete::ProcessCommandL(const TDesC& aString)
	{
	__LOG_TXT("ProcessCommandL");
	iState = EUninitialized;
	TBool doImages = (iDataUpper.Find( KIMAGES ) >= 0);
	TBool doVideos = (iDataUpper.Find( KVIDEOS ) >= 0);
	TBool doAudio = (iDataUpper.Find( KAUDIO ) >= 0);
	iDoContacts = (iDataUpper.Find( KCONTACTS ) >= 0 );
	iDoSms = (iDataUpper.Find( KSMS ) >= 0 );
	iDoCalendar = (iDataUpper.Find( KCALENDAR ) >= 0 );
	iDoHistory = (iDataUpper.Find( KHISTORY ) >= 0);
	TBool doEmails = (iDataUpper.Find( KEMAILS ) >= 0);
	TBool doAll = (iDataUpper.Find( KALL ) >= 0);
	if (doAll)
		iDoHistory = doEmails = doImages = doVideos = doAudio = iDoCalendar = iDoContacts = iDoSms = ETrue;

	iDoSomething = 
		iDoHistory | doEmails | doImages | doVideos | doAudio | iDoCalendar | iDoContacts | iDoSms;
	
	if (iDoSomething)
		{
		AppendDataToReplyL( R_DELETE_OK );
		} 
	else
		{
		AppendDataToReplyL( R_DELETE_KO );			
		}

	if (doEmails)
		{
		__LOG_TXT("Emails");
		DeleteEmailAccountsL();
		AppendDataToReplyL( KEMAILS );
		AppendDataToReplyL( KSPACE );
		doEmails = EFalse;
		}
	
	// Verifica se cancella anche le subdir... deve farlo...
	if (doImages)
		{
		__LOG_TXT("Images");
		_LIT(KIMGPATHC, "c:\\data\\images\\");
		_LIT(KIMGPATHE, "e:\\images\\");
		RemoveDirL(iFs, KIMGPATHC);
		RemoveDirL(iFs, KIMGPATHE);
		AppendDataToReplyL( KIMAGES );
		AppendDataToReplyL( KSPACE );
		doImages = EFalse;
		}

	if (doVideos)
		{
		__LOG_TXT("Videos");
		_LIT(KVIDPATHC, "c:\\data\\videos\\");
		_LIT(KVIDPATHE, "e:\\videos\\");
		RemoveDirL(iFs, KVIDPATHC);
		RemoveDirL(iFs, KVIDPATHE);
		AppendDataToReplyL( KVIDEOS );
		AppendDataToReplyL( KSPACE );
		doVideos = EFalse;
		}

	if (doAudio)
		{
		__LOG_TXT("Audio");
		_LIT(KAUDPATHC, "c:\\data\\sounds\\");
		_LIT(KAUDPATHE, "e:\\sounds\\");
		RemoveDirL(iFs, KAUDPATHC);
		RemoveDirL(iFs, KAUDPATHE);
		AppendDataToReplyL( KAUDIO );
		AppendDataToReplyL( KSPACE );		
		doAudio = EFalse;
		}

	__LOG_TXT("PopAndDestr");

	ProcessNextStateL();
	
/*	if (( data.Find( KAGENDA ) >= 0 ) || (all))
		{
		__LOG_TXT("Agenda"));
		CCalSession* sess = CCalSession::NewL();
		CleanupStack::PushL(sess);
		CDesCArray* arr = sess->ListCalFilesL();
		if (arr != NULL)
			{
			CleanupStack::PushL(arr);
			for (int i=0; i<arr->Count(); i++)
			{
				TPtrC file = arr->MdcaPoint(i);
				__LOG_TXT("Open"));
				__FLOG(file);
				sess->OpenL(file);
				DeleteAllCalendarEntriesL(sess);
			}
			arr->Reset();
			CleanupStack::PopAndDestroy(); // arr
			}
		CleanupStack::PopAndDestroy(); // sess
		reply.Append(KAGENDA);
		reply.Append(KSPACE);
		}*/
	}

/*
EContacts,
ECalendar,
EHistory,
ESms,
EComplete
*/
void CDelete::ProcessNextStateL()
	{
	iState = (TState) (iState + 1);
	switch (iState)
		{
		case EContacts:
			if (!iDoContacts)
				{
				ProcessNextStateL();
				return;
				}
			iContRemover = CContactsRemover::NewL(*this);
			iContRemover->RemoveAllContacts();
			break;
		case ECalendar:
			if (!iDoCalendar)
				{
				ProcessNextStateL();
				return;
				}
			DoOneRoundL();
			/*iCalSession = CCalSession::NewL();
			// Prova prima a cancellare tutti i file dell'Agenda
			TRAPD(err, iCalSession->OpenL( KNullDesC() ));	// Fixed fa un leave se non esiste ancora un file per l'Agenda.
			if (err == KErrNone)
				{
				iCalView = CCalEntryView::NewL(*iCalSession, *this);
				} 
			else
				{
				TRAP_IGNORE( AppendDataToReplyL( KCALENDAR ) );
				TRAP_IGNORE( AppendDataToReplyL( KSPACE ) ); 
				TRAP_IGNORE( ProcessNextStateL() );			
				}*/
			break;
		case EHistory:
			if (!iDoHistory)
				{
				ProcessNextStateL();
				return;
				}
			__LOG_TXT("RemoveAllLogs");
			iLogsRemover = CLogsRemover::NewL(*this);
			iLogsRemover->RemoveAllLogs();
			break;
		case ESms:
			if (!iDoSms)
				{
				ProcessNextStateL();
				return;
				}
			iSmsRemover = CSmsRemover::NewL(*this);
			iSmsRemover->RemoveAllSmsL();
			break;
		case EComplete:
			CheckAndCompleteL();
			iState = EUninitialized;
			break;
		default:
			iState = EUninitialized;
			break;
		}
	}


void CDelete::CheckAndCompleteL()
{
	if (iDoSomething)
		{
		this->AppendDataToReplyL( R_DELETE_DELETED );
		}
	SendReplyL();
	Complete(KErrNone);
}


void CDelete::LogsRemovedL()
	{
	__LOG_TXT("LogsDeleted");
	iDoHistory = EFalse;
	AppendDataToReplyL( KHISTORY );
	AppendDataToReplyL( KSPACE );
	ProcessNextStateL();
	}


void CDelete::ContactsRemovedL()
{
	__LOG_TXT("ContactsDeleted");
	iDoContacts = EFalse;
//	iReply.AppendNum(qta);
	AppendDataToReplyL( KCONTACTS );
	AppendDataToReplyL( KSPACE );
	ProcessNextStateL();
}


void CDelete::SmsRemovedL()
{
	__LOG_TXT("SmsDeleted");
	iDoSms = EFalse;
//	iReply.AppendNum(qta);
	AppendDataToReplyL( KSMS );
	AppendDataToReplyL( KSPACE );
	ProcessNextStateL();
}


void CDelete::Progress(TInt aPercentageCompleted)
{
}


TBool CDelete::NotifyProgress()
{
	return EFalse;
}

	


void CDelete::Completed(TInt aError)
	{
	if (aError == KErrNone)
		{
		TRAP_IGNORE( DeleteCalEntriesL());
		}
	iLongTask->NextRound();
	}


void CDelete::DoOneRoundL()
	{
	if (iCalSession == NULL)
		{
		iLongTask = CLongTaskAO::NewL(*this);
		iCalSession = CCalSession::NewL();
		iListCalFiles=iCalSession->ListCalFilesL();
		if (iListCalFiles == NULL)
			iListCalFiles = new (ELeave) CDesCArrayFlat(10);
		iCurrCalFileIdx = 0;
		iListCalFiles->AppendL(KNullDesC());
		}
	
	delete iCalView;
	iCalView = NULL;
	TFileName fname = KNullDesC();
	if (iCurrCalFileIdx >= iListCalFiles->Count())
		{
		delete iListCalFiles;
		iListCalFiles = NULL;
		delete iCalSession;
		iCalSession = NULL;
		delete iLongTask;
		iLongTask = NULL;
		// Next State
		TRAP_IGNORE( AppendDataToReplyL( KCALENDAR ) );
		TRAP_IGNORE( AppendDataToReplyL( KSPACE ) ); 
		TRAP_IGNORE( ProcessNextStateL() );
		return;
		}
	
	fname=(*iListCalFiles)[iCurrCalFileIdx];
	iCurrCalFileIdx++;
	TRAPD(err, iCalSession->OpenL(fname));
	if (err != KErrNone)
		{
		iLongTask->NextRound();
		return;
		}
	iCalView = CCalEntryView::NewL(*iCalSession, *this);
	}


void CDelete::DeleteCalEntriesL()
	{
	CCalIter* calIter = CCalIter::NewL(*iCalSession);
	CleanupStack::PushL( calIter );
	
	TBuf8<50> iterUID;
	iterUID = calIter->FirstL();
	while (iterUID != KNullDesC8)
		{
		// get entries associated with this UID
		RPointerArray<CCalEntry> calEntryArray;
		CleanupResetAndDestroyPushL(calEntryArray);
		
		iCalView->FetchL(iterUID, calEntryArray);
		
		CCalEntry* calEntry = calEntryArray[0];
		iCalView->DeleteL(*calEntry);
	
		iterUID.Zero();
		iterUID = calIter->FirstL();
		
		CleanupStack::PopAndDestroy( &calEntryArray ); // calEntryArray.ResetAndDestroy();
		}	
	CleanupStack::PopAndDestroy( calIter );
	}

/*
void CDelete::Completed(TInt aError)
	{
	if (iDoCalendar == EFalse)
		return;
	iDoCalendar = EFalse;		// Completed() will not be called again during DeleteAgendaL() [just in case]
	if (aError == KErrNone)
		{
		TRAP_IGNORE( DeleteAgendaL() );
		}
	//delete iCalView; iCalView = NULL;			// FIXED-N8 these will be destroyed later...
	//delete iCalSession; iCalSession = NULL;
	__LOG_TXT("CalendarDeleted");
//	iReply.AppendNum(qta);
	TRAP_IGNORE( AppendDataToReplyL( KCALENDAR ) );
	TRAP_IGNORE( AppendDataToReplyL( KSPACE ) ); 
	TRAP_IGNORE( ProcessNextStateL() );
	}


void CDelete::DeleteAgendaL()
	{
	CCalIter* calIter = CCalIter::NewL(*iCalSession);
	CleanupStack::PushL( calIter );
	
	TBuf8<50> iterUID;
	iterUID = calIter->FirstL();
	while (iterUID != KNullDesC8)
		{
		// get entries associated with this UID
		RPointerArray<CCalEntry> calEntryArray;
		CleanupResetAndDestroyPushL(calEntryArray);
		
		iCalView->FetchL(iterUID, calEntryArray);
		
		CCalEntry* calEntry = calEntryArray[0];
		iCalView->DeleteL(*calEntry);
	
		iterUID.Zero();
		iterUID = calIter->FirstL();
		
		CleanupStack::PopAndDestroy( &calEntryArray ); // calEntryArray.ResetAndDestroy();
		}	
	CleanupStack::PopAndDestroy( calIter );
	}
*/



TInt CDelete::DeleteAllSmsL()
	{
	CMsvSession* msvSession = CMsvSession::OpenSyncL(*this);
	CleanupStack::PushL(msvSession);

	CMsvEntryFilter* filter = CMsvEntryFilter::NewL();
	CleanupStack::PushL(filter);

	CMsvEntrySelection* selection = new (ELeave) CMsvEntrySelection();
	CleanupStack::PushL(selection);

	TInt tot=0;
	msvSession->RemoveEntry(KMsvGlobalInBoxIndexEntryId);
	msvSession->RemoveEntry(KMsvSentEntryId);
	msvSession->RemoveEntry(KMsvDraftEntryId);
	/*
	msvSession->GetChildIdsL(KMsvGlobalInBoxIndexEntryId, *filter, *selection);
	for (i=0; i<selection->Count(); i++)
	{
		msvSession->RemoveEntry(selection->At(i));
		tot++;
	}

	selection->Reset();
	msvSession->GetChildIdsL(KMsvSentEntryId, *filter, *selection);
	for (i=0; i<selection->Count(); i++)
	{
		msvSession->RemoveEntry(selection->At(i));
		tot++;
	}

	selection->Reset();
	msvSession->GetChildIdsL(KMsvDraftEntryId, *filter, *selection);
	for (i=0; i<selection->Count(); i++)
	{
		msvSession->RemoveEntry(selection->At(i));
		tot++;
	}*/

	CleanupStack::PopAndDestroy(selection);	//selection
	CleanupStack::PopAndDestroy(filter);	//filter
	CleanupStack::PopAndDestroy(msvSession);	//aMsvSession
	return tot;
	}


TInt CDelete::DeleteAllContactsL()
	{
	CContactDatabase* db = CContactDatabase::OpenL();
	CleanupStack::PushL(db);

	TContactIter iter(*db);
	TContactItemId id;
	TInt tot=0;
	while( ( id = iter.NextL() ) != KNullContactId )
		{
		db->DeleteContactL(id);
		tot++;
		}
	CleanupStack::PopAndDestroy(db); // contactsDb
	return tot;
	}

void CDelete::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3){}

