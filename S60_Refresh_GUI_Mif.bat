
@del C:\online\Guardian3rd\S60_GuardGUI\data\*.rsg
@del C:\online\Guardian3rd\S60_GuardGUI\data\*.mbg
@del C:\online\Guardian3rd\Server\inc\*.rsg
@del C:\online\Guardian3rd\Server\inc\*.mbg
@del C:\Symbian\9.1\S60_3rd_MR\Epoc32\release\winscw\udeb\z\private\101f875a\import\*.r01
@del C:\Symbian\9.1\S60_3rd_MR\Epoc32\release\winscw\udeb\z\private\101f875a\import\*.r05
echo "...S60_GUI..."

cd S60_GuardGUI\gfx
call compmif.bat
cd ..\..

cd S60_GuardGUI\help
call comphelp.bat
cd ..\..

REM cd S60_guardgui\group\
REM call comp9.bat guardgui // IL NOME DA ERRORE PER LA COMPILAZIONE DELL'HELP
REM call comp9.bat
REM cd ..\..
pause

