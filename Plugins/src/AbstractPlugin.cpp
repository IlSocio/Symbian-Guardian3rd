

#include "AbstractPlugin.h"
#include "common.h"

#include <FuzzyByte\Guardian\client.h>

// Construction and destruction functions

CAbstractPlugin::~CAbstractPlugin()
	{
	delete iResReader;
	iFs.Close();
	iDataUpper.Close();
	iReply.Close();
	iNumber.Close();
	__LOG_CLOSE;
	}


void CAbstractPlugin::BaseConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	TBuf<20> buf;
	buf.Append(PluginId());
	buf.Append(_L("_Plug.txt"));
	__LOG_OPEN_LIT(_L("Guardian"), buf);
	User::LeaveIfError( iFs.Connect() );
	iResReader = CResReader::NewL(iFs, KResFileName);
	}


TPtrC CAbstractPlugin::GetParamValue(const TDesC& aParam)
	{
	TInt pos = iDataUpper.Find( aParam ); // Trova TIME=10
	TInt len = 0;
	if (pos < 0)
		return TPtrC();
	pos+=aParam.Length()+1;
	len = iDataUpper.Mid(pos).Find(KSPACE);
	if (len<0) len = iDataUpper.Length()-pos;
	if ( pos+len <= iDataUpper.Length() )
		return iDataUpper.Mid(pos, len);
	return TPtrC();
	}


TInt CAbstractPlugin::GetParamValueInt(const TDesC& aParam)
	{
	TInt num = -1;
	TPtrC ptr = GetParamValue(aParam );
	TLex lex( ptr );
	lex.Val(num);
	return num;
	}


void CAbstractPlugin::Complete(TInt code)
	{
	__LOG("Complete:%d", code);
	if (iStatus == NULL)
		return;
	if (*iStatus == KRequestPending)
		{
		__LOG_TXT("IsPending");
		User::RequestComplete(iStatus, code);
		}
	__LOG_TXT("End Complete");
	}


void CAbstractPlugin::CancelRemoteCommandL()
	{
	__LOG_TXT("CancelRemoteCommand");
	CancelCommandL();
	if (iStatus == NULL)
		return;
	if (*iStatus == KRequestPending)
		{
		Complete(KErrCancel);
		}
	}


void CAbstractPlugin::CancelCommandL()
{
}


void CAbstractPlugin::SendSmsL(const TDesC& data, TBool split)
{
	RGuardian guard;
	User::LeaveIfError( guard.Connect() );
	CleanupClosePushL(guard);
	guard.SendMessage(iNumber, data, split);
	CleanupStack::PopAndDestroy(); // guard
}


void CAbstractPlugin::ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aData)
	{
	__LOG_TXT("ProcessRemoteCmdL");
	iStatus = &aCompletionStatus;
	CancelRemoteCommandL();
	*iStatus = KRequestPending;

	iDataUpper.Close();
	iDataUpper.CreateL(aData);
	iDataUpper.UpperCase();

	iMustReply = ETrue;
	if (iDataUpper.Find(KNOREPLY) >= 0)
		iMustReply = EFalse;

	iNumber.Close();
	iNumber.CreateL(KNUMBER_LEN);
	iNumber.Copy(srcNumb);

	iReply.Close();
	iReply.CreateL(INIT_REPLY_LEN);

	TPtrC numb = GetParamValue(KDESTNUMBER);
	if (numb.Length() > 0) iNumber.Copy(numb);

	ProcessCommandL(aData);
	}


TBool CAbstractPlugin::AppendDataToReplyL(const TInt aResourceID)
	{
	__LOG_TXT("AppendData RESID");
	HBufC* txt = iResReader->AllocReadLC(aResourceID);
	TBool ris = AppendDataToReplyL(*txt);
	CleanupStack::PopAndDestroy(txt);	
	return ris;
	}

TBool CAbstractPlugin::AppendDataToReplyL(const TDesC& data)
	{
	if (!iMustReply || data.Length() <= 0)
		{
		return EFalse;
		}
	TBool realloc = EFalse;
	if (iReply.Length() + data.Length() >= iReply.MaxLength())
	{
		__LOG("REALLOC:%d", data.Length());
		iReply.ReAllocL( iReply.Length() + data.Length() + 1);
		realloc = ETrue;
	}
	__LOG_TXT("Append...");
	__LOG_DES(data);
	iReply.Append(data);
	if (realloc)
		{
		SendReplyL();
		}
	return ETrue;
	}


TBool CAbstractPlugin::SendReplyL()
	{
	if (!iMustReply || iReply.Length() == 0)
		{
		iReply.Zero();
		return EFalse;
		}
	SendSmsL(iReply);
	iReply.Zero();
	return ETrue;
	}

