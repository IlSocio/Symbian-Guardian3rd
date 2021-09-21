
#include "AsyncQueryDialog.h"
#include "dialogpin.hrh"

#include <avkon.rsg>
#include <akndialog.h>


// Classe utilizzata per avere notifica della chiusura di un DIALOG NON MODALE... Asincrona...

CAsyncQueryDialog::CAsyncQueryDialog(MAsyncQueryObserver& obs, const TDesC& text) : CAknTextQueryDialog(iText), iObserver(obs)
{
	iText.Copy(text);
}
 
TKeyResponse CAsyncQueryDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	if (aKeyEvent.iScanCode == EStdKeyHash)	// Su N95 la pressione del # provoca un crash, quindi l'ho dovuto disattivare.
		return EKeyWasConsumed;
	
	if (aType != EEventKey)
		return CAknTextQueryDialog::OfferKeyEventL(aKeyEvent, aType);
	
	switch ( aKeyEvent.iCode )
	{
		/*case EKeyApplication19:			// disable camera key	Non serve perche' la camera parte comunque...
			{
			return EKeyWasConsumed;					
			}/**/ 
		
		case EKeyEscape:				// disable red key		
			{
			return EKeyWasConsumed;			
			}
		case EKeyNo:					// disable red key
			{
			return EKeyWasConsumed;
			}
		default:
			break; 
	}
	
/*	__FLOG_DECLARATION_MEMBER;
	__FLOG_OPEN("Guardian", "Keys.txt");
	__FLOG_1(_L("Type:%d"), aType );
	__FLOG_1(_L("ScanCode:%d"),aKeyEvent.iScanCode );
	__FLOG_1(_L("Code:%d"),aKeyEvent.iCode );
	__FLOG_CLOSE;/**/

	return CAknTextQueryDialog::OfferKeyEventL(aKeyEvent, aType);
	}


void CAsyncQueryDialog::Close()
	{
    TRAP_IGNORE( TryExitL(EAknSoftkeyCancel) );
	}
 

void CAsyncQueryDialog::PrepareLC(TInt aResourceId)
	{ 
	CAknDialog::PrepareLC(aResourceId);
/*	CAknQueryControl* control = STATIC_CAST(CAknQueryControl*, ControlOrNull(EGeneralQuery));
	if (control)
		{
//		control->SetPromptL(_L("prompt"));
//		control->SetTextL(_L("text"));
		CEikSecretEditor* secretEd = STATIC_CAST(CEikSecretEditor*, control->ControlByLayoutOrNull( EPinLayout ));
		if (secretEd)		
			{
//			secretEd->SetGloballyCapturing(ETrue);
//			secretEd->SetText(_L("1"));
			}
		}*/
	}


void CAsyncQueryDialog::PreLayoutDynInitL() // must not fail
{
//	SetBorder(TGulBorder::ENone);
//	SetExtentToWholeScreen();
}


void CAsyncQueryDialog::PostLayoutDynInitL() // must not fail
{
//	SetBorder(TGulBorder::ENone);
//	SetExtentToWholeScreen();
}


CAsyncQueryDialog::~CAsyncQueryDialog()
{
}

/*TBool CAsyncQueryDialog::CheckIfEntryTextOk() const
	{
	return ETrue;
	}

void CAsyncQueryDialog::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
{
}*/


TBool CAsyncQueryDialog::OkToExitL(TInt aButtonId)
{	
	TBool ok = (aButtonId == EAknSoftkeyOk);
	TBuf<10> txt;
// CAknQueryControl* control = STATIC_CAST(CAknQueryControl*, ControlOrNull(EGeneralQuery));
// Ho dovuto tenere EPinID perche' durante l'installaz. dell'aggiornam. RSC veniva sostituito ma il vecchio binario restava ancora in esecuzione
	CAknQueryControl* control = STATIC_CAST(CAknQueryControl*, ControlOrNull(EPinID));
	if (control)
		{
		CEikSecretEditor* secretEd = STATIC_CAST(CEikSecretEditor*, control->ControlByLayoutOrNull( EPinLayout ));
		if (secretEd)		
			secretEd->GetText(txt);
		}
		
/*	if (txt != iGoodPass) 
	{
        CAknErrorNote* note = new (ELeave) CAknErrorNote;
		note->ExecuteLD(iWrongMsg->Des());
		txt.Zero();
	}*/

	iObserver.DialogClosedL(ok, txt);
	return ETrue;
}
