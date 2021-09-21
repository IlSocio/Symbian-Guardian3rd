SMS Utilities

Installation to S60 3rd Edition SDK for Symbian OS, Maintenance Release.

Copy this archive to EPOCROOT and unzip. All files listed below will be 
installed.

API is used through these headers:
epoc32\include\smsuact.h
epoc32\include\smsuaddr.h
epoc32\include\smsulog.h
epoc32\include\smsulog.inl
epoc32\include\smsuset.h
epoc32\include\smsuset.inl
epoc32\include\smsustrm.h
epoc32\include\smsustrm.inl

Libraries related to this API:
epoc32\release\armv5\lib\smsu.dso
epoc32\release\armv5\lib\smsu.lib
epoc32\release\armv5\lib\smsu{000a0000}.dso
epoc32\release\armv5\lib\smsu{000a0000}.lib

API documentation can be found in PartnerAPIDoc\SMSUtilities\index.html.
README.txt can be found in PartnerAPIDoc\SMSUtilities\README.txt.

Notes about this API:

Please notice the following issues with this API:
1. Nokia is not giving any binary compatibility promise for this
API; neither between platform versions or within a platform version.
2. You must test your application with each device that the
application can be installed on. This is needed to ensure the best
possible user experience. To prevent application installation on
other than tested devices, define the Product ID(s) in the .pkg file.
More information can be found in the document S60 Platform:
Identification Codes available on the Forum Nokia Web site.


Copyright (c) 2001-2007 Nokia Corporation. All rights reserved. 
Nokia and Nokia Connecting People are registered trademarks of 
Nokia Corporation.
