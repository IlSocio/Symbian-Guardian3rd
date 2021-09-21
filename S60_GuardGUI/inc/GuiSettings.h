/*
 ============================================================================
 Name		: GuiSettings.h
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CGuiSettings declaration
 ============================================================================
 */

#ifndef GUISETTINGS_H
#define GUISETTINGS_H

// INCLUDES
#include <FuzzyByte\SettingsFile.h>

#include <e32std.h>
#include <e32base.h>
// CLASS DECLARATION

/**
 *  CGuiSettings
 * 
 */
class CGuiSettings : public CSettingsFile
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CGuiSettings();

	/**
	 * Two-phased constructor.
	 */
	static CGuiSettings* NewL(RFs& aFs);

	/**
	 * Two-phased constructor.
	 */
	static CGuiSettings* NewLC(RFs& aFs);

	virtual void ExternalizeL(RWriteStream& aStream) const;
	virtual void InternalizeL(RReadStream& aStream);
	
protected:
	virtual void UpgradeFromOldVersion(RReadStream& aStream, const TDesC& aOldVersion);
	virtual void RestoreToDefaults();
	
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CGuiSettings(RFs& aFs);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
public:
	TBool iLargeIcons;
	TBool iShowRomApps;
	TBool iShowUserApps;
	TBool iShowSystemApps;

	};

#endif // GUISETTINGS_H
