// GuardGUIDocument.cpp
//
// © Symbian Software Ltd 2005. All rights reserved.
//

#include <QikApplication.h>

#include "GuardGUIDocument.h"
#include "GuardGUIappUi.h"

CEikAppUi* CGuardGUIDocument::CreateAppUiL()
	{
	return new (ELeave) CGuardGUIAppUi;
	}
	
CGuardGUIDocument* CGuardGUIDocument::NewL(CQikApplication& aApp)
	{
	CGuardGUIDocument* self = new (ELeave) CGuardGUIDocument(aApp);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

void CGuardGUIDocument::ConstructL()
	{
	}

CGuardGUIDocument:: ~CGuardGUIDocument()
	{
	
	}

CGuardGUIDocument::CGuardGUIDocument(CQikApplication& aApp)
	: CQikDocument(aApp)
	{
	}