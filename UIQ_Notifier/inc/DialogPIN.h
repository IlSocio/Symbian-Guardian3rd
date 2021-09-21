
#ifndef __DialogPIN_H_
#define __DialogPIN_H_

#include <e32base.h>
#include <eiknotapi.h>
#include <e32cmn.h>
#include <ImplementationProxy.h>
//#include <akndialog.h> 
#include <eikdialg.h> 


class CDialogPIN : public CEikDialog, public MEikSrvNotifierBase2
	{
public: // new functions
    static MEikSrvNotifierBase2* NewL();
    void ConstructL();
	CDialogPIN();
    ~CDialogPIN();
//  IMPORT_C void UpdateL(const TDesC8 &aBuffer, TInt aReplySlot, const RMessagePtr2 &aMessage);
//	IMPORT_C void HandleSystemEventL(TUid aEvent);
//	IMPORT_C TInt NotifierCapabilites();

// from CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);

// from MEikSrvNotifierBase
	void Release();
	TNotifierInfo RegisterL();
	TNotifierInfo Info() const;
	TPtrC8 StartL(const TDesC8& buffer);
	void StartL(const TDesC8& buffer, TInt replySlot, const RMessagePtr2& aMessage);
	void Cancel();
	TPtrC8 UpdateL(const TDesC8 &aBuffer);
	
	void ChiudiNotifier(const TInt err, const TDesC8& valore);
// from CActive
//	void RunL();
//	void DoCancel();

private:
	TNotifierInfo iInfo;
	RMessagePtr2 iMessage;
	TInt iReplySlot;
	HBufC* iWrongMsg;
	TBuf<10> iGoodPass;
//	const TAny* iReturnVal;
    };

#endif

