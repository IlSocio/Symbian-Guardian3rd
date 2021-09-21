@echo off

call devices -setdefault @UIQ

echo "...SERVER..."
cd server\group\
call comp9.bat server
cd ..\..

echo "...CLIENT..."
cd server\group\
call compdll9.bat client
cd ..\..

echo "...GUARDIAN..."
cd Guardian\group\
call comp9.bat guardian
cd ..\..

REM echo "...RESOLVER..."
REM cd plugins\definition
REM call compdll9.bat interfacedefinition
REM cd ..\..

echo "...PLUGINS..."
cd plugins\group
call compdll9.bat defplugins
cd ..\..

echo "...UNINSTALL..."
cd uninstall\group
call comp9.bat uninstall
cd ..\..

echo "...UIQ_NOTIFIER..."
cd uiq_notifier\group\
call compdll9.bat dialogpin
cd ..\..

echo "...UIQ_RECOGNIZER_AUTOSTART..."
cd UIQ_guardauto\group\
call comp9.bat guardauto
cd ..\..

echo "...DONE..."
pause

