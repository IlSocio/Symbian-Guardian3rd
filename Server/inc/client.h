// t-client.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Transient server example - client interface

#ifndef __T_CLIENT_H__
#define __T_CLIENT_H__

#include <e32std.h>
#include <e32base.h>
#include <Etel3rdParty.h>
#include <BADESCA.H>
#include <FuzzyByte\Guardian\settings_consts.h>


enum TConfigChangeEvent
	{
	ENoChanges,
	EEnableChange,
	EPasswordChange,
	EDestAddressChange,
	EMessageChange,
	EImsiListChange,
	EInactivityDelayChange,
	//EInterceptAlwaysChange,
	EProtectedAppsChange,
	ERegistrationChange,
	ELockBehaviourChange,
	EMonitorParamsChange,
	EIsLockedChange,
	EForceShutdown_Uninstall = 1001
	};

typedef TPckg<TConfigChangeEvent> TConfigPckg;



class RGuardian : public RSessionBase
	{
public:
	IMPORT_C TInt GetInactivityDelay();
	IMPORT_C TInt SetInactivityDelay(TInt delay);
	IMPORT_C TInt GetProtectedListL(RArray<TInt32>& uidList);
	
	IMPORT_C TInt RegisterSim(TDes& name);		// restituisce il nome della sim
	IMPORT_C TInt RenameSim(const TDesC& oldName, const TDesC& newName);
	IMPORT_C TBool IsEnabled();
	IMPORT_C TInt SendMessage(const TDesC& dest, const TDesC& msg, TBool split=ETrue);
	IMPORT_C TInt GetMessage(TDes& msg);
	IMPORT_C TInt GetVersion(TDes& msg);
	IMPORT_C TUint32 GetBrandId();

	IMPORT_C TInt GetPassword(TDes& pass);
	IMPORT_C TInt GetImei(TDes& imei);

	IMPORT_C TInt Connect();
	IMPORT_C TInt SetPassword(const TDesC& pass);
	IMPORT_C TInt SetEnabled(TBool enabled);
	IMPORT_C TInt SetLocked(TBool locked);
	IMPORT_C TBool IsLocked();
	
	IMPORT_C TInt SetLockDelay(TUint32 aDelay);
	IMPORT_C TUint32 GetLockDelay();
	
	IMPORT_C TInt SetLockBehaviour(TLockBehaviour locked);
	IMPORT_C TLockBehaviour GetLockBehaviour();
	IMPORT_C TInt ClearOutBox();
	IMPORT_C TInt SetMessage(const TDesC& msg);
	IMPORT_C TInt GetDestAddress(TDes& dest);
	IMPORT_C TInt SetMonitorParams(TBool smsIn, TBool smsOut, TBool callIn, TBool callOut);
	IMPORT_C void GetMonitorParams(TBool& smsIn, TBool& smsOut, TBool& callIn, TBool& callOut);

	// name e' di output
	// oper e' di input/output
	IMPORT_C TInt GetRegCode(TDes& regcode);
	IMPORT_C TInt UnRegisterSim(const TDesC& simName);
	IMPORT_C TInt SetDestAddress(const TDesC& dest);
	IMPORT_C TInt GetAuthorizedListL(RArray<TImsiName>& nameList, RArray<TOperName>& operList);
	IMPORT_C TBool IsValidSim();
//	IMPORT_C void NotifyConfigChange(TRequestStatus& aStatus, TDes8& aChangePckg);
//	IMPORT_C void CancelNotifyConfigChange();

	IMPORT_C TBool IsIridium();
	
	// 0 = Free
	// 1 = Platinum or Iridium
	// 2 = Gold
	IMPORT_C TInt Register(const TDesC& regCode);
	IMPORT_C TInt AddProtectedUid(const TInt32& uid);
	IMPORT_C TInt RemProtectedUid(const TInt32& uid);

	IMPORT_C TBool IsLargeIconsGUI();
	IMPORT_C TInt SetLargeIconsGUI(TBool large);

	IMPORT_C void Uninstall();

//	IMPORT_C TInt Send(const TDesC& aMessage);
//	IMPORT_C void Receive(TRequestStatus& aStatus,TDes& aMessage);
//	IMPORT_C void CancelReceive();
	};

#endif

