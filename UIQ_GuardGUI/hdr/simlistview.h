#ifndef SIMLISTVIEW_H_
#define SIMLISTVIEW_H_

#include <e32base.h>
#include <QikViewBase.h>
#include <QikListBox.h>
#include <QikMenuPopout.h>
#include <MQikListBoxData.h>
#include <MQikListBoxModel.h>
#include <MQikListBoxObserver.h>
#include "client.h"


class CSimListView : public CQikViewBase 
	{
public:
	static CSimListView* NewLC(CQikAppUi& aAppUi,const TVwsViewId aParentViewId);
	~CSimListView();
	
	TVwsViewId ViewId()const;
	
protected: 

	void ViewConstructL();
	void ViewActivatedL(const TVwsViewId &aPrevViewId,
						const	  TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage);
	void HandleCommandL(CQikCommand& aCommand);
	void TabActivatedL(TInt aTabId);
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	CQikCommand* DynInitOrDeleteCommandL(CQikCommand* aCommand, const CCoeControl& aControlAddingCommands);


private:
	void GetSelectedNameAndOperL(TDes& name, TDes& oper);
	CSimListView(CQikAppUi& aAppUi,const TVwsViewId aParentViewId);
	void ConstructL();
	void AddElemToListBoxL(const TDesC& aFirstText, const TDesC& aSecondText);
	void ClearListBoxL();
	void UpdateListBoxViewL();

private:
	RGuardian iGuardian;
	CQikMenuPopout* iMenuPopout;
	TInt iOldSel;
	};
	
	
#endif /*PROVA10VIEW3_H_*/
