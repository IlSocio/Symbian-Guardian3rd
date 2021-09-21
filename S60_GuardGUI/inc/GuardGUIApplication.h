/*
============================================================================
 Name        : GuardGUIApplication.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Main application class
============================================================================
*/

#ifndef __GUARDGUIAPPLICATION_H__
#define __GUARDGUIAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "GuardGUI.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file

// CLASS DECLARATION

/**
* CGuardGUIApplication application class.
* Provides factory to create concrete document object.
* An instance of CGuardGUIApplication is the application part of the
* AVKON application framework for the GuardGUI example application.
*/
class CGuardGUIApplication : public CAknApplication
	{
	public: // Functions from base classes

		/**
		* From CApaApplication, AppDyellUid.
		* @return Application's UID (KUidGuardGUIApp).
		*/
		TUid AppDllUid() const;

	protected: // Functions from base classes

		/**
		* From CApaApplication, CreateDocumentL.
		* Creates CGuardGUIDocument document object. The returned
		* pointer in not owned by the CGuardGUIApplication object.
		* @return A pointer to the created document object.
		*/
		CApaDocument* CreateDocumentL();
	};

#endif // __GUARDGUIAPPLICATION_H__

// End of File
