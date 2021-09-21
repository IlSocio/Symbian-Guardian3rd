/*
* ==============================================================================
*  Name        : CoreApplicationUIsInternalPSKeys.h
*  Part of     : S60 Core Application UIs subsystem
*  Interface   : Internal
*  Description : Internal Publish&Subscribe definitions of the
*                Core Application UIs  subsystem
*  Version     : %version:ou1cfspd#15 %
*
*  Copyright © 2005, 2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef COREAPPLICATIONUISINTERNALPSKEYS_H
#define COREAPPLICATIONUISINTERNALPSKEYS_H

#include <coreapplicationuisdomainpskeys.h>

/*****************************************
*   Location Global Privacy Value
******************************************/
// Use TUid KUidSystemCategory = { 0x101f75b6 } 
const TInt KPSUidLocationGlobalPrivacyValue = 0x100052FA;
const TUid KPSUidLocationGlobalPrivacy={KPSUidLocationGlobalPrivacyValue};
enum EPSLocationGlobalPrivacy
    {
	EPSLocationGlobalPrivacyUninitialized = 0,
    EPSLocPrivAcceptAll,  
    EPSLocPrivRejectAll,
    EPSLocPrivAlwaysAsk,
    EPSLocPrivIndividualPrivacy,
    EPSLocPrivAcceptAllTimed,
    EPSLocPrivRejectAllTimed
    };

#endif      // COREAPPLICATIONUISINTERNALPSKEYS_H

// End of File

