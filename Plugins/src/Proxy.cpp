//
// Proxy.cpp
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

#include "Fakesms.h"
#include "Forward.h"
#include "Alarm.h"
#include "Delete.h"
#include "Localize.h"
#include "Config.h"
#include "Commands.h"
#include "WLanInfo.h"
#include "Monitor.h"
#include "Lock.h"

#include <e32std.h>
#include <ImplementationProxy.h>

//#include "null.h"


// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] = 
	{
		IMPLEMENTATION_PROXY_ENTRY(0x200112DE,	CWLanInfo::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E0,	CFakeSms::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E1,	CForward::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E2,	CAlarm::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E3,	CDelete::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E4,	CLocalize::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E5,	CConfig::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200112E6,	CCommands::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200131C9,  CMonitor::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0x200131CA,  CLock::NewL)
	};

// Exported proxy for instantiation method resolution
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
	return ImplementationTable;
	}
