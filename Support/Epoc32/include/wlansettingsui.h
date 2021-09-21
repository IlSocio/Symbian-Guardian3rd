/*
* ============================================================================
*  Name     : WlanSettingsUi.h 
*  Part of  : WLAN Settings UI
*
*  Description:
*      Declaration of class CWlanSettingsUi.   
*      
*  Version:
*
*  Copyright (C) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef WLAN_SETTINGS_UI_H
#define WLAN_SETTINGS_UI_H

// INCLUDES

#include <e32base.h>

// FORWARD DECLARATIONS

class CEikonEnv;
class CCommsDatabase;
class CWlanSettingsUiImpl;

// CLASS DECLARATION

/**
* Public interface of WLAN Settings UI.
* Proxy around the real implementation in CWlanSettingsUiImpl.
*/
NONSHARABLE_CLASS( CWlanSettingsUi ): public CBase
    {

    public:     // Constructors and destructor

        /**
        * Two-phased constructor. Leaves on failure.
        * @param aEikEnv Eikon environment.
        * @return The constructed CWlanSettingsUi object.
        */
        IMPORT_C static CWlanSettingsUi* NewL( CEikonEnv& aEikEnv );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CWlanSettingsUi();

    public:     // New methods

        /**
        * Launch General WLAN Settings view.
        * @param aCommsDb Comms database.
        */
        IMPORT_C void RunSettingsL( CCommsDatabase& aCommsDb );

        /**
        * Launch WLAN EAP plug-ins view.
        */
        IMPORT_C void RunEapPluginsViewL();

    private:    // Data 

        CWlanSettingsUiImpl* iImpl; ///< Implementation. Owned.

    };

#endif 
