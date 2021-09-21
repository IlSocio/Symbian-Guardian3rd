#ifndef SETTINGSVIEW_H_
#define SETTINGSVIEW_H_

#include <e32base.h>
#include <QikViewBase.h>
#include <QikListBox.h>
#include <QikMenuPopout.h>
#include <MQikListBoxData.h>
#include <MQikListBoxModel.h>
#include <MQikListBoxObserver.h>
#include "client.h"


class CSettingsView : public CQikViewBase
	{
public:
	static CSettingsView* NewLC(CQikAppUi& aAppUi,const TVwsViewId aParentViewId);
	~CSettingsView();
	
	TVwsViewId ViewId()const;
	
protected: 

	void ViewConstructL();
	void ViewActivatedL(const TVwsViewId &aPrevViewId,
						const	  TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage);
	void HandleCommandL(CQikCommand& aCommand);
	void TabActivatedL(TInt aTabId);
	//void HandleListBoxEventL(CQikListBox* aListBox, TQikListBoxEvent aEventType, TInt aItemIndex, TInt aSlotId);
	CQikCommand* DynInitOrDeleteCommandL(CQikCommand* aCommand, const CCoeControl& aControlAddingCommands);
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	void GetStarsL(TInt len, TDes& stars);


private:
	CSettingsView(CQikAppUi& aAppUi,const TVwsViewId aParentViewId);
	void ConstructL();
	void UpdateDataL(TInt aItemIndex, const TDesC& aText);
    TBool AskNumberL(TDes& number);
	TBool InputPasswordL(TDes& pass);


private:
	RGuardian iGuardian;
	CQikMenuPopout* iMenuPopout;
	TInt iOldSel;
	};
	
	
#endif /*PROVA10VIEW2_H_*/
