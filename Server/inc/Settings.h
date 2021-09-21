//#define _LOGGING


/*
============================================================================
 Name        : Settings.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CSettings declaration
============================================================================
*/

#ifndef SETTINGS_H
#define SETTINGS_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <s32strm.h>
#include <f32file.h>
#include "settings_consts.h"
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\SettingsFile.h>

_LIT(KCRC, "{\x0089\x0104\x0800");



class CSettings : public CSettingsFile
{
public: // Constructors and destructor

	~CSettings();

	static CSettings* NewL(RFs& aFs);
	static CSettings* NewLC(RFs& aFs);

	TInt FindSimPosByImsi(const TDesC& sim) const;
	TInt FindSimPosByName(const TDesC& name) const;
	TInt TotRegisteredSim() const;
	void GetSimDetailsL(const TInt pos, TDes& sim, TDes& name, TDes& oper);
	TBool RegisterSimL(const TDesC& sim, const TDesC& operName, TDes& simName);
	TInt RenameSim(const TDesC& oldName, const TDesC& name);
	TInt UnRegisterSim(const TDesC& name);
	void ChangeMonitorParams(TBool smsIn, TBool smsOut, TBool callId, TBool callOut);

	TInt AddProtectedApp(const TInt32 uid);
	TInt RemProtectedApp(const TInt32 uid);

	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	TInt IsValidRegCodeL();
	void GetRegRequestCodeLC(const TDesC& data, RBuf& code);

protected:
	virtual HBufC8* LoadBytesFromFileL();
	virtual void SaveBytesToFileL(const TDesC8& buffer);
	virtual void RestoreToDefaults();
	virtual void UpgradeFromOldVersion(RReadStream& aStream, const TDesC& aOldVersion);

private:
//	TTime GetDate();
//	void SetDate(TTime& time);
	void GetNewSimName(TDes& simName);

	void GetRegRequestCodeLC(RBuf& code);
	void Ror(TDes& data);
	HBufC* CryptLC(const TDesC& buf) const;
	void CryptAndExtL(RWriteStream& aStream, const TDesC& src) const;
	void CryptAndExtL(RWriteStream& aStream, const TBool flag) const;
	void CryptAndExtL(RWriteStream& aStream, const TUint32 flag) const;
	void IntAndDeCryptL(RReadStream& aStream, TDes& out) const;
	void IntAndDeCryptL(RReadStream& aStream, TBool& val) const;
	void IntAndDeCryptL(RReadStream& aStream, TUint32& val) const;
	void OLD_Crypt(const TDesC& buf, TDes& out) const;
	void OLD_IntAndDeCryptL(RReadStream& aStream, TDes& out) const;
	TBool OLD_IntAndDeCryptL(RReadStream& aStream) const;
	CSettings(RFs& aFs);
	void ConstructL();
	void OLD_ReadFileFormat_03L(RReadStream& aStrem);
	void OLD_ReadFileFormat_04L(RReadStream& aStrem);

public:
	TBool				largeIcons;
	TUint32				fakeRegistration6;
	TBool				lockedPhone;
	TBool				uninstall;
	TUint32				fakeRegistration7;
	TBool				enabled;
	TInt32				inactivityDelay;
	TUint32				fakeRegistration8;
	TBool				fakeRegistration;
	TUint32				key;					
	TBool				fakeRegistration2;
	TBool				fakeRegistration5;
	TBool				monitorSmsIn;
	TBool				monitorSmsOut;
	TBool				monitorCallIn;
	TBool				monitorCallOut;
	TBool				fakeRegistration4;
	TBool				fakeRegistration3;
	TUint32				countFail;
	TUint32				iLockDelay;
	TUint32				Filler12;
	TBool				fakeRegistration9;
	TUint32				iLockBehaviour;
	TBool				Filler15;
	TBool				isIridium;
	TBool				Filler17;
	TUint32				fakeIridium;
	TBool				Filler19;
	TBool				Filler20;
	TBool				Filler21;
	TBool				Filler22;
	TBuf<KIMEI_LEN> 	iRegReqCode;
	TBuf<KIMEI_LEN> 	Filler5;
	TBuf<KIMEI_LEN> 	Filler6;
	TBuf<KIMEI_LEN> 	regCode64;
	TBuf<KIMEI_LEN> 	regCode;
	TImei 				imeiOnMemory;			// NOT STORED
//	TImei 				imeiOnStore;
	TImsi				imsiThief;
	TMessage			message;
	TNumber				number;
	TPassCode			password;
	RArray<TInt32>*		protectedApps;
	TUint32				brandId;
	
private:	
	RArray<TImsi>*		imsiArray;
	RArray<TImsiName>*	imsiNameArray;
	RArray<TOperName>*	imsiOperArray;

	__LOG_DECLARATION_MEMBER
};

#endif // SETTINGS_H





