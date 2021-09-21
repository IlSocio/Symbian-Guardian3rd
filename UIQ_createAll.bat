@echo off

devices -setdefault @UIQ

cd server\group\
call createPrj9.bat server3rd
cd ..\..

cd server\group\
call createPrj9.bat client3rd
cd ..\..

cd UIQ_guardauto\group
call createPrj9.bat Recognizer
cd ..\..

cd guardian\group
call createPrj9.bat guardian
cd ..\..

cd UIQ_guardgui\group
call createPrj9.bat guardgui
cd ..\..

pause