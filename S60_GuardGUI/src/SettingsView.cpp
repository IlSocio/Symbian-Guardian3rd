/*
============================================================================
 Name        : CSettingsView from GuardGUIView2.h
 Author      : Marco Bellino
 Version     :
 Copyright   : All Rights Reserved
 Description : CSettingsView implementation
============================================================================
*/
#include "GuardGUI.hrh" // Per avere i valori di EChange, EEnable, EDisable
#include "SettingsView.h"
#include "SettingsContainer.h"
#include "guardguiappui.h"
#include "GuardGUIconsts.h"
#include "MyAknCheckBoxSettingPage.h"

#include <GuardGUI_200131CC.rsg>

#include <FuzzyByte\Notes.h>
#include <FuzzyByte\GuiUtils.h>
#include <FuzzyByte\Queries.h>
#include <FuzzyByte\Guardian\srverr.h>
#include <FuzzyByte\Guardian\settings_consts.h>

#include <aknradiobuttonsettingpage.h>
#include <AknCheckBoxSettingPage.h>
#include <aknviewappui.h>
#include <avkon.hrh>
#include <aknconsts.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <aknlists.h>
#include <CPbkContactEngine.h>
#include <RPbkViewResourceFile.h>
#include <CPbkSingleEntryFetchDlg.h>
#include <cntdb.h>
#include <CPbkSmsAddressSelect.h>
#include <TPbkContactItemField.h>
#include <eikmenup.h>
#include <akntitle.h>
#include <aknutils.h>
#include <mmf\common\mmfcontrollerpluginresolver.h>


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSettingsView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CSettingsView::ConstructL()
	{
	BaseConstructL( R_GUARDGUI_VIEW2 );
	User::LeaveIfError( iGuardian.Connect() );
	iTouchSupported = EFalse;
	iAcceptTouchEvents = EFalse;
	}

// ---------------------------------------------------------
// CSettingsView::~CSettingsView()
// destructor
// ---------------------------------------------------------
//
CSettingsView::~CSettingsView()
	{
	if ( iContainer )
		{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		}	
	if (iMonitorList)
		{
		iMonitorList->ResetAndDestroy();
		delete iMonitorList;
		iMonitorList = NULL;
		}
	delete iContainer;
	iGuardian.Close();
	}

// ---------------------------------------------------------
// TUid CSettingsView::Id()
//
// ---------------------------------------------------------
//
TUid CSettingsView::Id() const
	{
	return KView2Id;
	}

//const TInt KTimeValues[] = {0, 5, 10, 20, 30, 60, 60*2, 60*5, 60*10, 60*30, 60*60, 60*60*2, 60*60*5, 60*60*10, -1};
//const TInt KTimeLabels[] = {0, 5, 10, 20, 30, 1, 2, 5, 10, 30, 1, 2, 5, 10, -1};
//const TInt KTimeUnits[]  = {R_SEC, R_SEC, R_SEC, R_SEC, R_SEC, R_MIN1, R_MIN, R_MIN, R_MIN, R_MIN, R_HOU1, R_HOU, R_HOU, R_HOU, R_NEVER}; // RISORSE PER UNITA' DI MISURA
const TInt KTimeValues[] = {0, 5, 10, 20, 30, 60, 60*2, 60*5, 60*10, 60*30, 60*60, 60*60*5, -1};
const TInt KTimeLabels[] = {0, 5, 10, 20, 30, 1, 2, 5, 10, 30, 1, 5, -1};
const TInt KTimeUnits[]  = {R_IMMEDIATELY, R_SEC, R_SEC, R_SEC, R_SEC, R_MIN1, R_MIN, R_MIN, R_MIN, R_MIN, R_HOU1, R_HOU, R_NEVER}; // RISORSE PER UNITA' DI MISURA


void CSettingsView::GetItemDescriptionL(TInt index, TDes& descr)
	{
	// Recupera la label
	descr.Zero();
	if (KTimeLabels[index] > 0)
	{
		TBuf<15> after;
		iCoeEnv->ReadResourceL(after, R_AFTER );
		descr.Append(after);
		descr.Append(TChar(' '));
		descr.AppendNum(KTimeLabels[index]);
		descr.Append(TChar(' '));
	}
	// Recupera Unita' di misura dalla risorsa...
	TBuf<20> unit;
	iCoeEnv->ReadResourceL(unit, KTimeUnits[index] );
	descr.Append(unit);
	}


CDesCArray* CSettingsView::CreateRadioArrayForLockPhoneLC()
	{
    CDesCArray* array = new (ELeave) CDesC16ArrayFlat(16);
    CleanupStack::PushL(array);
	
    TBuf<80> text;
	iCoeEnv->ReadResourceL(text, R_NO );
	array->AppendL(text);
	iCoeEnv->ReadResourceL(text, R_ON_SIM_CHANGE );
	array->AppendL(text);
	iCoeEnv->ReadResourceL(text, R_ON_STARTUP );
	array->AppendL(text);

	return array;
	}

// Associa l'indice al valore corrispettivo...
// 0sec:5sec:10sec:15sec:20sec:30sec:1min:2min:5min:10min:30min:1ora:2ore:5ore:10ore:mai

CDesCArray* CSettingsView::CreateRadioButtonArrayLC()
	{
    CDesCArray* array = new (ELeave) CDesC16ArrayFlat(16);
    CleanupStack::PushL(array);
	TInt index = -1;
	do {
		index++;
		TBuf<40> buf;
		GetItemDescriptionL(index, buf);
		array->AppendL(buf);
	} while (KTimeValues[index] != -1);
	return array;
	}


TInt CSettingsView::Index2Seconds(TInt index)
	{
	return KTimeValues[index];
	}


TInt CSettingsView::Seconds2Index(TInt seconds)
	{
	TInt index=0;
	while (KTimeValues[index] != -1)
	{
		if (KTimeValues[index] == seconds)
			return index;
		index++;
	}
	return index;
	}


CSelectionItemList* CSettingsView::CreateCheckBoxArrayL(TBool smsIn, TBool smsOut, TBool callIn, TBool callOut)
	{
	CSelectionItemList* selList = new (ELeave) CSelectionItemList(4);

	TBuf<80> text;
	iCoeEnv->ReadResourceL(text, R_SMS_IN );	
	CSelectableItem* selectionItem = new (ELeave) CSelectableItem( text, smsIn );
	CleanupStack::PushL( selectionItem );
	selectionItem->ConstructL();
	selList->AppendL( selectionItem );
	CleanupStack::Pop( selectionItem );
	
	iCoeEnv->ReadResourceL(text, R_SMS_OUT );	
	selectionItem = new (ELeave) CSelectableItem( text, smsOut );
	CleanupStack::PushL( selectionItem );
	selectionItem->ConstructL();
	selList->AppendL( selectionItem );
	CleanupStack::Pop( selectionItem );
	
	iCoeEnv->ReadResourceL(text, R_CALLS_IN );	
	selectionItem = new (ELeave) CSelectableItem( text, callIn );
	CleanupStack::PushL( selectionItem );
	selectionItem->ConstructL();
	selList->AppendL( selectionItem );
	CleanupStack::Pop( selectionItem );
	
	iCoeEnv->ReadResourceL(text, R_CALLS_OUT );	
	selectionItem = new (ELeave) CSelectableItem( text, callOut );
	CleanupStack::PushL( selectionItem );
	selectionItem->ConstructL();
	selList->AppendL( selectionItem );
	CleanupStack::Pop( selectionItem );
	return selList;
	}

void CSettingsView::HandleCommandL( TInt aCommand )
    {
	switch (aCommand)
		{
		case EChange:
			{
			switch ( iContainer->iListBox->CurrentItemIndex() )
				{
				case 0: // Enabled
					{
						if (iGuardian.IsEnabled())
							HandleCommandL( EDisable );
						else
							HandleCommandL( EEnable );
						break;
					}
				case 1:
					{	// Number
						TNumber number;
						iGuardian.GetDestAddress(number);
						if ( !AskNumberL( number ) ) return;
						iGuardian.SetDestAddress(number);
						break;
					}
				case 2: // Text
					{
						TMessage message;
						iGuardian.GetMessage(message);
						if ( !AskTextL( message ) ) return;
						iGuardian.SetMessage(message);
						break;
					}
				case 3: // Password
					{
						TPassCode pass;
						iGuardian.GetPassword(pass);
						if ( !AskPasswordL( pass ) ) return;
						TInt ris = iGuardian.SetPassword(pass);
						ris = KErrNone;
						break;
					}
				case 4: // Lock On Sim Change
					{					
					CDesCArray* arr = CreateRadioArrayForLockPhoneLC();
					TInt index = iGuardian.GetLockBehaviour();
					CAknRadioButtonSettingPage* dlg = new (ELeave) CAknRadioButtonSettingPage(R_LOCK_SETTING_PAGE, index, arr);
					dlg->ConstructL();
					if ( dlg->ExecuteLD(CAknSettingPage::EUpdateWhenAccepted) )
					{
						TLockBehaviour behaviour = (TLockBehaviour) index;
						iGuardian.SetLockBehaviour( behaviour );
						// index;
						// Trasforma indice in secondi...
						// delay = Index2Seconds(index);
						// iGuardian.SetInactivityDelay(delay);
					}
					CleanupStack::PopAndDestroy(arr);
				
					break;
					}
				case 5: // Monitor
					{
					CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
					if (appui->iIsRegistered != 3)
					{
						Notes::WarningL(R_ERR_BUY_IRIDIUM);
						return;
					}
					TBool smsIn, smsOut, callIn, callOut;
					iGuardian.GetMonitorParams(smsIn, smsOut, callIn, callOut);
					
					delete iMonitorList;
					iMonitorList = CreateCheckBoxArrayL(smsIn, smsOut, callIn, callOut);
					
					// Necessario perche' su C5-03 il Softkey OK non viene visualizzato.
					CMyAknCheckBoxSettingPage* dlg = new (ELeave) CMyAknCheckBoxSettingPage(R_CHECKBOX_MONITOR, iMonitorList);
					dlg->ConstructL(); 
					if ( dlg->ExecuteLD(CAknSettingPage::EUpdateWhenAccepted) )
					{
						CSelectableItem* itemSmsIn = iMonitorList->At(0);
						CSelectableItem* itemSmsOut = iMonitorList->At(1);
						CSelectableItem* itemCallIn = iMonitorList->At(2);  
						CSelectableItem* itemCallOut = iMonitorList->At(3);
						smsIn = itemSmsIn->SelectionStatus();
						smsOut = itemSmsOut->SelectionStatus();
						callIn = itemCallIn->SelectionStatus();
						callOut = itemCallOut->SelectionStatus();
						iGuardian.SetMonitorParams(smsIn, smsOut, callIn, callOut);
					}
					
					iMonitorList->ResetAndDestroy();
					delete iMonitorList;
					iMonitorList = NULL;
					break;
					}
				case 6: // InactivityDelay
					{
						CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
						if (!appui->iIsRegistered)
						{
							Notes::WarningL(R_ERR_UNAVAILINFREE);
							return;
						}
						CDesCArray* arr = CreateRadioButtonArrayLC();
						TInt delay = iGuardian.GetInactivityDelay(); // secondi
						TInt index = Seconds2Index(delay);		 // Trasforma Delay in indice
						CAknRadioButtonSettingPage* dlg = new (ELeave) CAknRadioButtonSettingPage(R_CHECKBOX_INACTIVITY, index, arr);
						dlg->ConstructL();
						if ( dlg->ExecuteLD(CAknSettingPage::EUpdateWhenAccepted) )
						{
							// Trasforma indice in secondi...
							delay = Index2Seconds(index);
							iGuardian.SetInactivityDelay(delay);
						}
						CleanupStack::PopAndDestroy(arr);
						break;
					}
				}
			UpdateViewL();
			break;
			}
		case EEnable:
			{
			TInt ris = iGuardian.SetEnabled(ETrue);
			switch (ris)
			{
				case KErrPassNotSet:
					Notes::WarningL(R_ERR_NO_PASS);
				return;
				case KErrPassShort:
					Notes::WarningL(R_ERR_SHORT_PASS);
				return;
				case KErrNumberNotSet:
					Notes::WarningL(R_ERR_NO_NUMBER);
				return;
				case KErrSameValue:
				return;
			}

			// Avvia Guardian...
			_LIT(KGuardianImage, "Guardian_200131CB");
			const TUid KGuardianUid3={0x200131CB};

			const TUidType guardUid(KNullUid, KNullUid, KGuardianUid3);
			RProcess guardianProtection;			
			User::LeaveIfError( guardianProtection.Create(KGuardianImage, KNullDesC, guardUid) );
			guardianProtection.SetParameter(1, 1);	// Avvio da GUI.
			guardianProtection.Resume();	// logon OK - start the server
			guardianProtection.Close();
			break;
			}
		case EDisable:
			iGuardian.SetEnabled(EFalse);
			break;
		default:
			AppUi()->HandleCommandL(aCommand);
			break;
		}
    }


// ---------------------------------------------------------
// CSettingsView::HandleClientRectChange()
// ---------------------------------------------------------
//
void CSettingsView::HandleClientRectChange()
	{
	if ( iContainer )
		{
		iContainer->SetRect( ClientRect() );
		}
	}


LOCAL_C void AddInOutToBuff(TDes& buf, TBool in, TBool out)
	{
	if (in && out)
		{
		TBuf<32> all;
		CCoeEnv::Static()->ReadResourceL(all, R_ALL );
		buf.Append(all);
		return;
		}
	if (in)
		{
		TBuf<32> in;
		CCoeEnv::Static()->ReadResourceL(in, R_INCOMING );
		buf.Append(in);
		return;		
		}
	if (out)
		{
		TBuf<32> out;
		CCoeEnv::Static()->ReadResourceL(out, R_OUTGOING );
		buf.Append(out);
		return;		
		}
	}


void CSettingsView::UpdateViewL()
	{
	TNumber number;
	TPassCode password;
	TMessage message;

/*	TBool isEn = ETrue;
	number = _L("12345");
	message = _L("12345");
	password = _L("12345");
	TInt delay=5;*/
	
	TBool isEn = iGuardian.IsEnabled();
	TLockBehaviour lockBehaviour = iGuardian.GetLockBehaviour();
	iGuardian.GetDestAddress(number);
	iGuardian.GetMessage(message);
	iGuardian.GetPassword(password);
	TInt delay = iGuardian.GetInactivityDelay();
	
	TBuf<40> buf;
	TInt index = Seconds2Index(delay);
	GetItemDescriptionL(index, buf);
	if (buf[0] >= '0' && buf[0] <= '9')
	{
		TBuf<15> after;
		iCoeEnv->ReadResourceL(after, R_AFTER );
		after.Append(TChar(' '));
		buf.Insert(0, after);
	}
	
	TBool smsIn, smsOut, callIn, callOut;
	iGuardian.GetMonitorParams(smsIn, smsOut, callIn, callOut);
	TBuf<200> buffMon;
	if (smsIn || smsOut)
		{
		TBuf<32> sms;
		iCoeEnv->ReadResourceL(sms, R_SMS );
		buffMon.Append(sms);
		AddInOutToBuff(buffMon, smsIn, smsOut);
		}
	
	if (buffMon.Length() > 0)
		buffMon.Append(_L(" "));
	
	if (callIn || callOut)
		{
		TBuf<32> calls;
		iCoeEnv->ReadResourceL(calls, R_CALLS );
		buffMon.Append(calls);
		AddInOutToBuff(buffMon, callIn, callOut);
		}
	
	if (buffMon.Length() == 0)
		{
		TBuf<32> no;
		iCoeEnv->ReadResourceL(no, R_NO );
		buffMon.Append(no);
		}
		
	iContainer->UpdateListBoxViewL(isEn, number, message, password, buf, lockBehaviour, buffMon);
	}


// ---------------------------------------------------------
// CSettingsView::DoActivateL(...)
//
// ---------------------------------------------------------
//
void CSettingsView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
	{
	if (!iContainer)
		{
		iContainer = new (ELeave) CSettingsContainer;
		iContainer->SetMopParent(this);
		iContainer->ConstructL( ClientRect(), *this );
		AppUi()->AddToStackL( *this, iContainer );
		UpdateViewL();

		// Imposta il titolo
		GuiUtils::StatusPaneSetupTitleL(StatusPane(), R_SETTINGS_TITLE);
/*		CEikStatusPane* sp=iEikonEnv->AppUiFactory()->StatusPane();
		CAknTitlePane* tp=(CAknTitlePane*)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

		HBufC* string = CCoeEnv::Static()->AllocReadResourceL(R_SETTINGS);
		tp->SetText( string );*/
		}
	iOldIndex = iContainer->iListBox->CurrentItemIndex();
   }

// ---------------------------------------------------------
// CSettingsView::DoDeactivate()
//
// ---------------------------------------------------------
//
void CSettingsView::DoDeactivate()
	{
	if ( iContainer )
		{
		AppUi()->RemoveFromViewStack( *this, iContainer );
		}

	delete iContainer;
	iContainer = NULL;
	}


TBool CSettingsView::AskNumberL(TDes& number)
{
	CPbkContactEngine * ipPabEng = CPbkContactEngine::NewL(  );
	CleanupStack::PushL(ipPabEng);
	// load the contacts dialog resources

	CCoeEnv *env = CEikonEnv::Static();
	RPbkViewResourceFile pbkRes( *env);
	pbkRes.OpenL();

	CPbkSingleEntryFetchDlg::TParams para;
	para.iPbkEngine = ipPabEng;
	para.iContactView = &ipPabEng->AllContactsView();

	CPbkSingleEntryFetchDlg * anotherDlg = CPbkSingleEntryFetchDlg::NewL(para);
	TBool ris = anotherDlg->ExecuteLD();
	if (ris)
		{
		CPbkContactItem* item = ipPabEng->ReadContactLC( para.iSelectedEntry );
		CPbkSmsAddressSelect::TParams paraNumber(*item);
		CPbkSmsAddressSelect* dlgNumber = new (ELeave) CPbkSmsAddressSelect();
		ris = dlgNumber->ExecuteLD(paraNumber);
		if (ris)
			{
			paraNumber.SelectedField()->GetTextL( number );
			}
		CleanupStack::PopAndDestroy(item); // item;
		}
	pbkRes.Close();
	CleanupStack::PopAndDestroy(ipPabEng); // ipPabEng;
	return ris;/**/
}


TBool CSettingsView::AskTextL(TDes& text)
{
//	TBool predict = !GuiUtils::IsTouchSupportedL();
	return Queries::AskTextL(R_SMS_QUERY, text, ETrue);
/*	CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( text );

	// FIX: Stranamente sui Cell. Touch abilitando il Predictive, la tastiera diventa numerica e schianta dopo la pressione di un po' di tasti.
	// FIX: Questo se la query e' con flag EEikDialogFlagVirtualInput
	if (!GuiUtils::IsTouchSupportedL())
		dlg->SetPredictiveTextInputPermitted( ETrue );
	
	dlg->PrepareLC( R_SMS_QUERY );
	dlg->SetMaxLength( text.MaxLength() );
	if ( dlg->RunLD() ) return ETrue;
	return EFalse;
//	  CAknQueryDialog* dlg = new (ELeave) CAknQueryDialog( text, CAknQueryDialog::ENoTone );
//	return dlg->ExecuteLD( R_SMS_QUERY );*/
}


TBool CSettingsView::AskPasswordL(TDes& pass)
{
	TBool predict = !GuiUtils::IsTouchSupportedL();
	for(;;)
	{
		if (!Queries::AskTextL(R_PASS_VISIBLE_QUERY, pass, predict))
			return EFalse;
/*		CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( pass );

		dlg->PrepareLC( R_PASS_VISIBLE_QUERY );
		dlg->SetMaxLength( KPASS_LEN );

		if ( !dlg->RunLD() )
			return false;*/

		pass.UpperCase();
		if (pass.Length()>=5)
			return true;

		Notes::WarningL(R_ERR_SHORT_PASS);
	}
}


void CSettingsView::HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aEventType)
{
	if (aEventType == EEventPenDownOnItem) // 5th Ed.
		{
		iTouchSupported = ETrue;
		iAcceptTouchEvents = ETrue;
		}
//	CGuardGUIAppUi* appui = (CGuardGUIAppUi*) AppUi();
	switch (aEventType)
	{
	case EEventEnterKeyPressed:
	case EEventItemClicked:
	
/*		// Check se e' presente il supporto per il pennino...
		if (iTouchSupported)
			{ 
			if (!iAcceptTouchEvents)
				return;
			iAcceptTouchEvents = EFalse;
		    if (iContainer->iListBox->CurrentItemIndex() != iOldIndex)
				{
				iOldIndex = iContainer->iListBox->CurrentItemIndex();
				return;
				}
			iOldIndex = iContainer->iListBox->CurrentItemIndex();
			}/**/
		
		if (iContainer->iListBox->CurrentItemIndex() == 0)	// Solo per lo stato richiede conferma
			{ 
			if ( GuiUtils::ShowItemPopupL(R_CHANGE_ITEMS) < 0)
				return;
			}
		HandleCommandL( EChange );
		break;
/*	case EEventItemDoubleClicked: // 5th Ed. Doesn't work properly
		HandleCommandL( EChange );
        break; */
    case EEventItemDraggingActioned: // 5th Ed.
    	break;
	default:
		break;
	}
}


void CSettingsView::DynInitMenuPaneL( TInt aResourceId,	CEikMenuPane* aMenuPane )
{
	AppUi()->DynInitMenuPaneL(aResourceId, aMenuPane);
}
