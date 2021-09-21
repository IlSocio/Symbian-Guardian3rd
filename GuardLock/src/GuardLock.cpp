

#include "StartupWaiter.h"

#include <FuzzyByte\Guardian\Client.H>
#include <FuzzyByte\Processes.h>
#include <FuzzyByte\Utils.h>
#include <FuzzyByte\PubSubObserver.h>

#include <e32base.h>
#include <e32cons.h>            // Console
#include <f32file.h>
#include <S32FILE.H>
#include <BAUTILS.H>

// #include <FuzzyByte\UTILS.H>
// #include <FuzzyByte\InboxAttachment.h>

#include <e32math.h>
#include <apgtask.h>

const TUid KPinUid = {0x200107B1};



class CGuardLock : public CActive, public MPubSubObserver
	{
	public:
		static CGuardLock* NewLC();
		~CGuardLock();

	public: // New functions
		void RequestCodeL();

	protected:
        CGuardLock();
		void ConstructL();
		virtual void PropertyChangedL(TUid category, TUint key, TInt value);

	private: // From CActive
		void RunL();
		void DoCancel();
		TInt RunError(TInt /*aError*/);

	private:
		TBuf8<20> iPass8;
		TBuf8<20> iResp8;
		TBuf<20> iGoodCode;
		RNotifier iNotif;
		CPubSubObserver* iConfigObs;
		__LOG_DECLARATION_MEMBER
	};


CGuardLock::CGuardLock() : CActive(EPriorityStandard)
	{
	}

CGuardLock* CGuardLock::NewLC() 
	{
	CGuardLock* self = new (ELeave) CGuardLock();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	} 

void CGuardLock::ConstructL()
	{
	CActiveScheduler::Add(this);
	__LOG_OPEN("Guardian", "GuardLock.txt");

	User::LeaveIfError( iNotif.Connect() );
	iConfigObs = CPubSubObserver::NewL(*this, KServerUid3, KPSChangeConfig);
	iConfigObs->StartMonitorProperty();
	}

CGuardLock::~CGuardLock()
	{
	__LOG_TXT("Destructor");
	Cancel();

	iNotif.Close();
	delete iConfigObs;
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}

void CGuardLock::DoCancel()
	{
	__LOG_TXT("DoCancel");
	iNotif.CancelNotifier(KPinUid);
	}

TInt CGuardLock::RunError(TInt /*aError*/)
	{
	__LOG_TXT("RunError");
	return KErrNone;
	}


void CGuardLock::PropertyChangedL(TUid category, TUint key, TInt value)
	{
	switch (value)
		{
		case EIsLockedChange:
			CActiveScheduler::Stop();
			break;
		case EEnableChange:			
			CActiveScheduler::Stop();
			break;
		case EPasswordChange:
			{
			RequestCodeL();
			break;
			}
		}
	}


void CGuardLock::RequestCodeL()
	{
	__LOG_TXT("RequestCodeL");
	Cancel();
	
	RGuardian guard;	
	User::LeaveIfError( guard.Connect() );
	CleanupClosePushL(guard);
	guard.GetPassword(iGoodCode);
	CleanupStack::PopAndDestroy( &guard );
	
	iPass8.Copy(iGoodCode);
	iPass8.Insert(0, _L8("1"));
	iResp8.Zero();
	iNotif.StartNotifierAndGetResponse(iStatus, KPinUid, iPass8, iResp8);
	__LOG_TXT("StartedNotif");
	 
	SetActive();
	}



void CGuardLock::RunL()
	{
	__LOG("RunL: %d", iStatus.Int());
	
	if(iStatus.Int() == KErrCancel)
	{
		RequestCodeL();
		return; 
	}
	
	if(iStatus.Int() != KErrNone) 
	{
		// RequestCodeL();
		// Errore nel notifier
		CActiveScheduler::Stop();
		return;
	}
	
	__LOG_DES(iPass8);
	__LOG_DES(iResp8);
	
	if (iResp8.Length() == 0) // Pigiato Cancel
	{
		RequestCodeL();
		return;
	}
	
	TBuf<20> respCode;
	respCode.Copy(iResp8);
	TBool validCode = (respCode == iGoodCode);
	if (validCode)
		{
		RGuardian guard;
		User::LeaveIfError( guard.Connect() );
		CleanupClosePushL(guard);
		guard.SetLocked(EFalse);
		CleanupStack::PopAndDestroy( &guard );
		// scatena l'evento PropertyChangedL che stoppa l'activescheduler
		}
	else
		{
		RequestCodeL();
		}
	}





_LIT(KProcName, "GuardLock200131C8");

// Viene lanciato se LockBehaviour = OnStartup oppure OnSimChange
// oppure se e' stato attivato Lock dal plugin
// In ogni caso Guardian e' Locked...

LOCAL_C void DoStartL()
	{
	if (!Processes::RenameIfNotRunning(KProcName))
		{
		// Cambiato a partire dalla versione 4.00
		// Segnala a chi l'ha lanciato che e' pronto.
		RProcess myProcess; // Get my current process
		myProcess.Rendezvous(KErrNone);
		return;
		}
	// Cambiato a partire dalla versione 4.00
	// Segnala a chi l'ha lanciato che e' pronto.
	RProcess myProcess; // Get my current process
	myProcess.Rendezvous(KErrNone);

	// Puo' essere lanciato in fase di accensione da Guardian
	// oppure puo' essere lanciato in un secondo momento tramite il comando remoto Lock
	// TInt fromCommand = 0; // 0=OnStartup  1=FromCommand
	// User::GetTIntParameter(1, fromCommand);

	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	RFs fs;
	User::LeaveIfError( fs.Connect() );
	CleanupClosePushL( fs );
			
	// Wait for menu' process...
	CStartupWaiter* startupWaiter = CStartupWaiter::NewLC();
	startupWaiter->StartMonitorL(fs);
	CActiveScheduler::Start();
	CleanupStack::PopAndDestroy(startupWaiter);	

	CleanupStack::PopAndDestroy(&fs);			
	
	// Lock the phone...
	CGuardLock* lock = CGuardLock::NewLC();
	lock->RequestCodeL();
	CActiveScheduler::Start();
	CleanupStack::PopAndDestroy(lock);
			
	// Delete active scheduler
	CleanupStack::PopAndDestroy(scheduler);
	}


//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();

	// Run application code inside TRAP harness, wait keypress when terminated
	TRAPD(mainError, DoStartL());

	delete cleanup;
	__UHEAP_MARKEND;

	return mainError;
	}
