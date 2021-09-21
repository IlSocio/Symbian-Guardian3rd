cd %1
dir *.rsc /b > tmp.txt
for /F %%C IN (tmp.txt) do rename %%C "Internet %%C"
del tmp.txt
cd ..
pause
