// HelloWorldDialog.cpp
//

#include "InfoDialog.h"
#include <EIKEDWIN.H> 
#include <EIKLABEL.H>
#include <QikControlProvider.h> 
#include <GuardGUI_200107AF.rsg>
#include <EIKRTED.h>
#include <FRMTVIEW.H>
#include <TXTRICH.H>
#include <EIKGTED.H>

// E' strettamente legato a DLG_Info.RA
// Bisognerebbe fare una serie di Dialogs standard come questo e legarli ad un certo RSC...

CInfoDialog::CInfoDialog(const TDesC& aTitle, const TDesC& aText) : CQikSimpleDialog(), iText(aText), iTitle(aTitle)
{
}


CInfoDialog::~CInfoDialog() 
{
}

/*TInt  CMyEdwin::NumberOfLines()
{
 return(TextLayout()->GetLineNumber(TextLength()));
}*/

//	CEikRichTextEditor* label = LocateControlByUniqueHandle<CEikRichTextEditor>(1);

void CInfoDialog::PostLayoutDynInitL()
{
	CQikSimpleDialog::PostLayoutDynInitL();

	SetTitleTextL(iTitle);
//	CEikRichTextEditor* label = LocateControlByUniqueHandle<CEikRichTextEditor>(1);
//	CEikEdwin* label = LocateControlByUniqueHandle<CEikEdwin>(1);
//	CPlainText* plain = label->Text();
	CEikGlobalTextEditor* label = LocateControlByUniqueHandle<CEikGlobalTextEditor>(1);
	label->SetTextL(&iText);
//	label->SetWidth(200);
//	label->SetHeight(200);
/*	CGlobalText* plain = label->GlobalText();
	TInt len = plain->LdDocumentLength();
	plain->InsertL(0, _L("prova1"));
	len = plain->LdDocumentLength();
	plain->InsertL(plain->DocumentLength(), CEditableText::ELineBreak);
	len = plain->LdDocumentLength();
	plain->InsertL(plain->LdDocumentLength(), _L("prova2"));
	len = plain->LdDocumentLength();
	plain->InsertL(plain->DocumentLength(), CEditableText::ELineBreak);
	len = plain->LdDocumentLength();
	plain->InsertL(plain->DocumentLength(), _L("prova3"));
	len = plain->LdDocumentLength();
	plain->InsertL(plain->DocumentLength(), CEditableText::EParagraphDelimiter);
*/
//	CEikScrollBarFrame* scroll = label->CreateScrollBarFrameL();
//	scroll->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

	CTextView* textView = label->TextView();
	textView->EnablePictureFrameL(EFalse);
	label->SetFocusing(EFalse); // <==

	RequestRelayout(label);

	// CEditableText::ELineBreak
	// 0x2029  CEditableText::EParagraphDelimiter

// Spazio tra le linee
//CParaFormat paraFormat;
//TParaFormatMask paraFormatMask;
//paraFormatMask.SetAll(); // set the mask
//paraFormat.iLineSpacingInTwips = 100;
//iEdwin->ApplyParaFormatL(&paraFormat, paraFormatMask);
}


void CInfoDialog::HandleCommandL(CQikCommand& aCommand)
{
	if ((aCommand.Id() == EEikBidYes) ||
		(aCommand.Type() == EQikCommandTypeYes) ||
	    (aCommand.Type() == EQikCommandTypeDone))
	{
	}
	CQikSimpleDialog::HandleCommandL(aCommand); 
}


void CInfoDialog::PrepareLC()
{
	// Cosi' e' possibile modificare il Dialog aggiungendo es delle icone prima di mostrarlo...
	CQikSimpleDialog::PrepareLC(R_INFO_DIALOG);
}


TInt CInfoDialog::ExecuteLD()
{
	return CQikSimpleDialog::ExecuteLD(R_INFO_DIALOG); 
}

