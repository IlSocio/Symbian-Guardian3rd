// HelloWorldDialog.h
//

#ifndef NUMERIC_DIALOG_H
#define NUMERIC_DIALOG_H

#include <eikdialg.h>
#include <QikCommand.h>


class CNumericDialog : public CEikDialog
	{
public:
	CNumericDialog(const TDesC& aTitle, TDes& aDataText, TBool isSecret = EFalse);
	~CNumericDialog();
	SEikControlInfo CreateCustomControlL(TInt aControlType);
	void HandleCommandL(CQikCommand& aCommand);
	void PostLayoutDynInitL();
	// TBool OkToExitL(TInt aButtonId);
	void PrepareLC();
	TInt ExecuteLD();

private:
	TPtrC iTitle;
	TBool iSecreted;
	CCoeControl* iCtrl;
	TInt iType;
	TDes& iText;
	};

#endif // HELLOWORLDDIALOG_H
