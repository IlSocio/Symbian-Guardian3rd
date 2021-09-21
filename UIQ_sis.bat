del *.sisx
cd uiq_guardgui\sis\
del uiq_guardgui.sis
call makesis uiq_guardgui.pkg
call sisacs uiq_guardgui.sis
copy *.sisx ..\..
cd ..\..
