@echo off

devices -setdefault @UIQ

cd server\group\
call createPrj9.bat server
cd ..\..

cd server\group\
call createPrj9.bat client
cd ..\..

cd guardian\group
call createPrj9.bat guardian
cd ..\..

REM cd plugins\definition
REM call createPrj9.bat interfacedefinition
REM cd ..\..

cd plugins\group
call createPrj9.bat defplugins
cd ..\..

cd uninstall\group
call createPrj9.bat uninstall
cd ..\..

cd UIQ_notifier\group
call createPrj9.bat dialogpin.mmp
cd ..\..

cd UIQ_guardauto\group
call createPrj9.bat Recognizer
cd ..\..

pause