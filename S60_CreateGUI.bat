REM @echo off

cd S60_guardgui\group
call createPrj9.bat guardgui
cd ..\..

call s60_refresh_gui_mif.bat

pause
