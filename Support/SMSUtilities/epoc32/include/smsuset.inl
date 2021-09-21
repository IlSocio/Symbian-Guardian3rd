// SMSUSET.INL
//
// Copyright (c) Symbian Software Ltd. 1999-2005.  All rights reserved.


/**
* @file
* contains the implementation of the inline function the TSmsSettings class
* used to get and set the SMS settings
*/ 

 
inline const TTimeIntervalMicroSeconds32& TSmsSettings::Timeout() const
/** Gets the time-out value.

@return Time-out value */
	{
	return iTimeoutMicroSeconds32;
	}

inline void TSmsSettings::SetTimeout(const TTimeIntervalMicroSeconds32& aTimeout)
/** Sets the time-out value.

@param aTimeout Time-out value */
	{
	iTimeoutMicroSeconds32=aTimeout;
	}

inline TInt TSmsSettings::SendTryLimit() const
/** Gets the maximum number of attempts to send an SMS.

@return Maximum number of attempts to send a SMS */
	{
	return iSendTryLimit;
	}

inline void TSmsSettings::SetSendTryLimit(TInt aLimit)
/** Sets the maximum number of attempts to send an SMS.

@param aLimit Maximum number of attempts to send a SMS */
	{
	iSendTryLimit=aLimit;
	}

inline TBool TSmsSettings::DeletePDUsFromSIM() const
/** Gets whether the PDU can be deleted from the SIM.

@return True if the PDU can be deleted from the SIM */
	{
	return iFlags&ESmsFlagDeletePDUsFromSIM;
	}

inline void TSmsSettings::SetDeletePDUsFromSIM(TBool aDelete)
/** Sets whether the PDU can be deleted from the SIM.

@param aDelete True if the PDU can be deleted from the SIM */
	{
	iFlags=aDelete? iFlags|ESmsFlagDeletePDUsFromSIM: iFlags&(~ESmsFlagDeletePDUsFromSIM);
	}

inline TBool TSmsSettings::DeletePDUsFromPhoneStores() const
/** Gets whether the PDU can be deleted from the phone store.

@return True if the PDU can be deleted from the phone store */
	{
	return iFlags&ESmsFlagDeletePDUsFromPhoneStores;
	}

inline void TSmsSettings::SetDeletePDUsFromPhoneStores(TBool aDelete)
/** Sets whether the PDU can be deleted from the phone store.

@param aDelete True if the PDU can be deleted from phone store */
	{
	iFlags=aDelete? iFlags|ESmsFlagDeletePDUsFromPhoneStores: iFlags&(~ESmsFlagDeletePDUsFromPhoneStores);
	}

inline TBool TSmsSettings::DeletePDUsFromCombinedStores() const
/** Gets whether the PDU can be deleted from the combined store.

@return True if the PDU can be deleted from the combined store */
	{
	return iFlags&ESmsFlagDeletePDUsFromCombinedStores;
	}

inline void TSmsSettings::SetDeletePDUsFromCombinedStores(TBool aDelete)
/** Sets whether the PDU can be deleted from the combined store.

@param aDelete True if the PDU can be deleted from the combined store */
	{
	iFlags=aDelete? iFlags|ESmsFlagDeletePDUsFromCombinedStores: iFlags&(~ESmsFlagDeletePDUsFromCombinedStores);
	}

inline const TTimeIntervalMinutes& TSmsSettings::ReassemblyLifetime() const
/** Gets the value of the Reassembly store life time.

@return Reassembly store life time */
	{
	return iReassemblyLifetime;
	}

inline void TSmsSettings::SetReassemblyLifetime(const TTimeIntervalMinutes& aReassemblyLifetime)
/** Sets the value of the Reassembly store life time.

@param aReassemblyLifetime Reassembly store life time */
	{
	iReassemblyLifetime=aReassemblyLifetime;
	}

inline TInt TSmsSettings::KSegmentationLifetimeMultiplier() const
/** Gets the value of the segmentation store multiplier.

@return Segmentation store multiplier */
	{
	return iKSegmentationLifetimeMultiplier;
	}

inline void TSmsSettings::SetKSegmentationLifetimeMultiplier(TInt aKSegmentationLifetimeMultiplier)
/** Sets the value of the segmentation store multiplier.

@param aKSegmentationLifetimeMultiplier Segmentation store multiplier */
	{
	iKSegmentationLifetimeMultiplier=aKSegmentationLifetimeMultiplier;
	}

inline const TTimeIntervalMicroSeconds32& TSmsSettings::ModemInitializationTimeout() const
/** Gets the value of the modem initialisation timeout duration.

@return Modem initialisation timeout duration */
	{
	return iModemInitializationTimeoutMicroSeconds32;
	}

inline void TSmsSettings::SetModemInitializationTimeout(const TTimeIntervalMicroSeconds32& aTimeout)
/** Sets the value of the modem initialisation timeout duration.

@param aTimeout Modem initialisation timeout duration */
	{
	iModemInitializationTimeoutMicroSeconds32=aTimeout;
	}

inline const TTimeIntervalMicroSeconds32& TSmsSettings::SendTryTimeout() const
/** Gets the Send Try Timeout value

@return Time-out value
*/
	{
	return iSendTryTimeoutMicroSeconds32;
	}

inline void TSmsSettings::SetSendTryTimeout(const TTimeIntervalMicroSeconds32& aTimeout)
/** Sets the Send Try Timeout value.

@param aTimeout Time-out value
*/
	{
	iSendTryTimeoutMicroSeconds32=aTimeout;
	}
	
inline const TTimeIntervalMicroSeconds32& TSmsSettings::BootTimerTimeout()
/** Gets the Boot Timer Timeout value

@return Boot Timer Time-out value*/
    {
    return iBootTimerTimeout32;
    }

inline void TSmsSettings::SetBootTimerTimeout(const TTimeIntervalMicroSeconds32& aTimeout)
/** Sets the Boot Timer Timeout value

@param aTimeout Time-out value */
    {
    iBootTimerTimeout32 = aTimeout;
    }
