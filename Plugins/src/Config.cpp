

#include "config.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>
// Construction and destruction functions

CConfig* CConfig::NewL(TAny* aInitParams)
	{
	CConfig* self=new(ELeave) CConfig();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self; 
	}

CConfig::~CConfig()
	{
	}

CConfig::CConfig()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CConfig::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	}


TPtrC CConfig::PluginId()
	{
	return TPtrC(KCONFIG);
	}


void CConfig::ProcessCommandL(const TDesC& aString)
	{
	__LOG_TXT("ProcessCommandL");

	TPtrC ptrLock = GetParamValue(KLOCKPHONE);
	TPtrC ptrNumb = GetParamValue(KNEWNUMBER);
	TPtrC ptrPass = GetParamValue(KNEWCODE);
	TBool doLock = (ptrLock.Length() > 0);
	TBool doNewNumb = (ptrNumb.Length() > 3);
	TBool doNewPass = (ptrPass.Length() > 4) && (ptrPass.Length() < 9);
	TBool doDisable = ( iDataUpper.Find( KDISABLE ) >= 0 );
	RGuardian guard;
	User::LeaveIfError(guard.Connect());
	CleanupClosePushL(guard);

	TBool doSomething = doDisable | doNewPass | doNewNumb | doLock;
	if (doSomething)
		{
		AppendDataToReplyL(R_CONFIG_OK);
		}
	else
		{
		AppendDataToReplyL(R_CONFIG_KO);
		}
	
	if ( doLock ) 
		{
		if (ptrLock == KNO)
			{
			guard.SetLockBehaviour(ENoLock);
			AppendDataToReplyL(R_CONFIG_LOCK_OFF);
			}		
		if (ptrLock == KONSIMCHANGE)
			{		
			guard.SetLockBehaviour(ELockOnSimChange);
			AppendDataToReplyL(R_CONFIG_LOCK_ON_SIM_CHANGE);
			}
		if (ptrLock == KONSTARTUP)
			{		
			guard.SetLockBehaviour(ELockOnStartup);
			AppendDataToReplyL(R_CONFIG_LOCK_ON_STARTUP);
			}
		}
	
	if ( doDisable )
		{
		guard.SetEnabled(EFalse);
		AppendDataToReplyL(R_CONFIG_DISABLED);
		}

	if (doNewNumb)
		{
		TInt resID = 0;
		if (guard.SetDestAddress(ptrNumb) == KErrNone)
			resID = R_CONFIG_NUMB_CHANGED;
		else
			resID = R_CONFIG_NUMB_UNCHANGED;
		AppendDataToReplyL(resID);
		}

	if (doNewPass)
		{
		TInt resID = 0;
		if (guard.SetPassword(ptrPass) == KErrNone)
			resID = R_CONFIG_CODE_CHANGED;
		else
			resID = R_CONFIG_CODE_UNCHANGED;
		// iReply.Append(_L("Code Changed! "));
		// iReply.Append(_L("Code NOT Changed! "));
		AppendDataToReplyL(resID);
		}

/*	if ( iDataUpper.Find( KSTOPSMS ) >= 0 )
	{
		guard.SetEnabled(EFalse) == KErrNone
		reply.Append(_L("SMS Notify stopped! "));
	}*/
	CleanupStack::PopAndDestroy();	// guard
	
	SendReplyL();

	__LOG_TXT("ProcessCommandL");

	// NON EFFETTUA LA COMPLETE PERCHE' IL COMANDO SARA' ANNULLATO CAUSA CHIUSURA DI GUARDIAN...
	if (!doDisable)
		Complete(KErrNone);
	}

