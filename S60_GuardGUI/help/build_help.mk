# ============================================================================
#  Name	 : build_help.mk
#  Part of  : GuardGUI
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

MAKMAKE : do_nothing


BLD : do_nothing

CLEAN : 
	del ..\help\GuardGUI.h01
	del ..\help\GuardGUI.h01.hrh
	del ..\help\GuardGUI.h04
	del ..\help\GuardGUI.h04.hrh
	del ..\help\GuardGUI.h05
	del ..\help\GuardGUI.h05.hrh
	cshlpcmp ..\help\GuardGUI.01.cshlp
	cshlpcmp ..\help\GuardGUI.05.cshlp
ifeq (WINS,$(findstring WINS, $(PLATFORM)))
	copy ..\help\GuardGUI.h01 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy ..\help\GuardGUI.h04 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy ..\help\GuardGUI.h05 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy ..\help\GuardGUI.h05 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help\GuardGUI_0x200131CC.hlp
endif

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES : do_nothing

FINAL : do_nothing
