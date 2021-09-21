/*
============================================================================
 Name        : PluginManager.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CPluginManager declaration
============================================================================
*/

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

// INCLUDES
#include <FuzzyByte\FileLogger.h>
#include <e32std.h>
#include <e32base.h>
#include <DelimitedPath16.h>
#include "pluginao.h"

// CLASS DECLARATION


#define KMAX_PLUGIN_NAME 10
#define PLUGIN_DELIMITER '*'

class TPluginParser : public TDelimitedPathParser
	{
	public:
		TPluginParser();
//		TInt Remainder(const TPtrC16& aRemainder);
//		void SetDelimiter(TChar aDelimiter);
	};

/**
*  CPluginManager
* 
*/
class CPluginManager : public CBase, public MPluginObserver
{
public: // Constructors and destructor
	~CPluginManager();
	static CPluginManager* NewL(RFs& fs);
	static CPluginManager* NewLC(RFs& fs);

	void ProcessSmsPluginL(const TDesC& number, const TDesC& sms);
	void PluginCompletedL(TAny* src, TInt ris);

private:
	HBufC* ReadResL(TInt ResID);
	void SendSmsL(const TDesC& number, const TDesC& sms);
	CPluginManager(RFs& fs);
	void ConstructL();
	TInt FindElemPosByObj(TAny* obj);
	TInt FindElemPosById(const TDesC& id);

private:
	TBool iIsIridium;
	RFs& iFs;
	RPointerArray <CPluginAO> iArray;
	__LOG_DECLARATION_MEMBER
};



#endif // PLUGINMANAGER_H
