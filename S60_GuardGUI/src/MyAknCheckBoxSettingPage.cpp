/*
 ============================================================================
 Name		: CMyAknCheckBoxSettingPage.cpp
 Author	  : 
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CMyAknCheckBoxSettingPage implementation
 ============================================================================
 */

#include "MyAknCheckBoxSettingPage.h"

CMyAknCheckBoxSettingPage::CMyAknCheckBoxSettingPage(TInt aResourceID, CSelectionItemList* aItemArray) : CAknCheckBoxSettingPage(aResourceID, aItemArray)
	{
	// No implementation required
	}

CMyAknCheckBoxSettingPage::~CMyAknCheckBoxSettingPage()
	{
	}

CMyAknCheckBoxSettingPage* CMyAknCheckBoxSettingPage::NewLC(TInt aResourceID, CSelectionItemList* aItemArray)
	{
	CMyAknCheckBoxSettingPage* self =
			new (ELeave) CMyAknCheckBoxSettingPage(aResourceID, aItemArray);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CMyAknCheckBoxSettingPage* CMyAknCheckBoxSettingPage::NewL(TInt aResourceID, CSelectionItemList* aItemArray)
	{
	CMyAknCheckBoxSettingPage* self = CMyAknCheckBoxSettingPage::NewLC(aResourceID, aItemArray);
	CleanupStack::Pop(); // self;
	return self;
	}

void CMyAknCheckBoxSettingPage::ConstructL()
	{
	CAknCheckBoxSettingPage::ConstructL();
	}


// Necessario perche' su C5-03 il softkey Ok non viene visualizzato
void CMyAknCheckBoxSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent)
{
	if(aPointerEvent.iType==TPointerEvent::EButton1Down )
		{
		CAknSetStyleListBox* lb = ListBoxControl();
		CListBoxView* view = lb?lb->View():NULL;
		TInt selecteditemindex=-1;
		//by zjx calculate point in list and get itemindex of list.
		if(view->XYPosToItemIndex(aPointerEvent.iPosition,selecteditemindex))
			{
			if(selecteditemindex>=0)
				{
				CEikButtonGroupContainer *bgc;
				CCoeControl* MSK(NULL);
				CEikCba* cba(NULL);
				MopGetObject(bgc);
				if (bgc)
					{
					cba = (static_cast<CEikCba*> (bgc->ButtonGroup())); // downcast from MEikButtonGroup
					cba->SetCommandSetL(R_AVKON_SOFTKEYS_OK_CANCEL);
					if (cba)
						{
						cba->MakeCommandVisible(0,ETrue);
						cba->DimCommand(0,EFalse);
						cba->DrawNow();
						}
					}
				}
			}
		}
		CAknCheckBoxSettingPage::HandlePointerEventL(aPointerEvent);
	}


