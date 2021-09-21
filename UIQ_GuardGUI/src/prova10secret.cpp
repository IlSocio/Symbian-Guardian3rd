// Prova10View.cpp
//
// © Barolo 2007. All rights reserved.
//

#include <QikAppUi.h>
#include <QikCommand.h>
#include <EIKLABEL.H> 
#include <GULICON.H>

// da togliere
#include <eikseced.h>
#include <QikRowLayoutManager.h>
#include <QikGridLayoutManager.h>
#include <QikBuildingBlock.h>

#include "prova10secret.h"
#include "guardguiExternalInterface.h"

#include <GuardGUI_200107AF.rsg>
#include <GuardGUI_200107AF.mbg>
#include "prova10.hrh"


CProva10Secret* CProva10Secret::NewLC(CQikAppUi& aAppUi,const TVwsViewId aParentViewId)
	{
	CProva10Secret* self = new (ELeave) CProva10Secret(aAppUi,aParentViewId);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CProva10Secret::CProva10Secret(CQikAppUi& aAppUi,const TVwsViewId aParentViewId) 
: CQikViewBase(aAppUi, aParentViewId)
	{
	//iPassword 
	}

void CProva10Secret::ConstructL()
	{
	BaseConstructL();
	}

CProva10Secret::~CProva10Secret()
	{	
	}
//da togliwre
void CProva10Secret::ViewConstructL()
    {
//    ViewConstructFromResourceL(R_MY_SECRET_EDITOR_UI_CONFIGURATIONS, R_MY_SECRET_EDITOR_VIEW_CONTROLS);

    // Give a layout manager to the view
    CQikGridLayoutManager* gl = CQikGridLayoutManager::NewLC();
    SetLayoutManagerL(gl);
    CleanupStack::Pop(gl);
                        
    // Create a container and give it to the view
    ControlProvider()->ControlInfos().AddFromResourceL(R_MY_SECRET_EDITOR_VIEW_CONTROLS);
    CQikContainerBase* container = static_cast<CQikContainerBase*>(ControlProvider()->ControlConstructIfNeededL(EMyViewScrollableContainer, *this));
    ASSERT(container);
    Controls().AppendLC(container);
    CleanupStack::Pop(container);
                    
    // Create a layout manager to be used inside the container
    CQikRowLayoutManager* rowlayout = CQikRowLayoutManager::NewLC();

    container->SetLayoutManagerL(rowlayout);
    CleanupStack::Pop(rowlayout);
                    
    // Create label
    TResourceReader reader1;
    iEikonEnv->CreateResourceReaderLC(reader1, R_SECRET_LABEL);
    CEikLabel* label1 = new (ELeave) CEikLabel();
    container->AddControlLC(label1, ETextDialogLabel1);    
    label1->ConstructFromResourceL(reader1);
    label1->SetUniqueHandle(ETextDialogLabel1);
    CleanupStack::Pop(label1);
    CleanupStack::PopAndDestroy(); //reader
      
    // Create the Secret Editor and add it into the container
    TResourceReader reader;
    iEikonEnv->CreateResourceReaderLC(reader, R_MY_SECRET_EDITOR);
    CEikSecretEditor* editor = new (ELeave) CEikSecretEditor();
    container->AddControlLC(editor, EMyViewSecretEditor);//EPasswDialogSecretEditor
    editor->ConstructFromResourceL(reader);
    editor->SetUniqueHandle(EMyViewSecretEditor);
    
    editor->SetObserver(this);   
    
    CleanupStack::Pop(editor);
    CleanupStack::PopAndDestroy(); //reader
    CQikCommandManager& cmdManager = CQikCommandManager::Static();
    cmdManager.InsertIntoCommandListL(*this, *this, R_MY_SECRET_EDITOR_COMMANDS);
  
    //per il controllo lunghezza minima
    //cmdManager.SetAvailable(*this, ESecretLoginCmd, EFalse);
    cmdManager.SetDimmed(*this, ESecretLoginCmd, ETrue);

    }
	
void CProva10Secret::ViewActivatedL(const TVwsViewId &aPrevViewId,
							  const TUid aCustomMessageId, 
							  const TDesC8 &aCustomMessage)
	{
	}


TVwsViewId CProva10Secret::ViewId()const
	{
	return TVwsViewId(KUidGuardGUIApp, KUidProva10secret);
	}


void CProva10Secret::HandleCommandL(CQikCommand& aCommand)
   {
      switch(aCommand.Id())
      {
		case ESecretCancelCmd:
			{
			ActivatePreviousViewL(ECancel);
			break;
			}
		case ESecretLoginCmd:
			{
			CEikSecretEditor* secretEditor = LocateControlByUniqueHandle<CEikSecretEditor>(EMyViewSecretEditor);
			secretEditor->GetText(iPassword);
			
			ActivatePreviousViewL(ESave);
			break;
			}
         
      default:
         CQikViewBase::HandleCommandL(aCommand);
         break;
      }
   }

void CProva10Secret::HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType)
	{
	    switch(aEventType)
	    {
	    	case EEventStateChanged:
			{
			switch(aControl->UniqueHandle())
				{
				case EMyViewSecretEditor:
					{
					// Locate the edwin
					const CEikSecretEditor* edwinsec = LocateControlByUniqueHandle<const CEikSecretEditor >(EMyViewSecretEditor);
	            	// Sets the login command to available if the edwin contains any text
					TBuf<50> text;
					edwinsec->GetText(text);
				    CQikCommandManager& cmdManager = CQikCommandManager::Static();					
					if (text.Length()> 4)
						{
					    cmdManager.SetDimmed(*this, ESecretLoginCmd, EFalse);				
//					    cmdManager.SetAvailable(*this, ESecretLoginCmd, ETrue);				
						}
					else{
				    	cmdManager.SetDimmed(*this, ESecretLoginCmd, ETrue);					
						}
					break;
					}							
		        default:
		        break;
				}
			}
	        default:
	        break;			
	    }
	    CQikViewBase::HandleControlEventL(aControl, aEventType);
	}