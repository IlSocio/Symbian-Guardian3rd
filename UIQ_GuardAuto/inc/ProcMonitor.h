/*
============================================================================
 Name        : ProcMonitor.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CProcMonitor declaration
============================================================================
*/

#ifndef ProcMonitor_H
#define ProcMonitor_H

#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib


class MProcObserver 
{
public:
	virtual void NotifyProcTerminated(const TDesC& procName) = 0;
};


class CProcMonitor : public CActive
{
public:
	// C++ constructor
	CProcMonitor(MProcObserver& observer);
	
	// Second-phase constructor
	void ConstructL(const TDesC& process);
	
	// Cancel and destroy
	~CProcMonitor();


private: // From CActive
	// Handle completion
	void RunL();
	
	// How to cancel me
	void DoCancel();
	
	// Override to handle leaves from RunL(). Default implementation causes
	// the active scheduler to panic.
	//void RunError(TInt aError);

private:
	enum TProcMonitorState
	{
	    EUninitialized,	// Uninitialized
	    EInitialized,	// Initalized
	    EError			// Error condition
	};

private:
	MProcObserver& iObserver;
	RProcess iSysStartProcess;
	TInt    iState;		// State of the active object
	TFullName iProcName;
};

#endif
