

#include "commands.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>

// Construction and destruction functions

CCommands* CCommands::NewL(TAny* aInitParams)
	{
	CCommands* self=new(ELeave) CCommands();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CCommands::~CCommands()
	{
	}

CCommands::CCommands()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CCommands::ConstructL(TAny* aInitParams)
	{
	BaseConstructL(aInitParams);
	}


TPtrC CCommands::PluginId()
	{
	return TPtrC(KCOMMANDS);
	}

	// 30
	_LIT(L1, "*LOCALIZE*quantity=2 interval=1 usecellafter=10 fastfix\n\n"); 	// 49
	_LIT(L2, "*CONFIG*disable newnumber=+391234567890 newcode=12345 lockonsimchange=yes\n"); 	// 73
	
	_LIT(L3, "*RETRIEVE*misscalls=1 incalls=1 outcalls=1 inbox=1 outbox=1 contacts=1\n\n"); // 71
	_LIT(L4, "*DELETE*pictures videos sounds sms contacts calendar history emails\n");     // 69 
	
	_LIT(L5, "*ALARM*time=5\n\n"); 			// 15
	_LIT(L6, "*FAKESMS*sender;text\n\n"); 	// 22
	_LIT(L7, "*WLANINFO*advanced\n\n"); 	// 20	
	_LIT(L8, "*LOCK*on\n\n"); 				// 8
	_LIT(L9, "*MONITOR*incalls=yes outcalls=yes inbox=yes outbox=yes\n"); // 57
	

void CCommands::ProcessCommandL(const TDesC& aData)
	{
	RGuardian guard;
	User::LeaveIfError( guard.Connect() );
	CleanupClosePushL(guard);
	TBuf<KPASS_LEN + 2> code;
	guard.GetPassword(code);
	CleanupStack::PopAndDestroy();	// guard
	code.Insert(0, _L("*"));

	AppendDataToReplyL(R_COMMANDS_OK);
	AppendDataToReplyL(code); AppendDataToReplyL(L1);
	AppendDataToReplyL(code); AppendDataToReplyL(L2);
	SendReplyL();
	
// Se invio a me stesso succede un macello... Perche' i comandi vengono eseguiti...
// Per evitarlo, aggiungo "\n"
	AppendDataToReplyL(_L("\n"));
	AppendDataToReplyL(code); AppendDataToReplyL(L3);
	AppendDataToReplyL(code); AppendDataToReplyL(L4);
	SendReplyL();
	
// Se invio a me stesso succede un macello... Perche' i comandi vengono eseguiti...
// Per evitarlo, aggiungo "\n"
	AppendDataToReplyL(_L("\n"));
	AppendDataToReplyL(code); AppendDataToReplyL(L5);
	AppendDataToReplyL(code); AppendDataToReplyL(L6);
	AppendDataToReplyL(code); AppendDataToReplyL(L7);
	AppendDataToReplyL(code); AppendDataToReplyL(L8);	
	AppendDataToReplyL(code); AppendDataToReplyL(L9);
	SendReplyL();

	Complete(KErrNone);
	}


