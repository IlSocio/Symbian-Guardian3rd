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

class CDialogPIN;


LOCAL_C void CreateNotifiersL(CArrayPtrFlat<MEikSrvNotifierBase2>* aNotifiers)
    {
    MEikSrvNotifierBase2* notifier;
    notifier = CDialogPIN::NewL();
    CleanupStack::PushL(notifier);
    aNotifiers->AppendL(notifier);
    CleanupStack::Pop(notifier);
    // typically, repeat this procedure for as
    // many notifiers as are implemented
    // in the plug-in DLL.
    }


// Lib main entry point
EXPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray1()
    {
    CArrayPtrFlat<MEikSrvNotifierBase2>* notifiers=new CArrayPtrFlat<MEikSrvNotifierBase2>(5);
    if (notifiers)
        {
        TRAPD(err, CreateNotifiersL(notifiers));
        if(err)
            {
            TInt count = notifiers->Count();
            while(count--)
                {
                (*notifiers)[count]->Release();
                }
            delete notifiers;
            notifiers = NULL;
            }
        }
    return(notifiers);
    }



// ****************************************** PROXY

const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(0x200107B1, NotifierArray1)
    };

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    // __DEBUG_LOG("ImplementationGroupProxy");
    aTableCount = sizeof(ImplementationTable)/sizeof(TImplementationProxy);
    return ImplementationTable;
    }

// ****************************************** PROXY



const TUid KMyUid = {0x200107B1};
const TUid KScreenOutputChannel = {0};

// Member Functions

	MEikSrvNotifierBase2* CDialogPIN::NewL()
    {
    CDialogPIN* self = new (ELeave) CDialogPIN();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return (MEikSrvNotifierBase2*)self;
    }

	CDialogPIN::CDialogPIN() 
	{
	}
/*
	void CDialogPIN::RunL() 
	{
	}

	void CDialogPIN::DoCancel()
	{
	}*/

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

	void CDialogPIN::Release() 
	{
        delete this;
	}


	MEikSrvNotifierBase2::TNotifierInfo CDialogPIN::RegisterL()
	{
        iInfo.iUid=KMyUid;
        iInfo.iChannel=KScreenOutputChannel;
        iInfo.iPriority=ENotifierPriorityVHigh;
        return iInfo;
	}


	MEikSrvNotifierBase2::TNotifierInfo CDialogPIN::Info() const
	{
		return iInfo;
	}


	TPtrC8 CDialogPIN::StartL(const TDesC8& buffer)
    { // will not get called as this is a get response notifier
	    // RouseSleepingDialog();
        return TPtrC8(buffer);
	}


	void CDialogPIN::StartL(const TDesC8& buffer, TInt replySlot, const RMessagePtr2& aMessage)
    {	// display the notifier
        //const TAny* rdes=aMessage.Ptr2();
        //TInt desLength=aMessage.Client().GetDesLength(rdes);
        //if (desLength!=(TInt)sizeof(TMediaPswdReplyNotifyInfoV1))
        //        User::Leave(KErrGeneral);

		// non waiting dialog
        // iMessage = aMessage;
        // iReturnVal = aReturnVal;
		iReplySlot = replySlot;
		iMessage = aMessage;
		iGoodPass.Copy(buffer);

        TInt ris = RouseSleepingDialog();

		// Viene richiamato quando il dialog viene chiuso...
		ChiudiNotifier(KErrNone, _L8(""));/**/
	}


	void CDialogPIN::ChiudiNotifier(const TInt err, const TDesC8& valore) 
	{
        ExitSleepingDialog();
		if (!iMessage.IsNull()) 
		{
			iMessage.WriteL(iReplySlot, valore); // Qui deve scrivere il PIN appena letto dall'utente...
			iMessage.Complete(err);
		}
	}


	// Cancels an active notifier.
	// This is called as a result of a client-side call to RNotifier::CancelNotifier().
	void CDialogPIN::Cancel()
	{
		ChiudiNotifier(KErrCancel, _L8(""));
	}


	TPtrC8 CDialogPIN::UpdateL(const TDesC8 &aBuffer)
    { 
        return TPtrC8(NULL);
	}


/*EXPORT_C void CDialogPIN::UpdateL(const TDesC8 &aBuffer, TInt aReplySlot, const RMessagePtr2 &aMessage)
{
}

// Handles a screen change event.
EXPORT_C void CDialogPIN::HandleSystemEventL(TUid aEvent)
{
}

EXPORT_C TInt CDialogPIN::NotifierCapabilites()
{
	return 0;
}*/

	 
// Azzera il contenuto della password...
void CDialogPIN::PreLayoutDynInitL() // must not fail
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
	ChiudiNotifier(KErrNone, buff);
	return ETrue;
	}

	/*
TInt CCknMmcNotifier::DisplayNotifier()
        {
        RouseSleepingDialog();
        return KErrNone;
        }

void CCknMmcNotifier::PreLayoutDynInitL()
        { // must not fail in anyway
        }

TBool CCknMmcNotifier::OkToExitL(TInt aButtonId)
        {
        return ETrue;
		}  
	*/

