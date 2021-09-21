
#include "guardguiappui.h"
#include "guardguiExternalInterface.h"
#include <EIKEDWIN.H> 
#include <charconv.h>
#include <EIKLABEL.H>
#include <bautils.h>

#include "client.h"
#include "splashview.h"
#include "aboutview.h"
#include "settingsview.h"
#include "simlistview.h"
#include "protectionview.h"
#include "common.hrh"
#include "numericdialog.h"
#include "infodialog.h"
#include <QikSimpleDialog.h>
#include <EIKENV.H>
#include <GuardGUI_200107AF.rsg>
#include <QSkinIds.h>
#include <QikContent.h>


CGuardGUIAppUi::CGuardGUIAppUi():CQikAppUi()
	{	
	}


CGuardGUIAppUi::~CGuardGUIAppUi()
	{
	if (iTimer)
		delete iTimer;
	}



TBool CGuardGUIAppUi::AskPasswordL(TDes& pass)
{
	for (;;)
	{
		CNumericDialog* dlg = new(ELeave) CNumericDialog(_L("Code:"), pass, ETrue);
		if ( !dlg->ExecuteLD() ) 
			return EFalse; // Pigiato Cancel

		// Pigiato OK...
		if (pass.Length() >= 5) 
			return ETrue;

		// TODO: MESSAGGIO DI WARNING...
		// WarnMsg(R_ERR_SHORT_PASS);
	}
}


void CGuardGUIAppUi::ConstructL()
	{
	BaseConstructL();	
	iGuiActive = EFalse;

//	TVwsViewId parentView(KUidGuardGuiApp, KUidAboutView);
	TVwsViewId parentView = KNullViewId;
	
	CSplashView* iMyView1  = CSplashView::NewLC(*this, KNullViewId);
	AddViewL(*iMyView1);
	CleanupStack::Pop();
	
	iAboutView  = CAboutView::NewLC(*this, KNullViewId);
	AddViewL(*iAboutView);
	CleanupStack::Pop();
	
	CSettingsView* iMyView2  = CSettingsView::NewLC(*this, KNullViewId);
	AddViewL(*iMyView2);
	CleanupStack::Pop();

	CSimListView* iMyView3  = CSimListView::NewLC(*this, KNullViewId);
	AddViewL(*iMyView3);
	CleanupStack::Pop();	/**/
	
	CProtectionView* iMyView4  = CProtectionView::NewLC(*this, KNullViewId);
	AddViewL(*iMyView4);
	CleanupStack::Pop();	/**/
	

#define KSEC 1000000
#ifdef __WINS__
	TTimeIntervalMicroSeconds32 timeout(KSEC * 1);
#else
	TTimeIntervalMicroSeconds32 timeout(KSEC * 3);
#endif
	iTimer = CTimeOutTimer::NewL( *this );
	iTimer->After(timeout);
	}


void CGuardGUIAppUi::TimerExpiredL(TAny* src)
	{
	SetDefaultViewL(*iAboutView);	// <-- Serve per il bottone Done/Back

	TBuf<200> buff;

	RGuardian guard;
	guard.Connect();
	CleanupClosePushL(guard);

// VERIFICA ESISTENZA CONFIGURAZIONE
	guard.GetMessage(buff);
	if (buff.Length() == 0) 
		{
		// iCoeEnv->ReadResource( buff, R_WARNING_SMS );
		guard.SetMessage( _L("Warning Sim Changed!") );
		}
	guard.GetPassword(buff);
	buff.UpperCase();
	TBool enabled = guard.IsEnabled();
	CleanupStack::PopAndDestroy(); // guard

// VERIFICA PASSWORD
#ifndef  __WINS__
	if (enabled) 
		{
		TBuf<10> pass;
		if ( (!AskPasswordL(pass)) || ( pass != buff) ) 
			{
			// TODO: ErrorMsg(R_ERR_BAD_PASS);
			Exit();
			}
		}
#endif

	TVwsViewId viewId1 = TVwsViewId(KUidGuardGUIApp, KUidAboutView);
	ActivateViewL(viewId1);

	iGuiActive = ETrue;
	}


void CGuardGUIAppUi::MainTabActivatedL(TInt aTabId)
	{
	    switch(aTabId)
	    {
	    case 1:
			{
			TVwsViewId viewId1 = TVwsViewId(KUidGuardGUIApp, KUidAboutView);
			ActivateViewL(viewId1);
	        break;
			}
	    case 2:
			{
			TVwsViewId viewId2 = TVwsViewId(KUidGuardGUIApp, KUidSettingsView);
			ActivateViewL(viewId2);
			break;
			}
	    case 3:
			{
			TVwsViewId viewId3 = TVwsViewId(KUidGuardGUIApp, KUidSimListView);
			ActivateViewL(viewId3);
			break;  
			}
	    case 4:
			{
			TVwsViewId viewId4 = TVwsViewId(KUidGuardGUIApp, KUidProtListView);
			ActivateViewL(viewId4);
			break;  
			}
	    default:
	       break;
	    }
	}



void CGuardGUIAppUi::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
		/*case EInfoViewLicense:
			{
			ShowInfoFromFileL(_L("License Agreement"), _L("License.txt"));
			break;
			}*/
		  case ESimViewAdd:
			{
			ShowInfoFromFileL(_L("Add New Sim"), _L("AddNewSim.txt"));
	        break;
			}
		  case ERegisterCode:
			  // TODO: Codice registrazione...
		  break;
		  case ERegisterNet:
			  // TODO: Codice registrazione...
		  break;
		  case EEikCmdExit:
			  TBool response = CEikonEnv::Static()->QueryWinL(_L("Exit Guardian?"), _L(""));
			  if (!response) return;
		  break;
	  }
	  CQikAppUi::HandleCommandL(aCommand);
   }


void CGuardGUIAppUi::ShowInfoFromFileL(const TDesC& title, const TDesC& fileName)
	{
	RFs &fs= iCoeEnv->FsSession();
	
	// Make full path to privacy statement
	TFileName fullFileName;
	TFileName privatePath;
	fs.PrivatePath(privatePath);
	TParse parser;
	TFileName processFileName(RProcess().FileName());
	User::LeaveIfError(parser.Set(fileName, &privatePath, &processFileName));
	fullFileName = parser.FullName();
	
	if(BaflUtils::FileExists(fs, fullFileName)) 
		{
		RBuf text(CGuardGUIAppUi::ReadUnicodeFileL(fs, fullFileName));
		CleanupClosePushL(text);
/*		TBuf<20> buf = _L("123");
		buf.Append(CEditableText::ELineBreak);
		buf.Append(_L("456"));
		buf.Append(CEditableText::ELineBreak);
		text.Replace(0, 20, buf);*/

		CInfoDialog* dialog = new (ELeave) CInfoDialog(title, text);
		dialog->ExecuteLD();
		CleanupStack::PopAndDestroy(&text);
		}
	}

HBufC* CGuardGUIAppUi::ReadUnicodeFileL(RFs& aFs, const TDesC& aFileName)
	{
	RFile file;
	User::LeaveIfError(file.Open(aFs, aFileName, EFileShareReadersOnly | EFileStreamText | EFileRead));
	CleanupClosePushL(file);

	TInt size;
	User::LeaveIfError(file.Size(size));

	RBuf8 tmp;
	tmp.CreateL(size);
	CleanupClosePushL(tmp);
	User::LeaveIfError(file.Read(tmp));

	CCnvCharacterSetConverter * converter = CCnvCharacterSetConverter::NewLC();
	converter->PrepareToConvertToOrFromL(KCharacterSetIdentifierUtf8, aFs);

	HBufC *text = HBufC::NewL(size);

	TInt state = CCnvCharacterSetConverter::KStateDefault;
	TPtrC8 remainderOfForeignText(tmp);
	for(;;)
		{
		TPtr textPtr(text->Des());
		TInt retValue = converter->ConvertToUnicode(textPtr, remainderOfForeignText, state);
		if(retValue == CCnvCharacterSetConverter::EErrorIllFormedInput)
			User::Leave(KErrCorrupt);
		else if(retValue < 0)
			User::Leave(KErrGeneral);
		
		if(retValue == 0)
			break;
			
		remainderOfForeignText.Set(remainderOfForeignText.Right(retValue));
		}	
	
	CleanupStack::PopAndDestroy(converter);
	CleanupStack::PopAndDestroy(2);
	return text;
	}
