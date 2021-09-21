//
// CAlarm.h
// Copyright © 2001 Symbian Ltd. All rights reserved.
//

#ifndef _CALARM__
#define _CALARM__

#include "abstractplugin.h"
#include <e32base.h>
#include <msvapi.h>
#include <FuzzyByte\FileLogger.h>
#include <MdaAudioTonePlayer.h>


// An implementation of the CExampleInterface definition
class CAlarm : public CAbstractPlugin, public MMdaAudioToneObserver
	{
public:
	// Standardised safe construction which leaves nothing the cleanup stack.
	static CAlarm* NewL(TAny* aInitParams);
	// Destructor
	virtual ~CAlarm();

	// Implementation of CExampleInterface
//	void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString);
//	virtual void CancelRemoteCommand();
	virtual void ProcessCommandL(const TDesC& aString);
	virtual void CancelCommandL();

	TPtrC PluginId();
	virtual void MatoPrepareComplete(TInt aError);
	virtual void MatoPlayComplete(TInt aError);

private:
	// Construction
	CAlarm();
	virtual void ConstructL(TAny* aParams);

private:
	// Parameters taken from client
	CMdaAudioToneUtility* iPlayer;
	};

#endif

