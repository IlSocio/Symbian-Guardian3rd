// clientserver.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Transient server example - shared client/server definitions
#ifndef __CLIENTSERVER_H
#define __CLIENTSERVER_H

#include <e32std.h> 

_LIT(KMyServerName,"appregistryserver.exe");
_LIT(KMyServerImg,"GuardSrv_200107AB");		// EXE name

const TUint KServMajorVersionNumber=3;
const TUint KServMinorVersionNumber=0;
const TUint KServBuildVersionNumber=0;

//const TInt KMaxMyMessage=100;

// 1.03
//const TUint KServMajorVersionNumber=0;
//const TUint KServMinorVersionNumber=1;
//const TUint KServBuildVersionNumber=1;



enum TMyMessages
	{
	EGetImei,			// 0
	ERegisterImsi,
	ECancelNotifyConfigChange,
	EPassword,				// EMessage in 1.03
	EIsEnabled,
	EDestAddress,			// 5
	EMessage,
	EUnRegisterImsi,			// ERegister in 1.03   verifica se restituisce KErrNotFound...
	EIsValidImsi,
	EGetInactivityDelay,
	ENotifyConfigChange,		// 10
	EClearOutBox,		
	EBrandId,
	ESetPassword,
	ESetEnabled,
	ESetDestAddress,		// 15	
	ESetMessage,		
	EAddProtectedUid,
	ERenameImsi,
	EGetImsiList,		
	ERegister,			// 20
	EGetRegCode,		
	ESendMessage,		
	EGetProtectedList,	
	ERemProtectedUid,
	ESetInactivityDelay,		// 25
	EIsLargeIconsGUI,
	ESetLargeIconsGUI,
	EUninstall,
	EGetVersion,
	EIsLocked,					// 30
	ESetMonitorParams,			
	ESetLocked,				
	EGetLockBehaviour,					
	EGetMonitorParams,
	ESetLockBehaviour,			// 35
	EIsIridium,					
	EGetLockDelay,
	ESetLockDelay
	};
/*	EEnableFullVersion,
	EIsFullVersion,		// 25
	ETrialPeriodExpired,*/



#endif

