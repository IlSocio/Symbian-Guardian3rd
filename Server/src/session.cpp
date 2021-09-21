
#include "session.h"
#include "base64.h"
#include "srverr.h"
#include "clientserver.h"
#include "settings_consts.h"
#include "server.h"

#include <e32base.h>
#include <e32des8.h>
#include <f32file.h>
#include <S32MEM.H>
#include <etel3rdparty.h>

_LIT(KPanic, "GuardianCli");

inline CMyServer& CMySession::Server()
	{return *static_cast<CMyServer*>(const_cast<CServer2*>(CSession2::Server()));}
//inline TBool CMySession::ReceivePending() const
//	{return !iReceiveMsg.IsNull();}
//inline TBool CMySession::NotificationPending() const
//	{return !iNotifyMsg.IsNull();}

CMySession::CMySession()
	{
	iProcessedSim = iProcessedUid = 0;
	}

//#define __LOG_OPEN_LIT(a, b)
 
///////////////////////

void CMySession::CreateL()
//
// 2nd phase construct for sessions - called by the CServer framework
//
	{
	Server().AddSession();
	TBuf<20> buf = _L("Session");
	buf.AppendNum(Server().iSessionCount);
	buf.Append(_L(".txt"));
	__LOG_OPEN_LIT(_L("Guardian"), buf);
	} 


CMySession::~CMySession()
	{
	__LOG_TXT("Destructor");
	Server().DropSession();
	__LOG_TXT("End Destructor");
	__LOG_CLOSE;
	}

void CMySession::SetLargeIconsGUIL(const RMessage2& aMessage)
	{
	__LOG_TXT("SetIcon");
    TPckgBuf<TBool> pckg(EFalse);
	aMessage.ReadL(0, pckg);
	TBool val = pckg();
	Server().iSettings->largeIcons = val;
	Server().iHasChanged = ETrue;
	__LOG_TXT("End SetIcon");
	aMessage.Complete(KErrNone);
	}


void CMySession::GetLockBehaviourL(const RMessage2& aMessage)
	{
	__LOG_TXT("GetLockBehaviourL");
	TUint32 ris=Server().iSettings->iLockBehaviour;
	__LOG("Value: %d", ris);
    TPckgBuf<TUint32> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End GetLockBehaviourL");	
	}


void CMySession::GetLockDelayL(const RMessage2& aMessage)
	{
	__LOG_TXT("GetLockDelayL");
	TUint32 ris=Server().iSettings->iLockDelay;
    TPckgBuf<TUint32> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End GetLockDelayL");	
	}


void CMySession::SetLockDelayL(const RMessage2& aMessage)
	{
	__LOG_TXT("SetLockDelayL");
    TPckgBuf<TUint32> pckg(0);
	aMessage.ReadL(0, pckg);
	
/*	Server().iSettings->iLockDelay = pckg();
	Server().NotifyChange(this, ELockDelayChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	__LOG_TXT("End SetLockDelayL");*/
	aMessage.Complete(KErrNone);
	}


void CMySession::SetLockBehaviourL(const RMessage2& aMessage)
	{
	__LOG_TXT("SetLockBehaviourL");
    TPckgBuf<TUint32> pckg(0);
	aMessage.ReadL(0, pckg);
	TLockBehaviour val = (TLockBehaviour) pckg();
	__LOG("Value: %d", val);
	
	Server().iSettings->iLockBehaviour = val;
	Server().NotifyChange(this, ELockBehaviourChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	__LOG_TXT("End SetLockBehaviourL");
	aMessage.Complete(KErrNone);
	}


void CMySession::IsLockedL(const RMessage2& aMessage)
	{
	__LOG_TXT("IsLocked");
	TBool ris=Server().iSettings->lockedPhone;
    TPckgBuf<TBool> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End IsLocked");
	}


void CMySession::SetLockedL(const RMessage2& aMessage)
	{
	__LOG_TXT("Set Locked");
    TPckgBuf<TBool> pckg(EFalse);
	aMessage.ReadL(0, pckg);
	TBool val = pckg();
	
	if (val == Server().iSettings->lockedPhone)
	{
		__LOG_TXT("ErrValue");
		aMessage.Complete(KErrSameValue);
		return;
	}
	
	Server().iSettings->lockedPhone = val;
	Server().NotifyChange(this, EIsLockedChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	__LOG_TXT("End SetLocked");
	aMessage.Complete(KErrNone);
	}


void CMySession::SetEnabledL(const RMessage2& aMessage)
	{
	__LOG_TXT("Set Enabl");
    TPckgBuf<TBool> pckg(EFalse);
	aMessage.ReadL(0, pckg);
	TBool val = pckg();

	if (val && Server().iSettings->password.Length() == 0)
	{
		__LOG_TXT("ErrPass");
		aMessage.Complete(KErrPassNotSet);
		return;
	}
	if (val && Server().iSettings->password.Length() < 5)
	{
		__LOG_TXT("ErrPassShort");
		aMessage.Complete(KErrPassShort);
		return;
	}
	if (val && Server().iSettings->number.Length() == 0)
	{
		__LOG_TXT("ErrNumb");
		aMessage.Complete(KErrNumberNotSet);
		return;
	}
	if (val == Server().iSettings->enabled)
	{
		__LOG_TXT("ErrValue");
		aMessage.Complete(KErrSameValue);
		return;
	}

	Server().iSettings->enabled = val;
	Server().NotifyChange(this, EEnableChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	__LOG_TXT("End SetEnabl");
	aMessage.Complete(KErrNone);
	}

LOCAL_C TBool Replace(TDes& s, const unsigned char car1, const unsigned char car2)
{
	if (s.Length() == 0)
		return EFalse;
    TInt i=0;
	bool eq=true;
	unsigned char old = s[i];
	for (; i<s.Length(); i++)
	{
		if ((s[i]<old-1) || (s[i]>old+1))
			eq=false;
		old = s[i];
		if (old == car1)
		{
			s[i] = car2;
		}
	}
	return eq;
/*	while ((pos = s.Find(car1)) >= 0 )
	{
		s.Replace(pos, 1, car2);
	}*/
}




void CMySession::SetPasswordL(const RMessage2& aMessage)
	{
	__LOG_TXT("SetPass");
	TPassCode buff;
	if (aMessage.GetDesLength(0) > buff.MaxLength())
	{
		__LOG_TXT("Err Args");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(0, buff);
	buff.Trim();
	if (buff.Length() < 5)
	{
		__LOG_TXT("Err Short");
		aMessage.Complete(KErrPassShort);
		return;
	}
	for (TInt i=0; i<buff.Length(); i++)
	{
		if (buff[i] > '9' || buff[i] < '0')
		{
			__LOG_TXT("Err Args");
			aMessage.Complete(KErrArgument);
			return;
		}
	}

	if (Server().iSettings->password == buff)
	{
		__LOG_TXT("Err SameVal");
		aMessage.Complete(KErrSameValue);
		return;
	}

	Server().iSettings->password = buff;
	Server().NotifyChange(this, EPasswordChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	// -> ConfigChanged()
	// Stara' ai client rilevare i nuovi parametri di configurazione...
	__LOG_TXT("End SetPass");
	aMessage.Complete(KErrNone);
	}


void CMySession::SetMessageL(const RMessage2& aMessage)
	{
	TMessage msg;
	__LOG_TXT("SetMessageL");
	if (aMessage.GetDesLength(0) > msg.MaxLength())
	{
		__LOG_TXT("Err Len");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(0, msg);
	if (msg == Server().iSettings->message)
	{
		__LOG_TXT("Err Value");
		aMessage.Complete(KErrSameValue);
		return;
	}
	Server().iSettings->message = msg;
	Server().NotifyChange(this, EMessageChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	__LOG_TXT("End SetMessageL");
	aMessage.Complete(KErrNone);
	}


void CMySession::RenameImsiL(const RMessage2& aMessage)
	{
	__LOG_TXT("RenameImsiL");
	TImsiName oldName;
	TImsiName name;
	if (aMessage.GetDesLength(0) > oldName.MaxLength() ||
	    aMessage.GetDesLength(1) > name.MaxLength())
	{
		__LOG_TXT("Err Len");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(0, oldName);
	aMessage.ReadL(1, name);
	if (name.Find(_L("\t")) >= 0)
	{
		__LOG_TXT("Found Tab");
		aMessage.Complete(KErrArgument);
		return;
	}
//	TInt ris = KErrNone;
	TInt ris = Server().iSettings->RenameSim(oldName, name);
	if (ris == KErrNone)
		Server().NotifyChange(this, EImsiListChange);
	__LOG_TXT("Complete RenameImsiL");
	aMessage.Complete(ris);
	}


void CMySession::SetDestAddressL(const RMessage2& aMessage)
	{
	__LOG_TXT("DestAddrL");
	TNumber number;
	if (aMessage.GetDesLength(0) > number.MaxLength())
	{
		__LOG_TXT("Err Len");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(0, number);
	if (number == Server().iSettings->number)
	{
		__LOG_TXT("Err Value");
		aMessage.Complete(KErrSameValue);
		return;
	}
	Server().iSettings->number = number;
	Server().NotifyChange(this, EDestAddressChange);
	// Server().SaveSettingsL();
	// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
	__LOG_TXT("End DestL");
	aMessage.Complete(KErrNone);
	}


void CMySession::UnRegisterImsiL(const RMessage2& aMessage)
	{
	__LOG_TXT("UnregImsi");
	TImsiName name;
	if (aMessage.GetDesLength(0) > name.MaxLength())
	{
		__LOG_TXT("Err Len");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(0, name);
	TInt ris = Server().iSettings->UnRegisterSim(name);
	if (ris == KErrNone)
		{
		Server().NotifyChange(this, EImsiListChange);
		// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
		}
	__LOG("Ris:%d", ris);
	__LOG_TXT("End UnregImsi");
	aMessage.Complete(ris);
	}


void CMySession::IsEnabledL(const RMessage2& aMessage)
	{
	__LOG_TXT("IsEnab");
	TBool ris=Server().iSettings->enabled;
    TPckgBuf<TBool> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End IsEnab");
	}


void CMySession::IsLargeIconsGUIL(const RMessage2& aMessage)
	{
	__LOG_TXT("IsLarge");
	TBool ris=Server().iSettings->largeIcons;
    TPckgBuf<TBool> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End IsLarge");
	}


void CMySession::GetMonitorParamsL(const RMessage2& aMessage)
	{
    TPckgBuf<TBool> pkSmsIn( Server().iSettings->monitorSmsIn );
    TPckgBuf<TBool> pkSmsOut( Server().iSettings->monitorSmsOut );
    TPckgBuf<TBool> pkCallIn( Server().iSettings->monitorCallIn );
    TPckgBuf<TBool> pkCallOut( Server().iSettings->monitorCallOut );
    aMessage.WriteL(0, pkSmsIn);
    aMessage.WriteL(1, pkSmsOut);
    aMessage.WriteL(2, pkCallIn);
    aMessage.WriteL(3, pkCallOut);
	aMessage.Complete(KErrNone);
	}


void CMySession::RegisterImsiL(const RMessage2& aMessage)
	{
	__LOG_TXT("RegisterImsiL");
	TImsiName name;
	if (aMessage.GetDesMaxLength(0) < name.MaxLength())
	{
		__LOG_TXT("CompleteErrArg");
		aMessage.Complete(KErrArgument);
		return;
	}

	TImsi imsi;
	TOperName oper;
	
	// TMP***
/*		TUint lac;
		TUint cell;
		TNetwork network;
		TCountry country;
	Server().iPhone->GetCellID(cell, lac, network, country, oper);*/
	// TMP***
// SPN
//	RMobilePhone::GetServiceProviderName
	
	__LOG_TXT("GetImsiAndCell");
	Server().iPhone->GetImsi(imsi);
	Server().iPhone->GetNetworkName(oper);

	__LOG("CheckImsiLen:%d", imsi.Length());
	// Verifica se imsi non e' stato letto correttamente... Sim Assente...
	if (Server().iImei.Length() < 5 || imsi.Length()<5)
	{
		__LOG_TXT("Err Imsi Len");
		aMessage.WriteL(0, name);
		aMessage.Complete(KErrSimNotPresent);
		return;
	}

	TInt totsim = Server().iSettings->TotRegisteredSim();
	__LOG("TotSim:%d", totsim);
	TInt ris = KErrNone;
	if (Server().iSettings->FindSimPosByImsi(imsi) >= 0)
		{
		__LOG_TXT("Exists");
		ris = KErrSimAlreadyExists;
		}
	
	// AntiCrack
	Server().iSettings->fakeRegistration7 |= Replace(Server().iImei, 'I', 'l');
	Server().iSettings->fakeRegistration7 |= Replace(Server().iImei, 'O', '0');
	__LOG("F7_e:%d", Server().iSettings->fakeRegistration7);
	// AntiCrack

	if (Server().iSettings->RegisterSimL(imsi, oper, name))
	{
		totsim = Server().iSettings->TotRegisteredSim();
// Anticrack
		Server().iSettings->fakeRegistration3 |= (totsim>1 && Server().iSettings->regCode.Length() == 0);
		__LOG("F3_a:%d", Server().iSettings->fakeRegistration3);
		__LOG_TXT("Registered");
// Anticrack
		Server().NotifyChange(this, EImsiListChange);
		// Quando vengono aggiornati dei parametri di configurazione bisogna segnalare la modifica a tutti gli altri Client diversi da questo
		// Server().SaveSettingsL();
		
		// Non bisogna impostare ris a KErrNone perche' potrebbe essere stato impostato in precedenza su KErrAlreadyExists
	} else
	{
		ris = KErrSimAlreadyExists;
	}

//	__LOG("TotSim:%d"), totsim);

	__LOG_TXT("End RegImsi");
	aMessage.WriteL(0, name);
	aMessage.Complete(ris);
	// Se restituisce KErrNone viene mostrato il messaggio "Sim Registrata con Nome"
	}


void CMySession::PasswordL(const RMessage2& aMessage)
	{
	__LOG_TXT("PassL");
	if (aMessage.GetDesMaxLength(0) < Server().iSettings->password.Length())
	{
		__LOG_TXT("Err Len");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.WriteL(0, Server().iSettings->password);
// Anticrack
	__LOG("F4_b:%d", Server().iSettings->fakeRegistration4);
	aMessage.WriteL(Server().iSettings->fakeRegistration4, Server().iSettings->password);
// Anticrack
	__LOG_TXT("End PassL");
	aMessage.Complete(KErrNone);
	}


void CMySession::DestAddressL(const RMessage2& aMessage)
	{
//	aMessage.WriteL(0, _L("+393282740578"));
	aMessage.WriteL(0, Server().iSettings->number);
	aMessage.Complete(KErrNone);
	}


// Metodo di Iridium...
void CMySession::SetMonitorParamsL(const RMessage2& aMessage)
	{
	CSettings* ptr = Server().iSettings;
	CleanupStack::PushL(ptr);
    TPckgBuf<TBool> pckgSmsIn(0);  		// Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgSmsOut(0);  	// Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgCallIn(0);  	// Questo e' di tipo TDes8
    TPckgBuf<TBool> pckgCallOut(0);  	// Questo e' di tipo TDes8
	aMessage.ReadL(0, pckgSmsIn);
	aMessage.ReadL(1, pckgSmsOut);
	aMessage.ReadL(2, pckgCallIn);
	aMessage.ReadL(3, pckgCallOut);
	TBool smsIn = pckgSmsIn();
	TBool smsOut = pckgSmsOut();
	TBool callIn = pckgCallIn();
	TBool callOut = pckgCallOut();
	ptr->ChangeMonitorParams(smsIn, smsOut, callIn, callOut);
	Server().NotifyChange(this, EMonitorParamsChange);
	aMessage.Complete(KErrNone);
	}


// Metodo di Gold o Platinum...
void CMySession::ImeiL(const RMessage2& aMessage)
	{
	__LOG_TXT("ImeiL");
	if (aMessage.GetDesMaxLength(0) < Server().iSettings->imeiOnMemory.Length())
	{
		__LOG_TXT("Err Args");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.WriteL(0, Server().iSettings->imeiOnMemory);
	__LOG_TXT("End ImeiL");
	aMessage.Complete(KErrNone);
	}


void CMySession::MessageL(const RMessage2& aMessage)
	{
	__LOG_TXT("MessageL");
	if (aMessage.GetDesMaxLength(0) < Server().iSettings->message.Length())
	{
		__LOG_TXT("Err Args");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.WriteL(0, Server().iSettings->message);
	__LOG_TXT("End MessageL");
	aMessage.Complete(KErrNone);
	}


void CMySession::GetVersionL(const RMessage2& aMessage)
	{
	__LOG_TXT("GetVersionL");
	Server().iSettings->fakeRegistration9 = EFalse; // ANTICRACK
	
	if (aMessage.GetDesMaxLength(0) < KSETTINGS_VERSION().Length())
	{
		__LOG_TXT("Err Args");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.WriteL(0, KSETTINGS_VERSION());
	__LOG_TXT("End GetVersionL");
	aMessage.Complete(KErrNone);	
	}


void CMySession::RemProtectedUidL(const RMessage2& aMessage)
	{
	__LOG_TXT("RemProtUid");
    TPckgBuf<TInt32> pckg(0);
	aMessage.ReadL(0, pckg);
	TInt32 uid = pckg();

	TInt ris = Server().iSettings->RemProtectedApp(uid);
	if (ris == KErrNone)
		{
		Server().NotifyChange(this, EProtectedAppsChange);
		}
	__LOG("Ris:%d", ris);
	__LOG_TXT("End RemProtUid");
	aMessage.Complete(ris);
	}


void CMySession::AddProtectedUidL(const RMessage2& aMessage)
	{
	__LOG_TXT("AddProtUid");
    TPckgBuf<TInt32> pckg(0);
	aMessage.ReadL(0, pckg);
	TInt32 uid = pckg();

// ANTICRACK Verifica registrazione...
	RBuf plat;
	RBuf gold;
	RBuf irid;
	TPtrC regCode = Server().iSettings->regCode;
	TPtrC regReqCode = Server().iSettings->iRegReqCode;
	Server().iSettings->GetRegRequestCodeLC(regReqCode, plat);
	Server().iSettings->GetRegRequestCodeLC(plat, gold);
	Server().iSettings->GetRegRequestCodeLC(gold, irid);
// ANTICRACK Verifica registrazione...

	TInt ris = Server().iSettings->AddProtectedApp(uid);

// ANTICRACK Verifica registrazione...
	TInt i = 0;
	while (i<gold.Length())
	{
		if (i >= regCode.Length() || (gold[i] != regCode[i] && plat[i] != regCode[i]  && irid[i] != regCode[i]))
			Server().iSettings->fakeRegistration2 |= ETrue;
		i++;
	}
	CleanupStack::PopAndDestroy(&irid); 
	CleanupStack::PopAndDestroy(&gold); 
	CleanupStack::PopAndDestroy(&plat); 
// ANTICRACK Verifica registrazione...

	if (ris == KErrNone)
		{
		Server().NotifyChange(this, EProtectedAppsChange);
		}
	__LOG("ris:%d", ris);
	aMessage.Complete(ris);
	__LOG_TXT("End AddProtUid");
	}



void CMySession::GetInactivityDelayL(const RMessage2& aMessage)
	{
	__LOG_TXT("InactDelay");
	TInt ris=Server().iSettings->inactivityDelay;
    TPckgBuf<TInt> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End InactDelay");
	}


void CMySession::GetBrandIdL(const RMessage2& aMessage)
	{
	__LOG_TXT("BrandId");
	TUint32 ris=Server().iSettings->brandId;
    TPckgBuf<TUint32> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End BrandId");
	}


void CMySession::SetInactivityDelayL(const RMessage2& aMessage)
	{
	__LOG_TXT("SetInactDelay");
    TPckgBuf<TInt> pckg(0);
// ANTICRACK...
	__LOG("F1_c:%d", Server().iSettings->fakeRegistration);
	aMessage.ReadL(Server().iSettings->fakeRegistration, pckg);
// ANTICRACK...
//	aMessage.ReadL(0, pckg);
	TInt val = pckg();

	if (val == Server().iSettings->inactivityDelay)
	{
		__LOG_TXT("Err Val");
		aMessage.Complete(KErrSameValue);
		return;
	}
	Server().iSettings->inactivityDelay = val;
	Server().NotifyChange(this, EInactivityDelayChange);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End SetInactDelay");
	}


void CMySession::GetRegCodeL(const RMessage2& aMessage)
{
	__LOG_TXT("GetRegCode");
	if (aMessage.GetDesMaxLength(0) < Server().iSettings->regCode64.Length())
	{
		__LOG_TXT("Err Arg");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.WriteL(0, Server().iSettings->regCode64);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End GetRegCode");
}

/*
void CMySession::GetAuthorizedListL(const RMessage2& aMessage)
	{
	__LOG_TXT("AuthList"));
	TInt buffer_len = aMessage.GetDesMaxLength(0);
	__LOG("buffer_len:%d"), buffer_len);
	CBufFlat* buffer = CBufFlat::NewL(buffer_len); // Deve essere grande quanto il buffer in ingresso...
	CleanupStack::PushL(buffer);
	RBufWriteStream strm(*buffer);
	CleanupClosePushL(strm);

	TInt sentQty=0;
	TInt spaceLeft = buffer_len;
	TInt spaceUsed = 0;
	TInt totRegSim = Server().iSettings->TotRegisteredSim();
	__LOG("totRegSim:%d"), totRegSim);
	while ((iProcessedSim < totRegSim) && (spaceLeft > 0))
	{
		TImsi imsi;
		TBuf<KNAME_LEN+2> name;
		TBuf<KOPER_LEN+2> oper;
		Server().iSettings->GetSimDetailsL(iProcessedSim, imsi, name, oper);
		name.Append(TChar('\t'));
		oper.Append(TChar('\t'));
		__LOG("Sim:%d"), iProcessedSim);
		if (name.Length() + oper.Length() <= spaceLeft)
		{
			if (imsi.Length() > 1)
			{
				__FLOG(imsi);
				__FLOG(name);
				__FLOG(oper);
				strm.WriteL(name);
				strm.WriteL(oper);
				spaceLeft -= name.Length();
				spaceLeft -= oper.Length();
				spaceUsed += name.Length();
				spaceUsed += oper.Length();
				sentQty++;
			}
			iProcessedSim++;
		} else
		{
			__LOG_TXT("Space 0"));
			spaceLeft = 0;
		}
	}
	// Buffer Len 84...
	//
	__LOG("SpaceUsed:%d"), spaceUsed);
	__LOG("SpaceLeft:%d"), spaceLeft);
	__LOG("SizeBef:%d"), buffer->Size());
	buffer->ResizeL( spaceUsed );
	__LOG("SizeAft:%d"), buffer->Size());
	__LOG("ProcessedQty:%d"), iProcessedSim);
	__LOG("SentQty:%d"), sentQty);
	__LOG_TXT("Write Buffer"));
	__FLOG(buffer->Ptr(0));
	aMessage.WriteL(0, buffer->Ptr(0));
	__LOG_TXT("Buffer Written"));

	TPckgBuf<TInt> pck(sentQty);
	aMessage.WriteL(1, pck);
	__LOG_TXT("Qty Written"));

	CleanupStack::PopAndDestroy(); // imsi_strm
	CleanupStack::PopAndDestroy(); // imsi_buf

	if (iProcessedSim == totRegSim)
	{
		__LOG_TXT("End AuthList Completion"));
		iProcessedSim = 0;
		aMessage.Complete(KErrCompletion);
		return;
	}

	__LOG_TXT("End AuthList KErrNone"));
	aMessage.Complete(KErrNone);
	}*/



void CMySession::IsValidImsiL(const RMessage2& aMessage)
	{
	__LOG_TXT("IsValidImsi");
	TImsi imsi;
	Server().iPhone->GetImsi( imsi );
	// Confronta con quelli autorizzati e retituisci True / False
	TBool valid = (Server().iSettings->FindSimPosByImsi(imsi) >= 0);

    TPckgBuf<TBool> p(valid);
    aMessage.WriteL(0, p);
	__LOG_TXT("End IsValidImsi");
	aMessage.Complete(KErrNone);
	}


void CMySession::SendMessageL(const RMessage2& aMessage)
	{
	// Questo si occupa soltanto di creare il file in OUTBOX sara' poi il server a spedirlo...
	__LOG_TXT("SendMessage");

    TPckgBuf<TBool> pckg(0);
	TInt key1 = (Server().iSettings->key >> 24) ^ 0x21; // => 1
	aMessage.ReadL(Server().iSettings->fakeRegistration8, pckg); // Server().iSettings->fakeRegistration8 = 2
	TBool split = pckg();

	TNumber number;
	if (aMessage.GetDesLength(0) > number.MaxLength())
	{
		__LOG_TXT("Err Len");
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(0, number);
    TInt msglen = aMessage.GetDesLength(key1);
	if (msglen <= 0)
	{
		__LOG_TXT("Err Argument");
		aMessage.Complete(KErrArgument);
		return;
	}
	RBuf msg;
    msg.CleanupClosePushL();
    msg.CreateL(msglen);
    aMessage.ReadL(key1, msg);
/*    if (msg.Length() == 0)
        {
        User::Leave(ENonNumericString);
        }*/
	TInt ris=Server().SendMessageL(number, msg, split);

	__LOG("F3_d:%d", Server().iSettings->fakeRegistration3);
// ANTICRACK
	CleanupStack::PopAndDestroy( 1 + Server().iSettings->fakeRegistration3 ); // RBuf +
	//	CleanupStack::PopAndDestroy(); // RBuf
// ANTICRACK

	__LOG_TXT("End SendMessage");
	aMessage.Complete(ris);
	}


void CMySession::GetAuthorizedListL(const RMessage2& aMessage)
	{
	__LOG_TXT("AuthList");
	TInt buffer_len = aMessage.GetDesMaxLength(0);
	__LOG("buffer_len:%d", buffer_len);
	HBufC* buffer = HBufC::NewLC(buffer_len); // Deve essere grande quanto il buffer in ingresso...

	TInt sentQty=0;
	TInt spaceLeft = buffer_len;
	TInt totRegSim = Server().iSettings->TotRegisteredSim();
	__LOG("totRegSim:%d", totRegSim);
	while ((iProcessedSim < totRegSim) && (spaceLeft > 0))
	{
		TImsi imsi;
		TBuf<KNAME_LEN+2> name;
		TBuf<KOPER_LEN+2> oper;
		Server().iSettings->GetSimDetailsL(iProcessedSim, imsi, name, oper);
		name.Append(TChar('\t'));
		oper.Append(TChar('\t'));
		__LOG("Sim:%d", iProcessedSim);
		if (name.Length() + oper.Length() <= spaceLeft)
		{
			if (imsi.Length() > 1)
			{
				__LOG_DES(imsi);
				__LOG_DES(name);
				__LOG_DES(oper);
				buffer->Des().Append(name);
				buffer->Des().Append(oper);
				spaceLeft -= name.Length();
				spaceLeft -= oper.Length();
				sentQty++;
			}
			iProcessedSim++;
		} else
		{
			__LOG_TXT("Space 0");
			spaceLeft = 0;
		}
	}
	__LOG_DES(buffer->Des());
	__LOG_TXT("Write Buffer");
	aMessage.WriteL(0, buffer->Des());
	__LOG_TXT("Buffer Written");
	CleanupStack::PopAndDestroy(buffer);

	TPckgBuf<TInt> pck(sentQty);
	aMessage.WriteL(1, pck);
	__LOG_TXT("Qty Written");

	if (iProcessedSim == totRegSim)
	{
		__LOG_TXT("End AuthList Completion");
		iProcessedSim = 0;
		aMessage.Complete(KErrCompletion);
		return;
	}

	__LOG_TXT("End AuthList KErrNone");
	aMessage.Complete(KErrNone);
	}


TUint CMySession::ClientUID(const RMessagePtr2& aMsg)
{
	RThread ClientThread;
	aMsg.Client(ClientThread);// get client thread
	if(!ClientThread.Handle())// has handle???
	{
		PanicClient(aMsg, EPanicInvalidUID);
		return 0;
	}
	RProcess ClientProcess;
	TInt ris = ClientThread.Process(ClientProcess);// then get the process
	if (ris != KErrNone)
	{
		PanicClient(aMsg, EPanicInvalidUID);
		return 0;
	}
	TUint id=0;

#ifdef __UIQ__
	TUid uid = ClientProcess.Type()[3];
	id = uid.iUid;
#else
	// __SERIES60_3X__
	TSecureId prosID = ClientProcess.SecureId();// and check secure UID
	id = prosID.iId;
#endif
	return id;
}



void CMySession::GetProtectedListL(const RMessage2& aMessage)
	{
	__LOG_TXT("ProtList");
	TInt buffer_len = aMessage.GetDesMaxLength(0);
	HBufC8* buffer = HBufC8::NewLC(buffer_len); // Deve essere grande quanto il buffer in ingresso...


	TInt tot_uid = Server().iSettings->protectedApps->Count();
	TInt sentQty = 0;
	TUint spaceLeft = buffer_len;
	TUint spaceUsed = 0;
	while ((iProcessedUid < tot_uid) && (spaceLeft > 0))
	{
 		TInt32 uid = (*Server().iSettings->protectedApps)[iProcessedUid];
 		__LOG("uid%d=%d", iProcessedUid, uid);

		if (sizeof(uid) <= spaceLeft)
		{
			const TUint8* ptr = (TUint8 *) &uid;
			buffer->Des().Append(ptr, 4);
			spaceUsed += sizeof(uid);
			spaceLeft -= sizeof(uid);
			sentQty++;
			iProcessedUid++;
		} else
		{
			spaceLeft = 0;
		}
	}

	aMessage.WriteL(0, buffer->Des());

	TPckgBuf<TInt> pck(sentQty);
	aMessage.WriteL(1, pck);

	CleanupStack::PopAndDestroy(buffer);

	if (iProcessedUid == tot_uid)
	{
		__LOG_TXT("End ProtList KErrCompl");
		iProcessedUid = 0;
		aMessage.Complete(KErrCompletion);
		return;
	}

	__LOG_TXT("End ProtList KErrNone");
	aMessage.Complete(KErrNone);
	}


void CMySession::IsIridiumL(const RMessage2& aMessage)
	{
	__LOG_TXT("IsIridium");
	TBool ris=Server().iSettings->isIridium;
    TPckgBuf<TBool> p(ris);
    aMessage.WriteL(0, p);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End IsIridium");	
	}


void CMySession::RegisterL(const RMessage2& aMessage)
{
	__LOG_TXT("RegisterL");
	TInt regged = 0;

	TBuf<8> regCode64;
	if (aMessage.GetDesLength(1) > regCode64.MaxLength())
	{
		__LOG_TXT("ErrArgs");
	    TPckgBuf<TInt> p(regged);
	    aMessage.WriteL(0, p);
		aMessage.Complete(KErrArgument);
		return;
	}
	aMessage.ReadL(1, regCode64);

	if (regCode64.Length() == 0)
	{
		TPckgBuf<TInt> p(regged);
		aMessage.WriteL(0, p);
		__LOG_TXT("End RegisterL");
		aMessage.Complete(KErrNone);
		return;
	}

	// AntiCrack
	Server().iSettings->fakeRegistration = Replace(regCode64, 'I', 'l');
	Server().iSettings->fakeRegistration |= Replace(regCode64, 'O', '0');
	__LOG("F1_e:%d", Server().iSettings->fakeRegistration);
	// AntiCrack

	// Salva il vecchio valore del codice...
	TBuf<8> oldCode;
	oldCode.Copy(Server().iSettings->regCode);

	// Converte da Base64...
	CBase64CodecBase* base64 = new (ELeave) CBase64CodecBase();
	CleanupStack::PushL(base64);
	Server().iSettings->regCode.Zero();
	base64->Decode(regCode64, Server().iSettings->regCode);
	CleanupStack::PopAndDestroy();

	// Verifica Registrazione...
	__LOG_TXT("IsValidRegCodeL");
	__LOG_DES(Server().iSettings->regCode);
	regged = Server().iSettings->IsValidRegCodeL();
	if (!regged)
	{
		Server().iSettings->regCode.Copy(oldCode); // ripristina il vecchio codice (null oppure valido...)
	} else
	{
		if (regCode64 != Server().iSettings->regCode64)
		{
			__LOG_TXT("DIFF_64");
		}
		if (oldCode != Server().iSettings->regCode)
		{
			__LOG_TXT("DIFF_BIN");
			Server().iSettings->regCode64 = regCode64;
			Server().NotifyChange(this, ERegistrationChange);
		}
	}
	__LOG("Regged:%d", regged);

    TPckgBuf<TInt> p(regged);
    aMessage.WriteL(0, p);
	__LOG_TXT("End RegisterL");
	aMessage.Complete(KErrNone);
}


void CMySession::UninstallL(const RMessage2& aMessage)
{
	__LOG_TXT("Uninstall");
	Server().NotifyChange(this, EForceShutdown_Uninstall);
	aMessage.Complete(KErrNone);
	__LOG_TXT("End Uninstall");
}


void CMySession::ServiceL(const RMessage2& aMessage)
//
// Handle a client request.
// Leaving is handled by CMyServer::ServiceError() which reports
// the error code to the client
//
	{
	__LOG("ServiceL:%d", aMessage.Function());
	switch (aMessage.Function())
		{
/*	case ENotifyConfigChange:
		if (NotificationPending())
			PanicClient(aMessage, EPanicAlreadyWaiting);
		else
			iNotifyMsg = aMessage;
		return;	// E' asincrona, non bisogna richiamare la RMessage.Complete...
		break;
	case ECancelNotifyConfigChange:
		if (NotificationPending())
			iNotifyMsg.Complete(KErrCancel);
		aMessage.Complete(KErrNone);
		break;*/
	case EIsIridium:
		IsIridiumL(aMessage);
		break;
	case EIsEnabled:
		IsEnabledL(aMessage);
		break;
	case EPassword:
		PasswordL(aMessage);
		break;
	case EBrandId:
		{
		GetBrandIdL(aMessage);
		break;
		}
	case EDestAddress:
		DestAddressL(aMessage);
		break;
	case EMessage:
		MessageL(aMessage);
		break;
	case EGetVersion:
		GetVersionL(aMessage);
		break;		
	case EIsValidImsi:
		IsValidImsiL(aMessage);
		break;
	case ESendMessage:
		SendMessageL(aMessage);
		break;
	case EClearOutBox:
		Server().ClearOutBox();
		aMessage.Complete(KErrNone);
		break;
	case ESetPassword:
		SetPasswordL(aMessage);
		break;
	case EGetImei:
		ImeiL(aMessage);
		break;
	case ESetEnabled:
		SetEnabledL(aMessage);
		break;
	case ESetLocked:
		SetLockedL(aMessage);
		break;
	case EGetLockDelay:
		GetLockDelayL(aMessage);
		break;
	case ESetLockDelay:
		SetLockDelayL(aMessage);
		break;
	case EIsLocked:
		IsLockedL(aMessage);
		break;
	case EGetLockBehaviour:
		GetLockBehaviourL(aMessage);
		break;
	case ESetLockBehaviour:
		SetLockBehaviourL(aMessage);
		break;
	case EGetRegCode:
		GetRegCodeL(aMessage);
		break;
	case ESetDestAddress:
		SetDestAddressL(aMessage);
		break;
	case ESetMessage:
		SetMessageL(aMessage);
		break;
	case ERegisterImsi:
		RegisterImsiL(aMessage);
		break;
	case ESetMonitorParams:
		SetMonitorParamsL(aMessage);
		break;
	case EGetMonitorParams:
		GetMonitorParamsL(aMessage);
		break;
	case ERenameImsi:
		RenameImsiL(aMessage);
		break;
	case EUnRegisterImsi:
		UnRegisterImsiL(aMessage);
		break;
	case EGetImsiList:
		GetAuthorizedListL(aMessage);
		break;
	case EAddProtectedUid:
		AddProtectedUidL(aMessage);
		break;
	case ERemProtectedUid:
		RemProtectedUidL(aMessage);
		break;
	case EGetProtectedList:
		GetProtectedListL(aMessage);
		break;
	case ERegister:
		RegisterL(aMessage);
		break;
	case EGetInactivityDelay:
		GetInactivityDelayL(aMessage);
		break;
	case ESetInactivityDelay:
		SetInactivityDelayL(aMessage);
		break;
	case EUninstall:
		UninstallL(aMessage);
		break;
	case ESetLargeIconsGUI:
		SetLargeIconsGUIL(aMessage);
		break;
	case EIsLargeIconsGUI:
		IsLargeIconsGUIL(aMessage);
		break;
	default:
		__LOG_TXT("!!!PanicClient!!!");
		PanicClient(aMessage, EPanicIllegalFunction);
		// FIXED in 2.0 aMessage.Complete(KErrNone);
		break;
		}
	}


void CMySession::ServiceError(const RMessage2& aMessage, TInt aError)
//
// Handle an error from CMySession::ServiceL()
// A bad descriptor error implies a badly programmed client, so panic it;
// otherwise use the default handling (report the error to the client)
//
	{
	__LOG("!!!ServiceError:%d!!!", aError);
	if (aError==KErrBadDescriptor)
		PanicClient(aMessage,EPanicBadDescriptor);
	CSession2::ServiceError(aMessage, aError);
	}



void PanicClient(const RMessagePtr2& aMessage, TMyPanic aPanic)
//
// RMessage::Panic() also completes the message. This is:
// (a) important for efficient cleanup within the kernel
// (b) a problem if the message is completed a second time
//
	{
	aMessage.Panic(KPanic, aPanic);
	}



