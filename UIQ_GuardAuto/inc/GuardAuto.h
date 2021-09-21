// EXAMPLERECOGNIZER.H
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#if !defined(__EXAMPLERECOGNIZER_H__)
#define __EXAMPLERECOGNIZER_H__

#if !defined(__APMREC_H__)
#include <apmrec.h>
#endif

#include "procmonitor.h"

/*
CGuardAuto is a concrete data recognizer.
It implements CApaDataRecognizerType, the abstract base 
class for recognizers.
*/
class CGuardAuto: public CApaDataRecognizerType, public MProcObserver
	{
public:
    CGuardAuto();
	void ConstructL();
    TUint PreferredBufSize();
	TDataType SupportedDataTypeL(TInt) const;   
    static CApaDataRecognizerType* CreateRecognizerL();

	virtual void NotifyProcTerminated(const TDesC& procName);
private:
    void DoRecognizeL(const TDesC&, const TDesC8&);

private:
	CProcMonitor* iMonitor;
	};

#endif


