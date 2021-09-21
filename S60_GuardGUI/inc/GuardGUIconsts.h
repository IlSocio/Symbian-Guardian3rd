/*
============================================================================
 Name        : GuardGUI resource header file GuardGUI.hrh
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : This file contains declarations for constants of GuardGUI.
               The file can be included in C++ or resource file.
============================================================================
*/

#ifndef GUARDGUICONSTS_H
#define GUARDGUICONSTS_H

#include <e32def.h>
#include <e32cmn.h>


#define _UID3_ 0x200131CC

const TUid KUidGuardGUIApp = { _UID3_ };
const TUid KSplashViewId = {0};				// Splash
const TUid KViewId = {1};					// About
const TUid KView2Id = {2};					// Settings
const TUid KView3Id = {3};					// Sim
const TUid KView4Id = {4};					// Protection


#endif      // GUARDGUI_HRH
