
#ifndef GUARDGUIAPPUI_H_
#define GUARDGUIAPPUI_H_

#include <QikAppUi.h>
#include <QikCommand.h>
#include <timeouttimer.h>
#include "AboutView.h"


class CGuardGUIAppUi : public CQikAppUi, public MTimeOutNotifier
    {
public:
    CGuardGUIAppUi();
	// from CQikAppUi
	void ConstructL();
	~CGuardGUIAppUi();
	void MainTabActivatedL(TInt aTabId);	
	void HandleCommandL(CQikCommand& aCommand);	
    void TimerExpiredL(TAny* src);

private:
	HBufC* ReadUnicodeFileL(RFs& aFs, const TDesC& aFileName);
	TBool AskPasswordL(TDes& pass);
	void ShowInfoFromFileL(const TDesC& title, const TDesC& file);

private:
	TBool iGuiActive;
	CTimeOutTimer* iTimer;
	CAboutView* iAboutView;
	};
	
#endif 
