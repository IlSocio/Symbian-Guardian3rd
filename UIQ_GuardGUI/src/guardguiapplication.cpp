
#include <eikstart.h>

#include "guardguiApplication.h"
#include "guardguiExternalInterface.h"
#include "GuardGUIDocument.h"

CApaApplication* CGuardGUIApplication::NewApplication()
	{
	return new CGuardGUIApplication();
	}
	
CApaDocument* CGuardGUIApplication::CreateDocumentL()
	{
	return CGuardGUIDocument::NewL(*this);
	}	
	
TUid CGuardGUIApplication::AppDllUid() const
	{
	return KUidGuardGUIApp;
	}

TInt E32Main()
	{
	return EikStart::RunApplication(CGuardGUIApplication::NewApplication);
	}