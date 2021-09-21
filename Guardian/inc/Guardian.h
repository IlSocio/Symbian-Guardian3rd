/*
============================================================================
 Name        : Guardian.h
 Author      : Marco Bellino
 Version     :
 Copyright   : Your copyright notice
 Description : Exe header file
============================================================================
*/

#ifndef __GUARDIAN_H__
#define __GUARDIAN_H__

//  Include Files
#include "activitymanager.h"
#include "foregroundobserver.h"
#include "logcleaner.h"
#include "recvsmssocket.h"
#include "pluginmanager.h"
#include "SecurityCode.h"

#include <FuzzyByte\Guardian\settings_consts.h>
#include <FuzzyByte\Guardian\client.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\pubsubobserver.h>
#include <FuzzyByte\timeouttimer.h>
#include <FuzzyByte\phone.h>
#include <FuzzyByte\callsmonitor.h>
#include <FuzzyByte\SmsMtmMonitor.h>
#include <FuzzyByte\SimNotifier.h>

#include <e32base.h>
#include <MSVAPI.H> 

_LIT(KDELIMITER, "*");

class CGuardian : public CBase, public MFgrCallBack, public MPubSubObserver, public MSmsRecvHandler, public MPhoneObserver, MTimeOutNotifier, MCallsObserver, MSecurityCodeNotifier, MSmsMtmObserver, MSimNotifier
{
public:
	static CGuardian* NewLC(TBool fromGui);
	virtual ~CGuardian();
	void StartL();
	
private:
	void CheckSimAndSendSmsL();
	void StartObserversAndWaitForSimL();
	void CheckAndLockPhoneIfNeededL();
	virtual void ForegroundEventL(TUid aAppUid);
	virtual void PropertyChangedL(TUid category, TUint key, TInt value);
	virtual void IncomingSmsL(const TAny* src, const TDesC& aFromNumber, const TDesC& aData);
	virtual void HandlePhoneEventL(TPhoneFunctions event);

private: // From MSimNotifier
	virtual void SimNotifyL(TBool isPresentAndReady);

private: // From MSmsObserver	
	void HandleNewMtmSmsL(const TDesC& aNumber, const TDesC& aText, TBool isIncoming);

private: // From MSecurityCodeNotifier
	virtual void GotSecurityCodeL(TInt error, TBool isValidCode);

private: // from MTimeOutNotifier
    virtual void TimerExpiredL(TAny* src);

private: // from MCallsObserver
	virtual void CallStatusChangedL(CTelephony::TCallStatus& aStatus, TInt aError);

protected:
	void RealtimeSmsOrCallL(const TDesC& aDescription, const TDesC& aNumber, const TDesC& aText);
	void InitializeGoldAndPlatinumL(RGuardian& srv);
	CGuardian(TBool fromGui);
	void ConstructL();
//	TBool AskPasswordL(TDes& pass);

private: 
	CTelephony::TNetworkRegistrationV1Pckg iNetStatusPckg;
	CTelephony::TNetworkRegistrationV1 iNetStatus; // Network Status
	RWsSession iSession;
	CFgrObserver* iForegrObs;	// Gestisce richiesta Password per le applicazioni protette
	CLogCleaner* iLogCleaner;		// Pulisce il Registro SMS Inviati / Ricevuti
	CPubSubObserver* iConfigObs;	// Rileva cambi alla configurazione
	CSimNotifier* iSimNotifier;		// Rileva la presenza della SIM
	RFs iFs;
	RSocketServ iSockServ;
	CSmsReceiverSocket* iSmsPlugin;
	CSmsReceiverSocket* iSmsLostPass;
	CPhone* iPhone;
	TPassCode iPassword;
	RArray<TInt32>* iProtApps;
	TBool iProtApps_Enabled;
	TTimeIntervalSeconds iProtApps_Delay;
	//TTimeIntervalSeconds iProtAppsCurr_Delay;
	CTimeOutTimer* iTimer;
	CPluginManager* iPluginManager;
	TBuf<10> iRegCode;
	TBool iFromGui;
	CCallsMonitor*	iCallsMonitor;
	TBool iIsLocked;
	CSecurityCode* iSecurityCode;
	TBool iSmsIn;
	TBool iSmsOut;
	TBool iCallsIn;
	TBool iCallsOut;
	TBool iDoneInitialization;
	
    CSmsMtmMonitor* iSmsMonitor;
	__LOG_DECLARATION_MEMBER
};


//  Function Prototypes

GLDEF_C TInt E32Main();


#endif  // __GUARDIAN_H__
