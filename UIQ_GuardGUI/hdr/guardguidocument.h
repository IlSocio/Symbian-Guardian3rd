// GuardGUIDocument.h
//
// © Barolo 2007. All rights reserved.
//

#include <QikDocument.h>

class CQikApplication;
class CQikAppUi;

class CGuardGUIDocument : public CQikDocument
	{
public:
	static CGuardGUIDocument* NewL(CQikApplication& aApp);
	~CGuardGUIDocument();
	
private: 
	// from CQikDocument
	CEikAppUi* CreateAppUiL();
	
	CGuardGUIDocument(CQikApplication& aApp);
	void ConstructL();
	};
