#include <QikApplication.h>

/**
This class is the entry point to the application.
*/
class CGuardGUIApplication : public CQikApplication
	{
public:
	static CApaApplication* NewApplication();
	
private: 
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};


