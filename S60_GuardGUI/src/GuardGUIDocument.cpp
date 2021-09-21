/*
============================================================================
 Name        : CGuardGUIDocument from GuardGUIDocument.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CGuardGUIDocument implementation
============================================================================
*/

// INCLUDE FILES
#include "GuardGUIDocument.h"
#include "GuardGUIAppui.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CGuardGUIDocument::CGuardGUIDocument(CEikApplication& aApp)
: CAknDocument(aApp)	
	{
	}

// destructor
CGuardGUIDocument::~CGuardGUIDocument()
	{
	}

// EPOC default constructor can leave.
void CGuardGUIDocument::ConstructL()
	{
	}

// Two-phased constructor.
CGuardGUIDocument* CGuardGUIDocument::NewL(
		CEikApplication& aApp) // CGuardGUIApp reference
	{
	CGuardGUIDocument* self = new (ELeave) CGuardGUIDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop();

	return self;
	}
	
// ----------------------------------------------------
// CGuardGUIDocument::CreateAppUiL()
// constructs CGuardGUIAppUi
// ----------------------------------------------------
//
CEikAppUi* CGuardGUIDocument::CreateAppUiL()
	{
	return new (ELeave) CGuardGUIAppUi;
	}
