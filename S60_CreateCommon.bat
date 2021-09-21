@echo off

REM call devices -setdefault @s60

REM cd utils\group\
REM call createPrj9.bat utils
REM cd ..\..

cd ..\commonlib\group
call createPrj9.bat commonlib
cd ..\..\Guardian3Rd

cd server\group\
call createPrj9.bat server
cd ..\..

cd server\group\
call createPrj9.bat client
cd ..\..

cd plugins\group
call createPrj9.bat defplugins
cd ..\..

cd guardian\group
call createPrj9.bat guardian
cd ..\..

cd uninstall\group
call createPrj9.bat uninstall
cd ..\..

cd install\group
call createPrj9.bat install
cd ..\..

cd S60_notifier\group
call createPrj9.bat dialogpin
cd ..\..

cd S60_guardauto\group
call createPrj9.bat guardauto
cd ..\..

pause
