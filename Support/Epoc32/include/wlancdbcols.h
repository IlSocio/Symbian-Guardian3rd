/*
* ============================================================================
*  Name     : WlanCdbCols.h 
*  Part of  : WLAN Settings UI
*
*  Description:
*      Database table and column names for WLAN related Commsdb data.   
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

#ifndef WLAN_CDB_COLS_H
#define WLAN_CDB_COLS_H

// ---------------------------------------------------------
//
// WLAN Service Table
//
// ---------------------------------------------------------

#define WLAN_SERVICE                _S("WLANServiceTable")

// WLAN Table rows
#define WLAN_SERVICE_ID             _S("ServiceID")                 // to which iap these settings belong to

// Columns for WLAN security table
#define WLAN_CONNECTION_MODE        _S("WlanConnectionMode")
#define WLAN_SSID                   _S("WlanSSID")
#define WLAN_WEP_KEY1               _S("WlanWepKey1InHex")
#define WLAN_WEP_KEY2               _S("WlanWepKey2InHex")
#define WLAN_WEP_KEY3               _S("WlanWepKey3InHex")
#define WLAN_WEP_KEY4               _S("WlanWepKey4InHex")
#define WLAN_WEP_KEY1_FORMAT        _S("WlanWepKey1Format")
#define WLAN_WEP_KEY2_FORMAT        _S("WlanWepKey2Format")
#define WLAN_WEP_KEY3_FORMAT        _S("WlanWepKey3Format")
#define WLAN_WEP_KEY4_FORMAT        _S("WlanWepKey4Format")
#define WLAN_WEP_INDEX              _S("WlanWepKeyIndex")        

#define WLAN_SECURITY_MODE          _S("WlanSecurityMode")          // Encryption type
#define WLAN_AUTHENTICATION_MODE    _S("WlanAuthenticationMode")    // authentication type, none, wep, wpa, wpapresharedkey

#define WLAN_ENABLE_WPA_PSK         _S("UseWpaPreSharedKey")
#define WLAN_WPA_PRE_SHARED_KEY     _S("WlanWpaPreSharedKey")       // Shared key
#define WLAN_WPA_KEY_LENGTH         _S("WlanWpaKeyLength")          // Key length
#define WLAN_EAPS                   _S("WlanEapList")
#define WLAN_SCAN_SSID              _S("WlanScanSSID")
#define WLAN_CHANNEL_ID             _S("WlanChannelId")
#define WLAN_USED_SSID              _S("WlanUsedSSID")

#define KWlanWpaPskLength           64

#define WLAN_WEP_NOT_IN_USE         -1


// ---------------------------------------------------------
//
// WLAN Device Settings
//
// ---------------------------------------------------------
// Ids for Wlan settings type.
#define KWlanDefaultSettings                    0
#define KWlanUserSettings                       1

#define WLAN_DEVICE_SETTINGS                    _S("WLANDeviceTable")
#define WLAN_TABLE_VERSION                      _S("Version")

#define WLAN_DEVICE_SETTINGS_TYPE               _S("WlanDeviceSettingsType")

#define WLAN_BG_SCAN_INTERVAL                   _S("WlanBgScanInterval")

#define WLAN_USE_DEFAULT_SETTINGS               _S("WlanUseDefaultSettings")
#define WLAN_LONG_RETRY                         _S("WlanLongRetry")
#define WLAN_SHORT_RETRY                        _S("WlanShortRetry")
#define WLAN_RTS_THRESHOLD                      _S("WlanRTS")
#define WLAN_TX_POWER_LEVEL                     _S("WlanTxPowerLevel")
#define WLAN_ALLOW_RADIO_MEASUREMENTS           _S("AllowRadioMeasurements")
#define WLAN_POWER_MODE                         _S("WlanPowerMode")



// ---------------------------------------------------------
//
// WLAN Secondary SSID table
//
// ---------------------------------------------------------
// table name
#define WLAN_SECONDARY_SSID                     _S("SecondarySSID")
// table fields
#define WLAN_SEC_SSID_SERVICE_ID                _S("ServiceId")
#define WLAN_SEC_SSID_NAME                      _S("SecSSIDName")
#define WLAN_SEC_SSID_SCANNED_SSID              _S("ScannedSSID")
#define WLAN_SEC_SSID_USED_SSID                 _S("UsedSSID")
#define WLAN_SEC_SSID_ID                        _S("SecSSIDID")

// ---------------------------------------------------------
//
// Destination Network table
//
// ---------------------------------------------------------
// table name
#define DEST_NETWORK                            _S("DestinationNetwork")
// table fields
#define DEST_NW_SHOW_ROAMING                    _S("ShowRoaming")
#define DEST_NW_ACCESS_NWID                     _S("AccessNWID")



#endif 
