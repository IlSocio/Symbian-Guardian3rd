dir /AD /S /B>tmpdirs.txt
for /F %%C IN (tmpdirs.txt) do call doRename_rsc %%C
del tmpdirs.txt
pause
