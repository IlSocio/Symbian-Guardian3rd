// HelloWorldDialog.cpp
//

#include "NumericControls.hrh"
#include "NumericEdwin.h"
#include "NumericSecreted.h"
#include "NumericDialog.h"
#include <EIKSECED.H> 
#include <GuardGUI_200107AF.rsg>


CNumericDialog::CNumericDialog(const TDesC& aTitle, TDes& aDataText, const TBool isSecret) : CEikDialog(), iTitle(aTitle), iText(aDataText)
{
	iSecreted = isSecret;
}


CNumericDialog::~CNumericDialog() 
{
}


void CNumericDialog::PrepareLC()
{
	if (iSecreted)
		CEikDialog::PrepareLC(R_NUMERIC_SECRETED_DIALOG);
	else 
		CEikDialog::PrepareLC(R_NUMERIC_EDWIN_DIALOG);
}


TInt CNumericDialog::ExecuteLD()
{
	if (iSecreted)
		return CEikDialog::ExecuteLD(R_NUMERIC_SECRETED_DIALOG);
	return CEikDialog::ExecuteLD(R_NUMERIC_EDWIN_DIALOG);
}


void CNumericDialog::PostLayoutDynInitL()
{
	CEikDialog::PostLayoutDynInitL();

	SetTitleL(iTitle);
	switch (iType)
	{
		case ECtNumericEdwin:
			{
			// iSecreted = False
			CNumericEdwin* theEdwin = (CNumericEdwin*) iCtrl;
			theEdwin->SetTextL(&iText);
			theEdwin->SetTextLimit(iText.MaxLength());
			theEdwin->SelectAllL();
			break;
			}
		case ECtNumericSecreted:
			{
			// iSecreted = True
			CNumericSecreted* secr = (CNumericSecreted*) iCtrl;
			secr->SetText(iText);
			break;
			}
	}
	RequestRelayout(iCtrl);
}


void CNumericDialog::HandleCommandL(CQikCommand& aCommand)
{
	if ((aCommand.Id() == EEikBidYes) ||
		(aCommand.Type() == EQikCommandTypeYes) ||
	    (aCommand.Type() == EQikCommandTypeDone))
	{
	switch (iType)
		{
		case ECtNumericEdwin:
			{
			CNumericEdwin* theEdwin = (CNumericEdwin*) iCtrl;
			iText.Zero();
			theEdwin->GetText(iText);
			break;
			}
		case ECtNumericSecreted:
			{
			CNumericSecreted* secr = (CNumericSecreted*) iCtrl;
			iText.Zero();
			secr->GetText(iText);
			break;
			}
		}			
	}
	CEikDialog::HandleCommandL(aCommand); 
}


SEikControlInfo CNumericDialog::CreateCustomControlL(TInt aControlType)
	{
	iCtrl = NULL;
	iType = aControlType;
	SEikControlInfo ctrl = {NULL, 0, 0};
	switch (aControlType)
		{
		case ECtNumericEdwin:
			{
			iCtrl = new(ELeave) CNumericEdwin;
			break;
			}
		case ECtNumericSecreted:
			{
			iCtrl = new(ELeave) CNumericSecreted;
			break;
			}
		}
	ctrl.iControl = iCtrl;
	return ctrl;
	}

