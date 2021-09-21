
#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 
#include <GULICON.H>

#include "srverr.h"
#include "settings_consts.h"
#include "infodialog.h"
#include "textdialog.h"
#include "common.hrh"
#include "ProtectionView.h"
#include "protview.hrh"

#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include <GuardBMP_200107AF.mbg>

#include "guardguiappui.h"


CProtectionView* CProtectionView::NewLC(CQikAppUi& aAppUi,const TVwsViewId aParentViewId)
	{
	CProtectionView* self = new (ELeave) CProtectionView(aAppUi,aParentViewId);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CProtectionView::CProtectionView(CQikAppUi& aAppUi,const TVwsViewId aParentViewId) 
: CQikViewBase(aAppUi, aParentViewId)
	{
	}

void CProtectionView::ConstructL()
	{
	BaseConstructL();
	iGuardian.Connect();
	iMenuPopout = CQikMenuPopout::NewL(*iEikonEnv, *this);
	}

CProtectionView::~CProtectionView()
	{	
	if (iMenuPopout)
		delete iMenuPopout;
	iGuardian.Close();
	}


void CProtectionView::ViewConstructL()
	{
       ViewConstructFromResourceL(R_PROTECTION_VIEW_UI_CONFIGURATIONS);
              
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
	

void CProtectionView::ViewActivatedL(const TVwsViewId &aPrevViewId,
							  const TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage)
	{
	if (this->ActiveTabId() != 3)
		ActivateTabL(3);
	SetAppTitleNameL(_L("Authorized Sim"));

	// Popola la listbox...
	UpdateListBoxViewL();
	}


void CProtectionView::TabActivatedL(TInt aTabId)
	{
	if (aTabId == 3) return;
	CGuardGUIAppUi& appUi = (CGuardGUIAppUi &) iQikAppUi;
	appUi.MainTabActivatedL(aTabId);	
	}


TVwsViewId CProtectionView::ViewId()const
	{
	return TVwsViewId(KUidGuardGUIApp, KUidProtListView);
	}


CQikCommand* CProtectionView::DynInitOrDeleteCommandL(CQikCommand* aCommand, const CCoeControl& aControlAddingCommands)
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


void CProtectionView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
  {
  CQikListBox* listBox = LocateControlByUniqueHandle<CQikListBox>(EProtViewListBox);
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

      iMenuPopout->SetCommandListL(R_POPOUT_SIM_COMMANDS);
      iMenuPopout->DisplayL(position, EPopupTargetTopLeft);
      break;

    default:
      break;        
    }
  }


 void CProtectionView::UpdateListBoxViewL()
  {
	ClearListBoxL();
  	RArray<TImsiName> nameList;
  	CleanupClosePushL(nameList);
  	RArray<TOperName> operList;
  	CleanupClosePushL(operList);
  	iGuardian.GetAuthorizedListL(nameList, operList);
	for (int i=0; i<operList.Count(); i++) 
	{
		AddElemToListBoxL(nameList[i], operList[i]);
	}
	CleanupStack::PopAndDestroy(2); // imsiList, nameList
  	
/*	ClearListBoxL();

	CDesCArrayFlat* imsiList = new (ELeave) CDesCArrayFlat(10);
	CleanupStack::PushL(imsiList);
	CDesCArrayFlat* nameList = new (ELeave) CDesCArrayFlat(10);
	CleanupStack::PushL(nameList);
	iGuardian.GetAuthorizedListL(*imsiList, *nameList);

	for (int i=0; i<imsiList->Count(); i++) 
	{
		AddElemToListBoxL((*nameList)[i], (*imsiList)[i]);
	}

	CleanupStack::PopAndDestroy(2); // imsiList, nameList*/
	
/*	RArray<TImsiName> nameList;
	CleanupClosePushL(nameList);
	RArray<TOperName> operList;
	CleanupClosePushL(operList);
	iGuardian.GetAuthorizedListL(nameList, operList);
	iContainer->UpdateListBoxViewL(nameList, operList);
	CleanupStack::PopAndDestroy(2); // nameList, operList*/
  }


void CProtectionView::ClearListBoxL()
	{
    // Get a pointer to the List Box control
    CQikListBox* lbx = LocateControlByUniqueHandle<CQikListBox>(EProtViewListBox);
    if(!lbx) return;
    MQikListBoxModel& model(lbx->Model());
	model.RemoveAllDataL();
	}


void CProtectionView::AddElemToListBoxL(const TDesC& aFirstText, const TDesC& aSecondText)
    {
    // Get a pointer to the List Box control
    CQikListBox* lbx = LocateControlByUniqueHandle<CQikListBox>(EProtViewListBox);
    if(lbx)
        {
        MQikListBoxModel& model(lbx->Model());
        // Something has now been put on the Cleanup Stack
        model.ModelBeginUpdateLC();
        
        // Puts an item on the Cleanup Stack using CleanupClosePushL()
		MQikListBoxData* data = model.NewDataLC(MQikListBoxModel::EDataNormal);

        // aFirstText is added to be shown in layout slot EQikListBoxSlotText1  
        data->AddTextL(aFirstText, EQikListBoxSlotText1);
        
        // aSecondText is added to be shown in layout slot EQikListBoxSlotText2.        
        data->AddTextL(aSecondText, EQikListBoxSlotText2);       
        
        // Does a Close() on data       
        CleanupStack::PopAndDestroy(data);
        
        // This updates the List Box and removes the items
        // on the Cleanup Stack added by ModelBeginUpdateLC     
        model.ModelEndUpdateL();
        }
    }


void CProtectionView::GetSelectedNameAndOperL(TDes& name, TDes& oper)
{
    CQikListBox* listBox = LocateControlByUniqueHandle<CQikListBox>(EProtViewListBox);
    if(!listBox) return;

	TInt index = listBox->CurrentItemIndex();
    MQikListBoxModel& model = listBox->Model();
    MQikListBoxData* data = model.RetrieveDataL(index);
	CleanupClosePushL(*data);
	name = data->Text(EQikListBoxSlotText1);
	oper = data->Text(EQikListBoxSlotText2);
    CleanupStack::PopAndDestroy(); // data
}


void CProtectionView::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
      case ESimViewRen_Pop:
      case ESimViewRen:
		{
			TOperName oper;
			TImsiName name;
			GetSelectedNameAndOperL(name, oper);
			if (name.Length() == 0) return;
			TImsiName oldName;
			oldName.Copy(name);
			
			// TODO: if (!AskSimNameL(name)) return;
			
			CTextDialog* dialog = new (ELeave) CTextDialog(_L("Sim Name:"), name);
			if (!dialog->ExecuteLD()) return;
			TInt ris = iGuardian.RenameSim(oldName, name);
			if (ris == KErrSimAlreadyExists)
			{
				// TODO: Messaggio di Warning: Questo nome e' gia' esistente.
			}
			UpdateListBoxViewL();
	        break;
		}
      case ESimViewRem_Pop:
      case ESimViewRem:
		{    
			TOperName oper;
			TImsiName name;
			GetSelectedNameAndOperL(name, oper);
			if (name.Length() == 0) return;
			if (iGuardian.UnRegisterSim(name) == KErrSimOnlyAvail)
			{
				// TODO: Notes::WarningL( R_ERR_SIM0 );
				// TODO: Se c'e' stato un errore spara il messaggio...
				// TODO: WarnMsg( R_ERR_SIM0 );
				return ;
			}
			UpdateListBoxViewL();
			break;
		}
      default:
         CQikViewBase::HandleCommandL(aCommand);
         break;
      }
   }

