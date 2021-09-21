/*
============================================================================
 Name        : Installer.h
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CInstaller declaration
============================================================================
*/

#ifndef INSTALLER_H
#define INSTALLER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <MSVAPI.H>

// CLASS DECLARATION



/**
*  CInstaller
*
*/
class CInstaller : public CBase, public MMsvSessionObserver
{
public: // Constructors and destructor

	/**
        * Destructor.
        */
	~CInstaller();

        /**
        * Two-phased constructor.
        */
	static CInstaller* NewL();

        /**
        * Two-phased constructor.
        */
	static CInstaller* NewLC();

	TBool Get_BT_IRDA_InboxFileL(TDes& path);
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);

private:

	/**
        * Constructor for performing 1st stage construction
        */
	CInstaller();

	void ConstructL();

};

#endif // INSTALLER_H
