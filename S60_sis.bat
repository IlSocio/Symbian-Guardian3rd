del *.sisx
cd s60_guardgui\sis\
del *.sisx
del *.sis
makesis emb_guardian.pkg
call signsis emb_guardian.sis emb_guardian.sisx c:\progettiincorso\rda.cer  c:\progettiincorso\rda.key
move *.sisx ..\..
cd ..\..
pause