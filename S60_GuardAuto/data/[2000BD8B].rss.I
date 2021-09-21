# 1 "c:\\online\\Guardian3rd\\GuardAuto\\data\\[2000BD8B].rss"
# 1 "C:\\Symbian\\9.1\\S60_3rd_MR\\\\epoc32\\include\\startupitem.rh" 1
/*
* ==============================================================================
*  Name        : StartupItem.rh
*  Part of     : Startup
*  Description : Definitions for the stucture of a configuration file required
*                for components started at boot time.
*  Version     : 1
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/




# 1 "C:\\Symbian\\9.1\\S60_3rd_MR\\\\epoc32\\include\\StartupItem.hrh" 1
/*
* ==============================================================================
*  Name        : StartupItem.hrh
*  Part of     : Startup
*  Description : Definitions for the data types of a configuration file required
*                for components started at boot time.
*  Version     : 1
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/



// DATA TYPES

// The policy applied for the component if it's startup failes.
//
enum TStartupExceptionPolicy
    {
    EStartupItemExPolicyNone = 0        // Do nothing.
    };


            
// End of File
# 24 "C:\\Symbian\\9.1\\S60_3rd_MR\\\\epoc32\\include\\startupitem.rh" 2


//  STRUCTURE DEFINITIONS

// -----------------------------------------------------------------------------
// STARTUP_ITEM_INFO
// Information about a component to be started at boot time.
// -----------------------------------------------------------------------------
//
STRUCT STARTUP_ITEM_INFO
    {
    BYTE version = 0;
    LTEXT executable_name(255);                // The path and name of the executable.
    WORD recovery = EStartupItemExPolicyNone;  // The exception recovery policy used.
    LONG reserved_1 = 0;                       // Reserved for future use.
    BYTE reserved_2 = 0;                       // Reserved for future use.
    BYTE reserved_3 = 0;                       // Reserved for future use.
    }


            
// End of File
# 1 "c:\\online\\Guardian3rd\\GuardAuto\\data\\[2000BD8B].rss" 2


RESOURCE STARTUP_ITEM_INFO dispatcher
	{
	executable_name = "!:\\sys\\bin\\GuardAuto_2000BD8B.exe";
	recovery = EStartupItemExPolicyNone;
	}
