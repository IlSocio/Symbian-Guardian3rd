del pkg.pkg
dir *.rls /B>tmpFiles.txt
for /F %%C IN (tmpFiles.txt) do call doRcMod.bat %%~nC
del tmpFiles.txt
pause

@REM call doRcMod.bat 222_88_wind
@REM call doRcMod.bat 222_10_voda
@REM call doRcMod.bat 222_10_poste
@REM call doRcMod.bat 222_01_tim
@REM call doRcMod.bat 222_99_tre


echo Attenzione controllare il contenuto "pkg.pkg" e confrontarlo con "original pkg.pkg"
pause
