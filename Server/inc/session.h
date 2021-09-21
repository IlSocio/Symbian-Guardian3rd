//#define _LOGGING

#ifndef __T_SESSION_H__
#define __T_SESSION_H__

#include <e32base.h>

#include "server.pan"

class CMyServer;

//class CLicense;

void PanicClient(const RMessagePtr2& aMessage,TMyPanic TMyPanic);


#include <FuzzyByte\FileLogger.h>

class CMySession : public CSession2
	{
public:
	CMySession();
	void CreateL();
//	void DoNotifyChange(TConfigChangeEvent aChangeCode); // Notifica dal Server al Client
private:
	TUint ClientUID(const RMessagePtr2& aMessage);
	void SetPasswordL(const RMessage2& aMessage);
	void ImeiL(const RMessage2& aMessage);
	void SetEnabledL(const RMessage2& aMessage);
	void SetDestAddressL(const RMessage2& aMessage);
	void SetMessageL(const RMessage2& aMessage);
	void RegisterImsiL(const RMessage2& aMessage);
	void UnRegisterImsiL(const RMessage2& aMessage);
	void GetLockBehaviourL(const RMessage2& aMessage);
	void SetLockBehaviourL(const RMessage2& aMessage);
	void GetMonitorParamsL(const RMessage2& aMessage);
	void SetMonitorParamsL(const RMessage2& aMessage);
	void IsLockedL(const RMessage2& aMessage);
	void SetLockedL(const RMessage2& aMessage);
	void GetLockDelayL(const RMessage2& aMessage);
	void SetLockDelayL(const RMessage2& aMessage);
	void IsEnabledL(const RMessage2& aMessage);
	void PasswordL(const RMessage2& aMessage);
	void DestAddressL(const RMessage2& aMessage);
	void MessageL(const RMessage2& aMessage);
	void RenameImsiL(const RMessage2& aMessage); 
	void IsValidImsiL(const RMessage2& aMessage);
	void GetBrandIdL(const RMessage2& aMessage);
	void GetAuthorizedListL(const RMessage2& aMessage);
	void GetInactivityDelayL(const RMessage2& aMessage);
	void SetInactivityDelayL(const RMessage2& aMessage);
	//void GetInterceptAlwaysL(const RMessage2& aMessage);
	//void SetInterceptAlwaysL(const RMessage2& aMessage);
	void GetRegCodeL(const RMessage2& aMessage);

	void SetLargeIconsGUIL(const RMessage2& aMessage);
	void IsLargeIconsGUIL(const RMessage2& aMessage);
	void RegisterL(const RMessage2& aMessage);
	void IsIridiumL(const RMessage2& aMessage);

	void GetProtectedListL(const RMessage2& aMessage);
	void AddProtectedUidL(const RMessage2& aMessage);
	void RemProtectedUidL(const RMessage2& aMessage);

	void UninstallL(const RMessage2& aMessage);
	void GetVersionL(const RMessage2& aMessage);

	void SendMessageL(const RMessage2& aMessage);
	virtual ~CMySession();
	inline CMyServer& Server();
	void ServiceL(const RMessage2& aMessage);
	void ServiceError(const RMessage2& aMessage, TInt aError);

//	inline TBool NotificationPending() const;
// Forse non serve piu' perche' c'e' ServiceError ad occuparsene...
//	void DispatchMessageL(const RMessage2& aMessage);
private:
//	RMessagePtr2 iNotifyMsg;
	TInt iProcessedSim;
	TInt iProcessedUid;
	__LOG_DECLARATION_MEMBER
	};


#endif

