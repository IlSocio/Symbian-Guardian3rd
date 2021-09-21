/*
============================================================================
 Name        : GuardGUI.cpp
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : Application entry point
============================================================================
*/

// INCLUDE FILES
#include "GuardGUIApplication.h"

#include <eikstart.h>
 

LOCAL_C CApaApplication* NewApplication() 
	{
	return new CGuardGUIApplication; 
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}
 
  
 
