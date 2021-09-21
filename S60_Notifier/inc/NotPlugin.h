
#ifndef __NOTPLUGIN_H_
#define __NOTPLUGIN_H_

#include <e32base.h>
#include <eiknotapi.h>
#include <e32cmn.h>
#include <ImplementationProxy.h>
#include <FuzzyByte\timeouttimer.h>
#include "AsyncQueryDialog.h"
#include "pinview.h"


class CNotPlugin : public CActive, public MEikSrvNotifierBase2, public MAsyncQueryObserver
	{
public: // new functions
    static MEikSrvNotifierBase2* NewL();
    void ConstructL();
    CNotPlugin();
    ~CNotPlugin();
//  IMPORT_C void UpdateL(const TDesC8 &aBuffer, TInt aReplySlot, const RMessagePtr2 &aMessage);
//	IMPORT_C void HandleSystemEventL(TUid aEvent);
//	IMPORT_C TInt NotifierCapabilites();


// from MEikSrvNotifierBase
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& buffer);
	void StartL(const TDesC8& buffer, TInt replySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8 &aBuffer);

	virtual void DialogClosedL(TBool ok, const TDesC& code);

	
	void ChiudiNotifierL(const TInt err, const TDesC8& valore);
// from CActive
	void RunL();
	void DoCancel();
	virtual TInt RunError(TInt aError);

private:
	CPinView* iBackgr;
//	CAsyncQueryDialog* iDlg;
	TNotifierInfo iInfo;
	RMessagePtr2 iMessage;
	TInt iReplySlot;
	TBuf<20> iGoodPass;
	HBufC* iWrongMsg;
//	CTimeOutTimer* iTimer;
	TInt iOffset;
	CAsyncQueryDialog* iDlg;
	TBool iBadCode;
	TBool iDisableCancel;
	TBool iLaunchedGuardian;
    };

#endif

