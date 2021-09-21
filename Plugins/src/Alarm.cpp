

#include "alarm.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>

#include <MdaAudioTonePlayer.h>

// Construction and destruction functions

CAlarm* CAlarm::NewL(TAny* aInitParams)
	{
	CAlarm* self=new(ELeave) CAlarm();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CAlarm::~CAlarm()
	{
	if (iPlayer)
		delete iPlayer;
	}

CAlarm::CAlarm()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CAlarm::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	iPlayer = CMdaAudioToneUtility::NewL(*this, NULL, EMdaPriorityMax, EMdaPriorityPreferenceQuality);
	}


TPtrC CAlarm::PluginId()
	{
	return TPtrC(KALARM);
	}


void CAlarm::ProcessCommandL(const TDesC& aSmsData)
	{
	TInt time = GetParamValueInt(KTIMER);
	if (time <= 0)
		time = GetParamValueInt(KTIME);
	TInt freq = GetParamValueInt(KFREQ);
	if (time <= 0) time = 1;
	if (freq <= 0) freq = 3000;

//	iPlayer->SetRepeats(repeats, TTimeIntervalMicroSeconds(1000000));
	__LOG_TXT("PrepareToPlay");
	iPlayer->SetVolume(iPlayer->MaxVolume());
//	iPlayer->PrepareToPlayTone(freq, TTimeIntervalMicroSeconds(time * 1000000));
	iPlayer->PrepareToPlayDualTone(freq, freq + 3000, TTimeIntervalMicroSeconds(time * 1000000));

	__LOG_TXT("Reply");
	AppendDataToReplyL( R_ALARM_OK );
	SendReplyL();
	}


void CAlarm::MatoPrepareComplete(TInt aError)
	{
	__LOG_TXT("MatoPrepareComplete");
	if (aError != KErrNone)
	{
		Complete(aError);
		return;
	}
	iPlayer->Play();
	}


void CAlarm::MatoPlayComplete(TInt aError)
	{
	__LOG_TXT("MatoPlayComplete");
	Complete(aError);
	}


void CAlarm::CancelCommandL()
{
	__LOG_TXT("Cancel Remote Command");
	TMdaAudioToneUtilityState state = iPlayer->State();
	__LOG("State:%d", state);
	if (state == EMdaAudioToneUtilityNotReady)
		iPlayer->CancelPrepare();
	if (state == EMdaAudioToneUtilityPlaying)
		iPlayer->CancelPlay();
	__LOG_TXT("Cancelled");
}
