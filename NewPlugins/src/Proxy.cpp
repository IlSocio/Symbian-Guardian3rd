//
// Proxy.cpp
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

#include "Empty1.h"
#include "Empty2.h"

#include <e32std.h>
#include <ImplementationProxy.h>


// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] = 
	{
		IMPLEMENTATION_PROXY_ENTRY(0xE0021111,	CEmpty1::NewL),
		IMPLEMENTATION_PROXY_ENTRY(0xE0021112,	CEmpty2::NewL)
	};

// Exported proxy for instantiation method resolution
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
	{
	aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
	return ImplementationTable;
	}
