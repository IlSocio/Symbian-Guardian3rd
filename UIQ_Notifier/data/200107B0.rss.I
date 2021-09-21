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

# 1 "C:\\online\\Guardian3rd\\S60_GuardGUI\\data\\strings.loc" 1
CHARACTER_SET UTF8

// Localisation

				// English

# 1 "C:\\online\\Guardian3rd\\S60_GuardGUI\\data\\strings.en.l01" 1
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

//d:Caption string for app.
rls_string qtn_app_caption_string "Guardian"
rls_string qtn_app_short_caption_string "Guardian"


rls_string qtn_appl_help "Help"
rls_string qtn_appl_about "About"

rls_string qtn_appl_exit "Exit"

rls_string qtn_about_dialog_title "About"

//d:About dialog text
rls_string qtn_about_dialog_text "Guardian Version 1.0.0\n\nAuthor: Marco Bellino\n\nSupport: your support email here\n\nAll Rights Reserved"

//d:Privacy Statement file name
rls_string qtn_privacy_statement_filename "PrivacyStatement.txt"

//d:Privacy Statement dialog header
rls_string qtn_privacy_statement_header "Privacy Statement"
// End of File


// Comuni
rls_string txt_register 	"Registration"
rls_string txt_credits 		"Credits"
rls_string txt_exit 		"Exit"

// Vista About
rls_string txt_about 		"About"
rls_string txt_privacy 		"Privacy"
rls_string txt_imei_code 	"IMEI:"
rls_string txt_reg_code 	"Registration Code:"

// Vista Settings
rls_string txt_settings 		"Settings"

rls_string txt_phone  		"Recipient:"
rls_string txt_sms   		"SMS Text:"
rls_string txt_background 	"Execute SMS Commands:"
rls_string txt_pass   		"Password:"

rls_string txt_always   		"Always"
rls_string txt_sim_change  		"On SIM Change"
rls_string txt_warning_option	"This Setting is not recommended, Continue?"

rls_string txt_status 		"Status:"
rls_string txt_yes	   		"Enabled"
rls_string txt_no	   		"Disabled"


// Messaggio di popup settings
rls_string txt_change 		"Change"

// Vista SimList
rls_string txt_sim_list 		"Authorized Sim"
rls_string txt_sim 				"Sim Name:"
rls_string txt_rename_sim 		"Rename"
rls_string txt_remove_sim 		"Remove"
rls_string txt_add_sim 			"Add"


// Vista Protection
rls_string txt_protected_apps	"Protected Applications"
rls_string txt_large_icons		"Large Icons"
rls_string txt_small_icons		"Small Icons"
rls_string txt_guardian_pass	"Guardian Password:"


rls_string txt_sim_added	   	"This SIM has been Registered using name: "
rls_string txt_confirm_exit		"Exit Guardian?"

rls_string txt_warning_sms		"Warning Sim Changed!"

// ERRORI
rls_string txt_ok_code			"Thank You!"
rls_string txt_err_code			"Wrong Code!"
rls_string txt_err_bad_pass		"Wrong Password"
rls_string txt_err_imei			"Errore Lettura IMEI"
rls_string txt_err_imsi			"Errore Lettura IMSI"
rls_string txt_err_diff_imei	"IMEI differente"
rls_string txt_err_no_number	"Recipient not set"
rls_string txt_err_no_pass		"Password not set"
rls_string txt_err_short_pass	"Password Short"
rls_string txt_err_sim0			"Can't Remove SIM, SIM in use"
# 7 "C:\\online\\Guardian3rd\\S60_GuardGUI\\data\\strings.loc" 2




// French 





// German





				// Spanish - ES





				// Italian





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
    					display_name = "DialogPIN0x200107B0";	// 0x2000013C
    					default_data = "0x200107B1";			// 0x10305D66
    					opaque_data = "";
    				}
    			};
    		}
    	};
}
