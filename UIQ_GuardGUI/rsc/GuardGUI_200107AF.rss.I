# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss"

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh" 1
// UIKON.RH
//
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.
//





# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\BADEF.RH" 1
// BADEF.RH
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//




STRUCT BA_RSS_SIGNATURE
    {
    LONG signature=0; // this value must be changed if the resource file is loaded by an environment
    SRLINK self;
    }

STRUCT TBUF
    {
    BUF buf; // non-zero terminated text string
    }

STRUCT LBUF
    {
    LTEXT txt; // leading-byte counted text string
    }

STRUCT ARRAY
    {
    STRUCT items[];
    }

STRUCT UID_NAME_PAIR
	{
	LONG uid;
	STRUCT name; // an LBUF
	}



# 10 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh" 2




# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\BAERRRSVR.RH" 1
// BAERRRSVR.RH
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//





// Error Resolver

STRUCT ERROR_SET
	{
	STRUCT errorarrays[];
	}

STRUCT ERROR_ARRAY
	{
	LONG startError;
	LLINK errors;
	}

STRUCT SINGLE_ERROR
	{
	BYTE flags=0;
	LLINK text=0;
	}


# 14 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh" 2




# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh" 1
// uikon.hrh
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.


/** @internalTechnology @released */



# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikcolor.hrh" 1
// EIKCOLOR.HRH
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//

/** RGB colour constant: black.
@publishedAll 
@released 
*/


/** RGB colour constant: dark gray.
@publishedAll 
@released 
*/


/** RGB colour constant: dark red.
@publishedAll 
@released 
*/


/** RGB colour constant: dark green.
@publishedAll 
@released 
*/


/** RGB colour constant: dark yellow.
@publishedAll 
@released 
*/


/** RGB colour constant: dark blue.
@publishedAll 
@released 
*/


/** RGB colour constant: dark magenta.
@publishedAll 
@released 
*/


/** RGB colour constant: dark cyan.
@publishedAll 
@released 
*/


/** RGB colour constant: red.
@publishedAll 
@released 
*/


/** RGB colour constant: green.
@publishedAll 
@released 
*/


/** RGB colour constant: yellow.
@publishedAll 
@released 
*/


/** RGB colour constant: blue.
@publishedAll 
@released 
*/


/** RGB colour constant: magenta.
@publishedAll 
@released 
*/


/** RGB colour constant: cyan.
@publishedAll 
@released 
*/


/** RGB colour constant: gray.
@publishedAll 
@released 
*/


/** RGB colour constant: dithered light gray.
@publishedAll 
@released 
*/


/** RGB colour constant: 1-in-4 dithered gray.
@publishedAll 
@released 
*/


/** RGB colour constant: white.
@publishedAll 
@released 
*/



/** RGB colour constant: Symbian green.
@publishedAll 
@released 
*/


/** RGB colour constant: Symbian light green.
@publishedAll 
@released 
*/


/** RGB colour constant: Symbian blue.
@publishedAll 
@released 
*/


/** RGB colour constant: Symbian dark blue.
@publishedAll 
@released 
*/


/** RGB colour constant: Symbian orange.
@publishedAll 
@released 
*/



/** Logical colour value for use in resources: The colour of a window's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in a window. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the background contents of a control. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text inside a control. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The background colour of a control's border. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in a control's border. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a control's background when highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a control when highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a control's background when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a control when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a control's background when dimmed and highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a control when dimmed and highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a dialog's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text inside a dialog. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: A dialog title's background colour. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: A dialog title's background colour when pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The text colour in a dialog's title. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The text colour in a dialog's title when pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the menubar's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in the menubar. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the menubar title's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in the menubar title. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the menupane's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in the menu pane. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the menu pane background when highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in the menu pane when highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the menu pane background when dimmed and highlighted. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in the menu pane when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of text in the menu pane when dimmed and highlighted for selection. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button background, when the button is in the unset state. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button background when the button is in the set state. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button background when the button is in the set state and is pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button background when the button is in the unset state and is pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button text. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button text when the button is pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the button text when the button is dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the message window foreground. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the message window background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the scroll bar border. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the scroll bar shaft background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the scroll bar shaft background when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the scroll bar shaft background when pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the background for scroll bars with no thumb and no shaft. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of scroll bar buttons. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of scroll bar buttons when pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of scroll bar buttons when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a scroll bar thumb's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a scroll bar thumb's background when pressed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a scroll bar thumb's background when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a scroll bar thumb's edge. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a toolbar's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a toolbar. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of a status pane's background. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a status pane. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a label. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of emphasised text in a label. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the text in a label when dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the label background when highlighted and dimmed. 
@publishedAll 
@released 
*/


/** Logical colour value for use in resources: The colour of the label background when highlighted. 
@publishedAll 
@released 
*/

# 9 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh" 2



// EIKBTGPC.HRH

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// EIKBUTB.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/
// EIKCHLST.HRH
// EIgnoreNextPointerUp=0x800 it is a private value

// EIKEDWIN.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
Disables automatic selection of the entire text when the Edwin
gets focus.
@publishedAll
@released
@see EEikEdwinEnableAutoSelection
*/


/**
Automatically place the cursor at the end of the text when the control is
activated.
@publishedAll
@released
@see EEikEdwinDisableAutoCurEnd
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
Disables the cursor wrapping in edwin. Cursor wrapping is that if the cursor
is at the bottom or top of the document, it jumps to the other end of the document
when pressing the navigation keys.
@see EEikEdwinNoCursorWrapUp
@publishedAll
@released
*/


/**
Enables automatic selection of the entire text when the Edwin
gets focus.
@see EEikEdwinNoAutoSelection
@publishedAll
@released
@since "UIQ 3.0"
*/


/**
Disable that the cursor is moved to the end of the text when the control is
activated.
@see EEikEdwinJustAutoCurEnd
@publishedAll
@released
@since "UIQ 3.0"
*/


/**
Disables the cursor wrapping from the top to the bottom of the document.
@see EEikEdwinNoCursorWrap
@publishedAll
@released
@since "UIQ 3.0"
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// EIKLABEL.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/
// will switch oof the auto wrapping
/**
@publishedAll
@released
*/
// used together with the above flag to switch on the auto wrapping

/**
@publishedAll
@released
*/
enum EEikLabelStandardFont
	{
	EEikLabelFontNormal,
	EEikLabelFontLegend,
	EEikLabelFontAnnotation
	};

// EIKLBBUT.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// EIKLBX.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// EIKMENU.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// more flags to determine the type of scroll bar to be used
// deprecated in Uikon 1.2
/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// // not available before Release 6.2
/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/




// remaining flags only used internally
/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

//The following value is reserved			0x020000
/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

// EIKTBAR.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Toolbar flags

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// Toolbar control flags

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// standard toolbat sizes

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// EIKCMBUT.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//to be removed ...
//#define EEikCmdButNormal				0x0000
//#define EEikCmdButInverter				0x1000
//#define EEikCmdButChangeWithImage		0x2000
//#define EEikCmdButChangeWithoutImage	0x3000

// EIKDEF.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//








/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/
// cp1252=133
/**
@publishedAll
@released
*/
// cp1252=145
/**
@publishedAll
@released
*/
// cp1252=146
/**
@publishedAll
@released
*/
// cp1252=147
/**
@publishedAll
@released
*/
// cp1252=148
/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/
enum TEikAppResourceFileStandardOffset
	{
	ESignatureResourceOffset=1,
	EDefaultNameResourceOffset,
	EAppInfoResourceOffset
	};

// Added by Bill
// Built-in app UIDs

# 763 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh"


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/




# 821 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh"


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/




/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// Added by Gilad Tiefenbrun 25/2/99 to allow dynamic DLL loading
/**
@publishedAll
@released
*/


// EIKCMDS.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Standard command ids
// Reserved number series for command-ids:
// 0xFFFF FFF0 - 0x0000 03FF uikon.hrh from (-16 to +1023 decimal)
// 0x0400 - 0x07FF eikon.hrh
// 0x0800 - 0x0BFF qikon.hrh
// 0x0C00 - 0x0C3F embedded links
// 0x0C40 - 0x0CA4 reserved for licensees
// 0x0CA5 - 0x0FFF reserved for future use
// 0x1000 - KCategoryMenuIdOffset reserved for Applications

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


// EIKCTRLS.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/
enum TEikStockControls
	{
	EEikCtCommandButton,
	EEikCtLabeledButton,
	EEikCtEdwin,
	EEikCtRichTextEditor,
	EEikCtSecretEd,
	EEikCtCheckBox,
	EEikCtChoiceList,
	EEikCtOptionButton,
	EEikCtHorOptionButList,
	EEikCtFileNameSel,		// deprecated
	EEikCtFileNameEd,			// deprecated
	EEikCtFolderNameSel,		// deprecated
	EEikCtFolderNameEd,			// deprecated
	EEikCtDriveNameSel,			// deprecated
	EEikCtListBox,
	EEikCtImage,
	EEikCtImageArray,
	EEikCtLabel,
	EEikCtComboBox,
	EEikCtProgInfo,
	EEikCtGlobalTextEditor,
	EEikCtClock,
	EEikCtMenuButton,
	EEikCtDirContentsListBox,	// deprecated
	EEikCtDirTreeListBox,		// deprecated
	EEikCtCalendar,
	EEikCtSpacer,
	EEikCtColListBox,
	EEikCtTextButton,
	EEikCtBitmapButton,
	EEikCtDialogToolBar,
	EEikCtFileBrowser,			// deprecated
	EEikCtUnifiedFileSel,		// deprecated
	EEikCtTwoPictureCommandButton,
	EEikCtScrollBar,
	EEikCtArrowHeadScrollBar,
	EEikCtLabeledCheckBox
	};

// not available before Release 6.1
/**
@publishedAll
@released
*/
enum TEikStockButtonGroupControls
	{
	EEikBgToolBar,
	EEikBgButtonPanel // deprecated
	};

// EIKPRIV.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/
// > EEikBidDeferValidateFocusControl
/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//preview dialog

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


// setup menubutton

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//printer setup

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//serial port setup

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//printrange setup

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//print progress

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//previewrange setup

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


//page setup

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/**
@publishedAll
@released
*/

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// EIKDIALG.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// @see also EQikDlg flags in eikon.hrh

/** @internalTechnology @deprecated */

/** @internalTechnology @deprecated */

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

// defines continue as EQikDlg flags in eikon.hrh

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 


/** @internalTechnology @deprecated */ 


/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 


/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 

/** @internalTechnology @deprecated */ 


/** @internalTechnology @deprecated */
//EEikLabeledButtonShowHotKey
/** @internalTechnology @deprecated */ 
//EEikLabeledButtonPlainHotKey
/** @internalTechnology @deprecated */ 
//EEikLabeledButtonIsDefault

// EIKSPANE.HRH
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Status pane server, pane declaration flags
/** @publishedAll @released */

/** @publishedAll @released */



// Status pane server, top level layout flags
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */



// Status pane server, pane layout flags
/** @publishedAll @released */



// Status pane app constants
/** @publishedAll @released */


// error resolver
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */
// used for filling in empty slots in error ranges

/** @publishedAll @released */


/**
The disable_system_screen_furniture flag determines which command operators should be active.
If specific command operators are wanted, they can be OR-ed together
(specifiying individual command operators will assume no others are wanted).
NOTE: Setting the flags for individual command operators can not be used in conjunction with the AllOn or AllOff values!
@publishedAll @released
*/

/**
The disable_system_screen_furniture flag determines which command operators should be active.
If specific command operators are wanted, they can be OR-ed together
(specifiying individual command operators will assume no others are wanted).
NOTE: Setting the flags for individual command operators can not be used in conjunction with the AllOn or AllOff values!
@publishedAll @released
*/

/**
The disable_system_screen_furniture flag determines which command operators should be active.
If specific command operators are wanted, they can be OR-ed together
(specifiying individual command operators will assume no others are wanted).
NOTE: Setting the flags for individual command operators can not be used in conjunction with the AllOn or AllOff values!
@publishedAll @released
*/

/**
The disable_system_screen_furniture flag determines which command operators should be active.
If specific command operators are wanted, they can be OR-ed together
(specifiying individual command operators will assume no others are wanted).
NOTE: Setting the flags for individual command operators can not be used in conjunction with the AllOn or AllOff values!
@publishedAll @released
*/




# 18 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh" 2



# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.mbg" 1
// qikon.mbg
// Generated by BitmapCompiler
// Copyright (c) 1998-2005 Symbian Software Ltd. All rights reserved.
//

enum TMbmQikon
	{
	EMbmQikonPlaybutton,
	EMbmQikonStopbutton,
	EMbmQikonBrokenimage,
	EMbmQikonUnrecognisedfile_14hx15w,
	EMbmQikonUnrecognisedfile_10hx12w,
	EMbmQikonUnrecognisedfile_14hx15w_mask,
	EMbmQikonUnrecognisedfile_10hx12w_mask,
	EMbmQikonPlaceholder,
	EMbmQikonPlaceholdermask,
	EMbmQikonBrokenimagemask,
	EMbmQikonPanarrowup,
	EMbmQikonPanarrowupmask,
	EMbmQikonPanarrowdown,
	EMbmQikonPanarrowdownmask,
	EMbmQikonPanarrowleft,
	EMbmQikonPanarrowleftmask,
	EMbmQikonPanarrowright,
	EMbmQikonPanarrowrightmask,
	EMbmQikonPanarrowupdim,
	EMbmQikonPanarrowupdimmask,
	EMbmQikonPanarrowdowndim,
	EMbmQikonPanarrowdowndimmask,
	EMbmQikonPanarrowleftdim,
	EMbmQikonPanarrowleftdimmask,
	EMbmQikonPanarrowrightdim,
	EMbmQikonPanarrowrightdimmask,
	EMbmQikonCamera,
	EMbmQikonCameramask,
	EMbmQikonContrastindicator,
	EMbmQikonContrastindicatormask,
	EMbmQikonBrightnessindicator,
	EMbmQikonBrightnessindicatormask,
	EMbmQikonZoomindicator,
	EMbmQikonZoomindicatormask,
	EMbmQikonBrokenimage40x40,
	EMbmQikonBrokenimagemask40x40,
	EMbmQikonMissingimage,
	EMbmQikonMissingimagemask,
	EMbmQikonMissingimage40x40,
	EMbmQikonMissingimagemask40x40,
	EMbmQikonFilehandlinglarge,
	EMbmQikonFilehandlinglargemask,
	EMbmQikonPlaybuttonmask,
	EMbmQikonStopbuttonmask,
	EMbmQikonPlaceholder40x40,
	EMbmQikonPlaceholdermask40x40
	};
# 21 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh" 2


/**
A utility struct that provides a link to another resource.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT RESOURCE_LINK
	{
	/**
	 Link to another resource.
	*/
	LLINK id;
	}

/**
A utility struct that provides array of button groups and buttons.

@publishedAll
@deprecated
@since Quartz 6.0
*/
STRUCT BTG_RESOURCE_COLLECTION
    {
	/**
	 A variable-length array of button groups.
	*/
    STRUCT btg_sets[];

	/**
 	 A variable-length array of buttons.
 	 */
    STRUCT btg_buttons[];
    }

// EIKEDWIN.RH
//
//

/**
This struct specifies a Plain text editor control.
Resources with this structure are read by CEikEdwin::ConstructFromResourceL(), 
and describes the CEikEdwin to be constructed.

@publishedAll
@released
@see CEikEdwin
@since Quartz 6.0
*/
STRUCT EDWIN
    {
    /**
     Bitmask of flags for the edwin, used to customize the control, see in file uikon.hrh.
     @see EEikEdwinKeepDocument
	*/
    LONG flags=0;

    /**
     Sets the display width of the editor expressed in number of characters. 
	 This limits how much of the text content the editor displays.
	 If the <code>EEikEdwinWidthInPixels</code> flag is set, the width is specified in pixels.
     @see EEikEdwinWidthInPixels
	*/
    WORD width=0;

    /**
     Sets the maximum number of lines that the editor will display.
	*/
    WORD lines=1;

    /**
     Maximum length of the editable text in characters.
	*/
    WORD maxlength=0;
    }

//#include <eikedwin.hrh>

// EIKIMAGE.RH
//
//

//#include <eiklabel.hrh>
/**
This struct specifies an Image control.
Resources with this structure are read by CEikImage::ConstructFromResourceL(), 
and describe the CEikImage to be constructed.

This resource is deprecated, use QIK_IMAGE instead, see Qikon.rh

@publishedAll
@deprecated
@see CEikImage
@see QIK_IMAGE
@since Quartz 6.0
*/
STRUCT IMAGE
	{
    /**
	 * For internal use only, application developers must not change this.
	*/
	BYTE version = 0;

    /**
     How the image is horiozontally aligned.
     @see EEikLabelAlignHCenter
	*/
	WORD horiz_align= 0x01 ;

    /**
     How the image is vertically aligned.
     @see EEikLabelAlignVTop
	*/
	WORD vert_align= 0x00 ;

    /**
     The .mbm file that holds the bitmap and its mask.
	*/
	LTEXT bmpfile="z:\\Resource\\Apps\\qikon.mbm";

    /**
     ID of the image bitmap in the .mbm file.
	*/
	WORD bmpid=EMbmQikonBrokenimage; //Broken image

    /**
     ID of the image bitmap mask in the .mbm file.
	*/
	WORD bmpmask=0xffff;

    /**
     Not used.
	*/
	LLINK extension=0;
	}

// EIKLABEL.RH
//
//

//#include <eiklabel.hrh>
/**
Resources with this structure are read by CEikLabel::ConstructFromResourceL(), and describe the CEikLabel to be constructed.

@publishedAll
@released
@see CEikLabel
@since Quartz 6.0
*/
STRUCT LABEL
    {
    /**
     Used to customize the control. These are used to set text emphasis and characteristics, such as underlining, and strikethrough.
	 The flags available are defined in <file>Uikon.hrh</file>.
     @see EikLabelUnderline
    */
	WORD flags = 0;

    /**
     Specifies the horisontal alignment of the text.
     @see EEikLabelAlignHCenter
    */
	WORD horiz_align= 0x01 ;

    /**
     Specifies the vertical alignment of the text.
     @see EEikLabelAlignVTop
    */
	WORD vert_align= 0x00 ;

    /**
     Font for the label.
	 IDs for font types are defined in EEikLabelStandardFont in uikon.hrh.
     @see EEikLabelStandardFont
	 @see EEikLabelFontNormal
    */
	WORD standard_font=EEikLabelFontNormal;

    /**
     Specifies the maximum length of the text to display on the Label. Default is unlimited.
	 This means that the Label's text buffer will hold whatever length.
    */
	WORD reserve_length=0;

    /**
     Specifies the label's text.
    */
    LTEXT txt;
    }

// EIKLBX.RH
//
//
/**
Resources with this structure are read by CEikTextListBox::ConstructFromResourceL(), and describe the CEikTextListBox to be constructed.

@publishedAll
@deprecated
@since Quartz 6.0
@see CEikTextListBox

*/
STRUCT LISTBOX
	{
	/**
	 * For internal use only, application developers must not change this.
 	 */
	BYTE version=0;

	/**
     Used to customize the control.
	 The flags available are defined in <file>Uikon.hrh</file>.
     @see EEikListBoxMultipleSelection
 	 */
	WORD flags = 0;

	/**
 	 Height of the list box in items.
 	 */
	WORD height = 5;		// in items

	/**
 	 Width of the list box in characters.
 	 */
	WORD width = 10;		// in chars

	/**
 	 Link to an array of list box items.
	 The expected type is a LBUF[].
 	 */
    LLINK array_id = 0;
	}

//#include <eiklbx.hrh>

// EIKMENU.RH
//
//

/**
This resource type is used for members of HOTKEYS resources.

@publishedAll
@deprecated
@since Quartz 6.0
*/
STRUCT HOTKEY
    {
	/**
 	 Command ID for the hotkey.
 	 */
    LONG command;

	/**
 	 Key code for the hotkey.
 	 */
    LONG key;
    }

/**
Resources with this structure are read by CEikHotKeyTable::ConstructFromResourceL(), and describe the CEikHotKeyTable to be constructed.

@publishedAll
@deprecated
@since Quartz 6.0
@see CEikHotKeyTable
*/
STRUCT HOTKEYS
    {
	/**
 	 Variable-length array of HOTKEY resources for hotkeys invoked using the specified key without modifiers.
 	 */
    STRUCT plain[];

	/**
 	 Variable-length array of HOTKEY resources for hotkeys invoked using the specified key with the control modifier.
 	 */
    STRUCT control[];

	/**
	Variable-length array of HOTKEY resources for hotkeys invoked using the specified key with the SHIFT-control key modifiers.
 	 */
    STRUCT shift_control[];
    }

/**
Defines the menu items that comprise a menu pane. 

MENU_PANE resources are used to form the fields of MENU_TITLE resources.

Resources with this structure are read by CEikMenuPane::ConstructFromResourceL(), and describe the CEikMenuPane to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikMenuPane
*/
STRUCT MENU_PANE
    {
	/**
	Variable-length array of MENU_ITEM resources. 	 
	@see MENU_ITEM
	*/
    STRUCT items[]; // MENU_ITEMs

	/**
 	 Unused.
 	 */
    LLINK extension=0;
    }

/**
Defines a menu item. 

MENU_ITEMs are used in the fields of a MENU_PANE resource.

Resources with this structure are read by CEikMenuPaneItem::ConstructFromResourceL(), and describe the CEikMenuPaneItem to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikMenuPaneItem
@see MENU_PANE
*/
STRUCT MENU_ITEM
    {
	/**
 	 ID of the command invoked when this menu item is activated.
 	 */
    LONG command=0;

	/**
	Link to a cascaded menu, of type MENU_PANE, activated by this menu item.
	The default is no cascaded menu.
 	@see MENU_PANE
	*/
    LLINK cascade=0;

	/**
 	 Flags that dim, separate, display symbols, etc. on menu items.
	 @see EEikMenuItemDimmed
 	 */
    LONG flags=0;

	/**
 	 The text displayed in the menu item.
 	 */
    LTEXT txt;

	/**
 	 Extra text.

	 This text appears to the right of the menu item text, in a smaller and lighter font. This field cannot be used if there is a hotkey for the menu item.
 	 */
    LTEXT extratxt="";

	/**
 	 The .mbm file that holds an icon for the menu item.
 	 */
    LTEXT bmpfile="";

	/**
 	 ID of the icon bitmap in the specified .mbm file.

	 The default is no icon.
 	 */
    WORD bmpid=0xffff;

	/**
 	 ID of the icon bitmap mask in the specified .mbm file.

	 The default is no icon mask.
 	 */
    WORD bmpmask=0xffff;

	/**
 	 Unused.
 	 */
    LLINK extension=0;
    }

/**
The top level resource for using menus: defines the menu panes that comprise a menu bar.

Resources with this structure are read by CEikMenuBar::ConstructFromResourceL(), and describe the CEikMenuBar to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikMenuBar
*/
STRUCT MENU_BAR
    {
	/**
 	 Variable length array of MENU_TITLE resources.
	 @see MENU_TITLE
 	 */
    STRUCT titles[]; // MENU_TITLEs

	/**
 	 Unused.
 	 */
	LLINK extension=0;
    }

/**
Defines an association between a menu pane and its title. 

MENU_TITLEs are used in the fields of a MENU_BAR resource struct.

@publishedAll
@released
@since Quartz 6.0
@see CEikMenuBar
@see MENU_BAR
*/
STRUCT MENU_TITLE
    {
	/**
 	 Link to a MENU_PANE resource.
 	 @see MENU_PANE
	 */
    LLINK menu_pane;

	/**
 	 Title which appears in the menu bar for this menu pane.
 	 */
    LTEXT txt;

	/**
 	 Flags for the title.
	 ETitleDimmed dims the title.
	 @see CEikMenuBarTitle::ETitleDimmed
 	 */
    LONG flags=0;

	/**
 	 The .mbm file that holds an icon for the menu title.
 	 */
	LTEXT bmpfile="";

	/**
 	 ID of the icon bitmap in the specified .mbm file.

	The default is no icon.
 	 */
    WORD bmpid=0xffff;

	/**
 	 ID of the icon bitmap mask in the specified .mbm file.

	 The default is no icon mask.
 	 */
    WORD bmpmask=0xffff;

	/**
 	 Unused.
 	 */
	LLINK extension=0;
    }

//#include <eikmenu.hrh>

// EIKMNBUT.RH
//
//

//#include <eikcmbut.hrh>
/**
A menu button.

Resources with this structure are read by CEikMenuButton::ConstructFromResourceL(), and describe the CEikMenuButton to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikMenuButton
*/
STRUCT MNBUT
    {
	/**
 	 Link to a MENU_PANE resource.
 	 */
	LLINK popout=0;

	/**
	 * For internal use only, application developers must not change this.
 	 */
	BYTE version=0;

	/**
 	 Button behaviour flags.
 	 @see CEikButtonBase::TButtonBehaviour
	  @see EEikButStaysClear
 	 */
	WORD behavior=0;

	/**
 	 Button layout flags.
 	 @see CEikCommandButtonBase::TLayout
 	 @see CEikCommandButton::TLayout
 	 */
	WORD layout=0; // ETextRightPictureLeft

	/**
 	 Bubble help text.
 	 @see CEikButtonBase::SetBubbleHelpTextL
	  */
	LTEXT helptxt="";

	/**
	 Unused.
 	 */
	LLINK extension=0;

	/**
 	 Text for the menu button.
 	 */
    LTEXT txt="";

	/**
 	 The .mbm file that holds an icon for the menu button.
 	 */
	LTEXT bmpfile="";

	/**
 	 ID of the icon bitmap in the specified .mbm file.

	The default is no icon.
 	 */
    WORD bmpid=0xffff;

	/**
 	 ID of the icon bitmap mask in the specified .mbm file.

	The default is no icon mask.
 	 */
    WORD bmpmask=0xffff;
    }

// EIKRUTIL.RH
//
//

// Removed by Bill
//#include <eikfont.rh> // for STRUCT FONT

/**
Utility struct to hold a byte value.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT NUMBER_INT8
	{
	/**
 	 A byte value.
 	 */
	BYTE value=0;
	}

/**
Utility struct to hold a word value.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT NUMBER_INT16
	{
	/**
 	 A word value.
 	 */
	WORD value=0;
	}
/**
Utility struct to hold a long value.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT NUMBER_INT32
	{
	/**
 	 A long value.
 	 */
	LONG value=0;
	}

// EIKTBAR.RH
//
//

//#include <eiktbar.hrh>

/**
@publishedAll
@deprecated
*/
STRUCT TOOLBAR
    {
	WORD length=0;
	WORD breadth= 70 ;
	BYTE lines=1;
    LONG flags=0;
    STRUCT controls[];
	LLINK extension=0;
    }

/**
@publishedAll
@deprecated
*/
STRUCT TOOLBAND
    {
	WORD length=0;
	WORD breadth= 25 ;
	BYTE lines=1;
    LONG flags= 0x01 ;
    STRUCT controls[];
	LLINK extension=0;
    }

/**
@publishedAll
@deprecated
*/
STRUCT TBAR_CTRL
	{
	WORD type;
	WORD id=0;
	WORD flags=0;
	WORD length=0;
	STRUCT control;
	}

/**
@publishedAll
@deprecated
*/
STRUCT TBAR_BUTTON
	{
	WORD type=0; // EEikCtCommandButton;
	WORD id=0;
	WORD flags=0;
	WORD length=0;
	BYTE version=0;
	WORD behavior=0;
	WORD layout=0; // ETextRightPictureLeft|EEikCmdButShareExcess
	LTEXT helptxt="";
	LLINK extension=0;
    LTEXT txt="";
	LTEXT bmpfile="";
    WORD bmpid=0xffff;
    WORD bmpmask=0xffff;
	}

/**
@publishedAll
@deprecated
*/
STRUCT TBAR_PICBUT
	{
	WORD type=EEikCtTwoPictureCommandButton;
	WORD id=0;
	WORD flags=0;
	WORD length=0;
	BYTE version=0;
	WORD behavior=0;
	WORD layout=0; // ETextRightPictureLeft|EEikCmdButShareExcess
	LTEXT helptxt="";
	LLINK extension=0;
    LTEXT txt="";
	LTEXT bmpfile="";
    WORD bmpid=0xffff;
    WORD bmpmask=0xffff;
    WORD bmpsecondid=0xffff;
    WORD bmpsecondmask=0xffff;
	}

// EIKCMBUT.RH
//
//

//#include <eikcmbut.hrh>
/**
A command button.

Resources with this structure are read by CEikCommandButton::ConstructFromResourceL(), and describe the CEikCommandButton to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikCommandButton
@see CEikCommandButtonBase
@see CEikButtonBase
*/
STRUCT CMBUT
    {
	/**
	 * For internal use only, application developers must not change this.
 	 */
	BYTE version=0;

	/**
 	 Button behaviour flags.
 	 @see TButtonBehavior
 	 */
	WORD behavior=0;

	/**
 	 Flags to define how the horizontal space is handled between the button’s text and image.
 	 @see CEikCommandButton::TLayout
 	 @see EEikCmdButTextRightPictureLeft
 	 */
	WORD layout=0; // ETextRightPictureLeft|EEikCmdButShareExcess

	/**
 	 Help text for the button.
 	 */
	LTEXT helptxt="";

	/**
 	 Unused.
 	 */
	LLINK extension=0;

	/**
 	 Specifies the button’s text label.

	 The default is none.
 	 */
	LTEXT txt="";

	/**
 	 Specifies the bitmap filename from which to read the button’s image.
 	 */
	LTEXT bmpfile="";

	/**
 	 Specifies the index of the bitmap in the bmpfile file.

	 A default value of 0xffff indicates no bitmap.
 	 */
    WORD bmpid=0xffff;

	/**
 	 Specifies the index of the bitmap mask in the file. 

	 A default value of 0xffff indicates no bitmap mask.
 	 */
    WORD bmpmask=0xffff;
    }

/**
A button that can hold two pictures in addition to label text.

Resources with this structure are read by CEikTwoPictureCommandButton::ConstructFromResourceL(), and describe the CEikTwoPictureCommandButton to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikTwoPictureCommandButton
@see CEikCommandButtonBase
@see CEikButtonBase
*/
STRUCT PICMBUT
    {
	/**
	 * For internal use only, application developers must not change this.
 	 */
	BYTE version=0;

	/**
 	 Button behaviour flags.
 	 @see TButtonBehavior
 	 */
	WORD behavior=0;

	/**
 	 Flags to define how the horizontal space is handled between the button’s text and images.
 	 @see CEikTwoPictureCommandButton::TLayout
 	 @see EEikCmdButTextRightPictureLeft
 	 */
	WORD layout=0;	// ETextRightPictureLeft|EEikCmdButShareExcess

	/**
 	 Help text for the button.
 	 */
	LTEXT helptxt="";

	/**
 	 Unused.
 	 */
	LLINK extension=0;

	/**
 	 Specifies the button’s text label.

	 The default is none.
 	 */
	LTEXT txt="";

	/**
 	 Specifies the bitmap filename from which to read the button’s image.
 	 */
	LTEXT bmpfile="";

	/**
 	 Specifies the index of the first bitmap in the bmpfile file.

	 A default value of 0xffff indicates no bitmap.
 	 */
    WORD bmpid=0xffff;

	/**
 	 Specifies the index of the first bitmap mask in the file. 

	 A default value of 0xffff indicates no bitmap mask.
 	 */
    WORD bmpmask=0xffff;

	/**
 	 Specifies the index of the second bitmap in the bmpfile file.

	 A default value of 0xffff indicates no bitmap.
 	 */
    WORD bmpsecondid=0xffff;

	/**
	 Specifies the index of the second bitmap mask in the file.

	 A default value of 0xffff indicates no bitmap mask.
 	 */
    WORD bmpsecondmask=0xffff;
    }

/**
A command button with label text, and no pictures.

Resources with this structure are read by CEikTextButton::ConstructFromResourceL(), and describe the CEikTextButton to be constructed.

@publishedAll
@released
@since Quartz 6.0
see CEikTextButton
@see CEikCommandButtonBase
*/
STRUCT TXTBUT
    {
	/**
	 * For internal use only, application developers must not change this.
 	 */
	BYTE version=0;

	/**
 	 Button behaviour flags.
 	 @see TButtonBehavior
 	 */
	WORD behavior=0;

	/**
 	 Flags to define how the horizontal space is handled between the button’s text labels.
 	 @see CEikCommandButtonBase::TLayout
 	 @see EEikCmdButFirstRightSecondLeft
 	 */
	WORD layout=0; // EFirstRightSecondLeft|EEikCmdButShareExcess

	/**
 	 Help text for the button.
 	 */
	LTEXT helptxt="";

	/**
 	 Unused.
 	 */
	LLINK extension=0;

	/**
	Specifies the text for the first label component.

	The default is none.
 	 */
    LTEXT txt1="";

	/**
 	 Specifies the text for the second label component.

	 The default is none.
 	 */
    LTEXT txt2="";
    }

/**
A button that can hold two pictures, but no label text.

Resources with this structure are read by CEikBitmapButton::ConstructFromResourceL(), and describe the CEikBitmapButton to be constructed.

@publishedAll
@released
@since Quartz 6.0
see CEikBitmapButton
@see CEikCommandButtonBase
*/
STRUCT BMPBUT
    {
	/**
	 * For internal use only, application developers must not change this.
 	 */
	BYTE version=0;

	/**
 	 Button behaviour flags.
 	 @see TButtonBehavior
 	 */
	WORD behavior=0;

	/**
	 Flags to define how the horizontal space is handled between the button’s images.
 	 @see CEikCommandButtonBase::TLayout
 	 @see EEikCmdButFirstRightSecondLeft
 	 */
	WORD layout=0; // ETextRightPictureLeft|EEikCmdButShareExcess

	/**
 	 Help text for the button.
 	 */
	LTEXT helptxt="";

	/**
 	 Unused.
 	 */
	LLINK extension=0;

	/**
 	 Specifies the first bitmap filename from which to read the button’s image.
 	 */
	LTEXT bmp1file="";

	/**
 	 Specifies the index of the first bitmap in the bmpfile file.

	 A default value of 0xffff indicates no bitmap.
 	 */
    WORD bmp1id=0xffff;

	/**
 	 Specifies the index of the first bitmap mask in the file. 

	 A default value of 0xffff indicates no bitmap mask.
 	 */
    WORD bmp1mask;

	/**
 	 Specifies the second bitmap filename from which to read the button’s image.
 	 */
	LTEXT bmp2file="";

	/**
	Specifies the index of the second bitmap in the bmpfile file.

	A default value of 0xffff indicates no bitmap.
 	 */
    WORD bmp2id=0xffff;

	/**
 	 Specifies the index of the second bitmap mask in the file. 

	 A default value of 0xffff indicates no bitmap mask.
 	 */
    WORD bmp2mask;
    }

// EIKCOLOR.RH
//
//
/**
A utility struct that holds a RGB color value as three bytes.
COLORs are used in the fields of a CTRL_COLOR resource.

@publishedAll
@released
@since Quartz 6.0
@see CTRL_COLOR
*/
STRUCT COLOR
	{
	/**
 	 Red value.
 	 */
	BYTE red;

	/**
 	 Green value.
 	 */
	BYTE green;

	/**
 	 Blue value.
 	 */
	BYTE blue;
	}

/**
Defines an association between a logical color value and an RBG value.

An array of CTRL_COLOR resources can be read into a CColorArray using ResourceUtils::PopulateColorArrayL().

@publishedAll
@released
@since Quartz 6.0
@see COLOR
@see CColorArray
@see ResourceUtils::PopulateColorArrayL()
@see TLogicalColor
*/
STRUCT CTRL_COLOR
	{
	/**
 	 Logical colour value.
 	 @see TLogicalColor
	*/
	WORD logical_color;

	/**
 	 RGB value specified by a COLOR resource.

	 @see COLOR
 	 */
	STRUCT color; // COLOR
	}

/**
A utility struct that links to an array of COLOR resources.

@publishedAll
@released
@since Quartz 6.0
@see COLOR
*/
STRUCT COLORLIST
	{
	/**
 	 Link to an array of COLOR resources.
	 @see COLOR
 	 */
	LLINK array_id=0;
	}

/**
A utility struct that links to an array of COLOR resources.

@publishedAll
@released
@since Quartz 6.0
@see COLOR
*/
STRUCT EIKCOLORLIST
	{
	/**
 	 Link to an array of COLOR resources.
	 @see COLOR
 	 */
	LLINK array_id=0;

	/**
 	 Unused.
 	 */
	LLINK ext_id;
	}

//#include <eikcolor.hrh>

// EIKFONT.RH
//
//

//#include <eikfont.hrh>

/**
A font specified by UID.

Resources of this type can be read by ResourceUtils::CreateScreenFontL() to create a CFont.

@publishedAll
@released
@since Quartz 6.0
@see CFont
@see ResourceUtils::CreateScreenFontL()
*/
STRUCT FONT
	{
	/**
 	 UID of the font.

	 Font UIDs are published in fontids.h.
 	 */
	LONG fontid; // a value from fontids.h

	/**
 	 Font flags, a combination of EGulFontFlags.

 	 @see EGulFontFlagBold
 	 @see EGulFontFlagItalic
 	 @see EGulFontFlagMono
 	 @see EGulFontFlagDoubleWidth
 	 @see EGulFontFlagDoubleHeight
 	 */
	WORD flags=0; // a combination of EGulFontFlagXxxxs
	}

/**
A font specified by name.

Resources of this type can be read by ResourceUtils::CreateNamedScreenFontL() to create a CFont.

@publishedAll
@released
@since Quartz 6.0
@see CFont
@see ResourceUtils::CreateNamedScreenFontL()
*/
STRUCT NAMED_FONT
	{
	/**
 	 Name of the font.
 	 */
	LTEXT name;

	/**
 	 Height of the font in twips.
 	 */
	WORD height;	// in twips

	/**
 	 Font flags, a combination of EGulFontFlags.

 	 @see EGulFontFlagBold
 	 @see EGulFontFlagItalic
 	 @see EGulFontFlagMono
 	 @see EGulFontFlagDoubleWidth
 	 @see EGulFontFlagDoubleHeight
 	 */
	WORD flags=0; // a combination of EGulFontFlagXxxxs
	}

// EIKLBBUT.RH
//
//

//#include <eiklbbut.hrh>

/**
A button, optionally with a label below showing the keypress to access that command. 

Resources with this structure are read by CEikLabeledButton::ConstructFromResourceL(), and describe the CEikLabeledButton to be constructed.

@publishedAll
@released
@since Quartz 6.0
@see CEikLabeledButton
*/
STRUCT LBBUT
    {
	/**
 	 The button type.

	 Valid types are EEikCtCommandButton, EEikCtMenuButton, EEikCtTextButton, EEikCtBitmapButton, and EEikCtTwoPictureCommandButton.

	 @see EEikCtCommandButton
	 @see EEikCtMenuButton
	 @see EEikCtTextButton
	 @see EEikCtBitmapButton
	 @see EEikCtTwoPictureCommandButton
 	 */
	WORD buttontype=0; // EEikCtCommandButton

	/**
 	 Resource for the button, e.g. a CMBUT resource.
	 This should match the type specified in the buttontype field.

	 @see CMBUT
	 @see MNBUT
	 @see TXTBUT
	 @see BMPBUT
	 @see PICMBUT
 	 */
	STRUCT button;

	/**
 	 Hotkey key for the button.
 	 */
	LONG hotkey;

	/**
	Button flags.

	Options are EEikLabeledButtonPlainHotKey, EEikLabeledButtonShowHotKey, and EEikLabeledButtonIsDefault.
	The default is EEikLabeledButtonShowHotKey.

	@see EEikLabeledButtonShowHotKey
	@see EEikLabeledButtonPlainHotKey
	@see EEikLabeledButtonIsDefault
 	 */
	BYTE flags=1; // EEikLabeledButtonShowHotKey
    }

// EIKPRIV.RH
//
//
/**
Utility struct to hold a word value.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT INT16
	{
	/**
 	 A word value.
 	 */
	WORD value;
	}

// EIKPRTPV.RH
//
//

// EIKDEF.RH
//
//
/**
A utility struct that, used as the first resource in a resource file, provides a way to record what the resource offset is.

It contains two 32-bit fields: a version number and a self-referencing link. The RResourceFile::ConfirmSignatureL() function reads the signature resource and initialises the offset value from this resource.

@publishedAll
@released
@since Quartz 6.0
@see RResourceFile::ConfirmSignatureL()
*/
STRUCT RSS_SIGNATURE
    {
	/**
 	 A resource file version number.
 	 @see EEikResourceSignatureValue
 	 */
    LONG signature= 4 ;

	/**
	A link to the current resource (i.e. itself).

	This should not be assigned a value.
 	 */
    SRLINK self;
    }

/**
A utility struct that holds a 1-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF1
{
	/**
     Non-zero-terminated string.
	*/
	BUF<1> buf;
}

/**
A utility struct that holds a 2-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF2	{ /** Non-zero-terminated string. */ BUF<2> buf; }

/**
A utility struct that holds a 4-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF4	{ /** Non-zero-terminated string. */ BUF<4> buf; }

/**
A utility struct that holds a 8-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF8	{ /** Non-zero-terminated string. */ BUF<8> buf; }

/**
A utility struct that holds a 9-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF9	{ /** Non-zero-terminated string. */ BUF<9> buf; }

/**
A utility struct that holds a 16-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF16	{ /** Non-zero-terminated string. */ BUF<16> buf; }

/**
A utility struct that holds a 32-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF32	{ /** Non-zero-terminated string. */ BUF<32> buf; }

/**
A utility struct that holds a 40-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF40	{ /** Non-zero-terminated string. */ BUF<40> buf; }

/**
A utility struct that holds a 64-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF64	{ /** Non-zero-terminated string. */ BUF<64> buf; }

/**
A utility struct that holds a 80-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF80	{ /** Non-zero-terminated string. */ BUF<80> buf; }

/**
A utility struct that holds a 128-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF128	{ /** Non-zero-terminated string. */ BUF<128> buf; }

/**
A utility struct that holds a 256-character non-zero-terminated string.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT TBUF256	{ /** Non-zero-terminated string. */ BUF<256> buf; }

/**
A utility struct that holds an array of STRUCTs.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT CONTROLS
	{
	/**
 	 An array of control STRUCTs.
 	 */
	LEN BYTE STRUCT controls[];
	}

/**
Application UI information resource.

This resource is used to define an application's GUI command input and status display controls, e.g. menus, toolbars, status pane, toolbar, toolband, CBA (Control Button Array) and hotkeys. It is loaded by the application UI (derived from CEikAppUi).
Notes:
- Not all of the controls need to be used on every UI variant. For example, a CBA might be used instead of a toolbar.
- The controls created from this resource can be dynamically configured in code.

@publishedAll
@released
@since Quartz 6.0
@see CEikAppUi
*/
STRUCT EIK_APP_INFO
    {
	/**
 	 Hotkey resource.

	Hotkeys are key combinations that the user can press to invoke a particular application command. By default applications do not have any hotkeys.
	@see HOTKEYS
 	 */
    LLINK hotkeys=0;

	/**
	Menu bar resource.

	If this resource is declared, the app UI creates a menu bar for the application from which application commands can be issued. The commands are handled by the application's CEikAppUi::HandleCommandL() function overload.
	@see MENU_BAR
 	 */
    LLINK menubar=0;

	/**
	Toolbar resource.
	@deprecated The old toolbar and the way it was handled is now deprecated. Please use QIK_TOOLBAR in QIK_VIEW instead.
	@see QIK_TOOLBAR
	@see QIK_VIEW
 	 */
    LLINK toolbar=0;

	/**
 	 Toolband resource.

	The toolband is horizontal toolbar at the top of the screen.
 	@see TOOLBAND
 	 */
    LLINK toolband=0;

	/**
 	 Status pane resource.

	The Status pane provides information about the current state of the phone. If this value is not set, the app UI creates a default status pane.
 	@see STATUS_PANE_APP_MODEL
 	 */
    LLINK status_pane=0;

    BYTE disable_system_screen_furniture=0;
    }

/**
Defines page dimensions in twips.

@publishedAll
@released
@since Quartz 6.0
*/
STRUCT PAGESIZE
	{
	/**
 	 Page width.
 	 */
	LONG width=0;

	/**
 	 Page height.
 	 */
	LONG height=0;
	}

/**
View ID.

@publishedAll
@released
@since Quartz 6.0
@see TVwsViewId
*/
STRUCT VIEW_ID
	{
	/**
 	 An application UID.

	This uniquely identifies the application associated with the view.
 	 */
	LONG appuid;

	/**
 	 A view UID.

	This uniquely identifies the view.
 	 */
	LONG viewuid;
	}

// EIKDIALG.RH
//
//

// only buttons defined in Uikon

/**
A group of buttons for a dialog.

@publishedAll
@deprecated
@since Quartz 6.0
*/
STRUCT DLG_BUTTONS
    {
	/**
 	 Flags for the buttons.

	 Valid flags are EEikButtonGroupAddToStack, EEikButtonGroupDelayActivation, and EEikButtonGroupUseMaxSize.
 	 @see EEikButtonGroupAddToStack
	*/
	LONG flags= 0x01 ;

	/**
 	 An array of dialog buttons (DLG_BUTTON) resources.
 	 @see DLG_BUTTON
 	 */
    STRUCT buttons[];
    }

/**
A dialog button.

@publishedAll
@deprecated
@since Quartz 6.0
*/
STRUCT DLG_BUTTON
    {
	/**
 	 Value passed to CEikDialog::OkToExitL() to identify this button when it is pressed.
 	 */
	WORD id=0;

	/**
 	 Button type, e.g. EEikCtCommandButton for a command button.
	 @see EEikCtCommandButton
 	 */
	WORD buttontype=0; // EEikCtCommandButton

	/**
 	 A button resource, e.g. a CMBUT for a command button.
 	 @see CMBUT
 	 */
	STRUCT button;

	/**
 	 Hotkey key for the button.
 	 */
	LONG hotkey;

	/**
 	 Flags for the button.
	 Valid flags are EEikLabeledButtonShowHotKey (the default), EEikLabeledButtonPlainHotKey, and EEikLabeledButtonIsDefault.
	 @see EEikLabeledButtonShowHotKey
 	 */
	BYTE flags=1;

	/**
 	 The dialog line on which to place the button.
 	 */
	BYTE line=1;
    }

// EIKSPANE.RH
//
//

/**
System wide status pane declaration.

@publishedPartner
@released
*/
STRUCT STATUS_PANE_SYSTEM_MODEL				// System wide status pane declaration
	{
	/**
 	 Entire set of valid SPANE_PANEs.
 	 */
	STRUCT panes[];							// entire set of valid SPANE_PANEs

	/**
 	 Default STATUS_PANE_LAYOUT.
 	 */
	LLINK default_layout;					// default STATUS_PANE_LAYOUT

	/**
 	 Entire set of STATUS_PANE_LAYOUTs.
 	 */
	LLINK layouts[];						// entire set of STATUS_PANE_LAYOUTs
	}

/**
@publishedPartner
@released
*/
STRUCT SPANE_PANE
	{
	LONG id;
	WORD flags= 0 ;
	WORD type;
	LLINK resource=0;
	}

/**
@publishedPartner
@released
*/
STRUCT STATUS_PANE_LAYOUT
	{
	WORD position;

	/**
 	 SPANE_LAYOUT_TREE_NODE root of the layout tree.
 	 */
	STRUCT pane_tree;						// SPANE_LAYOUT_TREE_NODE root of the layout tree
	}

/**
@publishedPartner
@released
*/
STRUCT SPANE_LAYOUT_TREE_NODE
	{
	LONG id=0;
	WORD flags;
	WORD size;

	/**
 	  SPANE_LAYOUT_TREE_NODE sub panes.
 	 */
	STRUCT sub_panes[];						// SPANE_LAYOUT_TREE_NODE sub panes
	}

/**
Application specific status pane

@publishedPartner
@released
*/
STRUCT STATUS_PANE_APP_MODEL				// Application specific status pane
	{
	/**
 	 STATUS_PANE_LAYOUT to use for this app.
 	 */
	LLINK layout= 0 ;		// STATUS_PANE_LAYOUT to use for this app

	/**
 	 SPANE_PANE overrides to use for this app.
 	 */
	STRUCT panes[];							// SPANE_PANE overrides to use for this app
	}

// Notifiers
/**
@publishedAll
@released
*/
STRUCT NOTIFIER_LIST
	{
	LONG dll_uid;

	/**
 	 */
	LEN WORD STRUCT notifier_list[]; // notifier data
	}

/**
@publishedAll
@released
*/
STRUCT NOTIFIER_DATA
	{
	LONG notifier_uid;
	}


# 2 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikCommand.rh" 1
// QikCommand.rh
//
// Copyright (c) Symbian Software Ltd 2004.  All rights reserved.
// Created for UIQ 3.0




# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikCommand.hrh" 1
// QikCommand.hrh
//
// Copyright (c) Symbian Software Ltd 2004.  All rights reserved.
// Created for UIQ 3.0





/**
@publishedAll
@released
*/
enum TQikCommandType
	{
	/**	Commands added by the application valid for the current view. E.g. "Sort by size", "Find" or "Preferences".	*/
	EQikCommandTypeScreen	= 0x00000001,
	
	/**	Commands added by the currently focused control. E.g. Checkboxs "Check" command, 
	ChoiceLists "Options" command that opens the list of options. */ 
	EQikCommandTypeItem		= 0x00000002, 
	
	/**	Used to indicate a positive action, e.g. "Yes" delete the file, or "Answer call" or "Retrieve call" when in 
	the Phone application. When there is both a yes and a no command, you can expect a device to place both directly 
	visible and opposite each other when possible. */
	EQikCommandTypeYes		= 0x00000004,
	
	/**	Used to indicate a negative action, e.g. "No" do not delete the file, or "End call" when in the Phone application. 
	When there is both a yes and a no command, you can expect a device to place both directly 
	visible and opposite each other when possible. */
	EQikCommandTypeNo		= 0x00000008, 
	
	/**	"Save" and close, "Send" and close, etc. (the opposite of the Cancel command) */
	EQikCommandTypeDone		= 0x00000010, 
	
	/**	The command type assigned to the Clear key.	*/
	EQikCommandTypeDelete	= 0x00000020, 
	
	/**	The command that cancels all changes and closes the view, pop-out, or dialog. Assigned to the Back key.	*/
	EQikCommandTypeCancel	= 0x00000040, 
	
	/**	The command that opens the help application. Used for sorting purposes only, otherwise this is most often a Screen command.	*/
	EQikCommandTypeHelp		= 0x00000080, 
	
	/**	Commands added by the system. E.g. "End call" when not in the Phone app. */
	EQikCommandTypeSystem	= 0x00000100, 
	
	/**	Commands added by the operator. E.g. "Download more themes". */
	EQikCommandTypeOperator	= 0x00000200, 
	
	/**	Commands added by the FEP. For things like "Change current input language", but not for word-completion with T9 or similar.	*/
	EQikCommandTypeFep		= 0x00000400, 
	
	/**	For recognizing folders in the menu. */
	EQikCommandTypeCategory	= 0x00000800, 

	/**	A constant to mask all command types. Do not use this as a Command type. */
	EQikCommandTypeAll		= 0x7fffffff	//KMaxTInt
	};




// Use these flags to control a commands appearance and attributes.
// (Flags 0x0001->0x080000 are reused from the EEikMenuItem flags defined in Uikon.hrh)

// State flags

/**	Set this flag to dimm a command.
@publishedAll 
@released 
*/


/**	Set this flag if you want a command to occure as a checkbox in the menu. 
@publishedAll 
@released 
*/


/** The first radiobutton in a radiobutton group will create a controller that ensure only one
button in the group can be selected at a time.
@publishedAll
@released
*/


/** Any radiobutton for wich you do not want to create or release a radiobutton group controller.
Typically, it should be all radiobuttons between the first and the last.
@publishedAll
@released
*/


/**	The last radiobutton in the group will release the radiobutton group controller so that no more buttons
can be added to it.	
@publishedAll
@released
*/


/**	Used to toggle symbol mark for both radiobutton and checkbox. 
@publishedAll
@released
*/


/** A divider with text: ---Text---	
@publishedAll
@released
*/


/** Set this flag to sort on a command's text instead of priority. Note that this flag is only valid for 
commands which have the same type and belong to the same named group and the same anonymous group.
@publishedAll 
@released
*/


/** Set this flag to make a command unavailable (which will make the command invisible or dimmed
depending on the current UI configuration of the device). 
@publishedAll 
@released
*/


/**	Set this flag to hide a command.
@publishedAll 
@released
*/


/** A command with this flag will not be present in release builds.
@publishedAll 
@released
*/





// Cpf flags		

/**	Set this flag to prevent CQikContainerPopouts to add a Done command. Used for controls displayed in the container-
popout that do want to define the Done command itself. The container popout will observe the control's Done command. 
@publishedAll
@released
*/


/** User defined commands that should go to the button bar (when present) 
@publishedAll
@released
*/


/** A command with this flag set will be duplicated in e.g. softkey and more 
menu, button bar and application menu, hardware key and application menu.
@publishedAll 
@released
*/


/** E.g. when a device has two screens, some commands may not be present on the smaller screen.	 
@publishedAll
@released
*/


/** A command with this flag set will be mapped to the hardware confirm key. This is only used in the button bar 
@publishedAll
@released
*/


/** A done command with this flag will be placed on left softkey even if there are no item commands 
@publishedAll
@released
*/


/** A command with this flag will only be placed on a hardware key
@publishedAll 
@released
*/


/** A command with this flag will only be used when the UI configuration of the device has a touchscreen.
@publishedAll 
@released
*/

/** A command with this flag will only be used when the UI configuration of the device doesn't have a touchscreen.
@publishedAll 
@released
*/

/** A command with this flag will only be used when the interaction style of the device is menubar.
@publishedAll 
@released
*/

/** A command with this flag will only be used when the interaction style of the device is softkeys.
@publishedAll 
@released
*/

/** A command with this flag will only be used when the screenmode is portrait.
@publishedAll 
@released
*/

/** A command with this flag will only be used when the screenmode is landscape.
@publishedAll 
@released
*/

/** A command with this flag will be repeated when it's HW-button is pressed down. It will not repeate if the user clicks on the command on a touchscreen.
@publishedAll 
@released
*/



/**	Use these constants as group-id on EQikCommandTypeCategory commands to control the sorting between
the dynamic categorymodel commands (All, Unfiled, ..) in relation to the static
folder commands (Edit Folders)
@see EQikCommandTypeCategory 
@publishedAll
@released
*/


/**	Use these constants as group-id on EQikCommandTypeCategory commands to control the sorting between
the dynamic categorymodel commands (All, Unfiled, ..) in relation to the static
folder commands (Edit Folders)
@see EQikCommandTypeCategory 
@publishedAll
@released
*/


/**	Use these constants as group-id on EQikCommandTypeCategory commands to control the sorting between
the dynamic categorymodel commands (All, Unfiled, ..) in relation to the static
folder commands (Edit Folders)
@see EQikCommandTypeCategory 
@publishedAll
@released
*/




// __QIKCOMMAND_HRH__
# 9 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikCommand.rh" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\Qikon.hrh" 1
// qikon.hrh
//
// Copyright (c) Symbian Software Ltd 2003-2004. All rights reserved.





// Exported by quiklaf
# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikstockcontrols.hrh" 1
// qikstockcontrols.hrh
//
// Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.




/**
@publishedAll
@released
*/
enum TQikStockControls
	{
	// UIQ spcific framework stock controls
	EQikCtVertOptionButtonList		= 500,
	EQikCtSoundSelector				= 501,
	EQikCtArrowHeadScrollBar		= 502,
	EQikCtArrowHeadPageScrollBar	= 503,
	EQikCtTimeEditor				= 504,
	EQikCtDateEditor				= 505,
	EQikCtTimeAndDateEditor			= 506,
	EQikCtDurationEditor			= 507,
	EQikCtColorSelector				= 508,
	EQikCtTabScreen					= 509,
	EQikCtTabScreenPage				= 510,
	EQikCtScrollableContainer		= 511,
	EQikCtSlider					= 512,
	EQikCtNumberEditor				= 513,
	EQikCtFloatingPointEditor		= 514,
	EQikCtGregorianCalendar			= 515,	// can not be constructed from Resource, but by type
	EQikCtIpEditor					= 516,
	EQikCtImagePreview				= 517,
	EQikCtCameraViewFinder			= 518,
	EQikCtContainer					= 519,
	
	EQikCtControlStandIn 			= 520, // Not used for creating from resource, but used internally in EIKCAPC.CPP
	
	// was EQikCtFlexibleBuildingBlock=521 now removed
	EQikCtGenericBuildingBlock		= 522,
	
	  EQikCtFirstSystemBuildingBlock = 523,
	EQikCtOnelineBuildingBlock					= 523,
	EQikCtCaptionedTwolineBuildingBlock			= 524,
	//was EQikCtCaptionedThreelineBuildingBlock=525 now removed
	EQikCtTwolineBuildingBlock					= 526,
	EQikCtManylinesBuildingBlock				= 527,
	EQikCtIconOnelineBuildingBlock				= 528,
	EQikCtIconCaptionedTwolineBuildingBlock		= 529,
	//was EQikCtIconCaptionedThreelineBuildingBlock=530 now removed
	EQikCtIconTwolineBuildingBlock				= 531,
	EQikCtOnelineIconBuildingBlock				= 532,
	EQikCtIconOnelineIconBuildingBlock			= 533,
	EQikCtIconTwolineIconBuildingBlock			= 534,
	EQikCtMediumThumbnailDoubleOnelineBuildingBlock	= 535,
	EQikCtLargeThumbnailThreelineBuildingBlock		= 536,
	EQikCtCaptionedOnelineBuildingBlock			= 537,
	EQikCtIconCaptionedOnelineBuildingBlock		= 538,
	EQikCtTwolineIconBuildingBlock				= 539,
	EQikCtIconIconOnelineBuildingBlock			= 540,
	EQikCtHalflineHalflineBuildingBlock			= 541,
	EQikCtCaptionedHalflineBuildingBlock		= 542,
	  EQikCtLastSystemBuildingBlock = 542,

	EQikCtListBox								= 550,
	EQikCtLabeledColorSelector					= 551,
	EQikCtImageCapture							= 552
	};

/**
@publishedAll
@deprecated
*/
enum TQikToolbarTypes
	{
	EQikToolbar	= 500
	};


# 9 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\Qikon.hrh" 2



// Standard command ids
// Reserved number series for command-ids:
// 0xFFFF FFF0 - 0x0000 03FF uikon.hrh from (-16 to +1023 decimal)
// 0x0400 - 0x07FF eikon.hrh
// 0x0800 - 0x0BFF qikon.hrh
// 0x0C00 - 0x0C3F embedded links
// 0x0C40 - 0x0CA4 reserved for licensees
// 0x0CA5 - 0x0FFF reserved for future use
// 0x1000 - KCategoryMenuIdOffset reserved for Applications 
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// Commands for CQikListBox
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// Commands for Gregorian Calendar
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// Commands for CQikSelectFileDlg
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// Commands for CQikFolderBrowseDialog derived classes (i.e copy, move, save file dialogs)
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// Commands for entering and leaving fullscreen mode in views
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


//
// CQikTabGroup constants
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */


//
// CQikSlider constants
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


//
// The values of the following must be reflected in CQikTTimeEditor
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


//
// defines for the CQikKeytopControl
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


//
// defines for the CQikToolBar
//
/**
Default toolbar height used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR
*/

/**
Default width of toolbar horizontal margins used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR
*/

/**
Default width of toolbar top margin used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR
*/

/**
Default inter-control spacing for a toolbar used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR 
*/

/**
Left align a control on a toolbar used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR 
*/

/**
Centre align a control on a toolbar used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR 
*/

/**
Right align a control on a toolbar used in the UIQ toolbar resource struct, @c QIK_TOOLBAR.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR 
*/


/** @publishedAll @released */
enum TQikToolbarOrientation
	{
	EQikToolbarOrientationNorth=1,
	EQikToolbarOrientationSouth,
	EQikToolbarOrientationEast,
	EQikToolbarOrientationWest
	};

//
// defines for the CQikColorSelector
//

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */





//
// common defines for CQikContainer and CQikScrollableContainer
//

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


//
// defines for CQikScrollableContainer
//

// Wrapping
/** @publishedAll @released */

/** @publishedAll @released */


// visibility
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

// type
/** @publishedAll @released */

/** @publishedAll @released */


// visibility
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

// type
/** @publishedAll @released */

/** @publishedAll @released */



/** @publishedAll @released */





/** @publishedAll @released */

/** @publishedAll @released */




//
// constants for creation of views in CQikViewBase
//
/**
@publishedAll
@released
*/
enum TQikCtrlItemFlags
	{
	EQikCtrlFlagIsFocusing =		0x01,
	EQikCtrlFlagIsNonFocusing =		0x02,
	EQikCtrlFlagIsEditInPlace =		0x04,
	EQikCtrlFlagIsNonEditInPlace =	0x08
	};


//
// constants for layout managers
//

/**
@publishedAll
@released
*/
enum TQikStockLayoutManagers
	{
	EQikGridLayoutManager,
	EQikRowLayoutManager,
	EQikFlowLayoutManager,
	EQikColumnLayoutManager
	};

/**
@publishedAll
@released
*/
enum TQikLayoutMirroringSetting
	{
	EQikLayoutAutoMirror,
	EQikLayoutMirror,
	EQikLayoutNoMirroring
	};

/**
@publishedAll
@released
*/
enum TQikLayoutHorizontalAlignment
	{
	EQikLayoutHAlignInherit,
	EQikLayoutHAlignFill,
	EQikLayoutHAlignLeft,
	EQikLayoutHAlignCenter,
	EQikLayoutHAlignRight
	};

/**
@publishedAll
@released
*/
enum TQikLayoutVerticalAlignment
	{
	EQikLayoutVAlignInherit,
	EQikLayoutVAlignFill,
	EQikLayoutVAlignTop,
	EQikLayoutVAlignCenter,
	EQikLayoutVAlignBottom
	};

/**
@publishedAll
@released
*/
enum TQikLayoutBoolSetting
	{
	EQikLayoutInheritBoolValue = -1,
	EQikLayoutFalseValue = 0,
	EQikLayoutTrueValue = 1
	};

/**
@publishedAll
@released
*/
enum TQikGridLayoutManagerDirection
	{
	EQikGridLayoutManagerHorizontal,
	EQikGridLayoutManagerVertical
	};

/**
@publishedAll
@released
*/
enum TQikLayoutFlowBreak
	{
	EQikLayoutFlowBreakInherit,
	EQikLayoutFlowBreakBefore,
	EQikLayoutFlowDontBreak,
	EQikLayoutFlowAllowBreak
	};

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/**
@publishedAll
@released
*/
enum TQikLayoutLogicalMargins
	{
	EQikLayoutInheritMargin = -1,
	EQikLayoutContentGap = -2,
	EQikLayoutContentGapRight = -3,
	EQikLayoutContentGapLeft = -4,
	EQikLayoutLeftEdgeToContent = -5,
	EQikLayoutRightEdgeToContent = -6,
	EQikLayoutLeftEdgeToPopOut = -7,
	EQikLayoutRightEdgeToPopOut = -8,
	EQikLayoutRowTopMargin = -9,
	EQikLayoutRowBottomMargin = -10
	};
		
/**
@publishedAll
@released
*/
enum TQikLayoutLogicalSizes
	{
	EQikLayoutUseControlMinimum = -1,
	EQikLayoutInheritMinimum = -2,
	EQikLayoutSmallIconSize = -3,
	EQikLayoutMediumIconSize = -4,
	EQikLayoutLargeIconSize = -5,
	EQikLayoutMediumThumbnailSize = -6,
	EQikLayoutLargeThumbnailSize = -7,
	EQikLayoutMediumPortraitThumbnailSize = -8,
	EQikLayoutLargePortraitThumbnailSize = -9
	};


//
// UI configuration constants
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */


//
// UI configuration standard device configurations
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */



/** @deprecated @see TQikCommandOperatorPriority */

/** @deprecated @see TQikCommandOperatorPriority */

/** @deprecated @see TQikCommandOperatorPriority */

/** @deprecated @see TQikCommandOperatorPriority */


/**
@publishedAll
@released
*/
enum TQikCommandOperatorPriority
	{
	EQikCommandOperatorPrioFirst 					= 0,
	EQikCommandOperatorPrioBeforeHardware 			= 50,
	EQikCommandOperatorPrioHwKeys 					= 100,
	EQikCommandOperatorPrioAfterHardware			= 150,

	EQikCommandOperatorPrioBeforeTemporaryMenus 	= 200,
	EQikCommandOperatorPrioFepMenu 					= 250,
	EQikCommandOperatorPrioPopoutMenu 				= 300,
	EQikCommandOperatorPrioAfterTemporaryMenus 		= 350,

	EQikCommandOperatorPrioBeforeResidentButtons 	= 400,
	EQikCommandOperatorPrioDialogButtons 			= 450,
	EQikCommandOperatorPrioAppTitlebarButtons 		= 500,
	EQikCommandOperatorPrioButtonOrSoftkeyBar 		= 550,
	EQikCommandOperatorPrioAfterResidentButtons 	= 600,

	EQikCommandOperatorPrioBeforeResidentMenus 		= 650,
	EQikCommandOperatorPrioDialogMenu 				= 700,
	EQikCommandOperatorPrioAppTitlebar 				= 750,
	EQikCommandOperatorPrioAfterResidentMenus 		= 800,
	EQikCommandOperatorPrioLast 					= 850
	};

//
// CQikNumberEditor constants
//
/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */



/**
@publishedAll
@released
*/
enum TQikBuildingBlockSlots
	{
	EQikSlotContainer1,
	EQikSlotContainer2,
	EQikSlotContainer3,
	EQikSlotContainer4,
	EQikSlotContainer5,
	EQikSlotContainer6,
	EQikSlotContainer7,
	EQikSlotContainer8,
	EQikSlotContainer9,
	EQikSlotContainer10,
	
	EQikItemSlot1,
	EQikItemSlot2,
	EQikItemSlot3,
	EQikItemSlot4,
	EQikItemSlot5,
	EQikItemSlot6,
	EQikItemSlot7,
	EQikItemSlot8,
	EQikItemSlot9,
	EQikItemSlot10,
	
	EQikIconSlot1,
	EQikIconSlot2,
	EQikIconSlot3,
	EQikIconSlot4,
	EQikIconSlot5,
	EQikIconSlot6,
	EQikIconSlot7,
	EQikIconSlot8,
	EQikIconSlot9,
	EQikIconSlot10
	};
	
/**
@publishedAll
@released
*/
enum TQikBuildingBlockControlInternalAlignment
	{
	EQikAlignHLeftVTop,
	EQikAlignHLeftVCenter,
	EQikAlignHLeftVBottom,
	EQikAlignHCenterVTop,
	EQikAlignHCenterVCenter,
	EQikAlignHCenterVBottom,
	EQikAlignHRightVTop,
	EQikAlignHRightVCenter,
	EQikAlignHRightVBottom
	};

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */



/** @publishedAll @released */
enum TQikImageCaptureEntryMode
	{
	EQikImageCapturePassiveMode,
	EQikImageCaptureActiveMode
	};

// Image capture flags
/** @publishedAll @released */

/** @publishedAll @released */


//building block flags

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


// __QIKON_HRH__

# 10 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikCommand.rh" 2


/**
This resource struct specifies a list of @c QIK_COMMANDs and as an example it can be used in
resources like @c DIALOGs and @c QIK_VIEW_CONFIGURATIONs.

A command is the visual representation of an action in an application.
Application users initiate an action by selecting the corresponding command in the user interface.

More information about commands are available in the UIQ Developer Library.

@publishedAll
@released
@see QIK_COMMAND
*/
STRUCT QIK_COMMAND_LIST
	{
	/**
     Comma separated list of @c QIK_COMMAND items.
	 @see QIK_COMMAND
	 */
	STRUCT items[]; // QIK_COMMANDs

	/**
	 For future use. Not used now.
	 @see QIK_COMMAND
	 */
	LLINK extension=0;
	}

/**
This resource struct specifies a specific command and together with other commands
assembled in an array they are used in the @c QIK_COMMAND_LIST resource struct.

A command is the visual representation of an action in an application.
Application users initiate an action by selecting the corresponding command in the user interface.

More information about commands are available in the UIQ Developer Library.

@publishedAll
@released
@see QIK_COMMAND_LIST
@see CQikCommand
*/
STRUCT QIK_COMMAND
	{
	/**
	 For internal use only, application developers must not change this.
	 */
	BYTE version=3;

	/**
	 Mandatory to initalize this field.
	 ID of the command. The command ID is used when inserting, modifing, or
	 deleting commands by using the @c CQikCommandManager API.
	 @see EQikCmdUnassigned
	 */
	LONG id= 0x0812 ;

	/**
	 Mandatory to initalize this field.
	 Defines where and how in the user interface the command will occur and how it 
	 will be presented to the user.
     See file QikCommand.hrh for a complete list of available types.
	 @see TQikCommandType
	 */
	LONG type;

	/**
	Specifies the ID of the anonymous group to which this command belongs.
	To be able to group commands in an anonymous group, the commands must be of 
	the same type. These groups are usually surrounded by visual dividers. 
	If using anonymous groups in named groups (cascaded menues) the
	commands must be in the same named group and being of the same type.

	For more details about anonymous groups look in the UIQ Developer Library.
	Search for this topic by using the key words "anonymous group".
	*/
	LONG groupId=0;

	/**
	Specifies the ID of the named group to which this command links to.
	This is the ID of the cascaded menu which is launched when selecting this
	command.

	For more details about named groups look in the UIQ Developer Library.
	Search for this topic by using the key words "named group".
	 */
	LONG namedGroupLinkId=0;

	/**
	Specifies the named group ID.
	This is the ID of the named group (cascaded menu) to which this command 
	belongs.

	For more details about named groups look in the UIQ Developer Library.
	Search for this topic by using the key words "named group".
	 */
	LONG namedGroupId=0;

	/**
	 Priority of the command. The priority is used to control the sortorder for
	 commands of the same type within the same group.
	 */
	LONG priority=0;

	/**
	 Mandatory to initalize this field.
	 Text representation of the command. A command can have a text and 
	 an optional short text. When the text attribute is the only one set, 
	 it will be used both in menus and on softkeys.
	 */
	LTEXT text;

	/**
	 Short text is used on buttons if specified.
	 Short text will be the preferred choice on softkeys and buttons, 
	 while the text will be preferred in menus.
	 */
	LTEXT shortText="";

	/**
	 Icon and image representation of the command.

	 @see QIK_CONTENT
	 @see QIK_CONTENT_MBM
	 */
	LLINK icon=0; // QIK_CONTENT or QIK_CONTENT_MBM

	/**
	 @internalTechnology
	 @deprecated
	 */
	LTEXT bmpFile="*"; 		// deprecated

	/**
	 @internalTechnology
	 @deprecated
	 */
	WORD bmpId=0xffff;		// deprecated

	/**
	 @internalTechnology
	 @deprecated
	 */
	WORD bmpMaskId=0xffff;	// deprecated

	/**
     Controls the state, occurrence, appearance, and behavior of a single command.
     See file QikCOmmand.hrh for a complete list of available flags.

     Some of them are listed here:
     - @c EQikCmdFlagDimmed
     - @c EQikCmdFlagInvisible
     - @c EQikCmdFlagCheckBox
     - @c EQikCmdFlagSortAlphabetic

     @see EQikCmdFlagDimmed
     @see EQikCmdFlagInvisible
     @see EQikCmdFlagCheckBox
     @see EQikCmdFlagSortAlphabetic
	 */
	LONG stateFlags=0;

	/**
     Controls cooperation between the UIQ application framework and different command operators in the UI.
     See file QikCommand.hrh for a complete list of available flags.
	 */
	LONG cpfFlags=0;

	/**
	 For future use. Not used now.
	 */
	LLINK extension=0;
	}

// __QIKCOMMAND_RH__
# 3 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikdlg.rsg" 1



















































































































































# 4 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2



# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.rh" 1
// EIKON.RH
//
// Copyright © Symbian Software Ltd 1997-2005. All rights reserved.
//





# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.hrh" 1
// EIKON.HRH
// Copyright (c) Symbian Software Ltd 1997-2005.  All rights reserved.

// To get rid of the complaint from doc buld tool about unset define.
/** @internalTechnology @released */



# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh" 1
// uikon.hrh
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.


/** @internalTechnology @released */
# 2299 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh"

# 9 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.hrh" 2



// Quartz specific dialog flags
/**
A dialog flag that, if set, tells the framework not to perform any wrapping layout within the dialog.
Unless the application itself does some layout for the dialog it’s lines will be cut to fit width.
This flag shuts off wrapping functionality for the entire dialog.

@see QuartzSpecificDialogs.UsingDialogWrappingLayoutFunctionality
@since UIQ 2.0
@publishedAll 
@deprecated
*/

/**
A dialog flag that sets the dialog to use a dialog button layout where buttons are being laid out at
bottom, vertically, full width, and with centralised text. Buttons will be laid out following the
order in which they are defined in the resource file with the first button at the top.
@publishedAll 
@deprecated
*/


/** 
This flag will allocate text buttons in the dialogs buttonbar at dialog
construction time instead of display time. Useful for Out-Of-Memory dialog.
@internalTechnology 
@deprecated */ 


// Quartz specific dialog item flags
/**
A dialog line flag that sets the caption to appear above the control. Otherwise, it appears to the left. 
This flag can be specified in the itemflags field in the <code>DLG_LINE</code> struct.

@since Quartz 6.1
@publishedAll 
@deprecated
*/




/**
A dialog line flag that sets the caption and control on the dialog line is be more densely packed.

By default, captions are right aligned, and controls left aligned. With this flag, both the caption
and the control will be left aligned. It is typically used if one dialog line has a caption that is
a lot longer than the rest of the dialog lines.

Note that flag is distinct from <code>EEikDialogFlagDensePacking</code>, which affects the whole dialog
rather than one line, and makes the dialog lines more densely packed vertically, rather than horizontally.

@since Quartz 6.1
@publishedAll 
@deprecated
*/

/**
A dialog item flag that. If set, makes an item use the full available width in the dialog. Normally,
during layout a dialog item’s size will be set to its minimum size.

@since Quartz 6.1
@publishedAll 
@deprecated
*/

/**
A dialog line flag that sets the control to be edit in place. I.e. it will not be in a
popout but directly in the dialog page.
@since UIQ 3.0
@publishedAll 
@deprecated
*/
// UIQ hj
/**
A dialog line flag that sets the control to be not edit in place. I.e. it will be in a
popout and have a control stand-in showing a text representation for it.
@since UIQ 3.0
@publishedAll 
@deprecated
*/
// UIQ hj
/**
A dialog line flag that makes the line not display any highlight when it gets focus. The line will still get focus though.
@since UIQ 3.0
@publishedAll 
@deprecated
*/
// UIQ hj
/**
A dialog line flag that sets the line to share the available height of a dialog page. This is normally
used with listboxes to make the listbox fill the page no matter what font and margins it has.
@since UIQ 3.0
@publishedAll 
@deprecated
*/
// UIQ hj

/** @publishedAll @deprecated */



// EIKDIAL.HRH
//

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */


/** @publishedAll @released */
enum
	{
	EDialDlgButFreeDial=1,
	EDialDlgButDial,
	EDialDlgButDialOut,
	EFreeDialDlgButClear,
	EFreeDialDlgButRedial,
	EDialDlgEdwin1,
	EDialDlgEdwin2,
	EDialDlgEdwin3,
	EDialDlgEdwin4,
	EDialDlgEdwin5,
	EFreeDialDlgEdwin
	};

// EIKTIME.HRH
//
//

/**
Used in date editors to identify the maximum year.
@publishedAll 
@released
*/

/**
Used in date editors to identify the minimum year.
@publishedAll 
@released
*/


/** @publishedAll @released */


/**
Resource ID of the set city choicelist control.
@publishedAll 
@released
*/


/**
Resource ID of the set country choicelist control.
@publishedAll 
@released
*/


/**
Resource ID of the time editor (<code>CQikTTimeEditor</code>).
@publishedAll 
@released
*/


/**
Resource ID of the date editor (<code>CQikTTimeEditor</code>).
@publishedAll 
@released
*/


/**
Resource ID of the set summer time checkbox control.
@publishedAll 
@released
*/


/** @publishedAll @released */


/**
Resource ID of the Europe checkbox in the Daylight savings dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Northern checkbox in the Daylight savings dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Southern checkbox in the Daylight savings dialog.
@publishedAll
@released
*/


/**
Resource ID of the time format option button (12 or 24 hour clock).
@publishedAll
@released
*/


/**
Resource ID of the time separator choice list control.
@publishedAll 
@released
*/


/**
Resource ID of the date format choice list control.
@publishedAll 
@released
*/


/**
Resource ID of the date separator choice list control.
@publishedAll 
@released
*/


/**
Resource ID of the Monday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Tuesday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Wednesday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Thursday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Friday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Saturday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the Sunday checkbox in the Set Workdays dialog.
@publishedAll 
@released
*/


/**
Resource ID of the first day of the week choicelist.
@publishedAll 
@released
*/


/**
Resource ID of a description line used in the set city dialog.
@publishedAll 
@released
*/


// EIKCHLST.HRH
//

/**
Flag which indicates that the contents of a choice list are not owned by the choice list itself.
Can be specified in the flags field of a <code>CHOICELIST</code> control.
@publishedAll 
@released
*/


/**
Flag which indicates that the choice list supports incremental matching. Can be specified in the
flags field of a <code>CHOICELIST</code> control.
@publishedAll 
@released
*/


/**
Flag which disables the ability to launch a drop-down selection list from the choice list. Can be
specified in the flags field of a <code>CHOICELIST</code> control.
@publishedAll 
@released
*/


// EIKCAL.HRH
//
//

/** @publishedAll @released */

/** @publishedAll @released */


// EIKCLOCK.HRH
//
//

/**
Indicates the type of a locale conformant clock (<code>CEikLocaleConformantClock</code>). One of these
values can be specified in the type field of a <code>CLOCK</code> struct.

@since Quartz 6.0
@publishedAll 
@released
*/
enum
	{
	/**
	 * The clock's type depends on the locale's clock format setting.
	 */
	EEikLocaleConformantClockTypeChangesFormatAccordingToLocale,
	/**
	 * Digital clock.
	 */
	EEikLocaleConformantClockTypeDigital,
	/**
	 * Analog clock.
	 */
	EEikLocaleConformantClockTypeAnalog
	};

/**
Indicates the horizontal alignment for a resource constructed digital clock's text. One of these values can be
specified in the horizontalalignment field of a <code>DIGITAL_CLOCK_TEXT_SECTION</code> struct.

@since Quartz 6.0
@publishedAll 
@released
*/
enum
	{
	/**
	 * Text is left aligned.
	 */
	EEikResourceConstructedClockDigitalDisplayHorizontalTextAlignmentLeft,
	/**
	 * Text is center aligned.
	 */
	EEikResourceConstructedClockDigitalDisplayHorizontalTextAlignmentCenter,
	/**
	 * Text is right aligned.
	 */
	EEikResourceConstructedClockDigitalDisplayHorizontalTextAlignmentRight
	};

/**
Indicates the vertical alignment for a resource constructed digital clock's text. One of these values can be 
specified in the verticalalignment field of a <code>DIGITAL_CLOCK_TEXT_SECTION</code> struct.

@since Quartz 6.0
@publishedAll 
@released
*/
enum
	{
	/**
	 * Text is aligned to the top.
	 */
	EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentTop,
	/**
	 * Text is vertically center aligned, including the font's descent.
	 */
	EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentCenterInclDescent,
	/**
	 * Text is vertically center aligned, excluding the font's descent.
	 */
	EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentCenterExclDescent,
	/**
	 * Text is vertically bottom aligned, including the font's descent.
	 */
	EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentBottomInclDescent,
	/**
	 * Text is vertically bottom aligned, excluding the font's descent.
	 */
	EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentBottomExclDescent
	};

/**
Indicates the type of hand in an analog clock. One of the following values can be specified in the type field 
of an <code>ANALOG_CLOCK_HAND</code> struct.

@since Quartz 6.0
@publishedAll 
@released
*/
enum
	{
	/**
	 * The hour hand.
	 */
	EEikResourceConstructedClockAnalogDisplayHandOneRevPer12Hours,
	/**
	 * The minute hand.
	 */
	EEikResourceConstructedClockAnalogDisplayHandOneRevPerHour,
	/**
	 * The second hand.
	 */
	EEikResourceConstructedClockAnalogDisplayHandOneRevPerMinute
	};

/**
Indicates the type of feature to use in a hand in a resource constructed analog clock. One of the following 
values can be specified in the type field of an <code>ANALOG_CLOCK_HAND_FEATURE</code> struct.

@since Quartz 6.0
@publishedAll 
@released
*/
enum
	{
	/**
	 * A linear analog clock hand, drawn as a single line with a specific start and end point.
	 */
	EEikResourceConstructedClockAnalogDisplayHandFeatureLine,
	/**
	 * An analog clock hand feature which is drawn using a polyline, e.g. an arrowhead.
	 */
	EEikResourceConstructedClockAnalogDisplayHandFeaturePolyLine,
	/**
	 * A circular feature in an analog clock hand, with a specified centre point and radius.
	 */
	EEikResourceConstructedClockAnalogDisplayHandFeatureCircle
	};


// EIKPROGI.HRH
//
//

/**
Indicates the type of text displayed in the progress indicator control, <code>CEikProgressInfo</code>. One of 
these values can be specified in the <code>text_type</code> field of the <code>PROGRESSINFO</code> resource struct.

@since Quartz 6.0
@publishedAll 
@released
*/
enum TEikProgressTextType
	{
	/**
	 * No text is used in the progress indicator.
	 */
	EEikProgressTextNone,
	/**
	 * Text is displayed in the progress indicator as a percentage.
	 */
	EEikProgressTextPercentage,
	/**
	 * Text is displayed in the progress indicator as a fraction.
	 */
	EEikProgressTextFraction
	};

// EIKRTED.HRH
//
//

/**
Flag which sets all embedded objects in a rich text editor to be represented by icons. This can be
specified in the <code>flags</code> field of the <code>RTXTED</code> resource struct.
@publishedAll
@released
*/


/**
Flag which allows text parsers in the rich text editor. Text parsers are used to recognise and tag
text strings, e.g. URLs. This can be specified in the <code>flags</code> field of the <code>RTXTED</code> resource struct.
@publishedAll
@released
*/


/** @publishedAll @released */


// EIKSPACE.HRH
//
//

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */

/** @publishedAll @released */



/**
@publishedAll
@released
*/
enum
	{
	EEikCidImageType=1
	};

/**
@publishedAll
@released
*/
enum TQikButtonPanelTypes
	{
	EQikBrButtonPanel = 600
	};


// Standard command ids
// Reserved number series for command-ids:
// 0xFFFF FFF0 - 0x0000 03FF uikon.hrh from (-16 to +1023 decimal)
// 0x0400 - 0x07FF eikon.hrh
// 0x0800 - 0x0BFF qikon.hrh
// 0x0C00 - 0x0C3F embedded links
// 0x0C40 - 0x0CA4 reserved for licensees
// 0x0CA5 - 0x0FFF reserved for future use
// 0x1000 - KCategoryMenuIdOffset reserved for Applications 

/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr  //+Anu
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ hj
/** @publishedAll @released */
// UIQ hj
/** @publishedAll @released */
// UIQ up
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ hj
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ pr
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ an
/** @publishedAll @released */
// UIQ jp
/** @publishedAll @released */
// UIQ jp
/** @publishedAll @released */
// UIQ mh - each command group gets 16 enums each to be able to handle more commands in the future
/** @publishedAll @released */
// UIQ mh
/** @publishedAll @released */
// UIQ mh
/** @publishedAll @released */
// UIQ mh
/** @publishedAll @released */
// UIQ mh

/** @publishedAll @released */
// +Anu



# 10 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.rh" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh" 1
// UIKON.RH
//
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.
//

# 1701 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.rh"

# 11 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.rh" 2



// EIKDIALG.RH

// buttons are defined in Uikon
/**
Dialog resource.

@publishedAll
@deprecated 
@since Quartz 6.0
 */
STRUCT DIALOG
    {
    /**
	 * For internal use only, application developers must not change this.
     */
    BYTE version=0;
	/**
	 * Bitmask of flags for the dialog. 
	 *
	 * If <code>EEikDialogFlagWait</code> is set, the dialog's <code>ExecuteLD()</code> function does not return until 
	 * the dialog is dismissed.If <code>EEikDialogFlagNoUserExit</code> is set, and the dialog does not buttons that 
	 * allow the user to close the dialog, the framework will close the dialog when the application loses the foreground. 
	 * Other flags are defined by <code>EEikDialogFlagXxx</code> constants in uikon.hrh.
	 *
	 */
    LONG flags=0;
	/**
	 * The title. Displayed at the top of the dialog.
	 */
    LTEXT title="";
	/**
	 * The minimum width (wrapping width if control is a label), in pixels, that the framework will set for controls 
	 * within the dialog if it needs to shrink them when doing auto wrapping. If not specified or set to 0 a default 
	 * value of 70 pixels will be used.
	 */
	WORD controlMinWidth=70;
	/**
	 * The minimum wrapping width, in pixels, that the framework will set for trailers within the dialog if it needs 
	 * to shrink them when doing auto wrapping. If not specified or set to 0 a default value of 20 pixels will be used.
	 */
	WORD trailerMinWidth=20;
	/**
	 * The ID of another resource (of type ARRAY) which defines the pages in a multi page dialog. Omit if the dialog is single page.
	 */
	LLINK pages=0;
	/**
	 * The ID of another resource which defines what dialog buttons should be used, for instance R_EIK_BUTTONS_CANCEL_OK.
	 * @deprecated <code>command_list</code> should be used instead.
	 */
    LLINK buttons=0;
    /**
     * The ID of the command list (of type QIK_COMMAND_LIST) that specifies the
     * commands available in the dialog.
     */
    LLINK command_list=0;
     /**
	 * Comma separated list of the items contained in the dialog, usually of type DLG_LINE.
	 * items[] can not be used if "pages" is used.
	 */
    STRUCT items[];
    
    }

/**
Dialog line resource.

@publishedAll
@deprecated 
@since Quartz 6.0
 */
STRUCT DLG_LINE
    {
	/**
	 * An ID which identifies the type of control to create. May be one of the built-in controls or a custom control. 
	 * See the <code>TEikStockControls</code> enum, defined in uikon.hrh for a list of the type values for the built-in controls.
	 */
    WORD type;
	/**
	 * The control's caption. This appears to the left of the control in the dialog line, but if 
	 * <code>EQikDlgItemCaptionAboveControl</code> is specified in <code>itemflags</code>, the caption is displayed above the control.
	 */
    LTEXT prompt;
	/**
	 * A numeric ID that is used in the C++ source code to retrieve the control in this dialog line. The ID must be 
	 * defined in an .hrh file. It is passed to the function <code>CEikDialog::Control()</code>.
	 */
    WORD id=0;
	/**
	 * Optional bitmask of flags which can be used to set line attributes. The possible values are the 
	 * <code>EEikDlgItemXxx</code> constants, defined in uikon.hrh.
	 */
	LONG itemflags=0;
	/**
	 * A resource struct that contains the data used to create the control.
	 */
    STRUCT control;
	/**
	 * Optional text displayed after the control.
	 */
	LTEXT trailer="";
    }

/**
A dialog line resource as a link to another dialog line. This allows lines to be used in more than one dialog without 
having to define them more than once.

@publishedAll
@deprecated 
@since Quartz 6.0
 */
STRUCT DLG_LINE_INDIRECT
    {
	/**
	 * Ignore — this value is not for use by developers.
	 */
    WORD type= -1 ;
	/**
	 * The ID of a resource of type DLG_LINE representing the dialog line to use.
	 */
	LLINK line;
    }

/**
Single page in a multi-page dialog.

@publishedAll
@deprecated 
@since Quartz 6.0
 */
STRUCT PAGE
	{
	/**
	 * For internal use only, application developers must not change this.
	 */
	BYTE version=0;
	/**
	 * The ID of the page: allows it to be identified in the C++ source. This value is used by several 
	 * <code>CEikDialog</code> functions, for instance <code>ActivePageId()</code>.
	 */
	WORD id=0;
	/**
	 * The text that appears in the tab for the page.
	 */
	LTEXT text;
	/**
	 * The minimum width (wrapping width if control is a label), in pixels, that the framework will set for controls 
	 * within the page if it needs to shrink them when doing auto wrapping. This value overrides <code>controlMinWidth</code> 
	 * value used in the DIALOG resource struct. If not specified or set to 0 the DIALOG resource struct value will be used.
	 */
	WORD controlMinWidth=0;
	/**
	 * The minimum wrapping width, in pixels, that the framework will set for trailers within the page if it needs to 
	 * shrink them when doing auto wrapping. This value overrides <code>trailerMinWidth</code> value used in the 
	 * DIALOG resource struct. If not specified or set to 0 the DIALOG resource struct value will be used.
	 */
	WORD trailerMinWidth=0;
	/**
	 * The ID of another resource (of type DLG_BUTTONS) which defines what dialog page buttons should be used.
	 * @deprecated <code>command_list</code> should be used instead.
	 */
	LLINK buttons=0;
	/**
     * The ID of the command list (of type QIK_COMMAND_LIST) that specifies the
     * commands available in the dialog page.
     */
    LLINK command_list=0;	
	/**
	 * The ID of another resource which defines the lines in the dialog page.
	 */
	LLINK lines=0;
	/**
	 * Ignore — not for developer use.
	 */
	WORD flags=0;
	}

/**
A dialog resource that lets you re-use an existing list of dialog lines.

@publishedAll
@deprecated 
@since Quartz 6.0
 */
STRUCT DIALOG_INDIRECT
    {
    /**
	 * For internal use only, application developers must not change this.
     */
    BYTE version=0;
	/**
	 * Bitmask of flags for the dialog. If <code>EEikDialogFlagWait</code> is set, the dialog's <code>ExecuteLD()</code> function does not return 
	 * until the dialog is dismissed. Other flags are defined by <code>EEikDialogFlagXxx</code> constants in uikon.hrh.
	 */
    LONG flags=0; // UIQ me - WORD flags=0;
	/**
	 * The title. Displayed at the top of the dialog.
	 */
    LTEXT title=""; // UIQ me - LTEXT title;
    /**
	 * The minimum width (wrapping width if control is a label), in pixels, that the framework will set for controls 
	 * within the dialog if it needs to shrink them when doing auto wrapping. If not specified or set to 0 a default 
	 * value of 70 pixels will be used.
	 */
	WORD controlMinWidth=70; // UIQ me
	/**
	 * The minimum wrapping width, in pixels, that the framework will set for trailers within the dialog if it needs 
	 * to shrink them when doing auto wrapping. If not specified or set to 0 a default value of 20 pixels will be used.
	 */
	WORD trailerMinWidth=20; // UIQ me
	/**
	 * The ID of another resource (of type ARRAY) which defines the pages in a multi page dialog. Omit if the dialog is single page.
	 */
	LLINK pages=0;
	/**
	 * The ID of another resource which defines what dialog buttons should be used, for instance R_EIK_BUTTONS_CANCEL_OK for Cancel and OK buttons.
	 * @deprecated <code>command_list</code> should be used instead.
	 */
    LLINK buttons=0;
    /**
     * The ID of the command list (of type QIK_COMMAND_LIST) that specifies the
     * commands available in the dialog.
     */
    LLINK command_list=0;
	/**
	 * This field should be ignored by developers.
	 */
    WORD count= -1 ;
	/**
	 * The ID of a resource of type ARRAY representing the dialog lines to re-use.
	 */
	LLINK main=0;
    }

// EIKCHLST.RH
//
//
/**
Choice list resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CHOICELIST
	{
	/**
	 * Flags which may optionally be used to customise the control. Values are defined by EEikChlistXxx constants in eikon.hrh.
	 */
    WORD flags=0;
	/**
	 * Optional value which specifies the maximum width of the choice list, in characters.
	 */
    WORD maxdisplaychar=0;
	/**
	 * ID of another resource which specifies an array of text items each of which represents one choice.
	 */
	LLINK array_id=0;
	}


// EIKIMGAR.RH
//
//

/**
This resource can hold a collection of images

@publishedAll
@released
*/
STRUCT IMAGE_ARRAY
	{
	/**
	 * Number of images stored in the array.
	 */
	WORD width=0;
	/**
	 * ID of another resource which specifies an array of image items.
	 */
	LLINK array_id=0;
	}

// EIKCAL.RH
//
//

//#include <eikcal.hrh>

/**
Calendar control resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CALENDAR
	{
	/**
	 * Optional flags; possible values are the EEikCalendarFlagXxx constants, defined in eikon.hrh.
	 */
	WORD flags=0; // a combination of EEikCalendarFlagXxxxxs
	/**
	 * The number of pixels of vertical space above the year.
	 */
	WORD verticalspaceaboveyear;
	/**
	 * The number of pixels of vertical space below the year.
	 */
	WORD verticalspacebelowyear;
	/**
	 * The number of pixels of horizontal space on each side of the month matrix.
	 */
	WORD horizontalspaceoneachsideofmonthmatrix;
	/**
	 * The number of pixels between the initials of each day's name and the top row of dates.
	 */
	WORD verticalspacebetweendaynameinitialsandtoprowofdays;
	/**
	 * The number of pixels between the rows of dates.
	 */
	WORD verticalspacebetweeneachrowofdays;
	/**
	 * The number of pixels between the columns of dates.
	 */
	WORD horizontalspacebetweeneachcolumnofdays;
	/**
	 * The vertical space below the today button at the bottom of the calendar.
	 */
	WORD verticalspacebelowtoday;
	/**
	 * The horizontal space between the month matrix and the week numbers at the left of the calendar.
	 */
	WORD horizontalspacebetweenmatrixandweeks;
	/**
	 * A struct of type NAMED_FONT representing the font to use for the week numbers.
	 */
	STRUCT weekfont; // NAMED_FONT
	/**
	 * A struct of type NAMED_FONT representing the font to use for today's date.
	 */
	STRUCT dayfont; // NAMED_FONT
	/**
	 * A struct of type NAMED_FONT representing the font to use for the initials of the days of the week.
	 */
	STRUCT weekdayinitialfont; // NAMED_FONT
	/**
	 * A struct of type NAMED_FONT representing the font to use for the dates in the calendar.
	 */
	STRUCT numeralfont; // NAMED_FONT
	/**
	 * The text to display at the bottom of the calendar to represent today.
	 */
	LTEXT todaytext;
	}

// EIKCLOCK.RH
//
//

//#include <eikclock.hrh>

//
// primitive STRUCTs
//

/**
A pair of x,y coordinates representing a point on the screen.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT POINT
	{
	/**
	 * The x (horizontal) coordinate.
	 */
	WORD x;
	/**
	 * The y (vertical) coordinate.
	 */
	WORD y;
	}

/**
Resource struct for the shadow cast behind the numbers in a digital clock, or the hands in an analog clock. 
This struct is used in the shadow field in an analog or digital clock resource struct (see <code>DIGITAL_CLOCK</code>, 
<code>ANALOG_CLOCK_WITH_MASKED_FACE</code> and <code>ANALOG_CLOCK_WITH_UNMASKED_FACE</code>).

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CLOCK_SHADOW
	{
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=1;
	/**
	 * The shadow colour. A COLOR struct.
	 */
	STRUCT color; // COLOR
	/**
	 * The shadow's horizontal offset in pixels.
	 */
	BYTE offsetX;
	/**
	 * The shadow's vertical offset in pixels.
	 */
	BYTE offsetY;
	}


/**
Resource struct that indicates that no shadow is used behind a clock's hands or numbers. This struct is used in the 
shadow field in an analog or digital clock resource struct (see DIGITAL_CLOCK, ANALOG_CLOCK_WITH_MASKED_FACE and 
ANALOG_CLOCK_WITH_UNMASKED_FACE).

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT NO_CLOCK_SHADOW
	{
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=0;
	}

/**
Resource struct for the pen to use to draw an analog clock hand's outline. Can be specified in the pen field 
of an <code>ANALOG_CLOCK_HAND_FEATURE_LINE</code>, <code>ANALOG_CLOCK_HAND_FEATURE_POLY_LINE</code> or <code>ANALOG_CLOCK_HAND_FEATURE_CIRCLE</code>.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CLOCK_PEN_SOLID
	{
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=1;
	/**
	 * The pen color.
	 */
	STRUCT color; // COLOR
	/**
	 * The pen width in pixels.
	 */
	BYTE size;
	}

/**
Indicates that no pen is used to draw the clock hand's outline.

@internalTechnology
@released
@since Quartz 6.0
 */
STRUCT CLOCK_PEN_NULL
	{
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=0;
	}

/**
Resource struct for the fill colour to use for a circular or polyline feature in an analog clock hand. 
This colour is used within the outline drawn by the pen. Specified as the brush field in an 
<code>ANALOG_CLOCK_HAND_FEATURE_POLY_LINE</code> or <code>ANALOG_CLOCK_HAND_FEATURE_CIRCLE</code>.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CLOCK_BRUSH_SOLID
	{
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=1;
	/**
	 * A struct of type COLOR which identifies the fill color.
	 */
	STRUCT color; // COLOR
	}

/**
Indicates that no fill colour is used for a circular or polyline feature in an analog clock hand.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CLOCK_BRUSH_NULL
	{
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=0;
	}

//
// general clock STRUCT
//
/**
A locale-conformant clock. Its format (digital or analog) may change according to the locale's clock format setting.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT CLOCK
	{
	/**
	 * The clock's initial type (digital, analog, or dependent on the locale's clock format). See the EEikLocaleConformantClockTypeXxxxxs values defined in eikon.hrh.
	 */
	BYTE type=EEikLocaleConformantClockTypeChangesFormatAccordingToLocale; // one of the EEikLocaleConformantClockTypeXxxxxs
	/**
	 * Indicates whether the clock's type can change between digital and analog. Must not be set to true if the type is EEikLocaleConformantClockTypeChangesFormatAccordingToLocale.
	 */
	BYTE typeneverchanges=0;
	/**
	 * The ID of a resource of type DIGITAL_CLOCK that defines a digital version of the clock.
	 */
	LLINK digitalresourceid; // DIGITAL_CLOCK
	/**
	 * The ID of a resource of type ANALOG_CLOCK_WITH_MASKED_FACE or ANALOG_CLOCK_WITH_UNMASKED_FACE that defines an analog version of the clock.
	 */
	LLINK analogresourceid; // ANALOG_CLOCK_WITH_MASKED_FACE or ANALOG_CLOCK_WITH_UNMASKED_FACE
	}

//
// digital clock STRUCTs
//
/**
Resource struct that defines a text block in a digital clock.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT DIGITAL_CLOCK_TEXT_SECTION_TEXT_BLOCK
	{
	/**
	 * A format string which sets the format of the date and time. For information on how to format the date and time, 
	 * see the documentation of <code>TTime::FormatL()</code>.
	 *
	 * @see TTime::FormatL()
	 */
	LTEXT text;
	}

/**
Defines the formatting and appearance of a digital clock. An array of these structs can be specified in the 
<code>textsections</code> field of a <code>DIGITAL_CLOCK</code> struct, so that different sections of the clock e.g. the date and the 
time, can have different formatting.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT DIGITAL_CLOCK_TEXT_SECTION
	{
	/**
	 * A NAMED_FONT struct which defines the font to use.
	 */
	STRUCT font; // NAMED_FONT
	/**
	 * A COLOR struct which defines the text colour to use.
	 */
	STRUCT textcolor; // COLOR
	/**
	 * The horizontal text alignment. One of the <code>EEikResourceConstructedClockDigitalDisplayHorizontalTextAlignmentXxxxs</code> 
	 * constants, defined in eikon.hrh.
	 */
	BYTE horizontalalignment; // one of the EEikResourceConstructedClockDigitalDisplayHorizontalTextAlignmentXxxxxs
	/**
	 * The vertical text alignment. One of the <code>EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentXxxxs</code> 
	 * constants, defined in eikon.hrh.
	 */
	BYTE verticalalignment; // one of the EEikResourceConstructedClockDigitalDisplayVerticalTextAlignmentXxxxxs
	/**
	 * Optional — the horizontal margin.
	 */
	WORD horizontalmargin=0;
	/**
	 * Optional — the vertical margin.
	 */
	WORD verticalmargin=0;
	/**
	 * Array of text blocks. This is one or more DIGITAL_CLOCK_TEXT_SECTION_TEXT_BLOCKs.
	 */
	LEN BYTE STRUCT textblocks[]; // DIGITAL_CLOCK_TEXT_SECTION_TEXT_BLOCKs - will each be interspersed with a flashing-block delimiter
	}

/**
Resource struct for a digital clock. A resource of this type can be specified as the <code>digitalresourceid</code> in a 
<code>CLOCK </code> resource struct.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT DIGITAL_CLOCK
	{
	/**
	 * Whether or not to use a border around the clock.
	 */
	BYTE withsingleblackborder=1;
	/**
	 * Initial time for the clock, expressed as an offset from universal time.
	 */
	WORD offsetfromuniversaltime=0;
	/**
	 * A struct which defines the shadow to use behind the clock: either CLOCK_SHADOW or NO_CLOCK_SHADOW.
	 */
	STRUCT shadow; // CLOCK_SHADOW or NO_CLOCK_SHADOW
	/**
	 * This is deprecated. Any value given here is ignored. Use <code>CEikClock::OverrideColorL()</code> to set the background colour.
	 */
	STRUCT backgroundcolor[]; // COLOR		*** Deprecated (the value given will be ignored, use OverrideColorL() on the CEikClock instead) ***
	/**
	 * Defines the appearance and formatting of the digital clock. An array of DIGITAL_CLOCK_TEXT_SECTION structs.
	 */
	LEN BYTE STRUCT textsections[]; // DIGITAL_CLOCK_TEXT_SECTIONs
	}

//
// analog clock STRUCTs
//
/**
Defines the appearance of a linear analog clock hand.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_HAND_FEATURE_LINE
	{
	/**
	 * A struct which defines the pen to use to draw the hand: either a <code>CLOCK_PEN_SOLID</code> or <code>CLOCK_PEN_NULL</code>.
	 */
	STRUCT pen; // CLOCK_PEN_SOLID or CLOCK_PEN_NULL
	/**
	 * A POINT struct which identifies the coordinates of the hand's start point.
	 */
	STRUCT startpoint; // POINT
	/**
	 * A POINT struct which identifies the coordinates of the hand's end point.
	 */
	STRUCT endpoint; // POINT
	}

/**
Defines the appearance of an analog clock hand feature which is drawn using a polyline (a sequence 
of straight lines which join together to form a shape, e.g. an arrowhead).

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_HAND_FEATURE_POLY_LINE
	{
	/**
	 * A struct which defines the pen to use to draw the feature: either <code>CLOCK_PEN_SOLID</code> or <code>CLOCK_PEN_NULL</code>.
	 */
	STRUCT pen; // CLOCK_PEN_SOLID or CLOCK_PEN_NULL
	/**
	 * A struct which defines the brush to use to fill the feature: either <code>CLOCK_BRUSH_SOLID</code> or <code>CLOCK_BRUSH_NULL</code>.
	 */
	STRUCT brush; // CLOCK_BRUSH_SOLID or CLOCK_BRUSH_NULL
	/**
	 * Whether or not the polyline forms a closed shape.
	 */
	BYTE closed;
	/**
	 * The array of points for the polyline: an array of POINT structs.
	 */
	LEN BYTE STRUCT points[]; // POINTs
	}

/**
Defines a circular feature in an analog clock hand.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_HAND_FEATURE_CIRCLE
	{
	/**
	 * A struct which defines the pen to use to draw the feature: either <code>CLOCK_PEN_SOLID</code> or <code>CLOCK_PEN_NULL</code>.
	 */
	STRUCT pen; // CLOCK_PEN_SOLID or CLOCK_PEN_NULL
	/**
	 * A struct which defines the brush to use to fill the feature: either <code>CLOCK_BRUSH_SOLID</code> or <code>CLOCK_BRUSH_NULL</code>.
	 */
	STRUCT brush; // CLOCK_BRUSH_SOLID or CLOCK_BRUSH_NULL
	/**
	 * A POINT struct which identifies the centre of the circle.
	 */
	STRUCT circlecenter; // POINT
	/**
	 * The radius of the circle.
	 */
	WORD radius;
	}

/**
Resource struct which defines the features of an analog clock hand, for instance its colour, size and shape.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_HAND_FEATURE
	{
	/**
	 * The type of features which are used to draw the hand (line, polyline or circle). One of the 
	 * <code>EEikResourceConstructedClockAnalogDisplayHandFeatureXxxxxs</code> constants, defined in eikon.hrh.
	 */
	BYTE type; // one of the EEikResourceConstructedClockAnalogDisplayHandFeatureXxxxxs
	/**
	 * Defines the clock hand feature corresponding to the type specified. Possible values are 
	 * <code>ANALOG_CLOCK_HAND_FEATURE_LINE</code>, <code>ANALOG_CLOCK_HAND_FEATURE_POLY_LINE</code>, or <code>ANALOG_CLOCK_HAND_FEATURE_CIRCLE</code>.

	 */
	STRUCT feature; // ANALOG_CLOCK_HAND_FEATURE_LINE, ANALOG_CLOCK_HAND_FEATURE_POLY_LINE, or ANALOG_CLOCK_HAND_FEATURE_CIRCLE depending on "type"
	}

/**
Resource struct for analog clock hands.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_HAND
	{
	/**
	 * Defines the type of clock hand (hours, minutes or seconds). One of the 
	 * <code>EEikResourceConstructedClockAnalogDisplayHandOneRevPerXxxxxs</code> constants, 
	 * as defined in eikon.hrh.
	 */
	BYTE type; // one of the EEikResourceConstructedClockAnalogDisplayHandOneRevPerXxxxxs
	
	/**
	 * A resource struct which defines the features of the clock hand — of type <code>ANALOG_CLOCK_HAND_FEATUREs</code>.
	 */
	LEN BYTE STRUCT features[]; // ANALOG_CLOCK_HAND_FEATUREs
	}

/**
Resource struct for an analog clock with a masked face. The clock's face is drawn using a 
bitmap and mask contained in an .mbm file. A resource of this type is one of the possible 
values for the <code>analogresourceid</code> in the <code>CLOCK</code> resource struct.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_WITH_MASKED_FACE
	{
	/**
	 * Whether or not to use a border around the clock.
	 */
	BYTE withsingleblackborder=0;
	/**
	 * Initial time for the clock, expressed as an offset from universal time.
	 */
	WORD offsetfromuniversaltime=0;
	/**
	 * A struct which defines the shadow to use behind the clock: either CLOCK_SHADOW or NO_CLOCK_SHADOW.
	 */
	STRUCT shadow; // CLOCK_SHADOW or NO_CLOCK_SHADOW
	/**
	 * Identifies an .mbm file which contains the bitmap to use for the clock face. By default, the system multi-bitmap file is used.
	 */
	LTEXT filecontainingface=""; // defaults to the system multi-bitmap file
	/**
	 * Identifies which bitmap in the .mbm file to use. This is a value in a .mbg bitmap header file.
	 */
	LONG faceid; // a value defined in a *.MBG file
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=1;
	/**
	 * Identifies an .mbm file which contains the bitmap mask to use for the clock face. By default, the system multi-bitmap file is used. 
	 */
	LTEXT filecontainingfacemask=""; // defaults to the system multi-bitmap file
	/**
	 * Identifies which bitmap mask in the .mbm file to use. This is a value in a .mbg bitmap header file.
	 */
	LONG facemaskid; // a value defined in a *.MBG file
	/**
	 * Defines the clock hands. An array of ANALOG_CLOCK_HAND structs.
	 */
	LEN BYTE STRUCT hands[]; // ANALOG_CLOCK_HANDs
	}

/**
Resource struct for an analog clock with an unmasked face. A resource of this type is 
one of the possible values for the <code>analogresourceid</code> in the <code>CLOCK</code> resource struct.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT ANALOG_CLOCK_WITH_UNMASKED_FACE
	{
	/**
	 * Whether or not to use a border around the clock.
	 */
	BYTE withsingleblackborder=0;
	/**
	 * Initial time for the clock, expressed as an offset from universal time.
	 */
	WORD offsetfromuniversaltime=0;
	/**
	 * A struct which defines the shadow to use behind the clock: either CLOCK_SHADOW or NO_CLOCK_SHADOW.
	 */
	STRUCT shadow; // CLOCK_SHADOW or NO_CLOCK_SHADOW
	/**
	 * Identifies an .mbm file which contains the bitmap to use for the clock face. By default, the system multi-bitmap file is used.
	 */
	LTEXT filecontainingface=""; // defaults to the system multi-bitmap file
	/**
	 * Identifies which bitmap in the .mbm file to use. This is a value in a .mbg bitmap header file.
	 */
	LONG faceid; // a value defined in a *.MBG file
	/**
	 * Not for developer use.
	 */
	BYTE donotchange=0;
	/**
	 * Defines the clock hands. An array of ANALOG_CLOCK_HAND structs.
	 */
	LEN BYTE STRUCT hands[]; // ANALOG_CLOCK_HANDs
	}

// EIKCMBOX.RH
//
//
/**
Combo box resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT COMBOBOX
	{
	/**
	 * For internal use only, application developers must not change this.
     */
	BYTE version=0;	
	/**
	 * The width of the text editor in characters.
	 */
	WORD width; // in characters
	/**
	 * The maximum number of characters that can be inserted into the text editor.
	 */
	WORD maxlength;
	/**
	 * The maximum number of items in the drop down list.
	 */
	WORD maxarraysize;
	/**
	 * ID of another resource which specifies an array of text items
	 */
	LLINK array_id=0;
	}

// EIKHOPBT.RH
//
//

/**
Horizontal option button list resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT HOROPBUT
	{
	/**
	 * The inter-button spacing in pixels.
	 */
	WORD buttonSpacing=10;
	/**
	 * Whether text is located to the right or left of the buttons. 0 = text to the left, 1 = text to the right.
	 */
	WORD textOnRight=1;
	/**
	 * The ID of a resource (of type ARRAY) listing the text items associated with each button.
	 */
	LLINK array_id=0;
	}

/**
 Defines a specific option button.
 Items of OPBUT are put toghether in an array which is linked and used by HOROPBUT and QIK_VERTOPBUT.

@publishedAll
@released
*/
STRUCT OPBUT
	{
	/**
	 * The ID of the specific option button.
	 */
    WORD id=0;
	/**
	 * The text of the specific option button.
	 */
    LTEXT text;
	}

//
// primitive STRUCTs
//

/**
Time resource. Consists of hours, minutes and seconds fields. All are zero by default.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT TIME
	{
	/**
	 * Seconds.
	 */
	BYTE second=0;
	/**
	 * Minutes.
	 */
	BYTE minute=0;
	/**
	 * Hours.
	 */
	BYTE hour=0;
	}

/**
Date resource.

Contains values for the day, month and year.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT DATE
	{
	/**
	 * Identifies the day in the month. 
	 *
	 * From 0 to 27/28/29/30 inclusive. This value is based on zero, so these numbers correspond to the 1st to 28th/29th/30th/31st.
	 *
	 */
	BYTE day=0; // from 0 to 27/28/29/30 inclusive
	/**
	 * Identifies the month.
	 *
	 * From 0 to 11 inclusive. This value is based on zero so these numbers correspond to 1 to 12.
	 *
	 */
	BYTE month=0; // from 0 to 11 inclusive
	/**
	 * Identifies the year.
	 */
	WORD year;
	}

/**
This resource struct specifies a specific time and date. 
As an example this struct is used by struct QIK_TIME_AND_DATE_EDITOR to specify a minimum and maximum time and date.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT TIME_AND_DATE
	{
	/**
	 * Seconds.
	 */
	BYTE second=0;
	/**
	 * Minutes.
	 */
	BYTE minute=0;
	/**
	 * Hours.
	 */
	BYTE hour=0;
	/**
	 * Date. 
	 *
	 * From 0 to 27/28/29/30 inclusive. This value is based on zero, so these numbers correspond to the 1st to 
	 * 28th/29th/30th/31st.
	 */
	BYTE day=0; // from 0 to 27/28/29/30 inclusive
	/**
	 * Month.
	 *
	 * From 0 to 11 inclusive. This value is based on zero so these numbers correspond to 1 to 12.
	 */
	BYTE month=0; // from 0 to 11 inclusive
	/**
	 * Year.
	 */
	WORD year;
	}

/**
Resource struct for a duration in seconds.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT DURATION
	{
	/**
	 * The number of seconds — must be greater than or equal to zero.
	 */
	LONG seconds=0; // must be greater than or equal to zero
	}

/**
This resource is used to specify a time offset in seconds.

@publishedAll
@released
*/
STRUCT TIME_OFFSET
	{
	/**
	* The offset in seconds.
	*/
	LONG seconds=0;
	}

/**
This resource is used to specify a geographical position.

@publishedAll
@released
*/
STRUCT LATITUDE_AND_LONGITUDE
	{
	/**
	* The character or key code to represent the degree sign with. 
	*/
	LTEXT degreesign;

	/**
	* The character or key code to represent the minute sign with.
	*/
	LTEXT minutesign;

	/**
	* The character or key code to represent the second sign with.
	*/
	LTEXT secondsign;

	/**
	* The text to use for this cardinal point.
	*/
	LTEXT north;

	/**
	* The character to use for this cardinal point.
	*/
	WORD keytomatchfornorth;

	/**
	* The text to use for this cardinal point.
	*/
	LTEXT south;

	/**
	* The character to use for this cardinal point.
	*/
	WORD keytomatchforsouth;

	/**
	* The text to use for this cardinal point.
	*/
	LTEXT east;

	/**
	* The character to use for this cardinal point.
	*/
	WORD keytomatchforeast;

	/**
	* The text to use for this cardinal point.
	*/
	LTEXT west;

	/**
	* The character to use for this cardinal point.
	*/
	WORD keytomatchforwest;
	}

/**
This resource specifies a spread sheet cell.

@publishedAll
@released
*/
STRUCT CELL
	{

	/**
	* The row of the specific cell.
	*/
	WORD row=0;

	/**
	* The column of the specific cell.
	*/
	WORD col=0;
	}

// EIKPROGI.RH
//
//

/**
Progress information resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT PROGRESSINFO
 	{
	/**
	 * The type of text to use in the progress bar. By default, no text. For possible values, see the 
	 * <code>TEikProgressTextType</code> enum defined in eikon.hrh.
	 */
    WORD text_type=0;
	/**
	 * Optional: the number of vertical lines to display in the progress bar.
	 */
	WORD splits_in_block=0;
	/**
	 * The maximum value: when reached, the progress is complete.
	 */
	LONG finalval=10;
	/**
	 * The width of the progress bar in pixels.
	 */
	LONG width=206;
	/**
	 * The height of the progress bar in pixels. By default, zero, but in this case, the progress info control 
	 * <code>CEikProgressInfo</code> calculates an appropriate value.
	 */
  	LONG height=16;
	}

//#include <eikprogi.hrh>

// EIKRTED.RH
//
//

//#include <eikrted.hrh>
//#include <eikgted.hrh>
# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\gulftflg.hrh" 1
// GULFTFLG.HRH
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//

/** Maximum length for text selection.
@publishedAll 
@released 
*/


/** All font controls.
@publishedAll 
@released 
*/


/** Font control name.
@publishedAll 
@released 
*/


/** Font control size.
@publishedAll 
@released 
*/


/** Bold font control.
@publishedAll 
@released 
*/


/** Italic font control.
@publishedAll 
@released 
*/


/** Underline font control.
@publishedAll 
@released 
*/


/** Strikethrough font control.
@publishedAll 
@released 
*/


/** Font text color control.
@publishedAll 
@released 
*/


/** Print position font control.
@publishedAll 
@released 
*/


/** All fonts.
@publishedAll 
@released 
*/


/** Monospace fonts only.
@publishedAll 
@released 
*/


/** No monospace fonts.
@publishedAll 
@released 
*/


/** Symbol fonts only.
@publishedAll 
@released 
*/


/** No symbol fonts.
@publishedAll 
@released 
*/


/** No monospace or symbol fonts.
@publishedAll 
@released 
*/

# 1197 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.rh" 2


/**
Rich text editor resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT RTXTED
    {
	/**
	 * The width of the editor in characters (or in pixels, if the <code>EEikEdwinWidthInPixels</code> flag is specified).
	 */
	WORD width=0;
	/**
	 * The height of the editor, in pixels.
	 */
	WORD height=0;
	/**
	 * The maximum number of lines which can be displayed by the editor.
	 */
	WORD numlines=1;
	/**
	 * The maximum number of characters that can be entered into the editor. Zero, the default, means no limit.
	 */
	WORD textlimit=0;
	/**
	 * Optional bitmask of flags which control attributes of the editor, for instance whether it is read only. Possible 
	 * values are defined in uikon.hrh, see the <code>EEikEdwinXxx</code> constants.
	 */
	LONG flags=0;
	/**
	 * Font control flags. For possible values, see the <code>EGulFontControlXxx</code> flags defined in gulftflg.hrh.
	 */
	WORD fontcontrolflags=1;
	/**
	 * Font name flags. For possible values, see the flags defined in gulftflg.hrh beginning with <code>EGulAllFonts</code>.
	 */
	WORD fontnameflags= 0x10 ;
	/**
	 * 
	 */
	LONG displayMode=1; // EDisplayModeView
    }

// EIKSECED.RH
//
//

/**
Secret editor resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT SECRETED
	{
	/**
	 * The maximum number of characters that can be entered into the editor.
	 */
 	WORD num_letters=32;
	}

// EIKSPACE.RH
//
//

//#include <eikspace.hrh>

/**
This resource can be used to specify the <code>EEikCtSpacer</code> control.
As an example the SPACER struct can be used in the DLG_LINE resource when specifying
a specific dialog line.

@publishedAll
@released
*/
STRUCT SPACER
    {
	/**
	 * The width of the spacer.
	 */
	WORD width=0;

	/**
	 * The hight of the spacer.
	 */
	WORD height=0;

	/**
	 * The color of the spacer.
	 */
	LONG color=0; // clear
    }

//#include <eikwsel.hrh>
// EIKDLGTB.RH
//
//

//#include <eikctrls.hrh>

/**
Old dialog resource which is no longer used.

@internalTechnology
@deprecated
*/
STRUCT DLG_TOOLBAR
    {
	WORD width=0;
    STRUCT controls[];
    }

/**
Old dialog resource which is no longer used.

@internalTechnology
@deprecated
*/
STRUCT DLG_TBAR_BUTTON
	{
	WORD type=1; // EEikCtLabeledButton
	WORD id=0;
	WORD flags=0;
	WORD length=0;
	WORD buttontype=0; // EEikCtCommandButton
	STRUCT button;
	LONG hotkey;
	BYTE hotkeyflags=1; // EEikLabeledButtonShowHotKey
	}

/**
Old dialog resource which is no longer used.

@internalTechnology
@deprecated
*/
STRUCT DLG_TBAR_SPACER
	{
	WORD type=EEikCtSpacer;
	WORD id=0;
	WORD flags=0;
	WORD length=0;
	WORD width=0;
	WORD height=0;
	LONG color=0; // clear
	}

/**
Old dialog resource which is no longer used.

@internalTechnology
@deprecated
*/
STRUCT DLG_TBAR_CTRL
	{
	WORD type;
	WORD id=0;
	WORD flags=0;
	WORD length=0;
	STRUCT control;
	}


// EIKGTED.RH
//
//

/**
Global text editor resource.

@publishedAll
@released
@since Quartz 6.0
 */
STRUCT GTXTED
    {
	/**
	 * The width of the editor in characters (or in pixels, if the <code>EEikEdwinWidthInPixels</code> flag is specified).
	 */
	WORD width=0;
	/**
	 * The height of the editor, in pixels.
	 */
	WORD height=0;
	/**
	 * The maximum number of lines which can be displayed by the editor.
	 */
	WORD numlines=1;
	/**
	 * The maximum number of characters that can be entered into the editor. Zero, the default, means no limit.
	 */
	WORD textlimit=0;
	/**
	 * Optional bitmask of flags which control attributes of the editor, for instance whether it is read only. Possible 
	 * values are defined in uikon.hrh, see the <code>EEikEdwinXxx</code> constants.
	 */
	LONG flags=0;
	/**
	 * Font control flags. For possible values, see the <code>EGulFontControlXxx</code> flags defined in gulftflg.hrh.
	 */
	WORD fontcontrolflags=1;
	/**
	 * Font name flags. For possible values, see the flags defined in gulftflg.hrh beginning with <code>EGulAllFonts</code>.
	 */
	WORD fontnameflags= 0x10 ;
    }


// EikCheckBox
/**
This resource struct is used to specify a single checkbox control.
It has no elements to set, it is empty.

@publishedAll
@released
@since UIQ 3.0
*/
STRUCT CHECKBOX
{
}

// EikLabeledCheckBox

/**
This resource struct is used to specify a single labelled checkbox control.

@publishedAll
@released
*/
STRUCT LABELEDCHECKBOX
	{
	/**
	* The text to be used for the label of the chechbox.
	*/
	LTEXT labeltext="";

	/**
	* Controls where the label is placed, to the left or to the right of the checkbox.
	*/
	BYTE textonright=1; //true
	}


// __EIKON_RH__

# 7 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikcore.rsg" 1






























# 8 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.rh" 1
// qikon.rh
//
// Copyright © Symbian Software Ltd 2001-2005. All rights reserved.




# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.hrh" 1
// qikon.hrh
//
// Copyright (c) Symbian Software Ltd 2003-2004. All rights reserved.


// __QIKON_HRH__
# 717 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.hrh"


# 8 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.rh" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikcommand.hrh" 1
// QikCommand.hrh
//
// Copyright (c) Symbian Software Ltd 2004.  All rights reserved.
// Created for UIQ 3.0

// __QIKCOMMAND_HRH__
# 255 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikcommand.hrh"

# 9 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.rh" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh" 1
// uikon.hrh
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.


/** @internalTechnology @released */
# 2299 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh"

# 10 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qikon.rh" 2


/**
Defines properties of the category/folders in a drop list.

@publishedAll
@released

@see CQikCategoryModel
@see CQikCategory
*/
STRUCT QIK_CATEGORY
	{
	/**
	 * Name of the category presented in the drop list.
	 */
	LTEXT name(20);
	/**
	 * The handle or ID used to access the specific category.
	 */
	LONG handle		= -1;
	/**
	 * Category flags. The flags are defined in CQikCategory.hrh.
	 */
	WORD flags		= 0;
	/**
	 * Position of the category in the drop list. (If 0 the category will be sorted alphabetically.)
	 */
	WORD sortedAs	= 0;
	/**
	 * Flags defined by the application.
	 */
	LONG appflags	= 0;
	}

// VertOptionButtonList
/**
Vertical option button list resource.

@publishedAll
@released
*/
STRUCT QIK_VERTOPBUT
	{
	/**
	 * The inter-button spacing in pixels.
	 */
	WORD buttonSpacing	= 3;
	/**
	 * Wheter the text is located to the right or left of the buttons. A default value 
	 * of 1 indicates text to the right, and 0 indicates text to the left.
	 */
	WORD textOnRight	= 1;
	/**
	 * The ID of a resource (of typ ARRAY) listing items associated with each button.
	 */
	LLINK array_id		= 0;
	}


// SoundSelector
/**
This resource struct specifies a sound selector control.

@publishedAll
@released
@since UIQ 3.0
@see CQikSoundSelector
*/
STRUCT QIK_SOUND_SELECTOR
	{
	//If you add items here, there will be a SC/BC break
	}


// Time Editors
// ------------
// flags are directly binary compatible with standard UIKON controls.

/**
This resource struct specifies a time editor control.

@publishedAll
@released
@see CQikTimeEditor
*/
STRUCT QIK_TIME_EDITOR
	{
	 /**
	 * The minimum time allowed as an input value. Use a TIME struct.
	 * @see TIME
	 */
	STRUCT minTime;

	 /**
	 * The maximum time allowed as an input value. Use a TIME struct.
	 * @see TIME
	 */
	STRUCT maxTime;

	 /**
	 * Permitted flags: @c EQikTimeWithoutPopout, @c EQikTimeForce24HourFormat
	 */
	BYTE flags=0;
	}

/**
This resource struct specifies a date editor control.

@publishedAll
@released
@see CQikDateEditor
*/
STRUCT QIK_DATE_EDITOR
	{
	 /**
	 * The minimum date allowed as an input value. Use a DATE struct.
	 * @see DATE
	 */
	STRUCT minDate;
	 /**
	 * The maximum date allowed as an input value. Use a DATE struct.
	 * @see DATE
	 */
	STRUCT maxDate;
	 /**
	 * permitted flags: @c EQikTimeWithoutPopout
	 */
	BYTE flags=0;
	}


/**
This resource struct specifies a combined time and date editor control.

@publishedAll
@released
@see CQikTimeAndDateEditor
*/
STRUCT QIK_TIME_AND_DATE_EDITOR
	{
	 /**
	 * The minimum time and date allowed as an input value. Use a TIME_AND_DATE struct.
	 * @see TIME_AND_DATE
	 */
	STRUCT minTimeAndDate; 

	 /**
	 * The maximum time and date allowed as an input value. Use a TIME_AND_DATE struct.
	 * @see TIME_AND_DATE
	 */
	STRUCT maxTimeAndDate;

	 /**
	 * Permitted flags: @c EQikTimeWithoutPopout, @c EQikTimeForce24HourFormat
	 */
	BYTE flags=0;

	 /**
	 * Not used.
	 */
	LTEXT interveningtext=" ";
	}

/**
This resource struct specifies a duration editor control.

@publishedAll
@released
@see CQikDurationEditor
*/
STRUCT QIK_DURATION_EDITOR
	{
	 /**
	 * The minimum duration allowed as an input value. Use a DURATION struct.
	 * @see DURATION
	 */
	STRUCT minDuration;

	 /**
	 * The maximum duration allowed as an input value.  Use a DURATION struct.
	 * @see DURATION
	 */
	STRUCT maxDuration;

	 /**
	 * permitted flags: EQikTimeWithoutPopout
	 */
	BYTE flags=0;
	}

/**
This resource struct specifies a color selector control.
The Color Selector allows the user to select a color from a preset set of colors available in a 
pop out palette called the Color Picker.
@publishedAll
@released
<see-also>
  <api-item>CQikColorSelector</api-item>
</see-also>
*/
STRUCT QIK_COLOR_SEL
	{
	/**
	 Flags used:
	 @li @c EQikColorSelDisplayNoNoText (show no text),
	 @li @c EQikColorSelStandardColor (use standard color palette),
	 @li @c EQikColorSelStandard16 (use 16 color palette rather than 4),
	 @li @c EQikColorSelCustomPalette (use custom palette, supplied in palette_colors).
	 */
	WORD flags=0;	// permitted flags:	EQikColorSelDisplayNoText|	// show no text.
					//					EQikColorSelStandardColor|	// use std color palette
					//					EQikColorSelStandard16|		// use 16 palette rather than 4
					//					EQikColorSelCustomPalette	// use custom palette, supplied in palette_colors.
	/**
	 Assign with resource array of COLOR items if using a custom palette.
	 @see COLOR
	 */
	LLINK palette_colors=0;
	/**
	 Custom palette example:

	 @code
	 RESOURCE ARRAY my_custom_palette
	 	{
	 	items =
	 		{
	 		COLOR { red = 0xFF; green = 0x00; blue = 0xAA; },
	 		COLOR { red = 0x00; green = 0x00; blue = 0xFF; },
	 		etc...
	 		};
	 	}
	 
	 RESOURCE ARRAY my_palette_names
	 {
	 items =
	 	{
	 	LBUF { txt = "Purple"; },
	 	LBUF { txt = "Blue"; },
	 	etc...
	 	};
	 }
	 
	 RESOURCE QIK_COLOR_SEL my_color_selector
	 {
	 flags = EQikColorSelCustomPalette;
	 palette_colors = my_custom_palette;
	 palette_names = my_palette_names;
	 }
	 @endcode
	 */
	LLINK palette_names=0;
	}


// CQikTab
/**
A resource which contains info about a tab.

@publishedAll
@released
*/
STRUCT QIK_TAB
	{
	/**
	 * Specifies the button text label. The default is none.
	 */
	LTEXT text(32)	= "";
	/**
	 * Specifies the bitmap filename (path) from which to read the button's image.
	 */
	LTEXT bmpfile	= "";
	/**
	 * Specifies the index of the bitmap in the bitmap file. A default value of 0xffff indicates no bitmap.
	 */
	WORD bmpid		= 0xffff;	// -1
	/**
	 * Specifies the index of the bitmap mask in the bitmap file. A default value of 0xffff indicates no bitmap mask.
	 */
	WORD bmpmaskid	= 0xffff;	// -1
	}


// CQikTabGroup
/**
A resource which contains a couple of QIK_TABs, and how they shall be aligned.

@publishedAll
@released
@see CQikTabGroup
*/
STRUCT QIK_TABGROUP
	{
	/**
	 * Defines the width of the tabs.
	 * @see CQikTabGroup::TTabWidthType
	 */
	WORD tab_width_type = 2 ;
	/**
	 * Defines the alignment of a tab's content (pic and/or text).
	 * @see CQikTabGroup::THContentAlignment 
	 */
	WORD tab_content_alignment = 1 ;
	/**
	 * An array of QIK_TAB.
	 */
	STRUCT tabs[];
	}


// CQikTabScreen
/**
A resource which contains a couple of QIK_TABSCREENPAGEs, and how the tabs shall be aligned.

@publishedAll
@released
*/
STRUCT QIK_TABSCREEN
	{
	/**
	 * Defines the width of the tabs.
	 * @see CQikTabGroup::TTabWidthType
	 */
	WORD tab_width_type = 2 ;
	/**
	 * Defines the alignment of a tab's content (pic and/or text).
	 * @see CQikTabGroup::THContentAlignment 
	 */
	WORD tab_content_alignment = 1 ;
	/**
	 * An array of QIK_TABSCREENPAGE.
	 */
	STRUCT tab_pages[];
	}

/**
Couples together a tab with a tab screen page (can be any CCoeControl derived class).

@publishedAll
@released
*/
STRUCT QIK_TABSCREENPAGE
	{
	/**
	 * The QIK_TAB this tab screen page shall be attached to.
	 */
	STRUCT tab;
	/**
	 * Defines what type of control the page shall contain. E.g. @c EQikCtTabScreenPage for a regular 
	 * tab screen page or @c EQikCtScrollableContainer for a tab screen page with scroll support.
	 */
	WORD page_type;
	}


// CQikSlider
/**
Defines the properties for a slider control. It can either represent a continous range or a series of discrete values.

@publishedAll
@released
@see CQikSlider
*/
STRUCT QIK_SLIDER
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version = 0;

	/**
	 * Min value in the slider.
	 */
	WORD min_value = 0;

	/**
	 * Max value in the slider.
	 */
	WORD max_value;

	/**
	 * Number of markers shown in the slider.
	 */
	BYTE num_markers = 0;

	/**
	 * Used flags: @c EQikSliderSnapToMarker (indicator snap to markers in slider).
	 */
	BYTE flags = 0;
	}
	
/**
This struct is not used anymore.

@internalTechnology
@deprecated
*/
STRUCT QIK_DEVICE_PASSWORD_CTRL
	{
	STRUCT caption;
	STRUCT seced;
	}

// Numeric editors
/**
Defines the properties of a number editor. The number editor is presented with 
two spinner arrows allowing for incrementing or decrementing the values by 1.

@publishedAll
@released
@see CQikNumberEditor
*/
STRUCT QIK_NUMBER_EDITOR
	{
	/**
	 * For internal use only, application developers must not change this.	 
	*/
	BYTE version = 0;

	/**
	 * Set minimum value in the number editor.
	 */
	LONG min;

	/**
	 * Set maximum value in the number editor.
	 */
	LONG max;

	/**
	 * Permitted flags:
	 * @li @c EQikNone (NumberEditor WITHOUT leading zeros, but INCLUDING spinner arrows.)
	 * @li @c EQikDisplayLeadingZeros (Shows leading zeros infront of the entered number.)
	 * @li @c EQikUseSpinnerArrows (Makes the spinner arrows visible this can be omitted since the spinner arrows are visible as default.)
	 * @li @c EQikNoSpinnerArrows (Hides the spinner arrows that are visible as default to the right of the editor.)
	 */
	BYTE flags = 0;
	}

/**
Defines the properties of a floating point editor.

@publishedAll
@released
@see CQikFloatingPointEditor
*/
STRUCT QIK_FLOATING_POINT_EDITOR
	{
	/**
	 * For internal use only, application developers must not change this.	 
	*/
	BYTE version = 0; 

	/**
	 * Maximum length of displayed number in the editor.
	 */
	WORD maxlength=18;

	/**
	 * Minimum floating point value accepted in the editor.
	 */
	DOUBLE min=-9.9e99;

	/**
	 * Maximum floating point value accepted in the editor.
	 */
	DOUBLE max=9.9e99;
	}

// Toolbar

/**
Defines the properties and controls of a UIQ application toolbar. 

Resources of this type are used with @c CQikAppUi::SetToolbarL() or the toolbar member of an 
EIK_APP_INFO resource to construct a toolbar. 

No runtime modification, such as adding or deleting controls, of the toolbar is supported. 
Controls can be made visible/invisible and dimmed/not dimmed.

@publishedAll
@released
@since Quartz 6.1
@see CQikAppUi::SetToolbarL() 
*/
STRUCT QIK_TOOLBAR
	{
	/**
	* Not to be used.
	*/
	BYTE version=0;	
	/**
	 * The height of the toolbar. 
	 *
	 * If the height is not specified, it defaults to @c EQikToolbarHeight.
	 */
	WORD height = 28 ;
	/**
	 * The width of the horizontal margins of the toolbar. 
	 * 
	 * If the width is not specified, it defaults to @c EQikToolbarHorMargins.
	 */
	WORD horizontal_margins = 2 ;
	/**
	 * The height of the top margin of the toolbar. 
	 * 
	 * If the height is not specified, it defaults to @c EQikToolbarTopMargin.
	 */
	WORD top_margin = 2 ;
	/**
	* The orientation of the toolbar.
	* Default is south.
	*/
	LONG orientation = EQikToolbarOrientationSouth;
	/**
	* If the toolbar is to be movable.
	* Default is EFalse (0 = EFalse, 1 = ETrue).
	*/
	BYTE movable = 0;
	/**
	 * An array of toolbar controls (QIK_TBAR_CTRL) and/or toolbar buttons (QIK_TBAR_BUTTON) to put on the toolbar.
	 * 
	 * @see QIK_TBAR_BUTTON 
	 * @see QIK_TBAR_CTRL 
	 */
	STRUCT controls[];
	}

/**
Resources with this structure are used in the controls[] field of a QIK_TOOLBAR 
resource to create and initialise component controls of the toolbar.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR 
*/
STRUCT QIK_TBAR_CTRL
	{
	/**
	 * ID of the type of control to use.
	 */
	WORD type;
	/**
	 * The command invoked when this control is activated.
	 */
	WORD id=0;
	/**
	 * Flags to set how the control is sized. 
	 * 
	 * This is either @c EEikToolBarCtrlHasSetMinLength (fixed length) 
	 * or @c EEikToolBarCtrlIsStretchable (stretches to fill toolbar).
	 */
	WORD flags=0;
	/**
	 * The length of this control. 
	 * 
	 * This is only used if flags is set to @c EEikToolBarCtrlHasSetMinLength.
	 */
	WORD length=0;
	/**
	 * Sets the alignment of the control in the toolbar.
	 * 
	 * The options are left (@c EQikToolbarLeft), right (@c EQikToolbarRight) 
	 * and centred (@c EQikToolbarCenter). The default alignment is left.
	 */
	BYTE alignment= 0 ;
	/**
	 * Space between this control and adjacent controls. 
	 * 
	 * The default is @c EQikToolbarSpacing.
	 */
	WORD spacing= 5 ;
	/**
	 * Vertical offset for the control.
	 */
	WORD ypos=0;
	/**
	 * Resource struct defining the control. 
	 * 
	 * The type of struct to use depends on the type field.
	 */
	STRUCT control;
	}

/**
Resources with this structure are used in the controls[] field of a QIK_TOOLBAR 
resource to created and initialise a component button of the toolbar.

@publishedAll
@released
@since Quartz 6.1
@see QIK_TOOLBAR 
*/
STRUCT QIK_TBAR_BUTTON
	{
	/**
	 * ID of the type of control to use.
	 */
	WORD type=0;
	/**
	 * The command invoked when this control is activated.
	 */
	WORD id=0;
	/**
	 * Flags to set how the control is sized. 
	 * 
	 * This is either @c EEikToolBarCtrlHasSetMinLength (fixed length) or 
	 * @c EEikToolBarCtrlIsStretchable (stretches to fill toolbar).
	 */
	WORD flags=0;
	/**
	 * The length of this control. 
	 * 
	 * This is only used if flags is set to @c EEikToolBarCtrlHasSetMinLength.
	 */
	WORD length=0;
	/**
	 * Sets the alignment of the control in the toolbar.
	 * 
	 * The options are left (@c EQikToolbarLeft), right (@c EQikToolbarRight) 
	 * and centred (@c EQikToolbarCenter). The default alignment is left.
	 */
	BYTE alignment= 0 ;
	/**
	 * Space between this control and adjacent controls. 
	 * 
	 * The default is @c EQikToolbarSpacing.
	 */
	WORD spacing= 5 ;
	/**
	 * Vertical offset for the control.
	 */
	WORD ypos=0;
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version=0;
	/**
	 * Button behaviour flags.
	 * 
	 * Possible flag values are @c EEikButStaysClear, @c EEikButStaysSet, 
	 * @c EEikButLatches, and @c EEikButReportOnPointerDown.
	 *
	 * Note that the first three of these flags are mutually exclusive.
	 */
	WORD behavior=0;
	/**
	 * Flags to define how the horizontal space is handled between the button’s text and image.
	 *
	 * Options are @c ETextRightPictureLeft (text and image to be positioned horizontally; 
	 * text to the right of image), and @c EEikCmdButShareExcess (excess horizontal space 
	 * is shared between the command button’s text and image).
	 */
	WORD layout=0;
	/**
	 * Help text for the button.
	 */
	LTEXT helptxt="";
	/**
	 * Unused.
	 */
	LLINK extension=0;
	/**
	 * Specifies the button’s text label.
	 * 
	 * The default is none.
	 */
	LTEXT txt="";
	/**
	 * Specifies the bitmap filename from which to read the button’s image.
	 *
	 * The default is none.
	 */
	LTEXT bmpfile="";
	/**
	 * Specifies the index of the bitmap in the bmpfile file.
	 * 
	 * A default value of 0xffff indicates no bitmap.
	 */
	WORD bmpid=0xffff;
	/**
	 * Specifies the index of the bitmap mask in the file. 
	 *
	 * A default value of 0xffff indicates no bitmap mask.
	 */
	WORD bmpmask=0xffff;
	}

/**
Media file handling

@internalTechnology
@released
*/
STRUCT QIK_DRIVE_MEDIA_ROOT
	{
	LTEXT drive;
	LTEXT mediaRoot;
	}

/**
Media file handling

@internalTechnology
@released
*/
STRUCT QIK_DRIVE_FOLDER_ARRAY
	{
	LTEXT drive;
	LLINK folderArray;      
	}

/**
Media file handling

@internalTechnology
@released
*/
STRUCT QIK_EXTENSION_MIMETYPE
	{
	LTEXT ext(8);           // extension
	LTEXT mimeType="";      // MIME-TYPE
	}
	
/**
@internalTechnology
@released
*/
STRUCT QIK_FOLDER_MIME
	{
	LTEXT mimeType = "";
	LTEXT mimeTypeName = "";
	LTEXT folderPath = 0;
	}

// IpEditor
/**
This resource struct specifies a IP editor control.

@publishedAll
@released
@since UIQ 2.0
@see CQikIpEditor
*/
STRUCT QIK_IP_EDITOR
	{
	}



/**
This resource struct specifies a palette.
Was previously used to colorize specific not skinned controls like radio buttons in menu panes and visual cues.
These cues indicates that an item kan be tapped on to open an menu pane with commands.

@publishedAll
@released
<see-also>
  <api-item>CQikDynamicPaletteBitmap</api-item>
</see-also>
@see QIK_COLOR_COLORIZATION
@see QIK_COLOR_SUBSTITUTE
*/
STRUCT QIK_DYNAMIC_PALETTE_BITMAP
	{
	/**
	The name of the multi-bitmap file.
        */
	LTEXT bmp_file;

	/**
        This is an array of ID items for the bitmap pictures in the multi-bitmap file. Array of <code>NUMBER_INT16</code> items, see Uikon.rh.
        */
	STRUCT bmp_ids[];

	/**
	This element defines an array of <code>QIK_COLOR_SUBSTITUTE</code> items.
        Specify this element or the <code>color_colorization</code> element, never both.
	*/
	STRUCT color_substitutes[];

	/**
	This element defines an <code>QIK_COLOR_COLORIZATION</code> item.
        Specify this element or the <code>color_substitutes</code> element, never both.
	*/
	STRUCT color_colorization;
	}

//This resource struct specifies a color substitute for the palette.

/**
@publishedAll
@released
<see-also>
  <api-item>CQikDynamicPaletteBitmap</api-item>
</see-also>
*/
STRUCT QIK_COLOR_SUBSTITUTE
	{
	 //POINT from Eikon.rh
	STRUCT pixel_pos;

	/**
	 *
	 */
	LONG logical_color;

	/**
	 *
	 */
	BYTE sat;

	/**
	 *
	 */
	BYTE lum;
	}

//This resource struct specifies a color colorization for the palette.

/**
@publishedAll
@released
<see-also>
  <api-item>CQikDynamicPaletteBitmap</api-item>
</see-also>
*/
STRUCT QIK_COLOR_COLORIZATION
	{
	 //COLOR from Uikon.rh
	STRUCT base_color;

	/**
	 *
	 */
	LONG logical_target_color;
	}

/**
This resource specifies the Task Menu control.
The Task Menu is a control that contains a collection of Tasks. 
A Task is a configured DNL that launches another application or view.
A Task can also launch a specified viewer with a given file and file syntax.

@publishedAll
@released
@see CQikTaskMenu
@see CQikTaskEntry
*/
STRUCT QIK_TASK_MENU_ENTRY
	{
	/**
	 * The ID of the application to DNL to.
	 */
	LONG appUid=0;

	/**
	 * The ID of the view to open in the application.
	 */
	LONG viewUid=0;

	/**
	 * Parameter for the DNL
	 */
	LONG paramUid=0;

	/**
	 * Text that is displayed in the infoprint.
	 */
	LTEXT info="";

	/**
	 * Describes the file syntax for a viewer with UID = appUID
	 */
	LTEXT fileFormat="";

	/**
	 * Name of the file to create for viewers.
	 */
	LTEXT fileName="";

	/**
	 *  Path to the file.
	 */
	LTEXT filePath="";

	/**
	 * The command this task is mapped to.
	 */
	LONG commandId=0;
	}

/**
This resource specifies the Camera control.
This control encapulates the ECam api into a control.
QikCameraViewFinder only supports image capture and needs a camera
with DirectViewfinder support.

@publishedAll
@released
@since UIQ 3.0
@see CQikCameraViewFinder
*/
STRUCT QIK_CAMERA_VIEW_FINDER
	{
	/**
	 * The width of the control in pixels.
	 */
	WORD width=0;

	/**
	 *  The height of the control in pixels.
	 */
	WORD height=0;

	/**
	 * The format of the captured image, see CCamera::TFormat.
	 */
	LONG format=0;

	/**
	 * TRUE if a preview of the capture image should be shown.
	 */
	BYTE preview=0;

	/**
	 * TRUE if the default standby image should be shown when no image is shown in the viewfinder.
	 */
	BYTE useDefaultStandbyImage=1;

	/**
	 * The index of the camera that is created in ConstructL, -1 means use default camera.
	 */
	BYTE cameraIndex=-1;

	/**
	 * If TRUE the control will keep the aspect ratio of the viewfinder.
	 * If FALSE the control will strech the viewfinder to fit the control.
	 */
	BYTE keepAspectRatio=0;
	}



/**
This class provides a colour selector and a label. It is a compound control
containing a @c CQikColorSelector which allows the user to select a color and
a @c CEikLabel to display a string.

@publishedAll
@released
@see CQikLabeledColorSelector
@see CQikColorSelector
@see CEikLabel
@see QIK_COLOR_SEL
*/
STRUCT QIK_LABELED_COLOR_SEL
	{
	/**
	 The flags for managing the ColorSelector.
	 Permitted flags:
	 - EQikColorSelStandardColor
	 - EQikColorSelStandard16
	 - EQikColorSelCustomPalette

	 ALWAYS SET THE FLAG EQikColorSelDisplayNoText !
	 @see QIK_COLOR_SEL
	 */
	WORD flags=0;

	/**
	 Assign with resource array of COLOR items.
	 @see QIK_COLOR_SEL
	 @see COLOR
	 */
	LLINK palette_colors=0;

	/**
	 Assign with resource array of BUF names.
	 @see QIK_COLOR_SEL
	 @see BUF
	 */
	LLINK palette_names=0;

	/**
	 The label's text.
	 */
	LTEXT labeltext="";

	/**
	 If set to 1 (default), the label is placed to the right of the color selector.
	 If set to 0, the label is placed to the left of the color selector.
	 */
	BYTE textonright=1;
	}
	

/**
A layout manager for laying out controls in a grid where each cell in the grid has the same size.
See more details in UIQ Developer Library.
@publishedAll
@released
@since UIQ 3.0
@see CQikGridLayoutManager
@see MQikLayoutManager
@see CQikLayoutManager
*/
STRUCT QIK_GRID_LAYOUT_MANAGER
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version = 0;

	/**
	 * @See TQikLayoutMirroringSetting
	 * @See TMirroring
	 */
	BYTE mirrored = EQikLayoutAutoMirror;

	/**
	 * The number of columns the grid shall have. The number of rows will be
	 * determined by the number of components.
	 */
	BYTE columns = 0 ;

	/**
	 * The number of rows the grid shall have. The number of columns will be
	 * determined by the number of components.
	 */
	BYTE rows = 0 ;

	/**
	 * The horisontal gap between the cells in pixels.
	 */
	BYTE horizontal_gap = 0;

	/**
	 * The vertical gap between the cells in pixels.
	 */
	BYTE vertical_gap = 0;

	/**
	 * The direction the cells are layed out.
	 * @See TQikGridLayoutManagerDirection
	 */
	BYTE direction = EQikGridLayoutManagerHorizontal;

	/**
	 * @see QIK_GRID_LAYOUT_DATA
	 */
	STRUCT default_layout_data;
	}

/**
Layout data that can be associated with specific controls.
Layout data is settings on how to layout different component controls.
GridLayoutManager has layout data on component control level.
See more details in UIQ Developer Library.

@publishedAll
@released
@see CQikGridLayoutManager
@see  CQikLayoutManager::TLayoutData
*/
STRUCT QIK_GRID_LAYOUT_DATA
	{
 	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version1 = 0;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutHorizontalAlignment
	 */
	BYTE horizontal_alignment = EQikLayoutHAlignInherit;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutVerticalAlignment
	 */
	BYTE vertical_alignment = EQikLayoutVAlignInherit;

	/**
	 * Determines if the layout manager should allocate space for the control even when it's invisible.
	 * @see TQikLayoutBoolSetting
	 */
	BYTE layout_when_invisible = EQikLayoutInheritBoolValue;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_width = EQikLayoutInheritMinimum;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_height = EQikLayoutInheritMinimum;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE left_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE right_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE top_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE bottom_margin = EQikLayoutInheritMargin;

	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version2 = 0;
	}

/**
A layout manager for laying out controls with one control per row.
See more details in UIQ Developer Library.

@publishedAll
@released
@since UIQ 3.0
@see CQikRowLayoutManager
@see MQikLayoutManager
@see CQikLayoutManager
*/
STRUCT QIK_ROW_LAYOUT_MANAGER
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version = 0; 

	/**
	 * @see TQikLayoutMirroringSetting
	 */
	BYTE mirrored = EQikLayoutAutoMirror;

	/**
	 * Sets if the rows should be normalized.
	 * If the rows are normalized they will all get the same height as the heighest row.
	 * If any row has a vertical excess grab weight it might become heigher than the others.
	 */
	BYTE normalize_row_heights = 0;

	/**
	 * @see QIK_ROW_LAYOUT_DATA
	 */
	STRUCT default_layout_data;
	}

/**
Layout data that can be associated with specific controls.
Layout data is settings on how to layout different component controls.
RowLayoutManager has layout data on component control level.
See more details in UIQ Developer Library.

@publishedAll
@released
@see CQikRowLayoutManager
@see  CQikLayoutManager::TLayoutData
*/
STRUCT QIK_ROW_LAYOUT_DATA
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version1 = 0;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutHorizontalAlignment
	 */
	BYTE horizontal_alignment = EQikLayoutHAlignInherit;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutVerticalAlignment
	 */
	BYTE vertical_alignment = EQikLayoutVAlignInherit;

	/**
	 * Determines if the layout manager should allocate space for the control even when it's invisible.
	 * @see TQikLayoutBoolSetting
	 */
	BYTE layout_when_invisible = EQikLayoutInheritBoolValue;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_width = EQikLayoutInheritMinimum;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_height = EQikLayoutInheritMinimum;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE left_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE right_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE top_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE bottom_margin = EQikLayoutInheritMargin;

	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version2 = 0;

	/**
	* Determines how the extra space is to be devided between the rows. 
	* The weight is relative so if, for instance, two controls have a grab weight of three and six, one will be given one third, and the other two thirds.	 
	*/
	BYTE vertical_excess_grab_weight = -1 ;
	}

/**
A layout manager for laying out controls one after the other horizontally and breaks the rows when the controls don't fit the row.
See more details in UIQ Developer Library.

@publishedAll
@released
@since UIQ 3.0
@see CQikFlowLayoutManager
@see MQikLayoutManager
@see CQikLayoutManager
*/
STRUCT QIK_FLOW_LAYOUT_MANAGER
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version = 0;

	/**
	 * @see TQikLayoutMirroringSetting
	 */
	BYTE mirrored = EQikLayoutAutoMirror;

	/**
	 * Sets if the rows should be normalized.
	 * If the rows are normalized they will all get the same height as the heighest row.
	 * If any row has a vertical excess grab weight it might become heigher than the others.
	 */
 	BYTE normalize_row_heights = 0;

	/**
	 * @see QIK_FLOW_LAYOUT_DATA
	 */
	STRUCT default_layout_data;
	}

/**
Layout data that can be associated with specific controls.
Layout data is settings on how to layout different component controls.
FlowLayoutManager has layout data on component control level.
See more details in UIQ Developer Library.

@publishedAll
@released
@see CQikFlowLayoutManager
@see  CQikLayoutManager::TLayoutData
*/
STRUCT QIK_FLOW_LAYOUT_DATA
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version1 = 0; 

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutHorizontalAlignment
	 */
	BYTE horizontal_alignment = EQikLayoutHAlignInherit;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutVerticalAlignment
	 */
	BYTE vertical_alignment = EQikLayoutVAlignInherit;

	/**
	 * Determines if the layout manager should allocate space for the control even when it's invisible.
	 * @see TQikLayoutBoolSetting
	 */
	BYTE layout_when_invisible = EQikLayoutInheritBoolValue;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_width = EQikLayoutInheritMinimum;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_height = EQikLayoutInheritMinimum;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE left_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE right_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE top_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE bottom_margin = EQikLayoutInheritMargin;

	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version2 = 0; //don't change

	/**
	* Determines how the extra space is to be devided between the columns.
	* The weight is relative so if, for instance, two controls have a grab weight of three and six, one will be given one third, and the other two thirds.	 
	*/
	BYTE horizontal_excess_grab_weight = -1 ;

	/**
	* Determines how the extra space is to be devided between the rows. 
	* The weight is relative so if, for instance, two controls have a grab weight of three and six, one will be given one third, and the other two thirds.	 
	*/
	BYTE vertical_excess_grab_weight = -1 ;

	/**
	 * Determines if a control should always be placed on a new row, placed on a new row only when it doesn't fit, or never be placed on a new row.
	 * @see TQikLayoutFlowBreak
	 */
	BYTE row_break = EQikLayoutFlowBreakInherit;
	}

/**
A layout manager for laying out controls one after the other on one row. It aligns component controls of different compound controls to create columns.
See more details in UIQ Developer Library.

@publishedAll
@released
@since UIQ 3.0
@see CQikColumnLayoutManager
@see MQikLayoutManager
@see CQikLayoutManager
*/
STRUCT QIK_COLUMN_LAYOUT_MANAGER
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version = 0;

	/**
	 * @see TQikLayoutMirroringSetting
	 */
	BYTE mirrored = EQikLayoutAutoMirror;

	/**
	 * @see QIK_COLUMN_LAYOUT_DATA
	 */
	STRUCT default_layout_data;

	/**
	 * @see QIK_COLUMN_LAYOUT_DATA
	 */
	STRUCT column_layout_data[];
	}

/**
Layout data that can be associated with specific controls.
Layout data is settings on how to layout different component controls.
ColumnLayoutManager has layout data for each column as well as on component control level.
See more details in UIQ Developer Library.

@publishedAll
@released
@see CQikColumnLayoutManager
@see  CQikLayoutManager::TLayoutData
@released
*/
STRUCT QIK_COLUMN_LAYOUT_DATA
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version1 = 0;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutHorizontalAlignment
	 */
	BYTE horizontal_alignment = EQikLayoutHAlignInherit;

	/**
	 * Determines how the controls should be aligned.
	 * @see TQikLayoutVerticalAlignment
	 */
	BYTE vertical_alignment = EQikLayoutVAlignInherit;

	/**
	 * Determines if the layout manager should allocate space for the control even when it's invisible.
	 * @see TQikLayoutBoolSetting
	 */
	BYTE layout_when_invisible = EQikLayoutInheritBoolValue;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_width = EQikLayoutInheritMinimum;

	/**
	 * Determines if the layout manager should use the control's MinimumSize(), or a fixed value (pixels or CQikLayoutManager::TLogicalSizes)
	 * @see TQikLayoutLogicalSizes
	 */
	WORD minimum_height = EQikLayoutInheritMinimum;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE left_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE right_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE top_margin = EQikLayoutInheritMargin;

	/**
	 * Defined in pixels, or logical values.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE bottom_margin = EQikLayoutInheritMargin;

	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version2 = 0;

	/**
	* Determines how the extra space is to be devided between the columns.
	* The weight is relative so if, for instance, two controls have a grab weight of three and six, one will be given one third, and the other two thirds.	 
	*/
	BYTE horizontal_excess_grab_weight = -1 ;
	}

/**
A building block is a compound control used to layout the controls in a view, where the view can consist of multiple building blocks. 
Each building block has a defined layout and a certain number of slots where controls or captions can be inserted.

This resource is used when you want to make a customized building block.

See more details in UIQ Developer Library.

@publishedAll
@released
@see QIK_SYSTEM_BUILDING_BLOCK
*/
STRUCT QIK_GENERIC_BUILDING_BLOCK
	{
	/**
	 * For internal use only, application developers must not change this.
	 */
	BYTE version = 2;

	/**
	 * Is used to customize the control. The available flags are defined in qikon.hrh.
	 * Useful flags are @see EQikBuildingBlockDividerBelow, @see EQikBuildingBlockMirror, @see EQikBuildingBlockNoMirroring and @see EQikBuildingBlockDebugMode.
	 */
	LONG flags = 0;

	/**
	 * The default caption of the System Building Block.
	 */
	LTEXT default_caption = "";

	/**
	 * The ID of the group
	 */
	LONG group_id = -1;

	/**
	 * @see QIK_GENERIC_BUILDING_BLOCK_COLUMN
	 */
	STRUCT columns[];

	/**
	 * Can be a struct of type QIK_SLOT_CONTENT, QIK_SLOT_CONTENT_DIRECT or QIK_SLOT_CONTENT_INDIRECT.
	 * @see QIK_SLOT_CONTENT
	 * @see QIK_SLOT_CONTENT_DIRECT
	 * @see QIK_SLOT_CONTENT_INDIRECT
	 */
	STRUCT content[];
	}

/**
Respresents the content of a slot in a building block. Is referenced by
<code>QIK_SYSTEM_BUILDING_BLOCK</code> and <code>QIK_GENERIC_BUILDING_BLOCK</code>.

Use this struct when:
- the content of the slot is a caption, or
- the control is included in the <code>QIK_CONTROL_COLLECTION</code>, or
- the control factory only needs the unique handle to create the control.

See more details in UIQ Developer Library.

@publishedAll
@released
@see QIK_SLOT_CONTENT_INDIRECT
@see QIK_SLOT_CONTENT_DIRECT
@see QIK_CONTROL_COLLECTION
*/
STRUCT QIK_SLOT_CONTENT
	{
	/** 
	* The type of the struct. (Do not use!)
	*/
	BYTE struct_type = 0;

	/**
	* The id of the slot. Depends on the used building block, but are usually
	* a values from <code>TQikBuildingBlockSlots</code> (Mandatory).
	* @see TQikBuildingBlockSlots
	*/
	LONG slot_id = -1;

	/**
	* The unique handle (unique within the view) of the control,
	* (<code>CCoeControl::UniqueHandle()</code>). Is used to reference a specific
	* <code>QIK_CONTROL</code> in the control collection, or to tell a control
	* factory which control to create. (Mandatory if no caption is specified)
	* @see CCoeControl::UniqueHandle()
	* @see QIK_CONTROL
	*/
	LONG unique_handle = -1;

	/**
	* The caption. (Mandatory if no control is specified)
	*/
	LTEXT caption = "";
	}
	

/**
Respresents the content of a slot in a building block. Is referenced by
<code>QIK_SYSTEM_BUILDING_BLOCK</code> and <code>QIK_GENERIC_BUILDING_BLOCK</code>.

Use this struct when:
- you don't want to use a <code>QIK_CONTROL_COLLECTION</code>, and
- you want to reference the resource struct of the control through a link, or
- you don't want to create the control using resources

See more details in UIQ Developer Library..

@publishedAll
@released
@see QIK_SLOT_CONTENT
@see QIK_SLOT_CONTENT_DIRECT
@see QIK_CONTROL_COLLECTION
*/
STRUCT QIK_SLOT_CONTENT_INDIRECT
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 1;

	/** 
	The id of the slot. Depends on the used building block, but are usually
	a values from <code>TQikBuildingBlockSlots</code> (Mandatory) 
	@see TQikBuildingBlockSlots
	*/
	LONG slot_id = -1;

	/** 
	The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) 
	*/
	LONG unique_handle = -1;

	/** 
	The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory for controls created entirely from resource files, otherwise
	depends on the control factories)
	@see TQikStockControls
	*/
	LONG type = -1;

	/** 
	 * The flags from <code>TQikCtrlItemFlags</code> that controls the
	 * creation of the control. (Optional)
	 * @see TQikCtrlItemFlags
	 */
	LONG itemflags = 0;

	/** The resource struct that is read by the control's
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory for controls created entirely from 
	resource files, otherwise depends on the control factories) */
	LLINK control = 0;
	}

/**
Respresents the content of a slot in a building block. Is referenced by
<code>QIK_SYSTEM_BUILDING_BLOCK</code> and <code>QIK_GENERIC_BUILDING_BLOCK</code>.

Use this struct when:
- you don't want to use a <code>QIK_CONTROL_COLLECTION</code>, and
- you want to specify the control's resource inline

See more details in UIQ Developer Library..

@publishedAll
@released
@see QIK_SLOT_CONTENT
@see QIK_SLOT_CONTENT_INDIRECT
@see QIK_CONTROL_COLLECTION
*/
STRUCT QIK_SLOT_CONTENT_DIRECT
	{
	/**
	The type of the struct. (Do not use!)
	*/
	BYTE struct_type = 2;

	/** 
	 * The id of the slot. Depends on the used building block, but are usually
	 * a values from <code>TQikBuildingBlockSlots</code> (Mandatory)
	 * @see TQikBuildingBlockSlots
	 */
	LONG slot_id = -1;

	/** 
	The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) 
	*/
	LONG unique_handle = -1;

	/** 
	 * The control type of the control. Such as the items in
	 * <code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.	(Mandatory)
	 * @see TQikStockControls
 	 */
	LONG type = -1;

	/**
	 * The flags from <code>TQikCtrlItemFlags</code> that controls the
	 * creation of the control. (Optional)
	 * @see TQikCtrlItemFlags
	 */
	LONG itemflags = 0;

	/**
	 * The resource struct that is read by the control's
	 * <code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for
	 * <code>EQikCtSlider</code>. (Mandatory)
	 */
	STRUCT control;
	}

/**
See more details in UIQ Developer Library..

@publishedAll
@released
*/
STRUCT QIK_GENERIC_BUILDING_BLOCK_COLUMN
	{
	/**
	 * The ID of the slot
	 */
	LONG slot_id = -1;

	/**
	 * A struct o type QIK_GENERIC_BUILDING_BLOCK_ROW
	 * @see QIK_GENERIC_BUILDING_BLOCK_ROW
	 */
	STRUCT rows[];

	/**
	 * Used when determining how extra space should be devided between columns.
	 * The weight is relative so if, for instance, two controls have a grab 
	 * weight of three and six, one will be given one third, and the other two thirds.
	 */
	BYTE grabweight = 0;

	/**
	 * @see TQikLayoutHorizontalAlignment
	 */
	BYTE horizontal_alignment = EQikLayoutHAlignInherit;

	/**
	 * @see TQikLayoutVerticalAlignment
	 */
	BYTE vertical_alignment = EQikLayoutVAlignInherit;

	/**
	 * The left margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE left_margin = 0;

	/**
	 * The right margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE right_margin = 0;

	/**
	 * The top margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE top_margin = 0;

	/**
	 * The bottom margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE bottom_margin = 0;

	/**
	 * Maximum number of slots.
	 */
	BYTE max_num = 1;

	/**
	 *  Can be turned on by setting <code>auto_wrapping</code> to 1 and turned of by setting it to 0.
	 */
	BYTE auto_wrapping = 1;

	/**
	 * The number of visible lines in the building block column, unlimited if set to 0.
	 */
	BYTE number_of_visible_lines = 0;

	/**
	 Sets the internal alignment of a control which is an <code>MEikAlignedControl</code>,
	 to guide the control where to position its contents.
	 The alignment is specified by values defined in the type <code>TQikBuildingBlockControlInternalAlignment</code>.

	 @see MEikAlignedControl
	 @see TQikBuildingBlockControlInternalAlignment
	 */
	BYTE control_internal_alignment = EQikAlignHLeftVCenter;

	/**
	 * Size in pixels, supports the logical sizes of the layout managers.
	 * @see TQikLayoutLogicalSizes
	 */
	BYTE fixed_width = -1;

	/**
	 * Size in pixels, supports the logical sizes of the layout managers.
	 * @see TQikLayoutLogicalSizes
	 */
	BYTE fixed_height = -1;
	}

/**
See more details in UIQ Developer Library..

@publishedAll
@released
*/
STRUCT QIK_GENERIC_BUILDING_BLOCK_ROW
	{

	/**
	 *  The id of the slot.
	 */
	LONG slot_id = -1;

	/**
	 *  If set to 1 columns are allowed to break the row 
	 *  and the opposite if set to 0.
	 */
	BYTE allow_columns_to_break_row = 0;

	/**
	 * @see QIK_GENERIC_BUILDING_BLOCK_COLUMN
	 */
	STRUCT columns[];

	/**
	 * Used when determining how extra space should be devided between rows.
	 * The weight is relative so if, for instance, two controls have a grab
	 * weight of three and six, one will be given one third, and the other two thirds.
	 */
	BYTE grabweight = 0;

	/**
	 * The horizontal alignment of the building block column, specified by TQikLayoutHorizontalAlignment.
	 * @see TQikLayoutHorizontalAlignment
	 */
	BYTE horizontal_alignment = EQikLayoutHAlignInherit;

	/**
	 * @see TQikLayoutVerticalAlignment
	 */
	BYTE vertical_alignment = EQikLayoutVAlignInherit;

	/**
	 * The left margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE left_margin = 0;

	/**
	 * The right margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE right_margin = 0;

	/**
	 * The top margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE top_margin = 0;

	/**
	 * The bottom margin of the building block column.
	 * @see TQikLayoutLogicalMargins
	 */
	BYTE bottom_margin = 0;

	/**
	 * Maximum number of slots.
	 */
	BYTE max_num = 1;

	/**
	 * Can be turned on by setting <code>auto_wrapping</code> to 1 and turned of by setting it to 0.
	 */
	BYTE auto_wrapping = 1;

	/**
	 *  The number of visible lines in the building block column, unlimited if set to 0.
	 */
	BYTE number_of_visible_lines = 0;

	/**
	 Sets the internal alignment of a control which is an <code>MEikAlignedControl</code>,
	 to guide the control where to position its contents.
	 The alignment is specified by values defined in the type <code>TQikBuildingBlockControlInternalAlignment</code>.

	 @see MEikAlignedControl
	 @see TQikBuildingBlockControlInternalAlignment
	 */
	BYTE control_internal_alignment = EQikAlignHLeftVCenter;

	/**
	 * Size in pixels, supports the logical sizes of the layout managers.
	 * @see TQikLayoutLogicalSizes
	 */
	BYTE fixed_width = -1;

	/**
	 * Size in pixels, supports the logical sizes of the layout managers.
	 * @see TQikLayoutLogicalSizes
	 */
	BYTE fixed_height = -1;
	}

/**
A building block is a compound control used to layout the controls in a view, where the view can consist of multiple building blocks. 
Each building block has a defined layout and a certain number of slots where controls or captions can be inserted.

See more details in UIQ Developer Library..

@publishedAll
@released
*/
STRUCT QIK_SYSTEM_BUILDING_BLOCK
	{
	/**
	 * For internal use only, application developers must not change this.	 
	 */
	BYTE version = 2;

	/**
	 * Is used to customize the control. The available flags are defined in qikon.hrh.
	 * Useful flags are @see EQikBuildingBlockDividerBelow, @see EQikBuildingBlockMirror, @see EQikBuildingBlockNoMirroring and @see EQikBuildingBlockDebugMode.
	 */
	LONG flags = 0;

	/**
	 * The default caption of the System Building Block.
	 */
	LTEXT default_caption = "";

	/**
	 * A struct of type QIK_SLOT_CONTENT, QIK_SLOT_CONTENT_DIRECT or QIK_SLOT_CONTENT_INDIRECT.
	 * @see QIK_SLOT_CONTENT
	 * @see QIK_SLOT_CONTENT_DIRECT
	 * @see QIK_SLOT_CONTENT_INDIRECT
	 */
	STRUCT content[];
	}

/**
A collection of controls that can be used throughout the various
view/container/building block structs by using the identifier
<code>QIK_CONTROL.id</code> (which gets translated into 
<code>CCoeControl::UniqueHandle()</code>). So you can specify how the control
should be created here and just reference it from other places.

You have to add the control collection to the control provider (that creates all
controls referenced from resource files) either by calling
<code>CQikViewBase::ViewConstructFromResourceL()</code> or by calling 
<code>RQikControlInfoArray::AddFromResourceL()</code> (reached from a view by 
calling <code>ControlProvider()->ControlInfos().AddFromResourceL()</code>).

@publishedAll
@released
*/
STRUCT QIK_CONTROL_COLLECTION
	{
	/** The items in the collection. The struct must be a <code>QIK_CONTROL</code>.
	(Mandatory) */
	STRUCT items[];
	}

/**
A description of how to create a control. Used as part of a
<code>QIK_CONTROL_COLLECTION</code>.

Reflected in code as a <code>TQikControlInfo</code>.

@publishedAll
@released
*/
STRUCT QIK_CONTROL
	{
	/** The unique handle (unique within the view) of the control. Is used as 
	<code>CCoeControl::UniqueHandle()</code> and to reference a specific 
	<code>QIK_CONTROL</code> from other resource structs. (Mandatory) */
	LONG unique_handle = -1;
	/** The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory for controls created entirely from resource files, otherwise
	depends on the control factories) */
	LONG type = -1;
	/** The resource struct that is read by the control's 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory for controls created entirely from 
	resource files, otherwise depends on the control factories) */
	LLINK control = 0;
	/** The flags from <code>TQikCtrlItemFlags</code> that controls the 
	creation of the control. (Optional) */
	LONG itemflags = 0;
	}

/**
This resoure struct is used to define which configuration modes an application supports.

See more details in UIQ Developer Library..

@publishedAll
@released
*/
STRUCT QIK_VIEW_CONFIGURATIONS
	{
	/** 
	 * For internal use only, application developers must not change this.	 
	*/
	BYTE version = 0;

	/**
	 * A struct of type QIK_VIEW_CONFIGURATION.
	 * @see QIK_VIEW_CONFIGURATION
	 */
	STRUCT configurations[];
	}

/**
This is a specific view configuration supported by the application.
The recommended way to create a view is to specify the view and command_list members inside each QIK_VIEW_CONFIGURATION.
Then the framework will automatically switch view layout and commands when the window-server change mode.
See more details in UIQ Developer Library..

@publishedAll
@released
*/
STRUCT QIK_VIEW_CONFIGURATION
	{
	/** 
	 * For internal use only, application developers must not change this.	 
	*/
	BYTE version = 0;

	/**
	 A UI-configuration encoded into a unique identifier.

         The @c ui_config_mode parameter is mandatory and need to be set.
         Otherwise the application will panic with QIKON-PANIC:29, this panic code is defined by the <code>TQikPanic</code> member
         <code>EQikPanicInvalidUiConfigModeValueFromResource</code>.

         Example usage:	 ui_config_mode = KQikPenStyleTouchPortrait
         */
	LONG ui_config_mode = 0;

	/**
	 * A struct of type QIK_COMMAND_LIST.
	 * @see QIK_COMMAND_LIST
	 */
	LLINK command_list = 0;

	/**
	 * A struct of type QIK_VIEW.
	 * @see QIK_VIEW
	 */
	LLINK view = 0;
	}

/**
The struct used to specify commands and controls of a view.

Can either be linked from a <code>QIK_VIEW_CONFIGURATION</code> or be used as an
argument to <code>CQikViewBase::InitializeViewFromResourceL()</code>.

@publishedAll
@released
*/
STRUCT QIK_VIEW
	{
	/** 
	For internal use only, application developers must not change this.	 
	*/
	BYTE version = 2;

	/**
	With the viewmode parameter you can set fullscreen properties. (Optional)
	*/
	LLINK view_mode = 0;
	
	/**
	The list of commands that should be used for the view. The struct must be a <code>QIK_COMMAND_LIST</code>. (Optional)
	*/
	LLINK command_list = 0;

	/**
	The qiktoolbar to be used for this view. The CQikAppUi class will be the MEikCommandObserver.
	The struct must be a <code>QIK_TOOLBAR</code>. (Optional)
	*/
	LLINK qiktoolbar = 0;
	
	/**
	The page(s) of the view. The struct must be a
	<code>QIK_VIEW_PAGES</code>. (Optional)
	*/
	LLINK pages = 0;
	}

/**
The pages of a view. Used by <code>QIK_VIEW</code>.

@publishedAll
@released
*/
STRUCT QIK_VIEW_PAGES
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 0;

	/** The pages as <code>QIK_VIEW_PAGE</code>. If your view inherits from 
	<code>CQikMultiPageViewBase</code> you can specify multiple pages, but if it
	inherits from <code>CQikViewBase</code> you must specify excactly one page. 
	(Mandatory) */
	STRUCT pages[];
	}

/**
A page of a view. Used by <code>QIK_VIEW_PAGE</code>.

@publishedAll
@released
*/	
STRUCT QIK_VIEW_PAGE
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 2;
	/** Page id. Must be unique within a view. (Mandatory) */
	WORD page_id = -1;
	/** The caption of the tab. Only used by MultiPageViewBase. (Optional) */
	LTEXT tab_caption = "";
	/** The file used for the icon of the tab. The default value is the
	application default .mbm file. Only used by MultiPageViewBase. (Optional) */
	LTEXT tab_bmpfile = "*";
	/** The id of the bitmap within the .mbm file used for the icon of the tab.
	Only used by MultiPageViewBase. (Optional) */
	WORD tab_bmpid = -1;
	/** The id of the mask within the .mbm file used for the icon of the tab.
	Only used by MultiPageViewBase. (Optional) */
	WORD tab_bmpmaskid = -1;
	/** Boolean to decide whether the TAB_BMPFILE should be interpreted as a uri or not.
	(0 = FALSE, 1 = TRUE) (Mandatory) */
	BYTE tab_bmpfileasuri = 0;
	/** The list of commands that should be used for the page. The struct must
	be a <code>QIK_COMMAND_LIST</code>. (Optional) */
	LLINK command_list = 0;
	/** Id of the container (inheriting <code>CQikContainerBase</code>).
	
	If you specify neither <code>container_unique_handle</code>, nor
	<code>container_type</code> and <code>container</code> it uses the internal
	page control which means you have to use a <code>QIK_CONTAINER_SETTINGS</code>
	for <code>page_content</code>.
	
	(Optional) */
	LONG container_unique_handle = -1;
	/** If you don't want to include the container in the 
	<code>QIK_CONTROL_COLLECTION</code> you can specify the type of the container
	(normally <code>EQikCtContainer</code> or <code>EQikCtScrollableContainer</code>)
	here. (Optional) */
	LONG container_type = -1;
	/** If you have specified <code>container_type</code>, this is the struct used
	for creation of the container. This should link to the struct the container 
	reads in its <code>ConstructFromResourceL()</code>
	(<code>QIK_CONTAINER</code> for <code>EQikCtContainer</code>,
	<code>QIK_SCROLLABLE_CONTAINER</code> for <code>EQikCtScrollableContainer</code>).
	(Optional) */
	LLINK container = 0;
	/** The content of the page. The struct must be supported by the container's 
	<code>InitializeFromResourceL()</code> (<code>QIK_CONTAINER_SETTINGS</code> for
	<code>EQikCtContainer</code>, <code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>
	for <code>EQikCtScrollableContainer</code>). (Mandatory) */
	LLINK page_content = 0; 
	}

/**
The struct used by <code>CQikContainer</code> for creation.

@publishedAll
@released
*/
STRUCT QIK_CONTAINER
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 0;
	/** Flags used to make changes to the default behavior. The available flags 
	are defined in <code>Qikon.hrh</code>. (Optional) */
	LONG flags = 0 ;
	}

/**
The struct used by <code>CQikScrollableContainer</code> for creation.

@publishedAll
@released
*/
STRUCT QIK_SCROLLABLE_CONTAINER
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 0;
	/** Flags used to make changes to the default behavior. The available flags 
	are defined in <code>Qikon.hrh</code>.(Optional) */
	LONG flags = (0x00000001  | 0x00000002 	| 0x00800000  | 0x01000000 	| 0x04000000  | 0x20000000 	| 0x00002000 ) ;
	}

/**
The struct used by <code>CQikContainer::InitializeFromResourceL()</code> to 
set/change the controls the container contains and how they are laid out.

Is referenced by <code>QIK_VIEW_PAGE.page_content</code> and 
<code>QIK_CONTAINER_ITEM.container</code> (and all the other container items).

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_SETTINGS
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 0;
	/** Flags used to make changes to the default behavior. The available flags 
	are defined in <code>Qikon.hrh</code>. (Optional) */
	LONG flags = (0x00000001  | 0x00000002  | 0x00002000 ) ;
	/** The type the layout manager used by the container, either a 
	<code>TQikStockLayoutManagers</code> or a custom layout type. If none is 
	specified, a RowLayoutManager will be used, but you won't be able to specify 
	layout data for any of the controls. (Optional) */
	LONG layout_manager_type = -1;
	/** The resource used by the layout manager in its 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_ROW_LAYOUT</code> 
	for <code>EQikRowLayoutManager</code>. (Mandatory if 
	<code>layout_manager</code> is specified) */
	LLINK layout_manager = 0;
	/** The controls in the container. Must be any of the
	<code>QIK_CONTAINER_ITEM</code>'s (Optional) */
	STRUCT controls[];
	}

/**
The struct used by <code>CQikScrollableContainer::InitializeFromResourceL()</code> 
to set/change the controls the container contains and how they are laid out.

Is referenced by <code>QIK_VIEW_PAGE.page_content</code> and 
<code>QIK_CONTAINER_ITEM.container</code> (and all the other container items).

@publishedAll
@released
*/
STRUCT QIK_SCROLLABLE_CONTAINER_SETTINGS
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 0;
	/** Flags used to make changes to the default behavior. The available flags 
	are defined in <code>Qikon.hrh</code>. (Optional) */
	LONG flags = (0x00000001  | 0x00000002 	| 0x00800000  | 0x01000000 	| 0x04000000  | 0x20000000 	| 0x00002000 ) ;
	/** The type the layout manager used by the container, either a 
	<code>TQikStockLayoutManagers</code> or a custom layout type. If none is 
	specified, a RowLayoutManager will be used, but you won't be able to specify 
	layout data for any of the controls. (Optional) */
	LONG layout_manager_type = -1; 
	/** The resource used by the layout manager in its 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_ROW_LAYOUT</code> 
	for <code>EQikRowLayoutManager</code>. (Mandatory if
	<code>layout_manager</code> is specified) */
	LLINK layout_manager = 0;
	/** The controls in the container. Must be any of the
	<code>QIK_CONTAINER_ITEM</code>'s (Optional)*/
	STRUCT controls[];
	}

/**
An item describing a control to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* the control is specified in the <code>QIK_CONTROL_COLLECTION</code>, or
* the control factory only needs the unique handle to create the control, and
* you want to specify the layout data as a link (or no layout data at all)

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 0;
	/** The unique handle (unique within the view) of the control
	(<code>CCoeControl::UniqueHandle()</code>). Is used to reference a specific
	<code>QIK_CONTROL</code> in the control collection, or to tell a control 
	factory which control to create. (Mandatory) */
	LONG unique_handle = -1;
	/** The layout data specified for the control. Must be of the type expected 
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Optional) */
	LLINK layout_data = 0;
	}

/**
An item describing a control to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* you don't want to use a <code>QIK_CONTROL_COLLECTION</code>, and
* you want to reference the resource struct of the control through a link, or
* you don't want to create the control using resources, and
* you want to specify the layout data as a link (or no layout data at all)

This type of container item is normally used when you don't want to use the 
<code>QIK_CONTROL_COLLECTION</code>.

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_CI_LI
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 1;
	/** The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) */
	LONG unique_handle = -1;
	/** The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory for controls created entirely from resource files, otherwise
	depends on the control factories) */
	LONG type = -1;
	/** The flags from <code>TQikCtrlItemFlags</code> that controls the 
	creation of the control. (Optional) */
	LONG itemflags = 0;
	/** The resource struct that is read by the control's 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory for controls created entirely from 
	resource files, otherwise depends on the control factories) */
	LLINK control = 0;
	/** The layout data specified for the control. Must be of the type expected 
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Optional) */
	LLINK layout_data = 0;
	}

/**
An item describing a control to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* you don't want to use a <code>QIK_CONTROL_COLLECTION</code>, and
* you want to specify the control's resource inline, and
* you want to specify the layout data as a link (or no layout data at all)

This type of container item is normally used when you don't want to use the 
<code>QIK_CONTROL_COLLECTION</code> and you want to specify the control struct
inline.

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_CD_LI
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 2;
	/** The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) */
	LONG unique_handle = -1;
	/** The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory) */
	LONG type = -1;
	/** The flags from <code>TQikCtrlItemFlags</code> that controls the 
	creation of the control. (Optional) */
	LONG itemflags = 0;
	/** The resource struct that is read by the control's 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory) */
	STRUCT control;
	/** The layout data specified for the control. Must be of the type expected
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Optional) */
	LLINK layout_data = 0;
	}

/**
An item describing a control to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* the control is specified in the <code>QIK_CONTROL_COLLECTION</code>, or
* the control factory only needs the unique handle to create the control, and
* you want to specify the layout inline

This struct is exactly the same as <code>QIK_CONTAINER_ITEM</code>, besides that 
the layout data is specified inline.

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_LD
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 3;
	/** The unique handle (unique within the view) of the control
	(<code>CCoeControl::UniqueHandle()</code>). Is used to reference a specific
	<code>QIK_CONTROL</code> in the control collection, or to tell a control 
	factory which control to create. (Mandatory) */
	LONG unique_handle = -1;
	/** The layout data specified for the control. Must be of the type expected 
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Mandatory) */
	STRUCT layout_data;
	}

/**
An item describing a control to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* you don't want to use a <code>QIK_CONTROL_COLLECTION</code>, and
* you want to reference the resource struct of the control through a link, or
* you don't want to create the control using resources, and
* you want to specify the layout data inline

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_CI_LD
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 4;
	/** The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) */
	LONG unique_handle = -1;
	/** The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory for controls created entirely from resource files, otherwise
	depends on the control factories)
	*/
	LONG type = -1;
	/** The flags from <code>TQikCtrlItemFlags</code> that controls the 
	creation of the control. (Optional) */
	LONG itemflags = 0;
	/** The resource struct that is read by the control's 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory for controls created entirely from 
	resource files, otherwise depends on the control factories) */
	LLINK control = 0;
	/** The layout data specified for the control. Must be of the type expected 
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Mandatory) */
	STRUCT layout_data;
	}

/**
An item describing a control to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use thie struct when:
* you don't want to use a <code>QIK_CONTROL_COLLECTION</code>, and
* you want to specify the control's resource inline, and
* you want to specify the layout data inline

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_CD_LD
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 5;
	/** The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) */
	LONG unique_handle = -1;
	/** The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory) */
	LONG type = -1;
	/** The flags from <code>TQikCtrlItemFlags</code> that controls the 
	creation of the control. (Optional) */
	LONG itemflags = 0;
	/** The resource struct that is read by the control's 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory) */
	STRUCT control;
	/** The layout data specified for the control. Must be of the type expected
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Mandatory) */
	STRUCT layout_data;
	}


/**
An item describing a nested container to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* the control is a container (inheriting from <code>CQikContainerBase</code>), and
* the control is specified in the <code>QIK_CONTROL_COLLECTION</code>, or
* the control factory only needs the unique handle to create the control

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_NESTED_CONTAINER
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 6;
	/** The unique handle (unique within the view) of the control
	(<code>CCoeControl::UniqueHandle()</code>). Is used to reference a specific
	<code>QIK_CONTROL</code> in the control collection, or to tell a control 
	factory which control to create. (Mandatory) */
	LONG unique_handle = -1;
	/** The layout data specified for the control. Must be of the type expected 
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Optional) */
	LLINK layout_data = 0;
	/** The struct must be supported by the container's 
	<code>InitializeFromResourceL()</code> (<code>QIK_CONTAINER_SETTINGS</code> for
	<code>EQikCtContainer</code>, <code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>
	for <code>EQikCtScrollableContainer</code>). (Mandatory) */
	LLINK container = 0;
	}

/**
An item describing a nested container to be used in a container. Used in 
<code>QIK_CONTAINER_SETTINGS</code> and 
<code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>.

Use this struct when:
* the control is a container (inheriting from <code>CQikContainerBase</code>), and
* you don't want to use a <code>QIK_CONTROL_COLLECTION</code>

@publishedAll
@released
*/
STRUCT QIK_CONTAINER_ITEM_NESTED_CONTAINER_CI_LI
	{
	/** The type of the struct. (Do not use!) */
	BYTE struct_type = 7;
	/** The unique handle (unique within the view) of the control. Is used to set
	the control's <code>UniqueHandle()</code> and is sent to the control
	factories. (Optional) */
	LONG unique_handle = -1;
	/** The control type of the control. Such as the items in
	<code>TQikStockControls</code> defined in <code>QikStockControls.hrh</code>.
	(Mandatory for controls created entirely from resource files, otherwise
	depends on the control factories) */
	LONG type = -1;
	/** The flags from <code>TQikCtrlItemFlags</code> that controls the 
	creation of the control. (Optional) */
	LONG itemflags = 0;
	/** The resource struct that is read by the control's 
	<code>ConstructFromResourceL()</code>, such as <code>QIK_SLIDER</code> for 
	<code>EQikCtSlider</code>. (Mandatory for controls created entirely from 
	resource files, otherwise depends on the control factories) */
	LLINK control = 0;
	/** The layout data specified for the control. Must be of the type expected 
	by <code>SetLayoutDataFromResourceL()</code> of the layout manager specified 
	in the container, such as <code>QIK_ROW_LAYOUT_DATA</code> for 
	<code>EQikRowLayoutManager</code>. (Optional) */
	LLINK layout_data = 0;
	/** The struct must be supported by the container's 
	<code>InitializeFromResourceL()</code> (<code>QIK_CONTAINER_SETTINGS</code> for
	<code>EQikCtContainer</code>, <code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code>
	for <code>EQikCtScrollableContainer</code>). (Mandatory) */
	LLINK container = 0;
	}

//MaheshC Start
/**
 A control that encapulates the image viewer api into a control.
CQikImageCapture supports image formats like BMP, GIF, JPEG, ETC. 
It can take image from camera.

@publishedAll
@released
@see CQikImageCapture
@see CQikImagePreview
@since UIQ 3.0
*/
STRUCT QIK_IMAGE_CAPTURE
	{
	/**
	 * The width of the control in pixels
	 */
	WORD width=0;

	/**
	 * The height of the control in pixels
	 */
	WORD height=0;

	/**
	 * Is used to customize the control. The available flags are defined in qikon.hrh.
	 * Useful flags are @see EQikImageCaptureTile, @see EQikImageCaptureStretch, @see EQikImageCaptureBestFit and @see EQikImageCaptureNoAction.
	 * @see CQikImagePreview::TWallpaperPreviewFlags
	 */
	WORD preview= 0x20 ;

	/**
	 * The filename and path of the image source.
	 */
	LTEXT imageFilePath="";

	/**
	 * Defines the entry modes for the <code>CQikImageCapture</code>.
	 * @see CQikImageCapture::TEntryMode
	 * @see TQikImageCaptureEntryMode
	 */
	WORD entryMode=EQikImageCapturePassiveMode;

	/**
	 * Sets flags for configuration of the select file dialog.
	 * Possible values are <code>EQikImageCaptureEnableAutomaticConsumeLock</code> and <code>EQikImageCaptureEnableForwardableLock</code>.
	 * @see EQikImageCaptureEnableAutomaticConsumeLock
	 * @see EQikImageCaptureEnableForwardableLock
	 */
	WORD selectFileFlags=0;
	}

/**
@internalTechnology
@released
*/
STRUCT QIK_FILE_FOLDER_LOCALIZATION
	{
	LTEXT path		= "";
	LTEXT localizedName	= "";
	}

/**
@internalTechnology
@released
*/
STRUCT QIK_DIRECTORY_MAPPING
	{
	LTEXT mapFromPath	= "";
	LTEXT mapFromVirtualFolder	= "";
	LTEXT mapToPhysicalPath	= "";
	LTEXT filterMimeType	= "";
	}

/**
Example content might be animations, themed skins or icons, application
icons or non-native bitmap formats such as PNG or JPEGs.

@publishedAll
@released
<see-also>
  <api-item>CQikContent</api-item>
</see-also>

@see QIK_CONTENT_MBM
*/
STRUCT QIK_CONTENT
	{
 	/**
	 * For internal use only, application developers must not change this.
	 * Version number and type of content, 0 = QIK_CONTENT and 1 = QIK_CONTENT_MBM
	 */
	BYTE version = 0;

	/**
	 * URI for the content.
	 */
	LTEXT uri = "";
	}

/**
Example content might be themed skins or icons, application icons or non-native bitmap formats such as PNG, JPEGs, GIF and GIF animations.

@publishedAll
@released
<see-also>
  <api-item>CQikContent</api-item>
</see-also>
@see QIK_CONTENT
*/
STRUCT QIK_CONTENT_MBM
	{
	/**
	 * For internal use only, application developers must not change this.
	 * Version number and type of content, 0 = QIK_CONTENT and 1 = QIK_CONTENT_MBM
	 */
	BYTE version = 1;

	/**
	 * The file from which the image is created
	 */
	LTEXT bmpfile="*";

	/**
	 * The ID of the bitmap to use in the image
	 */
	WORD bmpid;

	/**
	 * The ID of the bitmap mask to use in the image.
	 * This can be the same as bmpid if you wish to use the same bitmap as both the bitmap and mask.
	 * -1 signifies that no mask is used.
	 */
	WORD bmpmask=0xffff;
	}

/**
This resource specifies an image control. For more information see the <code>CEikImage</code> class description.
The picture is specified in the element <code>content</code> which is of type <code>QIK_CONTENT</code>.

@publishedAll
@released
<see-also>
  <api-item>CEikImage</api-item>
  <api-item language="rsrc">QIK_CONTENT</api-item>
  <api-item language="rsrc">QIK_CONTENT_MBM</api-item>
</see-also>
*/
STRUCT QIK_IMAGE
	{
	/**
	 For internal use only, application developers must not change this.
	 Version number , 0 = IMAGE and 1 = QIK_IMAGE
	 @see IMAGE
	 */
	BYTE version = 1;

	/**
	 Specifies the Horizontal alignment of the image.
     <see-also>
       <api-item>EEikLabelAlignHCenter</api-item>
       <api-item>TGulHAlignment</api-item>
     </see-also>
	 */
	WORD horiz_align= 0x01 ;

	/**
	 Specifies the vertical alignment of the image.
     <see-also>
       <api-item>EEikLabelAlignVTop</api-item>
       <api-item>TGulVAlignment</api-item>
     </see-also>
	 */
	WORD vert_align= 0x00 ;

	/**
	 Specifies the image, use a resource struct of type QIK_CONTENT or QIK_CONTENT_MBM
	 @see QIK_CONTENT
	 @see QIK_CONTENT_MBM
	 */
	STRUCT content;

	/**
	 Currently not used.
	 */
	LONG flags;

	/**
	 Currently not used.
	 */
	LLINK extension = 0;
	}

/**
This resource specifies a specific configuration supported by the <code>QIK_DIALOG</code>.
It specifies the configuration, settings for the scrollable container and a set of commands used in the configuration.

@publishAll
@released
@see CQikSimpleDialog
@see QIK_DIALOG
*/
STRUCT QIK_DIALOG_CONFIGURATION
	{
	/**
	 * For internal use only, application developers must not change this.
	 */
	BYTE	version = 0;

	/**
	 * A UI configuration encoded into a unique identifier. Example usage:
	 * ui_config_mode = EQikScreenModePortrait | EQikOrientationNormal | EQikUiStyleMenubar | EQikTouchScreenYes;
	 * @see KQikPenStyleTouchPortrait
	 * @see EQikScreenModePortrait
	 */
	LONG	ui_config_mode = 0;

	/**
	 * Id of the <code>QIK_SCROLLABLE_CONTAINER_SETTINGS</code> resource struct.
	 * @see QIK_SCROLLABLE_CONTAINER_SETTINGS
	 */
	LLINK	container = 0;

	/**
	 * Id of the <code>QIK_COMMAND_LIST</code> resource struct. Specifies the commands used in this configuration.
	 * @see QIK_COMMAND_LIST
	 */
	LLINK	command_list = 0;
	}

/**
This resource specifies a simple dialog with just one page(without tabs) and no scrollbar.
The dialog is of type <code>CQikSimpleDialog</code>.

@publishAll
@released
@see CQikSimpleDialog
*/
STRUCT QIK_DIALOG
	{
	/**
	 * For internal use only, application developers must not change this.
	 */
	BYTE	version = 0;

	/**
	 * Currently not used.
	 */
	LONG	flags = 0;

	/**
	 * The title of the dialog.
	 */
	LTEXT	title = "";

	/**
	 * Id of the <code>QIK_CONTENT</code> resource struct.
	 * @see QIK_CONTENT
	 */
	LLINK	icon = 0;

	/**
	 * A resource of type <code>ARRAY</code> consisting of a number of <code>QIK_DIALOG_CONFIGURATION</code> resources.
	 * @see QIK_DIALOG_CONFIGURATION
	 */
	STRUCT	configurations[];

	/**
	 * Id of the <code>QIK_CONTROL_COLLECTION</code> resource struct.
	 * @see QIK_CONTROL_COLLECTION
	 */
	LLINK	controls = 0;
	}

/**
Ties an application UID and a view UID to a message.
Used by <code>CQikChangeScreenModeToContinueDlg</code> to display a specific message for the service to be started.
The application can choose to launch this dialog before switching to a view which doesn't support the current screen mode.
As an example the message can tell the user to change screen mode to be able to launch the application and view.

@publishedAll
@released
@see CQikChangeScreenModeToContinueDlg
*/
STRUCT QIK_CHANGE_SCREEN_MODE_TO_CONTINUE_DLG_MESSAGE
	{
	/**
	 * The UID of the application the user wants to launch.
	 */
	LONG appUid=0;

	/**
	 *  The UID of the view the user wants to launch.
	 */
	LONG viewUid=0;

	/**
	 *  The message to display.
	 */
	LTEXT message="";
	}
	
/**
@publishedAll
@released
*/
STRUCT QIK_UI_CONFIG_RESOURCE
	{
	LONG ui_config_mode;
	LLINK resource;
	}

/**
The struct used to specify a view's fullscreen properties.
To be linked from a <code>QIK_VIEW</code>

@publishedAll
@released
*/
STRUCT QIK_VIEW_MODE
	{
	/** For internal use only, application developers must not change this.	*/
	BYTE version = 0;

	/** (1) indicates that the screen furniture will be displayed, (0) that it will not. */
	BYTE app_titlebar = 1;
	BYTE button_or_softkeybar = 1;
	BYTE statusbar = 1;
	BYTE toolbar = 1;
	}

//  __QIKON_RH__
# 9 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikListBox.rh" 1
// QikListBox.rh
//
// Copyright © Symbian Software Ltd 2004-2005. All rights reserved.
// Created for UIQ 3.0

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.hrh" 1
// EIKON.HRH
// Copyright (c) Symbian Software Ltd 1997-2005.  All rights reserved.

// To get rid of the complaint from doc buld tool about unset define.
/** @internalTechnology @released */
# 673 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\eikon.hrh"

# 6 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikListBox.rh" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\qiklistbox.hrh" 1
// QikListBox.hrh
//
// Copyright (c) Symbian Software Ltd 2004-2005.  All rights reserved.
// Created for UIQ 3.0




/**
Indicate that the resource property should use default list box value.
@publishedAll
@released
*/


/**
Indicate default layout id.
@publishedAll
@released
*/


/**
Parameter is not applicable.
@publishedAll
@released
*/


/**
This is only used internally since external slot ids must be positive.
@publishedAll
@released
*/


/**
Point is outside the component area.
@publishedAll
@released
*/


/**
Used as type for <code>QIK_LISTBOX_ROW</code> and <code>QIK_LISTBOX_COLUMN</code>
to indicate if the slot has content or is just a parent for other rows or columns.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxContentsType
	{
	/** List box parent of other rows or columns */
	EQikListBoxParent,
	
	/** Icon content */
	EQikListBoxIcon,
	
	/** Thumbnail content */
	EQikListBoxThumbnail,
	
	/** Text content */
	EQikListBoxText,
	
	/** Content swaping left arrow */
	EQikListBoxLeftArrow,
	
	/** Content swaping right arrow*/
	EQikListBoxRightArrow,
	
	/** Separator content*/
	EQikListBoxSeparatorText
	};

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
The <code>QIK_LISTBOX_DATA</code> can have this type to indicate that
a listbox item is a separator and thus cannot be selected

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxDataFlags
	{
	/** Flag to indicate that a <code>QIK_LISTBOX_DATA</code> is a separator or not. */
	EQikListBoxSeparator 	= 0x00000001 ,
	
	/** Flag to indicate that a <code>QIK_LISTBOX_DATA</code> is disabled or not. */
	EQikListBoxDisabled		= 0x00000002 ,
	
	/** Flag to indicate that a <code>QIK_LISTBOX_DATA</code> is emphasized or not. */
	EQikListBoxEmphasis		= 0x00000004 ,
	
	/** Flag to indicate that a <code>QIK_LISTBOX_DATA</code> is dimmed or not. */
	EQikListBoxDimmed		= 0x00000008 ,

	/** Flag to indicate that a <code>QIK_LISTBOX_DATA</code> is unselectable or not. */
	EQikListUnselectable	= 0x01000000 
	};

/**
Defines what type of view the listbox will will create. If EQikCustomListBox is defined,
the view will not be created automatically. The application is responsible for creating
the custom view and then attach it to the listbox before ConstructFromResourceL is called.
If the listbox is constructed manually no specific order is needed.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxType 
 	{
 	/** The listbox will create a column list box view */
 	EQikRowListBox,
 	
 	/** The listbox will create a grid list box view */
 	EQikGridListBox,
 	
 	/** No view is selected and the application is responsible for creating the custom view */
 	EQikCustomListBox	= 0x7F
 	};


/**
It is possible to set the orientation of the selector (usually a checkbox).
If the selector is overridden or painted, the values might not have any significance.

When the listbox is mirrored the invert bit makes it easy to change from left to right etc.

@since UIQ 3.0
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/
enum TQikListBoxSelectorOrientation
	{
	/** When set, the multiple selection indication will be displayed on the left side of the listbox */
	EQikListBoxMultipleSelectionLeft			= 0x02 ,

	/** When set, the multiple selection indication will be displayed on the right side of the listbox */			
	EQikListBoxMultipleSelectionRight			= 0x03 ,

	/** When set, the multiple selection indication will be displayed in the top left corner of the selected slot */
	EQikListBoxMultipleSelectionSlotTopLeft		= 0x04 ,

	/** When set, the multiple selection indication will be displayed in the top right corner of the selected slot */
	EQikListBoxMultipleSelectionSlotTopRight	= 0x05 ,

	/** When set, the multiple selection indication will be displayed in the bottom left corner of the selected slot */
	EQikListBoxMultipleSelectionSlotBottomLeft	= 0x06 ,

	/** When set, the multiple selection indication will be displayed in the bottom right corner of the selected slot */
	EQikListBoxMultipleSelectionSlotBottomRight	= 0x07 ,

	/** When set, the multiple selection indication will be displayed in the center of the selected slot */
	EQikListBoxMultipleSelectionSlotCenter		= 0x08 ,
	
	/** When set, the multiple selection indication will not be displayed */
	EQikListBoxMultipleSelectionNone			= 0x09 
	};

/**
Used for specifying population direction. I.E. populate
view from top to bottom or from bottom to top.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxPopulationDirection
	{
	/** 
	The TopDataIndex has been modified, view should be populated starting from it 
	*/
	EQikListBoxPopulateForward,
	
	/** 
	The BottomDataIndex has been modified, view should be populated starting from it
	*/
	EQikListBoxPopulateReverse,
	
	/** 
	No change to Top- or BottomDataIndex was made instead other actions caused
	the need for re-populating the view. The view itself should be able to decide
	how to populate.
	*/
	EQikListBoxPopulateAutomatic
	};

/**
Standard property for listbox settings. Used when
a setting can be system, on or off.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxProperty
	{
	/** Let the system decide */
	EQikListBoxSystem,
	
	/** The property is on */
	EQikListBoxOn,
	
	/** The property is off*/
	EQikListBoxOff
	};


/**
Used for setting Interlacing for an Column.
Interlacing is when a Column "borrows" space from a neighbouring Column.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxColumnInterlacing
	{
	/** Do not borrow space from neighbouring Columns */
	EQikInterlacingDisabled,
	
	/** Borrow space from the next column */
	EQikInterlacingExpandNext,
	
	/** Borrow space from the previous column */
	EQikInterlacingExpandPrevious	
	};

/**
From lafpublc.h, only used in rh file.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikScrollBarVisibility
	{
	/** Do not use scrollbar */
	EQikScrollBarOff,
	
	/** Use scrollbar always */
	EQikScrollBarOn,
	
	/** Use scrollbar when needed */
	EQikScrollBarAuto
	};
	
/**
@publishedAll
@released
*/
enum TQikListBoxScrollDirection
	{
	/** Standard vertical scrollbar at side*/
	EQikVerticalDirection,
	
	/** Horizontal scrollbar at bottom*/
	EQikHorizontalDirection	
	};

/**
From CoeLayout.h. Settings for how to handle mirroring, i.e. languages using right-to-left
@publishedAll
@released
*/
enum TQikListBoxMirroring 
	{
	/** Mirror depending on current application language. */
	EAutoMirror,
	/** Force mirroring of the layout, disregard application language. */
	EMirror,
	/** Force no mirroring of the layout, disregard application language. */
	ENoMirroring
	};

/**
@publishedAll
@released
*/


/**
@publishedAll
@released
*/


/**
@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxLayoutFlags
	{
	/** 
	When layout is calculated it does not snap rows and columns to the system default row height. 
	*/
	EQikListBoxLayoutIsRowAware = 0x01 ,
	/**
	The default behavior is to not show a selector for items created as "unselectable", in a
	multiple select enabled List Box. By enabling this flag a dimmed selector will be showed for
	"unselectable" items.
	*/
	EQikListBoxLayoutShowUnselectableSelector = 0x02 
	}; 
	
/**
Used to specify the alignment of text within a row or column.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxTextAlignment
	{
	/** Aligns the text vertically upon a calculated baseline*/
	EQikListBoxTextAlignLeft,
	/** Aligns the text vertically upon a calculated baseline*/
	EQikListBoxTextAlignCenter,
	/** Aligns the text vertically upon a calculated baseline*/
	EQikListBoxTextAlignRight,
	/** Aligns the text vertically centered withins its element*/
	EQikListBoxTextAlignLeftVCenter,
	/** Aligns the text vertically centered withins its element*/
	EQikListBoxTextAlignCenterVCenter,
	/** Aligns the text vertically centered withins its element*/
	EQikListBoxTextAlignRightVCenter
	};
	
	
/**
Used to specify the logical size of content types image and thumbnail.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxContentTypeLogicalSize
	{
	/**
	Size of a small icon as defined system wide.
	Applicable to thumbnail content type as well.
	
	@see TQikLayoutValues
	*/
	EQikListBoxSizeSmallIcon, 
	
	/**
	Size of a medium icon as defined system wide.
	Applicable to thumbnail content type as well.
	
	@see TQikLayoutValues
	*/
	EQikListBoxSizeMediumIcon,
	
	/**
	Size of a large icon as defined system wide.
	Applicable to thumbnail content type as well.
	
	@see TQikLayoutValues
	@deprecated
	*/
	EQikListBoxSizeLargeIcon,
	
	/**
	Will map to the size in pixels of the actual icon bitmap.
	Not applicable to thumbnail content type.
	*/
	EQikListBoxSizeFromBitmapIcon,
		
	/**
	Size of a medium thumbnail as defined system wide.
	Applicable to icon content type as well.
	
	@see TQikLayoutValues
	*/
	EQikListBoxSizeMediumThumbnail,
	
	/**
	Size of a large thumbnail as defined system wide.
	Applicable to icon content type as well.
	
	@see TQikLayoutValues
	*/
	EQikListBoxSizeLargeThumbnail,
	
	/**
	Will make the thumbnail as big as the column or row it is placed in.
	When using this size to size a thumbnail content type, specifying a column/row
	to use EQikListBoxColWidthFromContentType/EQikListBoxRowHeightFromContentType is
	illegal.
	Not applicable to icon content type.
	*/
	EQikListBoxSizeThumbnailFill,
	
	/**
	Gives the opportunity to specify a custom fixed size on both icon and thumbnail.
	*/
	EQikListBoxSizeCustom
	};
	
/**
Used to specify the type of width a column uses.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxColumnSizeType
	{
	/**
	Makes the column as wide as the content type is calculated to be. Not 
	applicable when content type size is EQikListBoxSizeThumbnailFill.
	*/
	EQikListBoxColWidthFromContentType,
	
	/**
	Makes the column grab a portion of the free remaining width (remaining when
	fixed width columns has gotten their size). The width ratio between columns
	on the same level using grab is set using the width_value property of the
	QIK_LISTBOX_COLUMN struct. The value must be higher than 0.
	*/
	EQikListBoxColWidthGrab,
	
	/**
	Makes the column a specific number of pixels wide. The actual pixels are set
	using the width_value property of the QIK_LISTBOX_COLUMN struct.
	*/
	EQikListBoxColWidthPixels,
	
	/**
	This type makes the column get its width from the rows it is parent to. The column
	width will be that of the widest row, rest of the rows will be expanded so that all rows
	are equally wide.
	*/
	EQikListBoxColWidthFromChildTree
	};
	
/**
Used to specify the type of height a row uses. Note
that a row aware layout might override values or types used.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxRowSizeType
	{
	/**
	Makes the row as high as the content type is calculated to be. Not 
	applicable when content type size is EQikListBoxSizeThumbnailFill.
	*/
	EQikListBoxRowHeightFromContentType,
	
	/**
	Makes the row grab a portion of the free remaining height (dependent on
	height limitations put on the row by rows higher up in tree). The height ratio
	between rows on the same level using grab is set using the height_value 
	property of the	QIK_LISTBOX_ROW struct. The value must be higher than 0.
	*/
	EQikListBoxRowHeightGrab,
	
	/**
	Makes the row a specific number of pixels high. The actual pixels are set
	using the height_value property of the QIK_LISTBOX_ROW struct.
	*/
	EQikListBoxRowHeightPixels,
	
	/**
	This type makes the row get its height from the columns it is parent to. The row
	height will be that of the highest column, rest of the columns will be 
	expanded so that all columns are equally high.
	*/
	EQikListBoxRowHeightFromChildTree
	};
	
/**
Used to specify the type of height of the layout.

@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxLayoutSizeType
	{
	/**
	Makes the layout and in the end the item fill the entire height of the cell size 
	provided by the list box view. In a row view the cell size height would be the 
	entire visible height, i.e it is not a good idea to use this type in a row view.
	In a list box grid view the cell size height is the height of a grid cell, making 
	it useful to use this type to dynamically fill the entire height of a grid cell.	 
	*/
	EQikListBoxLayoutHeightFill,
	
	/**
	Makes the layout height fixed in pixels, should only be applicable to use
	in custom amde views.
	*/
	EQikListBoxLayoutHeightPixels,
	
	/**
	Makes the layout and in the end the item as high as the columns sub tree calculated
	itself to be. Should always be used in a list box using row view.
	*/
	EQikListBoxLayoutHeightFromColumns
	};

/**
The different logical sizes the font in the listbox can use.

Note! This enum must correspond to the enum TFlags in TCoeFont. Changes of the items in TFlags
will result in wrong sizes of the font.

@see TCoeFont::TLogicalSize
@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxFontLogicalSize 
	{ 
	EQikListBoxFontExtraSmall, 
	EQikListBoxFontSmall, 
	EQikListBoxFontMedium, 
	EQikListBoxFontLarge, 
	EQikListBoxFontExtraLarge, 
	EQikListBoxFontUndefinedSize = -1
	};         

/**
The different styles the font in the listbox can use.

@see TCoeFont::TStyle
@since UIQ 3.0
@publishedAll
@released
*/
enum TQikListBoxFontStyle 
	{
	EQikListBoxFontPlain = 0x00, 
	EQikListBoxFontItalic = 0x01, 
	EQikListBoxFontBold = 0x02, 
	EQikListBoxFontSuper = 0x04, 
	EQikListBoxFontSub = 0x08 
	}; 

/**
@publishedAll
@released
*/
enum TQikListBoxHighlightStyle
	{
	EQikListBoxHighlightSolid,
	EQikListBoxHighlightFrame
	};

/**
Setting for text scrolling.
@publishedAll
@released
*/
enum TQikListBoxTextScrollSetting
	{
	/** No scrolling of the text*/
	EQikListBoxTextScrollOff,
	/** The text will be scolled when the item containing the text content type is highlighted*/
	EQikListBoxTextScrollWhenHighlighted
	};

// __QIKLISTBOX_HRH__
# 7 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikListBox.rh" 2


/**
A row can contain one or more columns.
Type of height and a height value for applicable types are used to define
the height of a row. The row will be as wide as its parent column.

@since UIQ 3.0
@publishedAll
@released
*/	
STRUCT QIK_LISTBOX_ROW
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =					1;
	
	/**
	Array of sub columns for this row. Rows can either have
	sub columns or a component, not both. If the row has no component
	it must contain at least one column.
	*/
	STRUCT columns[];		
	
	/**
	The slot id of this row. All rows must be supplied with a non-negative 
	unique(for the layout) slot id.
	*/	
	LONG slot_id = 					-1 ;			
	
	/**
	To define a component this column will contain, see 
	QIK_LISTBOX_X_TYPE STRUCTs.

	@see QIK_LISTBOX_ICON_TYPE
	@see QIK_LISTBOX_THUMBNAIL_TYPE
	@see QIK_LISTBOX_TEXT_TYPE
	@see QIK_LISTBOX_LEFT_ARROW_TYPE
	@see QIK_LISTBOX_RIGHT_ARROW_TYPE
	*/
	STRUCT type;		

	/**
	Sets the type of height that will be used when calculating the height of 
	this row.
	Default is EQikListBoxRowHeightPixels.
	
	@see TQikListBoxRowSizeType
	*/	
	BYTE height_type =				-1 ;
	
	/**
	The height value of this row. Applicable for height_types of 
	EQikListBoxRowHeightGrab and EQikListBoxRowHeightPixels.
	Default is 50.
	*/
	WORD height_value =				-1 ;
	
	/**
	The inner margins of this row. The inner margins sets the margins between
	the row´s edges and it´s content.
	Default is 0 for all margins.
	*/
	BYTE top_margin =				-1 ;
	BYTE bottom_margin =			-1 ;
	BYTE left_margin =				-1 ;
	BYTE right_margin =				-1 ;
	}

/**
A column can contain one or more rows.
The type of width and width value are used to define the width of a column.
A column will be as high as its parent row, in the case of the top-level 
columns in the layout, these columns will get their hight depending on the 
layout height type.

@since UIQ 3.0
@publishedAll
@released
*/	
STRUCT QIK_LISTBOX_COLUMN
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =						1;				
	
	/**
	Array of sub rows to this column. Columns can either have
	sub rows or a component, not both. If the column has no component
	it must contain at least one row.
	*/							
	STRUCT rows[];
	
	/**
	The priority of this column if it utilizes column interlacing. If two
	columns wants to interlace on the same column this priority determines 
	who get´s served first.
	Default is 0;
	*/											
	BYTE interlacing_grab_priority =	-1 ;
	
	/**
	Setting for turning column interlacing on or off and determine if
	this column will try to interlace on the previous or next column.
	Only columns that contain a component can interlace, composit columns
	(columns with sub rows) can not.
	Default is EQikInterlacingDisabled.
	
	@see TQikListBoxColumnInterlacing
	*/
	BYTE interlacing =					-1 ;
	
	/**
	Sets whether this column will be hidden if the component (or sub tree) it
	contains has no data to display.
	Default is 0, meaning the column will not be hidden. 1 will enable hide 
	empty.
	*/
	BYTE hide_empty = 					-1 ;
	
	/**
	The slot id of this column. All columns must be supplied with a 
	non-negative unique	(for the layout) slot id.
	*/
	LONG slot_id = 						-1 ;
	
	/**
	To define a component this column will contain, 
	see QIK_LISTBOX_X_TYPE STRUCTs.

	@see QIK_LISTBOX_ICON_TYPE
	@see QIK_LISTBOX_THUMBNAIL_TYPE
	@see QIK_LISTBOX_TEXT_TYPE
	@see QIK_LISTBOX_LEFT_ARROW_TYPE
	@see QIK_LISTBOX_RIGHT_ARROW_TYPE
	*/
	STRUCT type;
	
	/**
	Sets the type of width used when calculating column width.
	Default is EQikListBoxColWidthFromContentType, this will make the column
	as wide as its content type is calculated to be.
	
	@see TQikListBoxColumnSizeType
	*/
	BYTE width_type = 					-1 ;

	/**
	The width value of this column. Only applicable for width types of
	EQikListBoxColWidthGrab and EQikListBoxColWidthPixels.
	Default is 0.
	*/
	WORD width_value =							-1 ;

	/**
	The inner margins of this column. The inner margins sets the margins 
	between	the column´s edges and it´s content.
	Default is 0 for all margins.
	*/
	BYTE top_margin =					-1 ;
	BYTE bottom_margin =				-1 ;
	BYTE left_margin =					-1 ;
	BYTE right_margin =					-1 ;
	}

/**
Contains specific settings for a parent layout component.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_PARENT_TYPE
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=1;
	
	/**
	The type of this component struct. Do not change.
	*/	
	BYTE type=EQikListBoxParent;
	}

/**
Contains specific settings for an icon layout component.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_ICON_TYPE
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =				1;
	
	/**
	The type of this component struct. Do not change.
	*/	
	BYTE type =					EQikListBoxIcon;
	
	/**
	The size of this icon component.
	Default is EQikListBoxSizeSmallIcon.
	
	@see TQikListBoxComponentSize
	*/
	BYTE size =					-1 ;
	
	/**
	If size is set to EQikListBoxSizeCustom, the width of
	the component is set here.
	Default is 0.
	*/
	WORD custom_width =			-1 ;

	/**
	If size is set to EQikListBoxSizeCustom, the height of
	the component is set here.
	Default is 0.
	*/
	WORD custom_height =		-1 ;
	}

/**
Contains specific settings for a thumbnail layout component.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_THUMBNAIL_TYPE
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =				1;
	
	/**
	The type of this component struct. Do not change.
	*/
	BYTE type =					EQikListBoxThumbnail;
	
	/**
	The size of this thumbnail component.
	Default is EQikListBoxSizeMediumThumbnail.
	
	@see TQikListBoxComponentSize
	*/
	BYTE size = 				-1 ;
	
	/**
	If size is set to EQikListBoxSizeCustom, the width of
	the component is set here.
	Default is 0.
	*/
	WORD custom_width =			-1 ;

	/**
	If size is set to EQikListBoxSizeCustom, the height of
	the component is set here.
	Default is 0.
	*/
	WORD custom_height =		-1 ;
	}

/**
Contains specific settings for a text layout component.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_TEXT_TYPE
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =				2;
	
	/**
	The type of this component struct. Do not change.
	*/
	BYTE type =					EQikListBoxText;
	
	/**
	The minimum number of lines this text component will use.
	Default is 1.
	*/
	BYTE min_num_of_lines = 	-1 ;	
	
	/**
	The maximum number of lines this text component will use.
	max_num_of_lines must be equal or higher than min_num_of_lines.
	Default is 1.
	*/
	BYTE max_num_of_lines = 	-1 ;
	
	/**
	The gap in pixels between lines of text if it uses multiple lines.
	Default behavior is to get this value from the layout settings by 
	the system.
	*/
	BYTE gap_between_lines = 	-1 ;
	
	/**
	The horizontal alignment of this text component within its row/column.
	Default is EQikListBoxTextAlignLeft.
	
	@see TQikListBoxTextAlignment
	*/
	BYTE alignment =			-1 ;

	/**
	The size of the font.

	@see TQikListBoxFontLogicalSize
	*/
	BYTE font_size = 			-1 ;

	/**
	The style of the font.
	
	@see TQikListBoxFontStyle
	*/
	BYTE font_style = 			-1 ;

	/**
	The size of the font when the item is emphasized.

	@see TQikListBoxFontLogicalSize
	*/
	BYTE emphasis_font_size = 	-1 ;

	/**
	The style of the font when the item is emphasized.

	@see TQikListBoxFontStyle
	*/
	BYTE emphasis_font_style =	-1 ;

	/**
	Text scrolling properties.
	
	@see TQikListBoxTextScrollSetting
	*/
	LONG scroll =				-1 ;
	}

/**
Contains specific settings for a left arrow layout component.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_LEFT_ARROW_TYPE
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=1;
	
	/**
	The type of this component struct. Do not change.
	*/
	BYTE type=EQikListBoxLeftArrow;
	
	/**
	Array of slot ids that this arrow will swap.
	*/
	LONG slots_to_swap[];
	}

/**
Contains specific settings for a right arrow layout component.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_RIGHT_ARROW_TYPE
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =		1;							
	
	/**
	The type of this component struct. Do not change.
	*/
	BYTE type =			EQikListBoxRightArrow;
	
	/**
	Array of slot ids that this arrow will swap.
	*/
	LONG slots_to_swap[];
	}

/**
A data item structure can hold icons, thumbnails, and text as content. 
Each item can also be connected to a certain layout through use of the
<code>layoutId</code>.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_DATA
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =		1;

	/**
	The index of the layout to use for this data. Layouts get indexes
	when added to a list box, this is such an index. Layouts added to the
	list box by resource (using QIK_LISTBOX struct´s layouts= property) get
	indexed starting from 0, i.e first layout pair added get index 0, second
	layout pair in the array get index 1 etc. When adding layout by calling
	a AddLayout method of the list box the index is returned by the method.
	
	Default is EQikListBoxDefaultLayoutId, meaning that this data
	will be displayed using the default layout of the list box.
	
	@see CQikListBox
	*/
	LONG layout_id =		-1 ;
	
	/**
	Settings for this data.
	@see TQikListBoxDataFlags
	*/					
	LONG data_flags =		-1 ;
	
	/**
	Array of QIK_LISTBOX_ICON, QIK_LISTBOX_TEXT and QIK_LISTBOX_THUMBNAIL 
	structs.
	@see QIK_LISTBOX_ICON
	@see QIK_LISTBOX_TEXT
	@see QIK_LISTBOX_THUMBNAIL
	*/
	STRUCT data[];
	}

/**
An icon contain information to instantiate an icon object.

The image ID should be a positive value and optionally a mask can be used by
specifying a positive value for the image mask.

This struct is deprecated, use QIK_LISTBOX_ICON_2 instead.

@see QIK_LISTBOX_ICON_2
@since UIQ 3.0
@publishedAll
@deprecated
*/
STRUCT QIK_LISTBOX_ICON
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =		1;	
	
	/**
	The type of this data resource. Do not change.
	*/
	BYTE type =			EQikListBoxIcon;
	
	/**
	The slot id this data will be displayed in. A valid (non negative) slot id 
	must be supplied.
	*/
	LONG slot_id = 		-1 ;	

	/**
	Path to an mbm file.
	*/
	LTEXT image_file =	"*";
	
	/**
	Not used.
	*/
	WORD image_id =		0x0000;
	
	/**
	Not used.
	*/
	WORD image_mask =	0xffff;
	}

/**
Contains information to instantiate an icon object.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_ICON_2
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =		2;	
	
	/**
	The type of this data resource. Do not change.
	*/
	BYTE type =			EQikListBoxIcon;
	
	/**
	The slot id this data will be displayed in. A valid (non negative) slot id 
	must be supplied.
	*/
	LONG slot_id = 		-1 ;
	
	/**
	Either a QIK_CONTENT or QIK_CONTENT_MBM STRUCT to specify the icon.
	@see QIK_CONTENT
	@see QIK_CONTENT_MBMs
	*/
	STRUCT content;
	}

/**
Contains information to instantiate a thumbnail object.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_THUMBNAIL
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =				1;	
	
	/**
	The type of this data resource. Do not change.
	*/	
	BYTE type =					EQikListBoxThumbnail;
	
	/**
	The slot id this data will be displayed in. A valid (non negative) slot id 
	must be supplied.
	*/
	LONG slot_id = 				-1 ;
	
	/**
	Path to the image this data will hold and create thumbnail from.
	*/
	LTEXT image_file =			"";
	}

/**
Contains information to instantiate a text object.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_TEXT
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version =		1;	
	
	/**
	The type of this data resource. Do not change.
	*/	
	BYTE type =			EQikListBoxText;
	
	/**
	The slot id this data will be displayed in. A valid (non negative) slot id 
	must be supplied.
	*/
	LONG slot_id = 		-1 ;
	
	/**
	The text for this text data.
	*/
	LTEXT txt;
	}

/**
This is the main structure for constructing a listbox using a resource.
The parameters for the structure can also be set from code.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=1;

	/**
	The type of list box to create.
	Default is EQikRowListBox.

	@see TQikListBoxType
	*/
	BYTE type = 								-1 ;

	/**
	Visibility setting for vertical scrollbar.
	Default is EQikScrollBarAuto.

	@see TQikScrollBarVisibility
	*/
	BYTE v_scrollbar = 							-1 ;

	/**
	Visibility setting for horizontal scrollbar.
	Default is EQikScrollBarAuto.

	@see TQikScrollBarVisibility
	*/						
	BYTE h_scrollbar = 							-1 ;			
	
	/**
	Link to a view struct used to construct the list box view.
	The view struct should correspond to the type of the list box view. 
	If type	is EQikGridListBox link to a QIK_LISTBOX_GRID_VIEW type resource,
	if type is EQikRowListBox link to a QIK_LISTBOX_ROW_VIEW type resource.
	The default value is 0. This means the list box will construct a view
	corresponding to the type set, i.e if list box type is EQikRowListBox
	the list box will construct the row view with the default values as defined 
	in the QIK_LISTBOX_ROW_VIEW struct. If your list box type is 
	EQikCustomListBox a link to a view resource must be supplied.
	
	@see QIK_LISTBOX_GRID_VIEW
	@see QIK_LISTBOX_ROW_VIEW
	*/
	LLINK view =								0;
	
	/**
	An array of links to QIK_LISTBOX_LAYOUT_PAIR resources.

	@see QIK_LISTBOX_LAYOUT_PAIR
	*/	
	LLINK layouts[];		
	
	/**
	An array of QIK_LISTBOX_DATA items.

	@see QIK_LISTBOX_DATA
	*/
	STRUCT item_data[];
	}
	
/**
Struct used to construct a list box row view.
Views are derived from CQikListBoxViewBase. This base class needs
several of the properties defined in this view struct, these are marked
"Needed by base class". When creating a custom view and a custom view struct,
these "Needed by base class"-properties must be present in the same order as in
this struct.

@since UIQ 3.0
@publishedAll
@released
@see CQikListBoxViewBase
*/
STRUCT QIK_LISTBOX_ROW_VIEW
	{
	/**
	 For internal use only, application developers must not change this.
	Needed by base class.
	*/
	BYTE version=2;	

	/**
	Determines the height that MinimumSize() will return. The row height is 
	retrieved from the central settings. Note that depending on the 
	implementation of TQikLayoutValues the row height might change run-time.
	Needed by base class.

	@see TQikLayoutValues
	*/
	BYTE height_in_rows = 						-1 ;

	/**
	Defaults to true.
	*/
	BYTE highlight_enabled = 					-1 ;
	
	/**
	Defaults to false.
	*/
	BYTE multiple_select =						-1 ;
	
	/**
	The following 4 elements specifies the margins between the listbox edges and
	the item closest to the specific edge inside the listbox.
	Needed by base class.
	All margins default to 0.
	*/			
	BYTE left_margin=							-1 ;
	BYTE right_margin=							-1 ;
	BYTE top_margin=							-1 ;
	BYTE bottom_margin=							-1 ;

	/**
	Sets whether the list box scroll will loop when top or bottom is reached 
	using keys to navigate.
	Default is EQikListBoxSystem.
	Needed by base class.

	@see TQikListBoxProperty
	*/
	BYTE looping = 								-1 ;
	
	/**
	Sets the list box mirroring behavior.
	Default is EAutoMirror.
	Needed by base class.

	@see TQikListBoxMirroring
	*/				
	BYTE mirroring = 							-1 ;		
	
	/**
	Sets the slot upon which incremental match will be used.
	Default is -1, meaning that incremental matching is disabled.
	Needed by base class.
	*/				
	LONG incremental_match_slot = 				-1 ;	
	
	/**
	Sets the max number of characters used in incremental matching.
	Default is 0.
	Needed by base class.
	*/
	LONG max_incremental_matching_characters = 	-1 ;

	/**
	Sets the type of highlight used for this view.
	*/
	BYTE highlight_type	=						EQikListBoxHighlightSolid;
	
	/**
	Centered scrolling makes the highlight move in center of the litbox view
	with an offset,	center_value sets this offset.
	Default is EQikListBoxSystem.
	Needed by base class.

	@see TQikListBoxProperty
	*/							
	BYTE centered_scrolling = 					-1 ;	
	
	/**
	Center value for centered scrolling. -1 centers the highlight. 
	Value > -1 sets the offset from top/bottom. 
	Default is 1.
	Needed by base class.
	*/		
	BYTE center_value = 						-1 ;	
	
	/**
	Sets how to handle partially visible items. Visibillity can be controlled by
	the system or directly.	A partially visible item is a top/bottom item 
	(depending on navigation direction) which doesn't fit as whole in the
	ListBox view.
	Possible values are: EQikListBoxSystem/EQikListBoxOn/EQikListBoxOff
	Default is EQikListBoxSystem.
	Needed by base class.
	
	@see TQikListBoxProperty
	*/			
	BYTE partially_visible_items = 				-1 ;	
	}
	
/**
Struct used to construct a list box grid view. 
Views are derived from CQikListBoxViewBase. This base class needs
several of the properties defined in this view struct, these are marked
"Needed by base class" in struct QIK_LISTBOX_ROW_VIEW. When creating a custom
view and a custom view struct, these "Needed by base class"-properties must be 
present in the same order as in this struct.

@since UIQ 3.0
@publishedAll
@released
@see CQikListBoxViewBase
*/
STRUCT QIK_LISTBOX_GRID_VIEW
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=2;	
	
	/**
	Determines the height that MinimumSize() will return, 
	height_in_rows * "row height". The row height is retrieved from the central 
	settings. Note that depending on the implementation of TQikLayoutValues 
	the row height might change run-time.
	
	@see TQikLayoutValues
	*/
	BYTE height_in_rows = 						-1 ;

	/**
	Defaults to true.
	*/
	BYTE highlight_enabled = 					-1 ;
	
	/**
	Defaults to false.
	*/
	BYTE multiple_select =						-1 ;
	
	/**
	The following 4 elements specifies the margins between the listbox edges and
	the item closest to the specific edge inside the listbox.
	All margins default to 0.
	*/			
	BYTE left_margin=							-1 ;						
	BYTE right_margin=							-1 ;						
	BYTE top_margin=							-1 ;							
	BYTE bottom_margin=							-1 ;		
	
	/**
	Sets whether the list box scroll will loop when top or bottom is reached 
	using keys to navigate.
	Default is EQikListBoxSystem.
	
	@see TQikListBoxProperty
	*/
	BYTE looping = 								-1 ;	
	
	/**
	Sets the list box mirroring behavior.
	Default is EAutoMirror.
	
	@see TQikListBoxMirroring
	*/				
	BYTE mirroring = 							-1 ;		
	
	/**
	Sets the slot upon which incremental match will be used.
	Default is -1, meaning that incremental matching is disabled.
	*/				
	LONG incremental_match_slot = 				-1 ;	
	
	/**
	Sets the max number of characters used in incremental matching.
	Default is 0.
	*/					
	LONG max_incremental_matching_characters = 	-1 ;
	
	/**
	Sets the type of highlight used for this view.
	*/
	BYTE highlight_type	=						EQikListBoxHighlightFrame;
	
	/**
	Number of columns the grid view will be made up of.
	*/
	BYTE grid_columns = 						-1 ;
	
	/**
	Number of rows the grid view will be made up of.
	*/
	BYTE grid_rows = 							-1 ;
	
	/**
	EQikVerticalDirection will make the grid view being laid out vertically,
	this i default.	EQikHorizontalDirection will make the grid view being
	laid out horizontally. The scrollbar will then appear at the bottom of the 
	listbox and the view is scrolled horizontally.
	
	@see TQikListBoxScrollDirection
	*/
	BYTE scroll_direction =						-1 ;
	}
	
/**
Structure for mapping a layoutId, i.e a TQikListBoxStandardLayout enum value, to
a QIK_LISTBOX_LAYOUT_PAIR structure.

Only used internally by the listbox, should not be used by anyone else.

@since UIQ 3.0
@internalTechnology
@released
@see QIK_LISTBOX_LAYOUT_PAIR
@see TQikListBoxStandardLayout
*/
STRUCT QIK_LISTBOX_LAYOUT_MAPPING
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=1;				// Do not change. Internally used.
	
	/**
	Type of layout. TQikListBoxStandardLayout.
	@see TQikListBoxStandardLayout
	*/
	LONG layout_id = 0;			// Type of layout. TQikListBoxStandardLayout.

	/**
	link to a QIK_LISTBOX_LAYOUT resource.
	@see QIK_LISTBOX_LAYOUT
	*/
	LLINK layout = 0;			// link to a QIK_LISTBOX_LAYOUT resource.
	}

/**
Wrapps a normal layout and a corresponding, but optional, highlight layout as a 
layout pair. Layouts can be a mix of standard layouts and custom made ones. 
The elements standard_normal_layout and standard_highlight_layout can be 
assigned a TQikListBoxStandardLayout enum signifying that this standard layout 
will be loaded as either the highlight or normal layout. Defaults are that no 
normal layout is loaded, hence either a standard normal layout or custom normal 
layout must be supplied since a normal layout is required in a layout pair.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_LAYOUT_PAIR
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=1;
	
	/**
	Supply a TQikListBoxStandardLayout enum to use a standard layout as 
	normal layout.
	Default is EQLbxNoLayout, meaning no standard normal layout will be used.

	@see TQikListBoxStandardLayout
	*/								
	LONG standard_normal_layout = -1 ;
	
	/**
	Supply a TQikListBoxStandardLayout enum to use a standard layout as 
	highlight layout.
	Default is EQLbxNoLayout, meaning no highlight layout will be used.

	@see TQikListBoxStandardLayout
	*/	
	LONG standard_highlight_layout = -1 ;
	
	/**
	A link to a QIK_LISTBOX_LAYOUT resource that defines a custom normal 
	layout to use.
	@see QIK_LISTBOX_LAYOUT
	*/
	LLINK custom_normal_layout = 	0;
	
	/**
	A link to a QIK_LISTBOX_LAYOUT resource that defines a custom highlight 
	layout to use.
	@see QIK_LISTBOX_LAYOUT
	*/
	LLINK custom_highlight_layout = 0;
	}

/**
Structure for creating a layout. A layout is a definition of how data
will be visually represented in a list box.

@since UIQ 3.0
@publishedAll
@released
*/
STRUCT QIK_LISTBOX_LAYOUT
	{
	/**
	 For internal use only, application developers must not change this.
	*/
	BYTE version=1;

	/**
	Layout settings. This setting is best left to default, this will make
	the layout utilize row awareness, meaning that sizes will be calculated
	automatically to a large extent, making the layout look-and-feel like
	the rest of the system.
	Default is EQikListBoxLayoutIsRowAware.

	@see TQikListBoxLayoutFlags
	*/											
	LONG flags = 								-1 ;
	
	/**
	This sets the placement of the selector/check box if the list box has
	multiple select turned on. This setting can be used to place the selector
	on the left or right hand side of the items or align it in several different 
	ways within a slot if multiple_selection_area_slot is set.  
	Default is EQikListBoxMultipleSelectionLeft.

	@see TQikListBoxSelectorOrientation
	*/
	BYTE multiple_selection_area_orientation = 	-1 ;	 
	
	/**
	Sets the slot that the selector will be placed in. To be able to
	set multiple_selection_area_orientation to something else than
	left or right a valid slot id in the layout must be specified here.
	Default is -1, meaning the selector will not be placed in any slot.

	@see TQikListBoxSelectorOrientation
	*/
	LONG multiple_selection_area_slot = 		-1 ;
	
	/**
	Sets the spacing between the left edge of the list box to the item. 
	This setting should be used in favour to the margins of the list box since 
	setting those will enforce a gap on the highlight as well. This setting is 
	best left alone since the default behaviour is to get the system value for 
	"edge-to-content" making the application look and feel as the rest of 
	the system.
	Default is to get this value from the system provided layout settings.
	*/
	BYTE left_edge_to_content = 				-1 ;
	
	/**
	Sets the spacing between the right edge of the list box to the item. 
	This setting should be used in favour to the margins of the list box since 
	setting those will enforce a gap on the highlight as well. This setting is 
	best left alone since the default behaviour is to get the system value for 
	"edge-to-content" making the application look and feel as the rest of 
	the system.
	Default is to get this value from the system provided layout settings.
	*/
	BYTE right_edge_to_content = 				-1 ;

	/**
	Sets the spacing/gap between columns on the same level in the layout.
	This setting is best left alone since the default behaviour is to get the 
	system value for "column-gap" making the application look and feel as 
	the rest of the system.
	Default is to get this value from the system provided layout settings.
	*/
	BYTE column_gap =  							-1 ;
	
	/**
	Defines how the height of the entire layout is calculated and what
	restrictions are posed upon the columns it contains.
	Default is EQikListBoxLayoutHeightFromColumns, meaning that the size of
	the entire item is based upon the size of the column sub-tree. In almost
	every case this is the aproperiate type for a row view list box. 
	EQikListBoxLayoutHeightFill is useful for a dynamic layout that fills 
	grid view cells.

	@see TQikListBoxLayoutSizeType.
	*/
	BYTE height_type=							-1 ;
	
	/**
	The height value. Only applicable when type is set to 
	EQikListBoxLayoutHeightPixels.
	Default is 0.
	*/
	WORD height_value =							-1 ;
	
	/**
	An array of QIK_LISTBOX_COLUMN structs making up the layout.

	@see QIK_LISTBOX_COLUMN
	*/
	STRUCT columns[];
	}
# 10 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\QikListBoxStandardLayouts.hrh" 1
// QikListBoxStandardLayouts.hrh
//
// Copyright (c) Symbian Software Ltd 2004-2005.  All rights reserved.
// Created for UIQ 3.0




/**
This is a list of IDs for the standard layouts. These IDs are used to specify 
which layouts that are to be added to a list box either through its resource file or
at a later stage by adding layouts from code.

Once added to the list box the IDs are used to get hold of different layout pairs to
be able to change them. For this to work custom (user created) layout pairs
must be assigned IDs for both normal and, if created, the highlight layout as well.

Positive IDs (including 0) are reserved for standard layouts while negative IDs 
are free to use for user created layout pairs.

For descriptions of what each layout does and look like, please read the 
How-To guide for the List Box control in the SDK documentation.

@publishedAll
@released
*/
enum TQikListBoxStandardLayout
	{
	/**
	Special ID to supply in a list box resource when no corresponding 
	highlight is wanted to a normal layout.
	*/
	EQikListBoxNoLayout = 0, //
	EQikListBoxLine,
	EQikListBoxIconLine,
	EQikListBoxLineIcon,
	EQikListBoxIconLineIcon,
	EQikListBoxIconIconLine,
	EQikListBoxLineIconIcon,
	EQikListBoxIconLineIconIcon,
	EQikListBoxIconHalfLineHalfLine,
	EQikListBoxIconHalfLineHalfLineLine,
	EQikListBoxCheckLineSwappingLine,
	EQikListBoxIconIconTwoLines,
	EQikListBoxTwoLines,
	EQikListBoxIconTwoLines,
	EQikListBoxMediumThumbTwoLines,
	EQikListBoxMediumIconTwoLines,
	EQikListBoxCheckLineIconLine
	};

/**
Slot ids used in standard layouts.

@publishedAll
@released
*/		
enum TListBoxStdLayoutSlots
	{
	/** Small icons */
	EQikListBoxSlotLeftSmallIcon1 = 100,
	EQikListBoxSlotLeftSmallIcon2,
	EQikListBoxSlotLeftSmallIcon3,
	EQikListBoxSlotLeftSmallIcon4,
	EQikListBoxSlotLeftSmallIcon5,
	EQikListBoxSlotRightSmallIcon1,
	EQikListBoxSlotRightSmallIcon2,
	EQikListBoxSlotRightSmallIcon3,
	EQikListBoxSlotRightSmallIcon4,
	EQikListBoxSlotRightSmallIcon5,
	
	/** Medium icons */
	EQikListBoxSlotLeftMediumIcon1 = 200,
	EQikListBoxSlotLeftMediumIcon2,
	EQikListBoxSlotLeftMediumIcon3,
	EQikListBoxSlotRightMediumIcon1,
	EQikListBoxSlotRightMediumIcon2,
	EQikListBoxSlotRightMediumIcon3,
	
	/** Large icons */
	EQikListBoxSlotLeftLargeIcon1 = 300,
	EQikListBoxSlotLeftLargeIcon2,
	EQikListBoxSlotRightLargeIcon1,
	EQikListBoxSlotRightLargeIcon2,
	
	/** Texts */
	EQikListBoxSlotText1 = 400,
	EQikListBoxSlotText2,
	EQikListBoxSlotText3,
	EQikListBoxSlotText4,
	EQikListBoxSlotText5,
		
	/** Medium thumbnails */
	EQikListBoxSlotLeftMediumThumbnail1 = 600,
	EQikListBoxSlotLeftMediumThumbnail2,
	EQikListBoxSlotLeftMediumThumbnail3,
	EQikListBoxSlotRightMediumThumbnail1,
	EQikListBoxSlotRightMediumThumbnail2,
	EQikListBoxSlotRightMediumThumbnail3,
	
	/** Large thumbnails */
	EQikListBoxSlotLargeThumbnail1 = 700,
	EQikListBoxSlotLargeThumbnail2,
	EQikListBoxSlotLargeThumbnail3,
	
	/** Content swapping arrows */
	EQikListBoxSlotLeftArrow1 = 800,
	EQikListBoxSlotRightArrow1,
	
	/** Parent */
	EQikListBoxSlotParent1 = 900,
	EQikListBoxSlotParent2,
	EQikListBoxSlotParent3,
	EQikListBoxSlotParent4,
	EQikListBoxSlotParent5,
	EQikListBoxSlotParent6,
	EQikListBoxSlotParent7,
	EQikListBoxSlotParent8,
	EQikListBoxSlotParent9,
	EQikListBoxSlotParent10,
	
	/** Selector */
	EQikListBoxSlotSelector = 1000,
	
	/** Empty slots */
	EQikListBoxSlotEmpty1 = 1100,
	EQikListBoxSlotEmpty2,
	EQikListBoxSlotEmpty3
	
	};


//__QIKLBXSTDLAYOUTS_HRH__
# 11 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2


//#include <eikedwin.h>

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\hdr\\common.hrh" 1


   
enum TPages
	{
	EInfoView_Page,
	ESettView_Page,
	ESimView_Page,
	EProtView_Page
	};

enum TCommands
	{
	ECommRegister,
	EInfoViewSettings,
	EInfoViewLicense,
	ESettViewEnable,
	ESettViewDisable,
	ESettViewChange,
	ESettViewChange_Pop,
	ESimViewRen,
	ESimViewRem,
	ESimViewAdd,
	ESimViewRen_Pop,
	ESimViewRem_Pop,
	EProtViewAddRem
	};
	

# 15 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\hdr\\numericControls.hrh" 1



/**
Unique controls in view.
*/
enum TNumericCtType
	{
	ECtNumericEdwin = 4554,
	ECtNumericSecreted
	};



# 16 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

// #include "strings.loc"
# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\prova10.rls" 1
// prova10.rls

// rls_string STRING_r_prova10_dialog "splashscreen"

rls_string txt_fuzzy "A FuzzyByte Product:"
rls_string txt_email "info@fuzzy-byte.com"
rls_string txt_web "http://www.fuzzy-byte.com/"
rls_string txt_reserved "All rights reserved 2008"
rls_string txt_guardian "Guardian GOLD Edition"
rls_string txt_version "Version 1.0"

rls_string STRING_r_prova10tabCommand1 "Settings"
rls_string STRING_r_prova10tabCommand2 "Privacy"
rls_string STRING_r_prova10tabCommand3 "Esci"
rls_string STRING_r_prova10tabCommand4 "Cambia"
rls_string STRING_r_prova10tabCommand5 "Rinomina"
rls_string STRING_r_prova10tabCommand6 "Aggiungi"

rls_string txt_mia_sim "Mia SIM"

rls_string txt_stato "Status:"
rls_string txt_destin "Recipient:"
rls_string txt_message "Message:"
rls_string txt_password "Code:"

rls_string txt_enabled "Enabled"
rls_string txt_disabled "Disabled"
rls_string txt_sim_cambiata "Warning Sim Changed!"


// The text showed in the exit dialog
rls_string STRING_r_exit_dialog_title "Esci"
rls_string STRING_r_exit_dialog_text "Vuoi uscire da guardian?"
rls_string STRING_r_exit_dialog_yes "Si"
rls_string STRING_r_exit_dialog_no "No"


// The text showed in the exit dialog
rls_string STRING_r_text_dialog_title "Testo Lungo"
rls_string STRING_r_text_dialog_text "Mille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille caratteriMille "
rls_string STRING_r_text_dialog_yes "Si"
rls_string STRING_r_text_dialog_no "No"

rls_string STRING_r_notifier_message_text "Messaggio Informativo"
rls_string STRING_r_notifier_warning_text "Messaggio di Warning"
rls_string STRING_r_notifier_error_text "Messaggio di Error"

rls_string STRING_r_info_dialog_text "testo Informazione"
rls_string STRING_r_info_dialog_title "titolo Informazione"


rls_string STRING_r_prova10_list_text "Scelta della lista"
rls_string STRING_r_prova10list_cmd_close "cmlist!"
rls_string STRING_r_prova10list_element "elemento lista"

rls_string STRING_r_viewcontext_string1 "tab1"
rls_string STRING_r_viewcontext_string2 "tab2"
rls_string STRING_r_viewcontext_string3 "tab3"

rls_string STRING_r_secret_text "Code: "


//************************************************************************

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
rls_string txt_pass   		"Code:"

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
rls_string txt_guardian_pass	"Guardian Code:"


rls_string txt_sim_added	   	"This SIM has been Registered using name: "
rls_string txt_confirm_exit		"Exit Guardian?"

rls_string txt_warning_sms		"Warning Sim Changed!"

// ERRORI
rls_string txt_ok_code			"Thank You!"
rls_string txt_err_code			"Wrong Code!"
rls_string txt_err_bad_pass		"Wrong Code"
rls_string txt_err_imei			"Errore Lettura IMEI"
rls_string txt_err_imsi			"Errore Lettura IMSI"
rls_string txt_err_diff_imei	"IMEI differente"
rls_string txt_err_no_number	"Recipient not set"
rls_string txt_err_no_pass		"Code not set"
rls_string txt_err_short_pass	"Code Short"
rls_string txt_err_sim0			"Can't Remove SIM, SIM in use"
# 17 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2


NAME PRVA

RESOURCE RSS_SIGNATURE { }

RESOURCE TBUF { buf = ""; }

RESOURCE EIK_APP_INFO {	}

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\infodialog.ra" 1



RESOURCE QIK_DIALOG r_info_dialog
  {
  title = "titolo:";
       configurations =
              {
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x100  | 0x4000 ) ;
					 container = r_info_dialog_container;
				     command_list = r_ok_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x02  | 0x80  | 0x100  | 0x4000 ) ;
					 container = r_info_dialog_container;
				     command_list = r_ok_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x40  | 0x200  | 0x4000 ) ;
					 container = r_info_dialog_container;
				     command_list = r_ok_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x03   | 0x40  | 0x200  | 0x4000 ) ;
					 container = r_info_dialog_container;
				     command_list = r_ok_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x04  | 0x40  | 0x200  | 0x4000 ) ;
					 container = r_info_dialog_container;
				     command_list = r_ok_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x200  | 0x4000 ) ;
					 container = r_info_dialog_container;
				     command_list = r_ok_commands;
                     }
              };
    controls = r_info_dialog_controls;
  }


//----------------------------------------------------
//------------- SIMPLE DIALOG CONTROLS ---------------
//----------------------------------------------------
RESOURCE QIK_CONTROL_COLLECTION r_info_dialog_controls
	{
	items = 
		{	
			QIK_CONTROL 
			{
            unique_handle = 1;
            itemflags = EQikCtrlFlagIsEditInPlace;
//            type = EEikCtLabel;
//            control = r_info_dialog_label;
// 		  	  type = EEikCtRichTextEditor;
//            control = r_info_dialog_text_editor;
//			  type = EEikCtEdwin;
//            control = r_info_dialog_edwin;
			type = EEikCtGlobalTextEditor;
			control = r_info_dialog_global_editor;

			}			
		};
	}



RESOURCE QIK_SCROLLABLE_CONTAINER_SETTINGS r_info_dialog_container
    {
    controls = 
        {
		QIK_CONTAINER_ITEM_CI_LI
			{
			type = EQikCtOnelineBuildingBlock;
			control = r_info_dialog_label_building_block;
			}
        };
    }

   
    
//----------------------------------------------------
//---------- SIMPLE DIALOG: BUILDING BLOCK -----------
//----------------------------------------------------
// Building block that contains the label.
RESOURCE QIK_SYSTEM_BUILDING_BLOCK r_info_dialog_label_building_block
    {
    content =
        {
		QIK_SLOT_CONTENT
			{
			slot_id = EQikItemSlot1; 
            unique_handle = 1;
			}
    	};
    }


RESOURCE GTXTED r_info_dialog_global_editor
	{
	flags= 0x00000008 | 0x20000000 | 0x00040000 | 0x00002000 ;
//	numlines=30;
	numlines=0;
	}

     
RESOURCE RTXTED r_info_dialog_text_editor
    {
    flags = 0x00000008  | 0x00002000  | 0x10 ;
    //height = 200;
    numlines = 0;
    }
    

RESOURCE EDWIN r_info_dialog_edwin
    {
    flags = 0x00040000  | 0x00000008  | 0x00002000 ;
//	flags = EEikEdwinResizable;
//    width = 10;
    lines = 150;
//    maxlength = 1500;
    }

    
RESOURCE LABEL r_info_dialog_label
	{
    // flags = EEikEdwinResizable;
	//standard_font = EEikLabelFontLegend;
	txt = "text";
	}
	
# 27 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\textdialog.ra" 1


RESOURCE QIK_DIALOG r_dialog_message
  {
  title = "titolo:";
       configurations =
              {
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x100  | 0x4000 ) ;
					 container = r_dialog_text_container;
				     command_list = r_ok_cancel_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x02  | 0x80  | 0x100  | 0x4000 ) ;
					 container = r_dialog_text_container;
				     command_list = r_ok_cancel_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x40  | 0x200  | 0x4000 ) ;
					 container = r_dialog_text_container;
				     command_list = r_ok_cancel_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x03   | 0x40  | 0x200  | 0x4000 ) ;
					 container = r_dialog_text_container;
				     command_list = r_ok_cancel_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x04  | 0x40  | 0x200  | 0x4000 ) ;
					 container = r_dialog_text_container;
				     command_list = r_ok_cancel_commands;
                     },
              QIK_DIALOG_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x200  | 0x4000 ) ;
					 container = r_dialog_text_container;
				     command_list = r_ok_cancel_commands;
                     }
              };
  }

   
    
// Defines the content of the simple dialog and how they are laid out. 
// Default layout manager is used for laying out the controls, which is a row 
// layout.
RESOURCE QIK_CONTAINER_SETTINGS r_dialog_text_container
    {
    layout_manager_type = EQikRowLayoutManager;
    layout_manager = r_row_layout_default;
    controls = 
        {
		QIK_CONTAINER_ITEM_CI_LI
			{
			itemflags = EQikCtrlFlagIsEditInPlace;
			unique_handle = 1;
			type = EEikCtEdwin;
			control = r_text_editor;
			}
        };
    }
    

//----------------------------------------------------
//---------------------- LABEL -----------------------
//----------------------------------------------------
	
RESOURCE EDWIN r_text_editor
    {
	flags = 0x00040000 ;
    width = 10;
    lines = 1;
    maxlength = 20;
    }
# 28 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\numericdialog.ra" 1

RESOURCE DIALOG r_numeric_edwin_dialog
	{
	title = "Code:";
	flags = 0x001 ;
	buttons = 0xf3b070 ;
	items=
		{
		DLG_LINE
			{
			type=ECtNumericEdwin;
			control=EDWIN
				{
				flags = 0x00000080  | 0x00040000 ;
 				};
			}
		};
	}


RESOURCE DIALOG r_numeric_secreted_dialog
	{
	title = "Code:";
	flags = 0x001 ;
	buttons = 0xf3b070 ;
	items=
		{
		DLG_LINE
			{
			type=ECtNumericSecreted;
			control=SECRETED
				{
				num_letters=8;
				};
			}
		};
	}

# 29 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\commands.ra" 1

# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh" 1
// uikon.hrh
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.


/** @internalTechnology @released */
# 2299 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh"

# 2 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\commands.ra" 2



RESOURCE QIK_COMMAND_LIST r_yes_no_commands
    {
    items=
        {
        QIK_COMMAND
        	{
        	id = 0x195 ;
        	type = EQikCommandTypeYes;
			text = "Yes";
        	},
        QIK_COMMAND
			{
			id = 0x196 ;
			type = EQikCommandTypeNo;
			text = "No";
			}
		};
    }


RESOURCE QIK_COMMAND_LIST r_ok_cancel_commands
    {
    items=
        {
        QIK_COMMAND
        	{
        	id = 0x195 ;
        	type = EQikCommandTypeDone;
			text = "Ok";
        	},
        QIK_COMMAND
			{
			id = 0x196 ;
			type = EQikCommandTypeCancel;
			text = "Cancel";
			}
		};
    }
    

RESOURCE QIK_COMMAND_LIST r_ok_commands
    {
    items=
        {
        QIK_COMMAND
        	{
        	id = 0x195 ;
        	type = EQikCommandTypeDone;
			text = "Ok";
        	}
		};
    }


RESOURCE QIK_COMMAND_LIST r_cancel_commands
    {
    items=
        {
        QIK_COMMAND
			{
			id = 0x196 ;
			type = EQikCommandTypeCancel;
			text = "Cancel";
			}
		};
    }
    
# 30 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\info_view.ra" 1
//view.ra

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\hdr\\infoview.hrh" 1




enum TInfoViewControls
    {
    ELabelCtrl1,
    ELabelCtrl2,
    ELabelCtrl3,
    ELabelCtrl4,
    ELabelCtrl5,
    ELabelCtrl6,
    ELabelCtrl7,
    ELabelCtrl8,
    EInfoViewNumberOfControls
    };
    	

# 3 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\info_view.ra" 2


RESOURCE QIK_VIEW_CONFIGURATIONS r_info_view_ui_configurations
	{
	configurations = 
		{
		QIK_VIEW_CONFIGURATION
			{
			ui_config_mode = (0x01   | 0x80  | 0x100  | 0x4000 ) ;
			command_list = r_info_commands;
			view = r_info_view;
			},
		QIK_VIEW_CONFIGURATION
			{
			ui_config_mode = (0x01   | 0x40  | 0x200  | 0x4000 ) ;
			command_list = r_info_commands;
			view = r_info_view;
			}
		};
	}

RESOURCE QIK_COMMAND_LIST r_info_commands
	{
	items =
		{
	 	 QIK_COMMAND
         {
         id = EInfoViewSettings;
         type = EQikCommandTypeScreen;
         text = "Settings";
         },
      	 QIK_COMMAND
         {
         id = EInfoViewLicense;
         type = EQikCommandTypeScreen;	
         text = "License Agreement";
         }
		};
	}
	
	

RESOURCE QIK_VIEW r_info_view
	{
	pages = r_info_view_layout_pages;
	}

RESOURCE QIK_VIEW_PAGES r_info_view_layout_pages
	{
	pages = 
		{
		QIK_VIEW_PAGE
			{
			page_id = EInfoView_Page;
 		    page_content = r_info_page_controls;
			}
		};
	}

//----------------------------------------------------
//------------------ VIEW CONTROLS -------------------
//----------------------------------------------------
RESOURCE QIK_CONTAINER_SETTINGS r_info_page_controls
{
layout_manager_type = EQikRowLayoutManager;
layout_manager = r_info_row_layout_manager;
controls =
	{
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl1;
		type = EEikCtLabel;
		control = r_label_fuzzy;
		},
    QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl2;
		type = EEikCtLabel;
		control = r_label_email;
		},
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl3;
		type = EEikCtLabel;
		control = r_label_web;
		},
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl4;
		type = EEikCtLabel;
		control = r_empty;
		},
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl5;
		type = EEikCtLabel;
		control = r_label_guardian;
		},
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl6;
		type = EEikCtLabel;
		control = r_label_version;
		},
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl7;
		type = EEikCtLabel;
		control = r_empty;
		},
	QIK_CONTAINER_ITEM_CI_LI
		{
		unique_handle = ELabelCtrl8;
		type = EEikCtLabel;
		control = r_label_reserved;
		}
	};
}
	

//----------------------------------------------------
//---------------------- LABEL -----------------------
//----------------------------------------------------
RESOURCE LABEL r_label_fuzzy
	{
	standard_font = EEikLabelFontLegend;
	txt = txt_fuzzy;
	}
RESOURCE LABEL r_label_email
	{
	standard_font = EEikLabelFontNormal;
	txt = txt_email;
	}
RESOURCE LABEL r_label_web
	{
	standard_font = EEikLabelFontNormal;
	txt = txt_web;
	}
RESOURCE LABEL r_label_guardian
	{
	standard_font=EEikLabelFontLegend;
	txt = txt_guardian;
	}
RESOURCE LABEL r_label_version
	{
	standard_font = EEikLabelFontLegend;
	txt = txt_version;
	}
RESOURCE LABEL r_label_reserved
	{
	standard_font = EEikLabelFontNormal;
	txt = txt_reserved;
	}
RESOURCE LABEL r_empty
	{
	standard_font = EEikLabelFontNormal;
	txt = "";
	}


//----------------------------------------------------
//-------------- GRID LAYOUT MANAGER -----------------
//----------------------------------------------------
RESOURCE QIK_ROW_LAYOUT_MANAGER r_info_row_layout_manager
{
	default_layout_data = QIK_ROW_LAYOUT_DATA 
	{
	top_margin = 5;
	horizontal_alignment = EQikLayoutHAlignFill;//EQikLayoutHAlignCenter;
	vertical_alignment = EQikLayoutVAlignCenter;//EQikLayoutVAlignTop;	
	};
}
	
# 31 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\settings_view.ra" 1
# 1 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh" 1
// uikon.hrh
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.


/** @internalTechnology @released */
# 2299 "C:\\Symbian\\UIQ3SDK\\\\EPOC32\\INCLUDE\\uikon.hrh"

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\settings_view.ra" 2


# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\hdr\\settview.hrh" 1



//    ESettViewScrollableContainer,

enum TSettViewControls
    {
    ESettViewListBox,
    ESettViewStato,
    ESettViewDestin,
    ESettViewMessage,
    ESettViewPassword,
    ESettViewNumberOfControls
    };
    	

# 3 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\settings_view.ra" 2


RESOURCE TBUF128 r_txt_enabled { buf = txt_enabled; }
RESOURCE TBUF128 r_txt_disabled { buf = txt_disabled; }

//---------------------------------------------------------------------
                                 
RESOURCE QIK_VIEW_CONFIGURATIONS r_settings_view_ui_configurations
	{
	configurations = 
		{
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x100  | 0x4000 ) ;
					command_list = r_settings_view_commands;
					view = r_settings_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x02  | 0x80  | 0x100  | 0x4000 ) ;
					command_list = r_settings_view_commands;
					view = r_settings_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x40  | 0x200  | 0x4000 ) ;
					command_list = r_settings_view_commands;
					view = r_settings_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x03   | 0x40  | 0x200  | 0x4000 ) ;
					command_list = r_settings_view_commands;
					view = r_settings_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x04  | 0x40  | 0x200  | 0x4000 ) ;
					command_list = r_settings_view_commands;
					view = r_settings_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x200  | 0x4000 ) ;
					command_list = r_settings_view_commands;
					view = r_settings_view;
                     }
		};
	}


RESOURCE QIK_COMMAND_LIST r_settings_view_commands
	{
	items =
		{
	 	 QIK_COMMAND
         {
         id = ESettViewChange;
         type = EQikCommandTypeItem;
         text = txt_change;
         }
		};
	}


RESOURCE QIK_COMMAND_LIST r_popout_sett_commands
	{
	items =
		{
	 	 QIK_COMMAND
         {
         id = ESettViewChange_Pop;
         text = txt_change;
         }
		};
	}


RESOURCE QIK_VIEW r_settings_view
	{
	pages = r_settings_view_layout_pages;
	}

RESOURCE QIK_VIEW_PAGES r_settings_view_layout_pages
	{
	pages = 
		{
		QIK_VIEW_PAGE
			{
			page_id = ESettView_Page;
			page_content = r_sett_listbox_page_control;
			}
		};
	}

// The page contains a List Box that fills the entire application space.
RESOURCE QIK_CONTAINER_SETTINGS r_sett_listbox_page_control
    {
    layout_manager_type = EQikRowLayoutManager;
    layout_manager = r_row_layout_default;
    controls = 
        {
        QIK_CONTAINER_ITEM_CI_LI
            { 
            unique_handle = ESettViewListBox;
            type = EQikCtListBox; 
            control = r_sett_listbox;
            // This makes the List Box fill the entire application space.
            layout_data = r_row_layout_data_fill;
            }
        };
    }


  
RESOURCE QIK_LISTBOX_LAYOUT r_layout_two_lines
    {
    columns=
        {
        QIK_LISTBOX_COLUMN
            {
            type=QIK_LISTBOX_PARENT_TYPE;
            width_type=EQikListBoxColWidthGrab;
            width_value=1;
            slot_id=EQikListBoxSlotParent1;
            rows=
                {
                QIK_LISTBOX_ROW
                    {
                    type=QIK_LISTBOX_TEXT_TYPE 
						{
						font_size  = EQikListBoxFontMedium;
						font_style = EQikListBoxFontBold;
						alignment  = EQikListBoxTextAlignLeft;
						};
                    height_type=EQikListBoxRowHeightFromContentType;
                    slot_id=EQikListBoxSlotText1;
                    },
                QIK_LISTBOX_ROW
                    {
                    type=QIK_LISTBOX_TEXT_TYPE 
						{
						font_size = EQikListBoxFontSmall;
						alignment = EQikListBoxTextAlignLeft;
						};
                    height_type=EQikListBoxRowHeightFromContentType;
                    slot_id=EQikListBoxSlotText2;
                    }
                };
            }
        };
    }


RESOURCE QIK_LISTBOX_LAYOUT_PAIR r_my_layout_pair
    {
//    standard_normal_layout = EQikListBoxTwoLines;
//    standard_highlight_layout = EQikListBoxTwoLines;
    custom_normal_layout = r_layout_two_lines;
//    custom_highlight_layout = r_layout_two_lines;
    }
    
    
RESOURCE QIK_LISTBOX r_sett_listbox
    {
    type = EQikRowListBox;
    layouts = {r_my_layout_pair}; // at least one layout pair is needed
    item_data =
        {
        QIK_LISTBOX_DATA
            {
            data = 
                {
                QIK_LISTBOX_TEXT
                    {
                    txt=txt_stato;
                    slot_id=EQikListBoxSlotText1;
                    },
                QIK_LISTBOX_TEXT
                    {
                    txt="Text 0";
                    slot_id=EQikListBoxSlotText2;
                    }
                };
            },
        QIK_LISTBOX_DATA
            {
            data = 
                {
                QIK_LISTBOX_TEXT 
                    {
                    txt=txt_destin;
                    slot_id=EQikListBoxSlotText1;
                    },
                QIK_LISTBOX_TEXT
                    {
                    txt="Text 1";
                    slot_id=EQikListBoxSlotText2;
                    }
                };
            },
        QIK_LISTBOX_DATA
            {
            data = 
                {
                QIK_LISTBOX_TEXT 
                    {
                    txt=txt_message;
                    slot_id=EQikListBoxSlotText1;
                    },
                QIK_LISTBOX_TEXT
                    {
                    txt="Text 1";
                    slot_id=EQikListBoxSlotText2;
                    }
                };
            },
        QIK_LISTBOX_DATA
            {
            data = 
                {
                QIK_LISTBOX_TEXT 
                    {
                    txt=txt_password;
                    slot_id=EQikListBoxSlotText1;
                    },
                QIK_LISTBOX_TEXT
                    {
                    txt="Text 1";
                    slot_id=EQikListBoxSlotText2;
                    }
                };
            }
        };
    }
    

//----------------------------------------------------
//-------------- GRID LAYOUT MANAGER -----------------
//----------------------------------------------------

RESOURCE QIK_ROW_LAYOUT_MANAGER r_row_layout_default
    {
    default_layout_data = QIK_ROW_LAYOUT_DATA {};
    }
    
RESOURCE QIK_ROW_LAYOUT_DATA r_row_layout_data_fill
    {
    vertical_alignment = EQikLayoutVAlignFill;
    vertical_excess_grab_weight = 1;
    }
   	
# 32 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\simlist_view.ra" 1
//view.ra

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\hdr\\simview.hrh" 1



enum TSimViewControls
    {
    ESimViewListBox,
    ESimViewSimName
    };

    	

# 3 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\simlist_view.ra" 2



RESOURCE QIK_VIEW_CONFIGURATIONS r_simlist_view_ui_configurations
	{
	configurations = 
		{
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x100  | 0x4000 ) ;
					command_list = r_simlist_view_commands;
					view = r_simlist_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x02  | 0x80  | 0x100  | 0x4000 ) ;
					command_list = r_simlist_view_commands;
					view = r_simlist_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x40  | 0x200  | 0x4000 ) ;
					command_list = r_simlist_view_commands;
					view = r_simlist_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x03   | 0x40  | 0x200  | 0x4000 ) ;
					command_list = r_simlist_view_commands;
					view = r_simlist_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x04  | 0x40  | 0x200  | 0x4000 ) ;
					command_list = r_simlist_view_commands;
					view = r_simlist_view;
                     },
              QIK_VIEW_CONFIGURATION
                     {
                     ui_config_mode = (0x01   | 0x80  | 0x200  | 0x4000 ) ;
					command_list = r_simlist_view_commands;
					view = r_simlist_view;
                     }
		};
	}



RESOURCE QIK_COMMAND_LIST r_simlist_view_commands
	{
	items =
		{
	 	 QIK_COMMAND
         {
         id = ESimViewRen;
         type = EQikCommandTypeItem;
         text = txt_rename_sim;
         },
	 	 QIK_COMMAND
         {
         id = ESimViewRem;
         type = EQikCommandTypeItem;
         text = txt_remove_sim;
         },
	 	 QIK_COMMAND
         {
         id = ESimViewAdd;
         type = EQikCommandTypeItem;
         text = txt_add_sim;
         }
		};
	}

	

RESOURCE QIK_VIEW r_simlist_view
	{
	pages = r_simlist_view_layout_pages;
	}

RESOURCE QIK_VIEW_PAGES r_simlist_view_layout_pages
	{
	pages = 
		{
		QIK_VIEW_PAGE
			{
			page_id = ESimView_Page;
			page_content = r_sim_listbox_page_controls;
			}
		};
	}


RESOURCE QIK_CONTAINER_SETTINGS r_sim_listbox_page_controls
    {
    layout_manager_type = EQikRowLayoutManager;
    layout_manager = r_row_layout_default;
    controls = 
        {
        QIK_CONTAINER_ITEM_CI_LI
            { 
            unique_handle = ESimViewListBox;
            type = EQikCtListBox; 
            control = r_sim_listbox;
            layout_data = r_row_layout_data_fill;
            }
        };
    }


RESOURCE QIK_COMMAND_LIST r_popout_sim_commands
	{
	items =
		{
	 	 QIK_COMMAND
         {
         id = ESimViewRen_Pop;
         text = txt_rename_sim;
         },
	 	 QIK_COMMAND
         {
         id = ESimViewRem_Pop;
         text = txt_remove_sim;
         }
		};
	}



RESOURCE QIK_LISTBOX r_sim_listbox
    {
    type = EQikRowListBox;
    layouts = {r_layout_italic_pair}; // at least one layout pair is needed
    item_data =
        {
        };
    }


RESOURCE QIK_LISTBOX_LAYOUT_PAIR r_layout_italic_pair
    {
//    standard_normal_layout = EQikListBoxTwoLines;
//    standard_highlight_layout = EQikListBoxTwoLines;
    custom_normal_layout = r_layout_two_lines_italic;
//    custom_highlight_layout = r_layout_two_lines_italic;
    }
    
    
RESOURCE QIK_LISTBOX_LAYOUT r_layout_two_lines_italic
    {
    columns=
        {
        QIK_LISTBOX_COLUMN
            {
            type=QIK_LISTBOX_PARENT_TYPE;
            width_type=EQikListBoxColWidthGrab;
            width_value=1;
            slot_id=EQikListBoxSlotParent1;
            rows=
                {
                QIK_LISTBOX_ROW
                    {
                    type=QIK_LISTBOX_TEXT_TYPE 
						{
						font_size  = EQikListBoxFontMedium;
						font_style = EQikListBoxFontBold;
						alignment  = EQikListBoxTextAlignLeft;
						};
                    height_type=EQikListBoxRowHeightFromContentType;
                    slot_id=EQikListBoxSlotText1;
                    },
                QIK_LISTBOX_ROW
                    {
                    type=QIK_LISTBOX_TEXT_TYPE 
						{
						font_size = EQikListBoxFontSmall;
						font_style = EQikListBoxFontItalic;
						alignment = EQikListBoxTextAlignLeft;
						};
                    height_type=EQikListBoxRowHeightFromContentType;
                    slot_id=EQikListBoxSlotText2;
                    }
                };
            }
        };
    }
    
    
    
# 33 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\protection_view.ra" 1
# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\hdr\\protview.hrh" 1




enum TProtViewControls
    {
    EInfoView_Page,
    ELabelCtrl1,
    ELabelCtrl2,
    ELabelCtrl3,
    ELabelCtrl4,
    ELabelCtrl5,
    ELabelCtrl6,
    ELabelCtrl7,
    ELabelCtrl8,
    EInfoViewNumberOfControls
    };
    	

# 1 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\protection_view.ra" 2



RESOURCE QIK_VIEW_CONFIGURATIONS r_protection_view_ui_configurations
	{
	configurations = 
		{
		QIK_VIEW_CONFIGURATION
			{
			ui_config_mode = (0x01   | 0x80  | 0x100  | 0x4000 ) ;
			command_list = r_protection_commands;
			view = r_protection_view;
			},
		QIK_VIEW_CONFIGURATION
			{
			ui_config_mode = (0x01   | 0x40  | 0x200  | 0x4000 ) ;
			command_list = r_protection_commands;
			view = r_protection_view;
			}
		};
	}

RESOURCE QIK_COMMAND_LIST r_protection_commands
	{
	items =
		{
	 	 QIK_COMMAND
         {
         id = EProtViewAddRem;
         type = EQikCommandTypeItem;
         text = "Add";
         }
		};
	}
	
	

RESOURCE QIK_VIEW r_protection_view
	{
	pages = r_protection_view_layout_pages;
	}

RESOURCE QIK_VIEW_PAGES r_protection_view_layout_pages
	{
	pages = 
		{
		QIK_VIEW_PAGE
			{
			page_id = EProtView_Page;
			page_content = r_info_page_controls;
			}
		};
	}

	
# 34 "C:\\online\\Guardian3rd\\UIQ_GuardGUI\\Rsc\\GuardGUI_200107AF.rss" 2




RESOURCE QIK_COMMAND_LIST r_common_commands
	{
	items =
		{
      	 QIK_COMMAND
         {
         id = ECommRegister;
         type = EQikCommandTypeScreen;
         text = "Register";
         },
	 	 QIK_COMMAND
         {
		 id = 0x100 ;
		 type = EQikCommandTypeScreen;
         text = "Exit";
         }
		};
	}	
