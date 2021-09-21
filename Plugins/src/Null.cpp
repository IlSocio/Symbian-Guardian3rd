

#include "null.h"
#include "client.h"
#include "common.h"

// Construction and destruction functions

CNull* CNull::NewL(TAny* aInitParams)
	{
	CNull* self=new(ELeave) CNull();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams); 
	CleanupStack::Pop();
	return self;
	}

CNull::~CNull()
	{
	}

CNull::CNull()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CNull::ConstructL(TAny* aInitParams)
	{
	BaseConstructL(aInitParams);
	}


TPtrC CNull::PluginId()
	{
	return TPtrC(KNULL);
	}


void CNull::ProcessCommandL(const TDesC& aData)
	{
	TInt errCode = GetParamValueInt(KERR);
	switch (errCode)
	{
		case 0: // Miss Delim
			TBuf<64> txt;
			iResReader->ReadL(R_NULL_DELIM, txt);
			break;
		case 1:	// Guardian: Error - Plugin Name Exceed Maximum Length!
			TBuf<64> txt;
			iResReader->ReadL(R_NULL_LENGTH, txt);
			break;
		case 2:	// Miss Plugin
			TPtrC plugname = GetParamValue(KNAME);
			TBuf<128> txt;
			iResReader->ReadL(R_NULL_NOTFOUND, txt);
			txt.Append(plugname);
			break;
		default:
			TBuf<64> txt;
			iResReader->ReadL(R_NULL_UNKN, txt);
			break;
			break;
	}
	SendSmsL(txt);
	Complete(KErrNone);
	}
	
