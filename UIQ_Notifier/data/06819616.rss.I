# 1 "c:\\online\\Notifier\\data\\06819616.rss"
/*
============================================================================
 Name        : 0a6afd49.rss
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Resource for the ECom plugin on S60 3rd Ed.
============================================================================
*/

# 1 "C:\\Symbian\\9.1\\S60_3rd_MR\\\\epoc32\\include\\ecom\\RegistryInfo.rh" 1
// RegistryInfo.rh
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//



// SYMBIAN_SECURE_ECOM



STRUCT IMPLEMENTATION_INFO
	{
	LONG	implementation_uid;
	BYTE	version_no;
	LTEXT	display_name;
	LTEXT8	default_data;
	LTEXT8	opaque_data;
	}

STRUCT BINARY_IMPLEMENTATION_INFO
	{
	LONG	implementation_uid;
	BYTE	version_no;
	LTEXT	display_name;
	LEN BYTE BYTE	default_data[];
	LEN BYTE BYTE	opaque_data[];
	}

STRUCT INTERFACE_INFO
	{
	LONG	interface_uid;
	STRUCT	implementations[];
	}

STRUCT REGISTRY_INFO
	{
	LONG	dll_uid;
	STRUCT	interfaces[];
	}

# 11 "c:\\online\\Notifier\\data\\06819616.rss" 2


// Declares info for one implementation
RESOURCE REGISTRY_INFO theInfo
	{
	// UID for the DLL which implements interface
	dll_uid = 0x0a6afd49;
	// Declare array of interface info
	interfaces = 
		{
		INTERFACE_INFO
			{
			// UID of interface that is implemented
			interface_uid = 0x0f8984e8;
			implementations = 
				{
				// Info for CSampleImpl plugin.
				IMPLEMENTATION_INFO
					{
					implementation_uid = 0x06819616;
					version_no = 1;
					display_name = "CSampleImpl";
					default_data = "";
					opaque_data = "";
					}
				};
			}
		};
	}

