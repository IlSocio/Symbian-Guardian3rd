# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Reg\\GuardGUI_200107AF_loc.rss"

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\AppInfo.rh" 1
// APPINFO.RH
//
// Copyright (c) Symbian Software Ltd 2004-2005. All rights reserved.
//



//
// contains definitions for the Application Information resource files

/**
@publishedAll
@released
*/


//////////////////////////////////////////////////////////////////
// DEFINITIONS FOR THE NON-LOCALISABLE REGISTRATION RESOURCE FILE
//////////////////////////////////////////////////////////////////

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/
// constants for capability.hidden



/**
@publishedAll
@released
*/
// constants for capability.newfile



/**
@publishedAll
@released
*/
// constants for capability.embeddability






/**
@publishedAll
@released
*/
// constants for capability.launch



/**
@publishedAll
@released
*/
// bit flags for capability.attributes




/**
@publishedAll
@released
*/
// application group name



/**
@publishedAll
@released
*/
STRUCT APP_REGISTRATION_INFO
	{
	LONG reserved_long = 0; // reserved for future use, do not use
	LLINK reserved_llink = 0; // reserved for future use, do not use
	//
	LTEXT app_file(256 ) = ""; // name of application binary file (not including extension) - mandatory
	LONG attributes = 0;
	//
	LTEXT localisable_resource_file(256 ) = ""; // path (not including drive) and name of localisable resource file
	LONG localisable_resource_id = 1;
	//
	BYTE hidden = 0 ;
	BYTE embeddability = 0 ;
	BYTE newfile = 0 ;
	BYTE launch = 0 ;
	LTEXT group_name(16 ) = "";
	//
	BYTE default_screen_number = 0;
	//
	LEN WORD STRUCT datatype_list[]; // DATATYPE
	//
	LEN WORD STRUCT file_ownership_list[]; // FILE_OWNERSHIP_INFO
	//
	LEN WORD STRUCT service_list[]; // SERVICE_INFO
	//
	LLINK opaque_data = 0;	// use for opaque data to send to non-native application launchers i.e. MIDlet id
	}


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/
enum
	{
	EDataTypePrioritySystem = 0xFFF9,
	EDataTypePriorityHigh = 10000,
	EDataTypePriorityNormal = 0,
	EDataTypePriorityLow = -10000,
	EDataTypePriorityLastResort = -20000
	};

/**
@publishedAll
@released
*/
STRUCT DATATYPE
	{
	LONG priority;
	LTEXT8 type(256 );
	}

/**
@publishedAll
@released
*/
STRUCT FILE_OWNERSHIP_INFO
	{
	LTEXT file_name(256 );
	}

/**
@publishedAll
@released
*/
STRUCT SERVICE_INFO
	{
	LONG uid = 0;
	LEN WORD STRUCT datatype_list[];
	LLINK opaque_data = 0;
	}


/////////////////////////////////////////////////
// DEFINITIONS FOR THE LOCALISABLE RESOURCE FILE
/////////////////////////////////////////////////

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/
STRUCT LOCALISABLE_APP_INFO
	{
	LONG reserved_long = 0; // reserved for future use, do not use
	LLINK reserved_llink = 0; // reserved for future use, do not use
	//
	LTEXT short_caption(256 ) = "";
	STRUCT caption_and_icon; // CAPTION_AND_ICON_INFO
	//
	LEN WORD STRUCT view_list[]; // VIEW_DATA
	//
	LTEXT group_name(16 ) = "";
	}

/**
@publishedAll
@released
*/
STRUCT CAPTION_AND_ICON_INFO
	{
	LONG reserved_long = 0; // reserved for future use, do not use
	LLINK reserved_llink = 0; // reserved for future use, do not use
	//
	LTEXT caption(256 ) = "";
	//
	WORD number_of_icons = 0; // each icon must be a bitmap/mask pair
	LTEXT icon_file(256 ) = "";
	}

/**
@publishedAll
@released
*/
STRUCT VIEW_DATA
	{
	LONG reserved_long = 0; // reserved for future use, do not use
	LLINK reserved_llink = 0; // reserved for future use, do not use
	//
	LONG uid = 0;
	//
	LONG screen_mode = 0;
	//
	STRUCT caption_and_icon; // CAPTION_AND_ICON_INFO
	}



# 2 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Reg\\GuardGUI_200107AF_loc.rss" 2


// This file localise the applications icons and caption
RESOURCE LOCALISABLE_APP_INFO
	{
	caption_and_icon =
		{
		CAPTION_AND_ICON_INFO
			{
			// The caption text is defined in the rls file
			caption = "Guardian";
			// Icons are used to represent applications in the 
			// application launcher and application title bar.
			// The number_of_icons value identifies how many icons 
			// that exist in the icon_file.
			number_of_icons = 3;
			// Using the application icons.
			icon_file = "\\Resource\\Apps\\GuardGUI_200107AF.mbm";
			}
		};
	}
