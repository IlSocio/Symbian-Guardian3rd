// Prova10bview.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 
#include <eikedwin.h>
#include <EIKIMAGE.H>


#include <QikTabScreen.h>

#include "prova10splash.h"
#include "prova10exit.h"
#include "prova10passw.h"
#include "prova10text.h"
#include "prova10bview.h"
#include "prova10secret.h"
#include "prova10ExternalInterface.h"

#include <prova10.rsg>
#include "prova10.hrh"


CProva10bView* CProva10bView::NewLC(CQikAppUi& aAppUi,const TVwsViewId aParentViewId)
	{
	CProva10bView* self = new (ELeave) CProva10bView(aAppUi,aParentViewId);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CProva10bView::CProva10bView(CQikAppUi& aAppUi,const TVwsViewId aParentViewId) 
	: CQikMultiPageViewBase(aAppUi, aParentViewId)
	{
	}

void CProva10bView::ConstructL()
	{
	BaseConstructL();
	}

CProva10bView::~CProva10bView()
	{	
	}

void CProva10bView::ViewConstructL()
	{
       ViewConstructFromResourceL(R_PROVA10TAB_UI_CONFIGURATIONS,R_PROVA10_VIEW_CONTROLS);
       
       TCoeFont iFont(40,10,0);
       CEikLabel* label = LocateControlByUniqueHandle<CEikLabel>(Eprova10LabelCtrl5);
       label->SetFont(iFont);
       
       CEikEdwin* edwin = LocateControlByUniqueHandle<CEikEdwin>(Eprova10Edwin);
       CEikEdwin* edwin1 = LocateControlByUniqueHandle<CEikEdwin>(Eprova10Edwin1);
       CEikEdwin* edwin2 = LocateControlByUniqueHandle<CEikEdwin>(Eprova10Edwin2);
       CEikEdwin* edwin3 = LocateControlByUniqueHandle<CEikEdwin>(Eprova10Edwin3);

       HBufC* KText1 = iEikonEnv->AllocReadResourceLC(R_PROVA10_STRING1);
       HBufC* KText2 = iEikonEnv->AllocReadResourceLC(R_PROVA10_STRING2);
       HBufC* KText3 = iEikonEnv->AllocReadResourceLC(R_PROVA10_STRING3);
       HBufC* KText4 = iEikonEnv->AllocReadResourceLC(R_PROVA10_STRING4);

       if(edwin)
           edwin->SetTextL(KText1);
       if(edwin1)
           edwin1->SetTextL(KText2);
       if(edwin2)
           edwin2->SetTextL(KText3);               
       if(edwin3)
           edwin3->SetTextL(KText4);
       CleanupStack::PopAndDestroy(4);  
       /*
       CQikTabScreen* tabScreen = new (ELeave) CQikTabScreen();
	   tabScreen->SetContainerWindowL(*this); 
	   TResourceReader resourceReader; 
	   iCoeEnv->CreateResourceReaderLC(resourceReader, R_PROVA10_TABSCREEN);
	   tabScreen->ConstructFromResourceL(resourceReader); 
	   CleanupStack::PopAndDestroy(); 
	   CQikTabScreenPage* tabPage = (CQikTabScreenPage*)tabScreen->PageControl(0); 
	   tabPage->ConstructL(*tabScreen);
	   //tabPage->AddControlL(); 
	   tabPage->SetExtent(TPoint(0, 0), TSize(Rect().Width(), Rect().Height())); 

	   CQikTabScreenPage* tabPage1 = (CQikTabScreenPage*)tabScreen->PageControl(1); 
	   tabPage1->ConstructL(*tabScreen);
	   tabPage1->SetExtent(TPoint(0, 0), TSize(Rect().Width(), Rect().Height())); 
	   //AddTabPageL()
	   tabScreen->SetCurrentTabL(1); 
	   tabScreen->ActivateL();*/
       
	}
	
void CProva10bView::ViewActivatedL(const TVwsViewId &aPrevViewId,
							  const TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage)
	{	
		if(ActivePageId() != Eprova10ViewPage2)
		{
			ActivatePageL(Eprova10ViewPage2);
		}
	}

void CProva10bView::TabActivatedL(TInt aTabId)
	{
	   _LIT(KCmd1Msg1, "About"); 
	   _LIT(KCmd1Msg2, "Impostazioni"); 
	   _LIT(KCmd1Msg3, "SIM Autorizzate"); 
	   _LIT(KCmd1Msgerr, "Error");

	   switch(aTabId)
	   {	   
       case Eprova10ViewPage2:
	   	   SetAppTitleNameL(KCmd1Msg1);
	       break;	   
       case Eprova10ViewPage3:
	   	   SetAppTitleNameL(KCmd1Msg2);
	       break;
       case Eprova10ViewPage4:
	   	   SetAppTitleNameL(KCmd1Msg3);
	       break;	       
	   default:
		   SetAppTitleNameL(KCmd1Msgerr);
		   break;
	   }
	   CQikMultiPageViewBase::TabActivatedL(aTabId);
	}

TVwsViewId CProva10bView::ViewId()const
	{
	return TVwsViewId(KUidProva10App, KUidProva10bView);
	}

void CProva10bView::HandleCommandL(CQikCommand& aCommand)
   {
   TBuf<48>Text11;
	CEikonEnv* iEikEnv = CEikonEnv::Static();
	HBufC* message;
   
   switch(aCommand.Id())
      {
      case Eprova10tabCommand1:
      CProva10Splash::RunDlgLD();
      /*CEikImage*  a = new CEikImage();      
      a->ConstructFromResourceL(R_PROVA10_IMAGE);
      a->DrawNow();*/
         break;
      case Eprova10tabCommand2:
      	 /*
   	 	 CProva10Passw::RunDlgLD(Text11);
   	 	 */
      	 TVwsViewId viewId2 = TVwsViewId(KUidProva10App, KUidProva10secret);
      	 iQikAppUi.ActivateViewL(viewId2);
   	 	 break;      
      case Eprova10tabCommand3:
		 // Displays a query dialog 
	  	 //TBool response = iEikonEnv->QueryWinL(R_EXIT_DIALOG_TITLE, R_EXIT_DIALOG_TEXT);
      	 CProva10exit::RunDlgLD();
      	 break;      	
      case Eprova10tabCommand4:
	 	 CProva10text::RunDlgLD();
	 	 break;  
      case Eprova10tabCommand5:	 
		 /*message = iEikEnv->AllocReadResourceLC(R_PROVA10_NOTIFIER_MESSAGE_TEXT);
		 iEikEnv->InfoWinL(message->Des(),message->Des());
	     CleanupStack::PopAndDestroy();*/  
      	//DisplayNotifierMessageL;
   	 	 CQikSimpleDialog* dialog1 = new(ELeave) CQikSimpleDialog;
     	 TInt ret1 = dialog1->ExecuteLD(R_INFO_DIALOG);
	 	 break;
      case Eprova10tabCommand6:
		/* message = iEikEnv->AllocReadResourceLC(R_PROVA10_NOTIFIER_WARNING_TEXT);
		 iEikEnv->AlertWin(message->Des());
	     CleanupStack::PopAndDestroy(); */
      	 /*CQikSimpleDialog* dialog2 = new(ELeave) CQikSimpleDialog;
         TInt ret2 = dialog2->ExecuteLD(R_WARNING_DIALOG);
         TInt ret2 = dialog2->ExecuteLD(R_ERROR_DIALOG);*/
         TVwsViewId viewId = TVwsViewId(KUidProva10App, KUidProva10ListView);
         iQikAppUi.ActivateViewL(viewId);
	 	 break;  	 	 
      default:
      CQikMultiPageViewBase::HandleCommandL(aCommand);
         break;
      }
   }

