# 1 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\200107B0.rss"
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

# 1 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\200107B0.rss" 2

# 1 "C:\\Symbian\\9.1\\S60_3rd_MR\\\\epoc32\\include\\uikon.hrh" 1
// UIKON.HRH
//
// Copyright (c) Symbian Software Ltd 1997 - 2005. All rights reserved.
//




/** UID for dynamically-loaded Uikon library.
@publishedAll 
@released 
*/



/** Application resource file standard offsets.
@publishedAll 
@released 
*/
enum TEikAppResourceFileStandardOffset
	{
	/** Offset of RSS_SIGNATURE resource.
	*/
	ESignatureResourceOffset=1,
	/** Offset of NAME resource.
	*/
	EDefaultNameResourceOffset,
	/** Offset of EIK_APP_INFO resource.
	*/
	EAppInfoResourceOffset
	};


/** Default RSS_SIGNATURE signature field value.
@publishedAll 
@released 
*/



/** ID of "Cancel" command button.
@publishedAll 
@released 
*/


// standard commands

/** "Canceled" command ID
@publishedAll 
@released 
*/


/** "Exit" command ID.
@publishedAll 
@released 
*/



// EIKSPANE.HRH
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//

// Status pane server, pane declaration flags

/** STATUS_PANE flags resource flag: the pane is owned by the UI server.
@publishedAll 
@released 
*/


/** STATUS_PANE flags resource flag: the pane is owned by the client application.
@publishedAll 
@released 
*/



// Status pane server, top level layout flags

/** STATUS_PANE_LAYOUT position resource flag: lay out panes from the top of the status pane area.
@publishedAll 
@released 
*/


/** STATUS_PANE flags resource flag: lay out panes from the bottom of the status pane area.
@publishedAll 
@released 
*/


/** STATUS_PANE flags resource flag: lay out panes from the left of the status pane area.
@publishedAll 
@released 
*/


/** STATUS_PANE flags resource flag: lay out panes from the right of the status pane area.
@publishedAll 
@released 
*/



/** STATUS_PANE_LAYOUT position resource flag: lay out panes horizontally.
@publishedAll 
@released 
*/


/** STATUS_PANE_LAYOUT position resource flag: lay out panes vertically.
@publishedAll 
@released 
*/



// Status pane server, pane layout flags
/** STATUS_PANE flags resource flag: status pane is stretched to fill the available space.
@publishedAll 
@released 
*/



// Status pane app constants
/** STATUS_PANE_APP_MODEL layout default value: use default layout.
@publishedAll 
@released 
*/


// error resolver
/** SINGLE_ERROR flags resource flag: this error should be dealt with at the system level and indicates and unrecoverable error (which will result in a panic) if it reaches the UI.
@publishedAll 
@released 
*/


/** SINGLE_ERROR flags resource flag: this error should not be displayed.
@publishedAll 
@released 
*/


/** SINGLE_ERROR flags resource flag: this error is used for filling in empty slots in error ranges.
@publishedAll 
@released 
*/
// used for filling in empty slots in error ranges


// EIKDEF.HRH
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//








/** Shell application bitmap file.
@publishedAll 
@released 
*/


/** CP1252 ellipsis character value.
@publishedAll 
@released 
*/
// cp1252=133

/** CP1252 left single quote character value.
@publishedAll 
@released 
*/
// cp1252=145

/** CP1252 right single quote character value.
@publishedAll 
@released 
*/
// cp1252=146

/** CP1252 left double quote character value.
@publishedAll 
@released 
*/
// cp1252=147

/** CP1252 right double quote character value.
@publishedAll 
@released 
*/
// cp1252=148

/** CP1252 copyright character value.
@publishedAll 
@released 
*/


/** CP1252 soft hyphen character value.
@publishedAll 
@released 
*/


/** CP1252 hyphen character value.
@publishedAll 
@released 
*/


/** UID of Uikon plugin interface notifiers.
@internalComponent
*/



# 2 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\200107B0.rss" 2

# 1 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\strings.loc" 1
CHARACTER_SET UTF8

// Localisation

				// English





// French 





// German





				// Spanish - ES





				// Italian

# 1 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\strings.it.l05" 1
/*
============================================================================
 Name        : GuardGUI.rls
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : String localization file
============================================================================
*/

//  LOCALISATION STRINGS

rls_string txt_guardian_pass	"Codice Segreto:"
rls_string txt_err_bad_pass		"Codice Segreto Errato"

# 31 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\strings.loc" 2




// Swedish





// Finnish





// American





// Portuguese





				// Turkish





				// Russian - RU





				// Dutch - NL





				// Czech - CS





				// Slovenian - SL





				// Chinese - TC HK ZH





				// Arabic - AR





// Tagalog





// Bulgarian





// Croatian





				// Farsi





// Greek





// Hebrew





// Khmer





// Malese





// BrazilianPortuguese





// Serbian





				// CyprusTurkish





				// ELangUkrainian




# 3 "C:\\online\\Guardian3rd\\S60_Notifier\\data\\200107B0.rss" 2



RESOURCE REGISTRY_INFO theInfo
{
	dll_uid = 0x200107B0;
   	interfaces =
	{
    		INTERFACE_INFO
    		{
    			interface_uid = 0x101fdfae ; // Resolver
    			implementations =
    			{
				IMPLEMENTATION_INFO
    				{
    					implementation_uid = 0x200107B1;		// 0x10305D66
					version_no = 1;
    					display_name = "DialogPIN_200107B0";	// 0x2000013C
    					default_data = "0x200107B1";			// 0x10305D66
    					opaque_data = "";
    				}
    			};
    		}
    	};
}
