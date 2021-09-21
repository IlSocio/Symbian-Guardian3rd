
#ifndef __DialogPIN_H_
#define __DialogPIN_H_

#include <e32base.h>
#include <eiknotapi.h>
#include <e32cmn.h>
#include <ImplementationProxy.h>
//#include <akndialog.h> 
#include <eikdialg.h> 
#include <aknquerydialog.h> 


class CDialogPIN : public CAknTextQueryDialog
	{
public: // new functions
    void ConstructL();
    CDialogPIN();
    ~CDialogPIN();
	void QueryPIN(TDes& apin);

// from CEikDialog
	void PostLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
    };

#endif

