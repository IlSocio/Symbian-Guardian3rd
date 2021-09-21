#ifndef ABOUTVIEW_H_
#define ABOUTVIEW_H_

#include <QikViewBase.h>
#include <timeouttimer.h>



class CAboutView : public CQikViewBase, public MTimeOutNotifier
	{
public:
	static CAboutView* NewLC(CQikAppUi& aAppUi,const TVwsViewId aParentViewId);
	~CAboutView();
	
	TVwsViewId ViewId()const;
	void TimerExpiredL(TAny* src);
	
protected: 

	void ViewConstructL();
	void ViewActivatedL(const TVwsViewId &aPrevViewId,
						const	  TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage);
	void HandleCommandL(CQikCommand& aCommand);
	void TabActivatedL(TInt aTabId);

	void Draw(const TRect &aRect) const;

private:
	CAboutView(CQikAppUi& aAppUi,const TVwsViewId aParentViewId);
	void ConstructL();

private:
	CTimeOutTimer* iTimer;
	CFbsBitmap* iBitmap;
	};
	
	
#endif 
