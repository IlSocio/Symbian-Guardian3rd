#include "SecurityCode.h"
#include <e32math.h>
#include <apgtask.h>

const TUid KPinUid = {0x200107B1};

CSecurityCode::CSecurityCode(RWsSession& aSession, MSecurityCodeNotifier& notifier) : CActive(EPriorityStandard), iSession(aSession), iObs(&notifier)
	{
	}

CSecurityCode* CSecurityCode::NewL(RWsSession& aSession, MSecurityCodeNotifier& notifier) 
	{
	CSecurityCode* self = new (ELeave) CSecurityCode(aSession, notifier);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

void CSecurityCode::ConstructL()
	{
	CActiveScheduler::Add(this);
	__LOG_OPEN("Guardian", "SecurityCode.txt");

	iTimer = CTimeOutTimer::NewL(*this);
	User::LeaveIfError( iNotif.Connect() );
	}

CSecurityCode::~CSecurityCode()
	{
	__LOG_TXT("Destructor");
	Cancel();

	delete iTimer;

	iNotif.Close();
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}


void CSecurityCode::DoCancel()
	{
	__LOG_TXT("DoCancel");
	iTimer->Cancel();
	iNotif.CancelNotifier(KPinUid);
	}


TInt CSecurityCode::RunError(TInt /*aError*/)
	{
	__LOG_TXT("RunError");
	iTimer->Cancel();
	return KErrNone;
	}


//const TUid KMenuUid = {0x101F4CD2};
//const TUid KIdleUid = {0x101FD64C};


void CSecurityCode::RequestCodeL(TUid aAppUid, const TDesC& aGoodCode)
	{
	__LOG_TXT("RequestCodeL");
//	NON va bene perche' per la vecchia richiesta potrebbe esserci il Cancel abilitato
/*	 if (IsActive())
		{
		__LOG_TXT("IsActive()");
		return;
		}/**/
	Cancel();
	// Stranamente, nonostante la Cancel() sembra che la richiesta attuale resti ancora in corso e che ne venga inviata una nuova.
	
	iAppUid = aAppUid;
	iGoodCode = aGoodCode;
	iRespCode.Zero();
	
	TApaTaskList tasklist(iSession);
	//TApaTask TaskMenu = tasklist.FindApp(KMenuUid);
	TApaTask ProtectedTask = tasklist.FindApp(aAppUid);
	if (ProtectedTask.Exists())
		{
		ProtectedTask.SendToBackground(); 
		}
	iTimer->AfterTime( TTimeIntervalSeconds(1) );

	// If there is still a Request in progress doesn't proceed.
	//if (IsActive())
	//	return;
	
	iPass8.Copy(iGoodCode);
	iPass8.Insert(0, _L8("0"));	// Cancel enabled
	iResp8.Zero();
	iNotif.StartNotifierAndGetResponse(iStatus, KPinUid, iPass8, iResp8);
	__LOG_TXT("StartedNotif");
	 
	SetActive();
	}



void CSecurityCode::RunL()
	{
	__LOG("RunL: %d", iStatus.Int());
	iTimer->Cancel();
	
	if(iStatus.Int() != KErrNone)
	{
		iObs->GotSecurityCodeL(iStatus.Int(), EFalse);
		return;
	}
	
	__LOG_DES(iPass8);
	__LOG_DES(iResp8);
	
	if (iResp8.Length() == 0) // Pigiato Cancel
	{
		// Manda l'applicazione in Background mettendo il menu' in Foreground...
		// Serve per fare in modo che pigiando "c" venga nascosto il programma di disinstallazione...
		/*if (ProtectedTask.Exists())
			ProtectedTask.SendToBackground();*/
		
		iObs->GotSecurityCodeL(KErrNone, EFalse);
		return;
	}
	
	iRespCode.Copy(iResp8);
	TBool validCode = (iRespCode == iGoodCode);
	if (validCode)
		{
		TApaTaskList tasklist(iSession);
		//TApaTask TaskMenu = tasklist.FindApp(KMenuUid);
		TApaTask ProtectedTask = tasklist.FindApp(iAppUid);
		if (ProtectedTask.Exists())
			ProtectedTask.BringToForeground();
		}
	iObs->GotSecurityCodeL(iStatus.Int(), validCode);
	}


// Manda in background sempre iAppUid
void CSecurityCode::TimerExpiredL(TAny* src)
	{
	TApaTaskList tasklist(iSession);
//	TApaTask TaskMenu = tasklist.FindApp(KMenuUid);
	TApaTask ProtectedTask = tasklist.FindApp(iAppUid);	
	if (ProtectedTask.Exists())
		{
		ProtectedTask.SendToBackground();
		}
	iTimer->AfterTime( TTimeIntervalSeconds(1) );
	}

