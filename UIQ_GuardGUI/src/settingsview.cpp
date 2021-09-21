

#include <e32base.h>
#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 
#include <GULICON.H>
#include <MQikListBoxData.h>
#include <MQikListBoxModel.h>
#include <ContacUIReturnData.h>
#include <ContacuiListDialog.h>
#include <QikSimpleDialog.h>

#include "srverr.h"
#include "common.hrh"
#include "textdialog.h"
#include "settings_consts.h"
#include "numericdialog.h"
#include "settingsview.h"
#include "guardguiExternalInterface.h"

#include "settview.hrh"
#include <GuardGUI_200107AF.rsg>
#include <GuardBMP_200107AF.mbg>
#include <EIKEDWIN.H>

#include "guardguiappui.h"

CSettingsView* CSettingsView::NewLC(CQikAppUi& aAppUi, const TVwsViewId aParentViewId)
	{
	CSettingsView* self = new (ELeave) CSettingsView(aAppUi,aParentViewId);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CSettingsView::CSettingsView(CQikAppUi& aAppUi, const TVwsViewId aParentViewId) 
: CQikViewBase(aAppUi, aParentViewId)
	{
	}

void CSettingsView::ConstructL()
	{
	BaseConstructL();
	iGuardian.Connect();
	iMenuPopout = CQikMenuPopout::NewL(*iEikonEnv, *this);
	}

CSettingsView::~CSettingsView()
	{	
	if (iMenuPopout)
		delete iMenuPopout;
	iGuardian.Close();
	}


void CSettingsView::GetStarsL(TInt len, TDes& stars)
	{
	stars.Zero();
	for (int i=0; i<len; i++)
		stars.Append(_L("*"));
	}


void CSettingsView::UpdateDataL(TInt aItemIndex, const TDesC& aText)
    {
    CQikListBox* listBox = LocateControlByUniqueHandle<CQikListBox>(ESettViewListBox);
	if (!listBox) return;

    MQikListBoxModel& model = listBox->Model();
    model.ModelBeginUpdateLC();
    MQikListBoxData* data = model.RetrieveDataL(aItemIndex);
    
    // To make sure data is closed in case of a Leave   
	CleanupClosePushL(*data);
    
	data->SetTextL(aText, EQikListBoxSlotText2);
    CleanupStack::PopAndDestroy(); // data

    // Tell the model a particular data item has been updated
    model.DataUpdatedL(aItemIndex);
    model.ModelEndUpdateL();   
    }


void CSettingsView::ViewConstructL()
	{
       ViewConstructFromResourceL(R_SETTINGS_VIEW_UI_CONFIGURATIONS); //, R_SETTINGS_VIEW_CONTROLS);

	   CGulIcon* myIcon = NULL;
       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afAbout, EMbmGuardbmp_200107afAbout_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(1, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();
															 
       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afSettings, EMbmGuardbmp_200107afSettings_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(2, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();

       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afSim, EMbmGuardbmp_200107afSim_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(3, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();

       myIcon = iEikonEnv->CreateIconL(_L("\\Resource\\Apps\\GuardBMP_200107AF.mbm"), EMbmGuardbmp_200107afSim, EMbmGuardbmp_200107afSim_mask);
       CleanupStack::PushL(myIcon);
       AddTabL(4, _L(""), myIcon->Bitmap(), myIcon->Mask());
       myIcon->SetBitmapsOwnedExternally(ETrue);
	   CleanupStack::PopAndDestroy();


       CQikCommandManager& man = CQikCommandManager::Static(*iEikonEnv);
       man.InsertIntoCommandListL(*this, *this, R_COMMON_COMMANDS);
   	}
	

void CSettingsView::ViewActivatedL(const TVwsViewId &aPrevViewId,
							  const TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage)
	{
	if (this->ActiveTabId()!= 2)
		ActivateTabL(2);

	// TODO: Leggi da risorse...
	SetAppTitleNameL(_L("Settings"));

	TBuf<20> enab;
	if (iGuardian.IsEnabled()) 
		iCoeEnv->ReadResource(enab, R_TXT_ENABLED );
	else 
		iCoeEnv->ReadResource(enab, R_TXT_DISABLED );
	TBuf<KNUMBER_LEN> number;
	TBuf<KMSG_LEN> message;
	TBuf<KPASS_LEN> pass;
	iGuardian.GetDestAddress(number);
	iGuardian.GetMessage(message);
	iGuardian.GetPassword(pass);
	GetStarsL(pass.Length(), pass);

	UpdateDataL(0, enab);
	UpdateDataL(1, number);
	UpdateDataL(2, message);
	UpdateDataL(3, pass);
	}


void CSettingsView::TabActivatedL(TInt aTabId)
	{
	if (aTabId == 2) return;
	CGuardGUIAppUi& appUi = (CGuardGUIAppUi &) iQikAppUi;
	appUi.MainTabActivatedL(aTabId);	
	}


TVwsViewId CSettingsView::ViewId()const
	{
	return TVwsViewId(KUidGuardGUIApp, KUidSettingsView);
	}


CQikCommand* CSettingsView::DynInitOrDeleteCommandL(CQikCommand* aCommand, const CCoeControl& aControlAddingCommands)
{
	switch(aCommand->Id())
	{
		case EQikListBoxCmdSelect:
		{
			aCommand->SetAvailable(EFalse);
			break;
		}
    }
	return aCommand;
}


void CSettingsView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
  {
  CQikListBox* listBox = LocateControlByUniqueHandle<CQikListBox>(ESettViewListBox);
  if (!listBox) return;

  switch(aPointerEvent.iType)
    {
	case TPointerEvent::EButton1Down:
	  iOldSel = listBox->CurrentItemIndex();
	  break;
	}
	  
  CQikViewBase::HandlePointerEventL(aPointerEvent);

  switch(aPointerEvent.iType)
    {
	case TPointerEvent::EButton1Up:
	  TInt newSel = listBox->CurrentItemIndex();
	  if (iOldSel != newSel) return;
      TPoint position(aPointerEvent.iPosition);
      position += iEikonEnv->EikAppUi()->ClientRect().iTl;

      iMenuPopout->SetCommandListL(R_POPOUT_SETT_COMMANDS);
      iMenuPopout->DisplayL(position, EPopupTargetTopLeft);
      break;

    default:
      break;        
    }
  }



TBool CSettingsView::AskNumberL(TDes& number)
  {
	TBool	retVal(EFalse);
 
	RPointerArray<CContacuiReturnData> *resultArray = new (ELeave) RPointerArray<CContacuiReturnData>(1); // granularity = 1 -> only 1 number should be selected
	CleanupStack::PushL(resultArray);
 
	// let the user select a phonenumber from the phonebook    EListDialogNoFisheye 
	if(CContactUiListDialog::RunDlgLD(*resultArray, EListDialogSingleSelect, CContactDatabase::EUnfiltered))
	{
//		TBool smsAble	= (*resultArray)[0]->IsSmsable();
//		TBool phoneAble	= (*resultArray)[0]->IsPhonable();
		TBool smsAble = ETrue;
		TBool phoneAble = ETrue;

		// the selected number is only valid if only ONE number was selected
		// AND this one is sms or phone able
		if ((resultArray->Count() == 1) && (smsAble || phoneAble))
		{
			number.Copy((*resultArray)[0]->ReturnedData());			
			retVal = ETrue;	 // the selection was successfull
		}
	}
 
	// cleanup
	resultArray->Reset(); 
	CleanupStack::PopAndDestroy();

	return retVal;
  }


TBool CSettingsView::InputPasswordL(TDes& pass)
{
	for (;;)
	{
		CNumericDialog* dlg = new(ELeave) CNumericDialog(_L("Code:"), pass, EFalse);
		if ( !dlg->ExecuteLD() ) 
			return EFalse; // Pigiato Cancel

		// Pigiato OK...
		if (pass.Length() >= 5) 
			return ETrue;

		// TODO: MESSAGGIO DI WARNING...
//			WarnMsg(R_ERR_SHORT_PASS);
	}
}


void CSettingsView::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
	  case ESettViewEnable:
		  {
			TInt ris = iGuardian.SetEnabled(ETrue);
			switch (ris) 
			{
				case KErrPassNotSet:
					// TODO: WarnMsg(R_ERR_NO_PASS);
				return;
				case KErrPassShort:
					// TODO: WarnMsg(R_ERR_SHORT_PASS);
				return;
				case KErrNumberNotSet:
					// TODO: WarnMsg(R_ERR_NO_NUMBER);
				return;
				case KErrSameValue:
				return;
			}

			// Avvia Guardian...
			const TUid KGuardianUid3={0x200107AE};
			_LIT(KGuardianImage, "Guardian_200107AE");
			const TUidType guardUid(KNullUid, KNullUid, KGuardianUid3);
			RProcess guardianProtection;
			User::LeaveIfError( guardianProtection.Create(KGuardianImage, KNullDesC, guardUid) );
			guardianProtection.Resume();	// logon OK - start the server
			guardianProtection.Close();

			TBuf<20> enab;
			iCoeEnv->ReadResource(enab, R_TXT_ENABLED );
			UpdateDataL(0, enab);
			break;
		  }
	  case ESettViewDisable:
		  {
		  TInt ris = iGuardian.SetEnabled(EFalse);
		  TBuf<20> disab;
		  iCoeEnv->ReadResource(disab, R_TXT_DISABLED );
		  UpdateDataL(0, disab);
		  break;
		  }

      case ESettViewChange_Pop:
      case ESettViewChange:
		  {
			CQikListBox* listBox = LocateControlByUniqueHandle<CQikListBox>(ESettViewListBox);
			if (!listBox) return;
			TInt sel = listBox->CurrentItemIndex();

			switch ( sel ) 
				{
				case 0: // Enabled
					{
						TInt commId = 0;
						if (iGuardian.IsEnabled())
							commId = ESettViewDisable;
						else 
							commId = ESettViewEnable;
						CQikCommand* comm = CQikCommand::NewLC(commId);
						HandleCommandL( *comm );
						CleanupStack::PopAndDestroy();
						break;
					}
				case 1: 
					{	// Number
						TBuf<KNUMBER_LEN> number;
						iGuardian.GetDestAddress(number);
						if ( !AskNumberL( number ) ) return;
						iGuardian.SetDestAddress(number);
						UpdateDataL(1, number);
						break;
					}
				case 2: // Text
					{
						TBuf<KMSG_LEN> message;
						iGuardian.GetMessage(message);

						CTextDialog* dialog = new (ELeave) CTextDialog(_L("Message:"), message);
						if ( !dialog->ExecuteLD() ) return;

						iGuardian.SetMessage(message);
						UpdateDataL(2, message);
						break;
					}
				case 3: // Password
					{
						TBuf<KPASS_LEN> pass = _L("");
						iGuardian.GetPassword(pass);
						if ( !InputPasswordL( pass ) ) return;
						iGuardian.SetPassword(pass);
						GetStarsL(pass.Length(), pass);
						UpdateDataL(3, pass);
						break;
					}
				}
			break;
		  }
      default:
         CQikViewBase::HandleCommandL(aCommand);
         break;
      }
   }
