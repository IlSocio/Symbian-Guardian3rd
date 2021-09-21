

#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include <QikSimpleDialog.h>
#include <QikCommand.h>


class CInfoDialog : public CQikSimpleDialog
	{
public:
	CInfoDialog(const TDesC& aTitle, const TDesC& aDataText);
	~CInfoDialog();
	void HandleCommandL(CQikCommand& aCommand);
	void PostLayoutDynInitL();
	void PrepareLC(); // Da usare insieme a RunL...
	TInt ExecuteLD();

private:
	TPtrC iTitle;
	TPtrC iText;
	};

#endif // HELLOWORLDDIALOG_H
