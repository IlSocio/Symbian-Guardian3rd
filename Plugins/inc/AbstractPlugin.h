//
// CAbstractPlugin.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CABSTRACTPLUGIN__
#define _CABSTRACTPLUGIN__

#include "Interface.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\FileLogger.h>
//#include <MdaAudioTonePlayer.h>
#include <FuzzyByte\ResReader.h>


// An implementation of the CExampleInterface definition
class CAbstractPlugin : public CGuardPlugInterface
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	~CAbstractPlugin();
	virtual TPtrC PluginId() = 0;

protected:
	virtual void ProcessCommandL(const TDesC& aString)=0;
	virtual void CancelCommandL();
	void Complete(TInt aCode);
	TInt GetParamValueInt(const TDesC& aParam);
	TPtrC GetParamValue(const TDesC& aParam);

	// Per ora serve esclusivamente per il log su file...
	void BaseConstructL(TAny* aParams);
	
	TBool AppendDataToReplyL(const TInt aResourceID);
	TBool AppendDataToReplyL(const TDesC& buff);
	TBool SendReplyL();

private:
	void SendSmsL(const TDesC& aData, TBool split=ETrue);
	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
	void CancelRemoteCommandL();

protected:
	// Parameters taken from client
	RFs iFs;
	RBuf iDataUpper;
	__LOG_DECLARATION_MEMBER

private:
	CResReader* iResReader;
	RBuf iReply;
	TBool iMustReply;
	TRequestStatus* iStatus;
	RBuf iNumber;
	};

#endif

