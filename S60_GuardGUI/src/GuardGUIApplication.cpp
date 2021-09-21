/*
============================================================================
 Name        : GuardGUIApplication.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Main application class
============================================================================
*/

// INCLUDE FILES
#include "GuardGUIDocument.h"
#include "GuardGUIApplication.h"
#include "GuardGUIconsts.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CGuardGUIApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CGuardGUIApplication::CreateDocumentL()
	{
	// Create an GuardGUI document, and return a pointer to it
	return (static_cast<CApaDocument*>
		( CGuardGUIDocument::NewL( *this ) ) );
	}

// -----------------------------------------------------------------------------
// CGuardGUIApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CGuardGUIApplication::AppDllUid() const
	{
	// Return the UID for the GuardGUI application
	return KUidGuardGUIApp;
	}

// End of File
