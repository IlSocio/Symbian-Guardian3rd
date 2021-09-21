//
// CCommands.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CCOMMANDS__
#define _CCOMMANDS__

#include "abstractplugin.h"
#include <e32base.h>
#include <msvapi.h>


// An implementation of the CExampleInterface definition
class CCommands : public CAbstractPlugin
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CCommands* NewL(TAny* aInitParams);
	// Destructor
	~CCommands();

	// Implementation of CExampleInterface
	void ProcessCommandL(const TDesC& aData);
	TPtrC PluginId();

private:
	// Construction
	CCommands();
	void ConstructL(TAny* aParams);

private:
	};

#endif

