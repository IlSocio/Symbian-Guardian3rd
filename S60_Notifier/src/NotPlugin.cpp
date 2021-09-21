
#include "notplugin.h"

#include <DialogPIN_200107B1.rsg>

#include <FuzzyByte\Notes.H>
#include <FuzzyByte\FileLogger.H>

#include <eikdef.h>
#include <EIKENV.H>
#include <aknnotifystd.h>
#include <avkon.rsg>
#include <avkon.mbg>
#include <eikmfne.h>
#include <eikseced.h>
#include <akncontrol.h>
#include <aknquerydialog.h>
#include <aknnotewrappers.h>
#include <COEAUI.H>


_LIT(KNotifierDir, "c:\\system\\data\\200107B0\\");


// ****************************************** PROXY

IMPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray1();
 
#ifdef __WINSCW__
_LIT(KFileName, "z:\\resource\\apps\\DialogPIN_200107B1.r05");
#else
_LIT(KFileName, "c:\\resource\\apps\\DialogPIN_200107B1.rsc");
#endif 


const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(0x200107B1, NotifierArray1)
    };

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    // __DEBUG_LOG("ImplementationGroupProxy");
	__LOG_DECLARATION_MEMBER
	__LOG_OPEN("Guardian", "Start.txt");
	__LOG_TXT("1 - ImplGroup");
    aTableCount = sizeof(ImplementationTable)/sizeof(TImplementationProxy);
    __LOG("ImplGroup:%d",aTableCount);
    __LOG_CLOSE;
    return ImplementationTable;
    }

// ****************************************** PROXY


LOCAL_C void CreateNotifiersL(CArrayPtrFlat<MEikSrvNotifierBase2>* aNotifiers)
    {
__LOG_DECLARATION_MEMBER;
__LOG_OPEN("Guardian", "Start.txt");
__LOG_TXT("3 - Create");
__LOG_CLOSE;
    MEikSrvNotifierBase2* notifier;
    notifier = CNotPlugin::NewL();
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
	__LOG_DECLARATION_MEMBER;
__LOG_OPEN("Guardian", "Start.txt");
__LOG_TXT("2 - Entry");
__LOG_CLOSE;
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



LOCAL_C void LaunchGuardianL()
	{
	// Charging UID = 10003A4A
	
/*	__LOG_DECLARATION_MEMBER
	__LOG_OPEN("Guardian", "Start.txt");
	TUint32 uidCall = RProcess().Type().MostDerived().iUid;		// Gets UID3
	__LOG("Proc uid3: %X", uidCall);

	TFindProcess processFinder(_L("*"));
	TFullName fullName;
	while (processFinder.Next(fullName) == KErrNone)
		{
		__LOG_DES(fullName);
		}
	__LOG_CLOSE;*/

	
	// Prepare to Launch Guardian...	
	TUid uid3 = {0x200131CB};
	const TUidType guardUid(KNullUid, KNullUid, uid3);
	RProcess guardian;
	TInt r=guardian.Create(_L("Guardian_200131CB"), KNullDesC, guardUid);
	if (r!=KErrNone) 
		{
		return;
		}
	TRequestStatus stat;
	guardian.Rendezvous(stat);
	if (stat != KRequestPending)
	{
		guardian.Kill(0);				// abort startup
	}
	else
	{
		guardian.SetParameter(1, 2);	// Avvio da Extended Notifier
		guardian.Resume();				// logon OK - start the server
	}
	User::WaitForRequest(stat);		// wait for start or death
	r=(guardian.ExitType()==EExitPanic) ? KErrGeneral : stat.Int();
	guardian.Close();	
	}

const TUid KMyUid = {0x200107B1};
const TUid KScreenOutputChannel = { 0x10009D48 };

// Member Functions

	MEikSrvNotifierBase2* CNotPlugin::NewL()
    {
    CNotPlugin* self = new (ELeave) CNotPlugin();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return (MEikSrvNotifierBase2*)self;
    }

	void CNotPlugin::DoCancel()
	{
	}

	CNotPlugin::CNotPlugin() : CActive(EPriorityStandard)
	{
		CActiveScheduler::Add(this);
	}

	void CNotPlugin::ConstructL()
	{
//		iTimer = CTimeOutTimer::NewL(EPriorityNormal, *this);
		iWrongMsg = HBufC::NewL(64);
		iBackgr = NULL;		
	}


	CNotPlugin::~CNotPlugin()
	{
__LOG_DECLARATION_MEMBER;
__LOG_OPEN("Guardian", "Start.txt");
__LOG_TXT("**** - Destroy"); 
__LOG_CLOSE;
	    Cancel();
		delete iWrongMsg;
	}

	void CNotPlugin::Release()
	{
__LOG_DECLARATION_MEMBER;
__LOG_OPEN("Guardian", "Start.txt");
__LOG_TXT("**** - Release"); 
__LOG_CLOSE;
        delete this;
	} 
 
	//*** 1 
	MEikSrvNotifierBase2::TNotifierInfo CNotPlugin::RegisterL()
	{	
__LOG_DECLARATION_MEMBER;
__LOG_OPEN("Guardian", "Start.txt");
__LOG_TXT("4 - Register"); 
__LOG_CLOSE;	
        iInfo.iUid=KMyUid;
        iInfo.iChannel=KScreenOutputChannel;
//        iInfo.iPriority=ENotifierPriorityVHigh;
		iInfo.iPriority=ENotifierPriorityLow;

		// Attenzione perche' si puo' compromettere la possibilita' di fare hard-reset...
		// Commentando il User::WaitForRequest(stat);
		if (!iLaunchedGuardian)
			{
			// nel caso in cui venisse richiamato piu' volte
			LaunchGuardianL();
			iLaunchedGuardian = ETrue;
			}
		
		return iInfo;
	}


	MEikSrvNotifierBase2::TNotifierInfo CNotPlugin::Info() const
	{
		return iInfo;
	}


	TPtrC8 CNotPlugin::StartL(const TDesC8& buffer)
    { // will not get called as this is a get response notifier
	    // RouseSleepingDialog();
        return TPtrC8(buffer);
	}



	void CNotPlugin::StartL(const TDesC8& buffer, TInt replySlot, const RMessagePtr2& aMessage)
	{
		iReplySlot = replySlot;
		iMessage = aMessage;
		
		iDisableCancel = (buffer.Left(1) == _L8("1"));
		// iDisableCancel = EFalse;
		iGoodPass.Copy(buffer.Mid(1));
		
	    SetActive();
	    iStatus = KRequestPending;
	    TRequestStatus* stat = &iStatus;
	    User::RequestComplete(stat, KErrNone);    
	}

	
	void CNotPlugin::RunL()
		{
		// Crea dir pubblica Notifier
		RFs& fs = CCoeEnv::Static()->FsSession();
		TInt err = fs.MkDirAll( KNotifierDir );
		__LOG("MkDir: %d", err);

		// Che succede se fa Panic? 
		// Se fa Leave, viene richiamata RunError 
		// User::Leave(KErrNotFound); 
		
		__LOG_DECLARATION_MEMBER;
		__LOG_OPEN("Guardian", "Notifier.txt");
		__LOG("Slot:%d", iReplySlot);

		if (iOffset == 0)
			{			
			iOffset = CCoeEnv::Static()->AddResourceFileL(KFileName);
			__LOG("AddResFile :%x", iOffset);

		    //iKeyHandle1 = CCoeEnv::Static()->RootWin().CaptureKey( EKeyPhoneEnd, 0, 0, EPriorityFileServer ) ;
		    //iKeyHandle2 = CCoeEnv::Static()->RootWin().CaptureKeyUpAndDowns( EStdKeyNo, 0, 0, EPriorityFileServer );
			}
		
		if (iBackgr == NULL)
		{		
			__LOG_TXT("Backgr Null");
			iBackgr = CPinView::NewL(this);
			CCoeEnv::Static()->AppUi()->AddToStackL(iBackgr);
			__LOG_TXT("Done Backgr");
		}/**/

		TBuf<10> pass;
		pass.Zero();
		// Questa dialog NON e' modale, sara' lanciata, presa in carico dal framework e l'esecuzione continuera'...
		iDlg = new( ELeave ) CAsyncQueryDialog( *this, pass );
		
//		CAknTextQueryDialog* dlg = new (ELeave) CAknTextQueryDialog(pass);
		__LOG_TXT("SetFocus");
		iDlg->SetFocus(ETrue);
		iDlg->SetPredictiveTextInputPermitted( EFalse );
	 	
		__LOG_TXT("ExecuteLD");
		 
		TInt resource = R_PIN_QUERY;
		if (iDisableCancel)
			resource = R_PIN_QUERY_NO_CANCEL;
		
		// Chiama notifier
//		User::Leave( KErrNotFound );
		TRAPD( trap_err, err = iDlg->ExecuteLD( resource ); );
		__LOG("TrapErr: %d  Err: %d", trap_err, err);

		// Elimina dir pubblica Notifier
		err = fs.RmDir( KNotifierDir );
		__LOG("RmDir: %d", err);
				
/*		if (iDisableCancel)
			{
			R_PIN_QUERY_NO_CANCEL;
			//iDlg->PrepareLC( R_PIN_QUERY_NO_CANCEL );
			//__LOG_TXT("SetMaxLen"); 
			// iDlg->SetMaxLength( 8 ); // KPASS_LEN
			TRAPD( trap_err, err = iDlg->ExecuteLD( R_PIN_QUERY_NO_CANCEL ); );
//			TRAPD( trap_err, iDlg->PrepareLC( R_PIN_QUERY_NO_CANCEL ); err = iDlg->RunLD(););
			__LOG("Trap Err: %d", trap_err);		
			}
		else
			{
			//iDlg->PrepareLC( R_PIN_QUERY );
			//__LOG_TXT("SetMaxLen"); 
			// iDlg->SetMaxLength( 8 ); // KPASS_LEN
			iDlg->PrepareLC( R_PIN_QUERY );
			__LOG_TXT("RunLD");
			err = iDlg->RunLD();
//			TRAPD( trap_err, iDlg->PrepareLC( R_PIN_QUERY ); err = iDlg->RunLD(););
			TRAPD( trap_err, err = iDlg->ExecuteLD( R_PIN_QUERY ); );
			__LOG("Trap Err: %d", trap_err);		
			}
		__LOG("RunLD Err: %d", err);		*/

		/*
		CAknTextQueryDialog* Dialog =
		CAknTextQueryDialog::NewL(pass, CAknQueryDialog::ENoTone);
		Dialog->PrepareLC(R_ASK_NAME_DIALOG);
		Dialog->SetPromptL(_L("Title"));
		TInt err = KErrNone;
		TRAPD(lv, err = Dialog->RunLD());/**/
		
		if (iBadCode)
			{
			__LOG_TXT("iBadCode");
			if (iWrongMsg->Length() == 0)
				{
				TPtr16 ptr = iWrongMsg->Des();
				__LOG_TXT("ReadResFile");
				CCoeEnv::Static()->ReadResource( ptr, R_WRONG_PASS );
				}
			CAknErrorNote* dialog = new ( ELeave ) CAknErrorNote(EFalse);
			dialog->ExecuteLD( iWrongMsg->Des() );
			iBadCode = EFalse;
			}
		__LOG_CLOSE;		
		}


	void CNotPlugin::ChiudiNotifierL(const TInt err, const TDesC8& valore)
	{		 
		if (iOffset)
		{
			//__LOG_TXT("DeleteResFile"));
			CCoeEnv::Static()->DeleteResourceFile(iOffset);
			iOffset = 0;
			 // Release captured keys
//			CCoeEnv::Static()->RootWin().CancelCaptureKey( iKeyHandle1 );
//			CCoeEnv::Static()->RootWin().CancelCaptureKey( iKeyHandle2 );
		}

		__LOG_DECLARATION_MEMBER;
		__LOG_OPEN("Guardian", "Notifier.txt");
		__LOG("*Close: %d", err);
		if (iBackgr)
		{
			CCoeEnv::Static()->AppUi()->RemoveFromStack(iBackgr);
			__LOG_TXT("DeleteBack");
			delete iBackgr;
			__LOG_TXT("Set Back to NULL");
			iBackgr = NULL;
		}/**/
		if (!iMessage.IsNull())
		{
			__LOG_TXT("MsgNotNULL");
			__LOG("WriteSlot: %d", iReplySlot);
			iMessage.WriteL(iReplySlot, valore); // Qui deve scrivere il PIN appena letto dall'utente...
			__LOG_TXT("Complete");
			iMessage.Complete(err);
		} else {
			__LOG_TXT("MsgNULL");
		}
		__LOG_CLOSE;
		// iManager->CancelNotifier(KNotifier1Uid);
	}


	void CNotPlugin::DialogClosedL(TBool ok, const TDesC& code)
	{
		__LOG_DECLARATION_MEMBER;
		__LOG_OPEN("Guardian", "Notifier.txt");
		__LOG("*DialogClose: %d", ok);
		__LOG_DES(code);
		__LOG_DES(iGoodPass);
		__LOG_CLOSE;
		iDlg = NULL;
		if (!ok)
		{	// Cancel
			ChiudiNotifierL(KErrCancel, KNullDesC8());
			return;
		}

		iBadCode = EFalse;
		// Pigiato Ok
		if (code.Compare(iGoodPass) != 0)
		{
			//			CAknErrorNote* dialog = new ( ELeave ) CAknErrorNote(ETrue);
			// Usando il Flag EFalse il focus viene preso da un'altro processo e poi restituito all'applicazione...
			// Generando una nuova richiesta Password quindi di fatto ne impedisce l'accesso se la pass e' sbagliata...
			// Mentre nella BETA si vuole consentire l'accesso anche con la pass sbagliata
			//
			if (code.Length() > 0)
				iBadCode = ETrue;
			RunL();
/*			TBuf<10> pass;
			pass.Zero();
			// Questa dialog NON e' modale, sara' lanciata, presa in carico dal framework e l'esecuzione continuera'...
			CAsyncQueryDialog* dlg = new( ELeave ) CAsyncQueryDialog( *this, pass );
			dlg->SetPredictiveTextInputPermitted( EFalse );
			dlg->PrepareLC( R_PIN_QUERY );
			dlg->SetFocus(ETrue);
			
			dlg->SetMaxLength( 8 ); // KPASS_LEN
			dlg->RunLD();
			
			if (code.Length() > 0)
				{
				CAknErrorNote* dialog = new ( ELeave ) CAknErrorNote(EFalse);
				dialog->ExecuteLD( iWrongMsg->Des() );
				}*/
			return;
		}/**/
		TBuf8<20> pass8;
		pass8.Copy(code);
		ChiudiNotifierL(KErrNone, pass8);
	}


	TInt CNotPlugin::RunError(TInt aError)
		{
__LOG_DECLARATION_MEMBER;
__LOG_OPEN("Guardian", "Notifier.txt");
__LOG("**** - RunError: %d", aError); 
__LOG_CLOSE;
/*		RFs fs;
		fs.Connect();
		TBuf<40> buf = _L("c:\\data\\notiferr");
		buf.AppendNum(aError);
		buf.Append(_L("\\"));
		fs.MkDirAll(buf);
		fs.Close();/**/
		TRAP_IGNORE( ChiudiNotifierL(aError, KNullDesC8()) );
		// Chiude il notifier e riporta l'errore al chiamante...
		return aError;
		} 
 
	// Cancels an active notifier.
	// This is called as a result of a client-side call to RNotifier::CancelNotifier()
	void CNotPlugin::Cancel()
	{
	    CActive::Cancel();
		// Close the pending dialog

	    if (iDlg)
	    	iDlg->Close();
	    
		TRAP_IGNORE( ChiudiNotifierL(KErrCancel, KNullDesC8()) );
	}


	TPtrC8 CNotPlugin::UpdateL(const TDesC8 &aBuffer)
    {
        return TPtrC8(NULL);
	}


/* Utile per debug...
TInt CNotifier1::NotifierCapabilites()
{
return EScreenDeviceChangeSupported;
}*/

