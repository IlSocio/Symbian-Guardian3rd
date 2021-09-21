
#ifndef __PINQUERYDIALOG_H__
#define __PINQUERYDIALOG_H__


#include <aknquerydialog.h>

class MAsyncQueryObserver
{
public:
	virtual void DialogClosedL(TBool ok, const TDesC& code) = 0;
};


class CAsyncQueryDialog : public CAknTextQueryDialog 
{
public:	
    CAsyncQueryDialog(MAsyncQueryObserver& obs, const TDesC& text);
    virtual ~CAsyncQueryDialog();
	virtual TBool OkToExitL(TInt aButtonId);
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void PrepareLC(TInt aResourceId);
    void PreLayoutDynInitL();
    void PostLayoutDynInitL();
    void Close();
//    virtual void DynInitMenuPaneL(TInt /*aResourceId*/, CEikMenuPane* /*aMenuPane*/);
//    virtual TBool CheckIfEntryTextOk() const;

private:
    TBool iDisableCancel;
	MAsyncQueryObserver& iObserver;
	TBuf<20> iText;
};



#endif

