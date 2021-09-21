//#define _LOGGING

#ifndef __T_SERVER_H__
#define __T_SERVER_H__

#include <e32base.h>
#include "clientserver.h"
#include "Server.pan"
#include "sendsmssocket.h"
#include <f32file.h>
#include <ES_SOCK.H>
#include "client.h"
#include "settings.h"
//#include "settingsOld.h"
#include <FuzzyByte\timeouttimer.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\phone.h>


//_LIT(KOUTPATH, "c:\\private\\200107AB\\outbox\\");
//_LIT(KConfigFile, "c:\\private\\200107AB\\guardian.dat");
_LIT(KOutBoxDir, "outbox\\");
_LIT(KNewConfigFile, "guardian4.dat");
_LIT(KBrandFile, "brand.txt");


/*class CShutdown : public CTimer
	{
//	const TInt KMyShutdownDelay=0x2000000;	// approx 20s
public:
	inline CShutdown();
	inline void ConstructL();
	inline void Start();
private:
	void RunL();
	};*/


class CMyServer : public CServer2, public MSmsSendHandler, public MTimeOutNotifier
	{
public:
	static CMyServer* NewLC();
	virtual ~CMyServer();
	static TInt EntryPoint(TAny* aStarted);
	void AddSession();
	void DropSession();
	void SetMessageL(const TDesC& aMessage);
	void NotifyChange(TAny* aSource, const TConfigChangeEvent aChangeCode);
	virtual void SmsSentL();
	virtual void AllSmsWereSentL();
	TInt SendMessageL(const TDesC& aNumber, const TDesC& aMessage, TBool split);
	void ClearOutBox();
	void TimerExpiredL(TAny* src);

private:
	CMyServer(TInt aPriority);
	void ConstructL();
	CSession2* NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const;
	static void ThreadMainL();
	TUint32 LoadBrandTxtL();

	TInt LoadSettingsL();
	void SaveSettingsL();

public:
	TBool iMsgToSend;
	RFs iFs;
	CPhone* iPhone;
	CSettings* iSettings;
//	CSettingsOld* iSettings;
	TImei iImei;
	TInt iSessionCount;
	TBool iHasChanged;

private:
	TBool iUninstall;
	RBuf iConfigFile;
	CSmsSenderSocket* iSmsSender;
	RSocketServ iSocketServ;
	CTimeOutTimer* iShutdown;
	__LOG_DECLARATION_MEMBER
	};

#endif

