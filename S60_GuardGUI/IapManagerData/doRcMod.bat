@echo #include "%1.rls">tmp.rss
@type IapManager.rss>>tmp.rss
@call epocrc -u -I\Symbian\9.1\S60_3rd_MR\Epoc32\include\ tmp.rss -o%1.rsc -h\Symbian\9.1\S60_3rd_MR\Epoc32\include\IapManager.rsg

@REM call epocrc -DOPER_%1 -u -I\Symbian\9.1\S60_3rd_MR\Epoc32\include\ IapManager.rss -o%1.rsc -h\Symbian\9.1\S60_3rd_MR\Epoc32\include\IapManager.rsg
@del tmp.rss

@echo "..\IapManagerData\%1.rsc"	- "c:\private\200131CC\%1\Internet .rsc">>pkg.pkg
