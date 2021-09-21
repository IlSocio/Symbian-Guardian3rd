/*
 ============================================================================
 Name		: GuiSettings.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CGuiSettings implementation
 ============================================================================
 */

#include "GuiSettings.h"
#include <FuzzyByte\FileUtils.h>
#include <s32strm.h>
#include <f32file.h>

_LIT(KConfigFile, "guardian4.dat");
_LIT(KConfigVersion, "0.1");

CGuiSettings::CGuiSettings(RFs& aFs) : CSettingsFile(aFs)
	{
	// No implementation required
	}

CGuiSettings::~CGuiSettings()
	{
	}

CGuiSettings* CGuiSettings::NewLC(RFs& aFs)
	{
	CGuiSettings* self = new (ELeave) CGuiSettings(aFs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CGuiSettings* CGuiSettings::NewL(RFs& aFs)
	{
	CGuiSettings* self = CGuiSettings::NewLC(aFs);
	CleanupStack::Pop(); // self;
	return self;
	}

void CGuiSettings::ConstructL()
	{
	TFileName filename = KConfigFile();
	FileUtils::CompleteWithPrivatePathL(iFs, filename);
	Load(filename, KConfigVersion);
	}

void CGuiSettings::UpgradeFromOldVersion(RReadStream& aStream, const TDesC& aOldVersion)
	{	
	}

void CGuiSettings::RestoreToDefaults()
	{	
	iLargeIcons = EFalse;
	iShowRomApps = ETrue;
	iShowUserApps = ETrue;
	iShowSystemApps = ETrue;
	}

void CGuiSettings::ExternalizeL(RWriteStream& aStream) const
	{ 
	// scrive usando imei che proviene dallo store...
	aStream << (TUint32) iLargeIcons;
	aStream << (TUint32) iShowRomApps;
	aStream << (TUint32) iShowUserApps;
	aStream << (TUint32) iShowSystemApps;
	}

void CGuiSettings::InternalizeL(RReadStream& aStream)
	{
	TUint32 intVal = 0;
	aStream >> intVal;	iLargeIcons = (TBool) intVal;
	aStream >> intVal;	iShowRomApps = (TBool) intVal;
	aStream >> intVal;	iShowUserApps = (TBool) intVal;
	aStream >> intVal;	iShowSystemApps = (TBool) intVal;
	}
