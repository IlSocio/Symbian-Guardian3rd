// HelloWorldDialog.cpp
//

#include "TextDialog.h"
#include <EIKEDWIN.H> 
#include <QikControlProvider.h> 
#include <GuardGUI_200107AF.rsg>

// E' strettamente legato a DLG_TEXT.RA
// Bisognerebbe fare una serie di Dialogs standard come questo e legarli ad un certo RSC...

CTextDialog::CTextDialog(const TDesC& aTitle, TDes& aDataText) : CQikSimpleDialog(), iTitle(aTitle), iText(aDataText)
{
}


CTextDialog::~CTextDialog() 
{
}


void CTextDialog::PostLayoutDynInitL()
{
	CQikSimpleDialog::PostLayoutDynInitL();

	SetTitleTextL(iTitle);
	CEikEdwin* theEdwin = LocateControlByUniqueHandle<CEikEdwin>(1);
	theEdwin->SetTextL(&iText);
	theEdwin->SetTextLimit(iText.MaxLength());
	theEdwin->SelectAllL();
	RequestRelayout(theEdwin);
}


void CTextDialog::HandleCommandL(CQikCommand& aCommand)
{
	if ((aCommand.Id() == EEikBidYes) ||
		(aCommand.Type() == EQikCommandTypeYes) ||
	    (aCommand.Type() == EQikCommandTypeDone))
	{
		CEikEdwin* theEdwin = LocateControlByUniqueHandle<CEikEdwin>(1);
		iText.Zero();
		theEdwin->GetText(iText);
	}
	CQikSimpleDialog::HandleCommandL(aCommand); 
}


void CTextDialog::PrepareLC()
{
	// Cosi' e' possibile modificare il Dialog aggiungendo es delle icone prima di mostrarlo...
	CQikSimpleDialog::PrepareLC(R_DIALOG_MESSAGE);
}


TInt CTextDialog::ExecuteLD()
{
	return CQikSimpleDialog::ExecuteLD(R_DIALOG_MESSAGE); 
}

