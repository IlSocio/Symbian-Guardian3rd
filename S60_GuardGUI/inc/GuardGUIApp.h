/*
============================================================================
 Name        : CGuardGUIApp from GuardGUIApp.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Declares main application class.
============================================================================
*/

#ifndef GUARDGUIAPP_H
#define GUARDGUIAPP_H

// INCLUDES
#include <aknapp.h>

// CLASS DECLARATION

/**
* CGuardGUIApp application class.
* Provides factory to create concrete document object.
* 
*/
class CGuardGUIApp : public CAknApplication
	{
	
	public: // Functions from base classes
	private:

		/**
		* From CApaApplication, creates CGuardGUIDocument document object.
		* @return A pointer to the created document object.
		*/
		CApaDocument* CreateDocumentL();
		
		/**
		* From CApaApplication, returns application's UID (KUidGuardGUI).
		* @return The value of KUidGuardGUI.
		*/
		TUid AppDllUid() const;
	};

#endif



