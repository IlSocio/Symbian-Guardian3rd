//
// CNull.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CNULL__
#define _CNULL__

#include "abstractplugin.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\logging.h>


// An implementation of the CExampleInterface definition
class CNull : public CAbstractPlugin
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CNull* NewL(TAny* aInitParams);
	// Destructor
	~CNull();

	// Implementation of CExampleInterface
	void ProcessCommandL(const TDesC& aData);
	TPtrC PluginId();

private:
	// Construction
	CNull();
	void ConstructL(TAny* aParams);

private:
	};

#endif

