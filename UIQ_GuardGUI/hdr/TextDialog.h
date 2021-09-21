

#ifndef TEXT_DIALOG_H
#define TEXT_DIALOG_H

#include <QikSimpleDialog.h>
#include <QikCommand.h>


class CTextDialog : public CQikSimpleDialog
	{
public:
	CTextDialog(const TDesC& aTitle, TDes& aDataText);
	~CTextDialog();
	void HandleCommandL(CQikCommand& aCommand);
	void PostLayoutDynInitL();
	void PrepareLC(); // Da usare insieme a RunL...
	TInt ExecuteLD();

private:
	TPtrC iTitle;
	TDes& iText;
	};

#endif // HELLOWORLDDIALOG_H
