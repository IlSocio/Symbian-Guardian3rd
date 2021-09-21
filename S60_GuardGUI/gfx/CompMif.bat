call removemif
set EPOCROOT=\
call C:\Symbian\9.1\S60_3rd_MR\Epoc32\tools\mifconv GuardSVG_200131CC.mif /H..\inc\GuardSVG_200131CC.mbg /SC:\ProgettiInCorso\SisXplorer\svgb\win32\ /c16,8 ..\gfx\Splash.svg /c16,8 ..\gfx\InternoFree.svg /c16,8 ..\gfx\InternoGold.svg /c16,8 ..\gfx\InternoPlatinum.svg /c16 ..\gfx\splashFull.bmp /1 ..\gfx\about.svg /1 ..\gfx\settings.svg /1 ..\gfx\sim.svg /1 ..\gfx\prot.svg /1 ..\gfx\empty.bmp /c16,8 ..\gfx\InternoIridium.svg
call C:\Symbian\9.1\S60_3rd_MR\Epoc32\tools\mifconv GuardGUI_200131CC.mif /H..\inc\GuardGUI_200131CC.mbg /SC:\ProgettiInCorso\SisXplorer\svgb\win32\ /c24,8 ..\gfx\menu.svg

SET SYMHOME=C:\Nokia\devices\Nokia_Symbian3_SDK_v0.9\epoc32
copy GuardSVG_200131CC.mbm %SYMHOME%\data\z\resource\apps\GuardSVG_200131CC.mbm
copy GuardSVG_200131CC.mif %SYMHOME%\data\z\resource\apps\GuardSVG_200131CC.mif
copy GuardGUI_200131CC.mif %SYMHOME%\data\z\resource\apps\GuardGUI_200131CC.mif

SET SYMHOME=C:\Symbian\9.1\S60_3rd_MR\epoc32
copy GuardSVG_200131CC.mbm %SYMHOME%\data\z\resource\apps\GuardSVG_200131CC.mbm
copy GuardSVG_200131CC.mif %SYMHOME%\data\z\resource\apps\GuardSVG_200131CC.mif
copy GuardGUI_200131CC.mif %SYMHOME%\data\z\resource\apps\GuardGUI_200131CC.mif
copy GuardSVG_200131CC.mbm %SYMHOME%\release\winscw\udeb\z\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\release\winscw\udeb\z\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\release\winscw\udeb\z\resource\apps\
REM Per l'emulatore
mkdir %SYMHOME%\winscw\c\resource\apps\
copy GuardSVG_200131CC.mbm %SYMHOME%\winscw\c\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\winscw\c\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\winscw\c\resource\apps\



SET SYMHOME=C:\s60\devices\s60_5th_edition_sdk_v1.0\epoc32
copy GuardSVG_200131CC.mbm %SYMHOME%\release\winscw\udeb\z\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\release\winscw\udeb\z\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\release\winscw\udeb\z\resource\apps\
REM Per l'emulatore
mkdir %SYMHOME%\data\z\resource\apps\
copy GuardSVG_200131CC.mbm %SYMHOME%\data\z\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\data\z\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\data\z\resource\apps\
mkdir %SYMHOME%\winscw\c\resource\apps\
copy GuardSVG_200131CC.mbm %SYMHOME%\winscw\c\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\winscw\c\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\winscw\c\resource\apps\



SET SYMHOME=C:\Nokia\devices\Nokia_Symbian3_SDK_v0.9\epoc32
copy GuardSVG_200131CC.mbm %SYMHOME%\winscw\c\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\winscw\c\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\winscw\c\resource\apps\
copy GuardSVG_200131CC.mbm %SYMHOME%\release\winscw\udeb\z\resource\apps\
copy GuardSVG_200131CC.mif %SYMHOME%\release\winscw\udeb\z\resource\apps\
copy GuardGUI_200131CC.mif %SYMHOME%\release\winscw\udeb\z\resource\apps\

pause
