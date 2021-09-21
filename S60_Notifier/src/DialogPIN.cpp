#include "DialogPIN.h" // CDialogPIN
#include <eikdef.h>
#include <EIKENV.H>
#include <aknnotifystd.h>
#include "DialogPIN_200107B1.rsg"
#include <avkon.rsg>
#include <avkon.mbg>
#include "DialogPIN.hrh"
#include <eikmfne.h> 
#include <eikseced.h> 
#include <akncontrol.h> 
#include <aknquerydialog.h> 
#include <aknnotewrappers.h> 


	CDialogPIN::CDialogPIN() 
	{
	}


	void CDialogPIN::ConstructL()
	{
/*        BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(),fileName);
        TInt offset=iEikonEnv->AddResourceFileL(fileName_rsc);
        TRAPD(err, ConstructSleepingAlertDialogL(R_CHECKBOX_DEMO_DIALOG));
        iEikonEnv->DeleteResourceFile(offset);
        User::LeaveIfError(err);*/
/*	TFileName fileName(KResFileName);
	BaflUtils::NearestLanguageFile(iCoeEnv->FsSession(),fileName);
	TInt offset=iEikonEnv->AddResourceFileL(fileName);
	TRAPD(err,ConstructSleepingAlertDialogL(R_VW_NOTIFIER_DIALOG));
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);*/

	// Nell'emulatore viene cercato in questo percorso...
	// C:\Symbian\9.1\S60_3rd_MR\Epoc32\winscw\c\resource\apps
	_LIT(fileName, "c:\\resource\\apps\\DialogPIN_200107B1.rsc");
	TInt offset = iEikonEnv->AddResourceFileL(fileName);
	TRAPD(err, ConstructSleepingDialogL(R_PIN_QUERY));
	iWrongMsg = HBufC::NewL(64);
	TPtr16 ptr = iWrongMsg->Des();
   	iEikonEnv->ReadResourceL( ptr, R_WRONG_PASS );
	iEikonEnv->DeleteResourceFile(offset);
	User::LeaveIfError(err);
	}


	CDialogPIN::~CDialogPIN()
	{
		if (iWrongMsg)
			delete iWrongMsg;
        iEikonEnv->RemoveFromStack(this);
	}


	void CDialogPIN::Show()
	{
	RouseSleepingDialog();
	}


	// Azzera il contenuto della password...
	void CDialogPIN::PostLayoutDynInitL() // must not fail
	{
    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*, ControlOrNull(EPinID));
    CEikSecretEditor* secretEd = STATIC_CAST(CEikSecretEditor*, control->ControlByLayoutOrNull( EPinLayout ));
    if (secretEd)
		secretEd->SetText(_L(""));
	}


TBool CDialogPIN::OkToExitL(TInt aButtonId)
	{
	// A quanto pare viene richiamato solo se si pigia "OK"...
	TBuf<10> txt;
	CAknQueryControl* control = STATIC_CAST(CAknQueryControl*, ControlOrNull(EPinID));
	CEikSecretEditor* secretEd = STATIC_CAST(CEikSecretEditor*, control->ControlByLayoutOrNull( EPinLayout ));
	secretEd->GetText(txt);

/*	if (txt != iGoodPass) 
	{
        CAknErrorNote* note = new (ELeave) CAknErrorNote;
		note->ExecuteLD(iWrongMsg->Des());
		txt.Zero();
	}*/

	TBuf8<10> buff;
	buff.Copy( txt );
//	ChiudiNotifier(KErrNone, buff);
	return ETrue;
	}

