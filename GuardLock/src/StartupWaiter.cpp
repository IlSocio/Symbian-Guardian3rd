
#include "StartupWaiter.h"
#include <startupdomainpskeys.h>   
#include <FuzzyByte\FileLogger.H>
#include <FuzzyByte\Utils.H>
#include <FuzzyByte\Guardian\client.H>


CStartupWaiter::CStartupWaiter() : CBase()
	{
	}

CStartupWaiter::~CStartupWaiter()
	{
	delete iTimer;
	delete iPubSubWaiter;
	__LOG_CLOSE;
	}

CStartupWaiter* CStartupWaiter::NewLC()
	{
	CStartupWaiter* self = new (ELeave) CStartupWaiter();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;	
	}

void CStartupWaiter::ConstructL()
	{	
	__LOG_OPEN("Guardian", "StartupWaiter.txt");
	iPubSubWaiter = CPubSubWaiter::NewL(*this);
	iTimer = CTimeOutTimer::NewL(*this);
	} 


void CStartupWaiter::PropertyReadyL(TAny* src)
	{
	__LOG_TXT("PropertyReadyL()");
	//	iProcWaiter->WaitForProcess( _L("*200113dd"), TTimeIntervalSeconds(3) );
	//  Attende processo menu'...
	iTimer->AfterTime( TTimeIntervalSeconds(0) );
	}


void CStartupWaiter::TimerExpiredL(TAny* src)
	{
	if (iMenuIsReady)
		{
		CActiveScheduler::Stop();
		return;
		}

	// http://www.developer.nokia.com/Community/Wiki/UID_standby_phone
	// 102750f0	homescreen	// 3rd FP2, 5th, belle
	// 101fd64c				// 3rd FP1
	// 100058b3				// 3rd (e anche S^3)
	// 101F4CD2 menu'
	TBool ready = Processes::IsRunning(_L("*102750f0"));
	__LOG("102750f0 = %d", ready);
	if (!ready)
		{
		ready = Processes::IsRunning(_L("*101fd64c"));
		__LOG("101fd64c = %d", ready);
		}
	if (!ready)
		{
		ready = Processes::IsRunning(_L("*100058b3"));		
		__LOG("100058b3 = %d", ready);
		}
	if (!ready)
		{
		ready = Processes::IsRunning(_L("*101F4CD2"));
		__LOG("101F4CD2 = %d", ready);
		}
	if (!ready)
		{
		iTimer->AfterTime( TTimeIntervalSeconds(3) );
		return;
		} 

	iMenuIsReady = ETrue;
	iTimer->AfterTime( TTimeIntervalSeconds(iLockDelay) );
	}


_LIT(KNotifierDir, "c:\\system\\data\\200107B0\\");

void CStartupWaiter::StartMonitorL(RFs& fs)
	{
	__LOG_TXT("StartMonitorL()");
	iMenuIsReady = EFalse;

	// Controlla esistenza dir pubblica Notifier
	// Get and update Panic Lock Delay...
	// Serve per evitare il blocco completo del telefono, nel caso in cui il Notifier schianti...
	RGuardian guard;
	User::LeaveIfError( guard.Connect() );
	CleanupClosePushL( guard );
	iLockDelay = guard.GetLockDelay();
	__LOG("LockDelay: %d", iLockDelay);
	TEntry entry;
	TInt err = fs.Entry(KNotifierDir, entry);
	if (err == KErrNone)
		{
		iLockDelay += 3;
		guard.SetLockDelay( iLockDelay );
		__LOG("NewLockDelay: %d", iLockDelay);
		fs.Delete( KNotifierDir );
		}
	CleanupStack::PopAndDestroy( &guard );

	TUint major;
	TUint minor;
	Utils::GetS60PlatformL(fs, major, minor);
	// 3.0 (3rd) e 3.1 (3rd FP1) sono da scartare perche' non hanno quella chiave...
	__LOG("Platform: %d %d", major, minor);
	if (major >= 5)
		{
		__LOG_TXT("WaitForPropertyL()");
		// Su N96 (3rd FP2) non c'e'...
		// Lancia il Waiter di PubSub solo per 5th - S^1 / S^3 Anna / Belle
		iPubSubWaiter->WaitForPropertyL(KPSUidStartup, KPSStartupUiPhase, EStartupUiPhaseAllDone);
		} else
		{
		// Per gli altri passa ad attendere direttamente il processo Menu'
		PropertyReadyL( this );
		}
	}

/**/
