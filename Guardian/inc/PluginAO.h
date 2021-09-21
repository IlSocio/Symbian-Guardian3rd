/*
============================================================================
 Name        : PluginAO.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CPluginAO declaration
============================================================================
*/

#ifndef PLUGINAO_H
#define PLUGINAO_H
#include <Ecom\ECom.h>

#include <FuzzyByte\FileLogger.h>
#include <e32base.h>	// For CActive, link against: euser.lib
#include <e32std.h>		// For RTimer, link against: euser.lib
#include <FuzzyByte\Guardian\Interface.h>


class CGuardPlugInterface;

class MPluginObserver 
{
public:
	virtual void PluginCompletedL(TAny* src, TInt ris) = 0;
};


class CPluginAO : public CActive
{
public:
	static CPluginAO* NewL(const TDesC& name);
	// Cancel and destroy
	~CPluginAO();

	// Function for making the initial request
	void StartPlugin(const TDesC& srcNumber, const TDesC& data);
	TBool Exists();
	void SetObserver(MPluginObserver* obs);
	TPtrC PluginId();

protected: 
	CPluginAO();
	void ConstructL(const TDesC& name);

	// Handle completion
	void RunL();
	
	// How to cancel me
	void DoCancel();
	
	// Override to handle leaves from RunL(). Default implementation causes
	// the active scheduler to panic.
	TInt RunError(TInt aError);

private:
	enum TPluginAOState
	{
	    EUninitialized,	// Uninitialized
	    EPluginRunning	// Initalized
	};

private:
	TPluginAOState iState;
	CGuardPlugInterface* iPlugin;
	MPluginObserver* iObserver;
	__LOG_DECLARATION_MEMBER
};

#endif

