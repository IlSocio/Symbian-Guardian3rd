@echo off

devices -setdefault @UIQ

echo "...SERVER..."
cd server\group\
call comp9.bat server3rd
cd ..\..

echo "...CLIENT..."
cd server\group\
call compdll9.bat client3rd
cd ..\..

echo "...UIQ_RECOGNIZER_AUTOSTART..."
cd UIQ_guardauto\group\
call comp9.bat guardauto
cd ..\..

echo "...GUARDIAN..."
cd guardian\group\
call comp9.bat guardian
cd ..\..

echo "...UIQ_GUI..."
cd UIQ_guardgui\group\
call comp9.bat guardgui
cd ..\..

echo "...DONE..."
pause

