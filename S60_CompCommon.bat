REM @echo off

REM call devices -setdefault @s60

echo "...COMMON..."
cd ..\commonlib\group
call comp9.bat commonlib
cd ..\..\Guardian3Rd

echo "...SERVER..."
cd server\group\
call comp9.bat server
cd ..\..

echo "...CLIENT..."
cd server\group\
call compdll9.bat client
cd ..\..

echo "...PLUGINS..."
cd plugins\group
call compdll9.bat defplugins
cd ..\..


echo "...GUARDIAN..."
cd Guardian\group\
call comp9.bat guardian
cd ..\..


REM echo "...RESOLVER..."
REM cd plugins\definition
REM call compdll9.bat interfacedefinition
REM cd ..\..

echo "...UNINSTALL..."
cd uninstall\group
call comp9.bat uninstall
cd ..\..


echo "...INSTALL..."
cd install\group
call comp9.bat install
cd ..\..


echo "...S60_NOTIFIER..."
cd S60_notifier\group\
call compdll9.bat dialogpin
cd ..\..


echo "...S60_AUTO..."
cd S60_guardauto\group\
call comp9.bat guardauto
cd ..\..

echo "...DONE..."
pause

