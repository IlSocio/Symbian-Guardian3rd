/*
 ============================================================================
 Name        : Settings.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CSettings implementation
 ============================================================================
 */
#include "Settings.h" 
#include "srverr.h"
#include <FuzzyByte\AES.h>
#include <FuzzyByte\FileUtils.h>

_LIT(KYes, "Yes");
_LIT(KNo, "No");   

_LIT8(KIV,  "\x0:4.00.0000\xFF\xFF\x0\x0\x0");
_LIT8(KKEY, "Guardian\xFFVersion");

CSettings::CSettings(RFs& aFs) : CSettingsFile(aFs)
	{
	// No implementation required
	}

CSettings::~CSettings()
	{
	__LOG_TXT("Destructor");
	if (imsiArray)
		{
		imsiArray->Close();
		delete imsiArray;
		}
	if (imsiNameArray)
		{
		imsiNameArray->Close();
		delete imsiNameArray;
		}
	if (imsiOperArray)
		{
		imsiOperArray->Close();
		delete imsiOperArray;
		}
	if (protectedApps)
		{
		protectedApps->Close();
		delete protectedApps;
		}
	__LOG_TXT("End Destructor");
	}

CSettings* CSettings::NewLC(RFs& aFs)
	{
	CSettings* self = new (ELeave) CSettings(aFs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSettings* CSettings::NewL(RFs& aFs)
	{
	CSettings* self = CSettings::NewLC(aFs);
	CleanupStack::Pop(); // self;
	return self;
	}


HBufC8* CSettings::LoadBytesFromFileL()
	{
	HBufC8* encrData = FileUtils::ReadFileContentsL(iFs, iFileName);
	CleanupStack::PushL(encrData);
	HBufC8* ris = AES::DecryptL(*encrData, KIV, KKEY);
	CleanupStack::PopAndDestroy(encrData);
	return ris;
	}


void CSettings::SaveBytesToFileL(const TDesC8& buffer)
	{
	HBufC8* encrData = AES::EncryptL(buffer, KIV, KKEY);
	CleanupStack::PushL(encrData);	
	FileUtils::DumpToFileL(iFs, iFileName, *encrData, EFalse);
	CleanupStack::PopAndDestroy(encrData);
	}


void CSettings::ConstructL()
	{
	__LOG_OPEN("Guardian", "Settings.txt");
	protectedApps = new (ELeave) RArray<TInt32> ();
	imsiArray = new (ELeave) RArray<TImsi> ();
	imsiNameArray = new (ELeave) RArray<TImsiName> ();
	imsiOperArray = new (ELeave) RArray<TOperName> ();
	RestoreToDefaults();
	}

void CSettings::RestoreToDefaults()
	{
	number.Zero();
	largeIcons = ETrue;
	lockedPhone = EFalse;
	fakeRegistration7 = EFalse;
	fakeRegistration4 = EFalse;
	fakeRegistration8 = inactivityDelay = 60;
	enabled = EFalse;
	fakeRegistration3 = EFalse;
	//		inactivityDelay = 0;	// DA RIMUOVERE CAMBIARE IN RELEASE
	fakeRegistration = ETrue;
	fakeRegistration6 = EFalse;
	uninstall = EFalse;
	fakeRegistration2 = EFalse;
	fakeRegistration5 = ETrue;
	monitorSmsIn = monitorSmsOut = monitorCallIn = monitorCallOut = EFalse;
	Filler5.Zero();
	Filler6.Zero();
	brandId = 0;
	regCode.Zero();
	regCode64.Zero();
	iRegReqCode.Zero();
	Filler19 = Filler20 = fakeRegistration9 = Filler15 = Filler21 = ETrue;
	isIridium = Filler17 = Filler22 = EFalse;
	fakeIridium = 0;
	iLockDelay = 3;
	iLockBehaviour = ENoLock;
	//		imeiOnStore.Zero();
	countFail = Filler12 = 0x5F;
	imsiThief.Zero();
	message.Zero();
	password.Zero();
	protectedApps->Reset();
	imsiArray->Reset();
	imsiNameArray->Reset();
	imsiOperArray->Reset();
	}

/*	TTime CSettings::GetDate()
 {
 TInt64 num=0;
 TLex lex(simChangeDate);
 lex.Val(num);
 TTime time(num);
 return time;
 }


 void CSettings::SetDate(TTime& time)
 {
 TInt64 num = time.Int64();
 simChangeDate.NumUC(num);
 }*/

void CSettings::Ror(TDes& data)
	{
	TInt oldResto = 0;
	for (TInt i = 0; i < data.Length(); i++)
		{
		TInt resto = 0;
		if (data[i] % 2 == 1)
			resto = 0x80;
		data[i] = (TUint16) ((data[i] >> 1) + oldResto);
		oldResto = resto;
		}
	data[0] = (TUint16) (data[0] + oldResto);
	}

// Prende in input 6 bytes e restituisce altri 6 bytes
// Restituisce il RegRequestCode che viene ricavato dalla sorgente
void CSettings::GetRegRequestCodeLC(const TDesC& data, RBuf& buff)
	{
	buff.Close();
	buff.CleanupClosePushL();
	buff.CreateL(data);
	TInt tot = 0;
	for (TInt i = 0; i < data.Length(); i++)
		{
		tot += data[i];
		tot %= 112;
		}
	TUint32 key2 = key & 0xFF;
	//__LOG(("key: %d"), key2);
	//__LOG(("tot: %d"), tot);
	for (TInt j = 0; j < buff.Length(); j++)
		{
		Ror(buff);
		TInt val = (key2 * (j + 1) + tot + brandId) % 256;
		val ^= buff[j];
		buff[j] = (TUint16) val;
		}
	}

// Restituisce il RegRequestCode che viene ricavato dal codice imei
void CSettings::GetRegRequestCodeLC(RBuf& buff)
	{
	TBuf<7> tmp;
	tmp = imeiOnMemory.Right(7);
	tmp.SetLength(6);
	GetRegRequestCodeLC(tmp, buff);
	}

// Restituisce
// 0 Free
// 1 Platinum se il RegCode impostato e' corretto per il codice imei impostato
// 2 Gold se il RegCode impostato e' corretto per il codice imei impostato
// 3 => 1 Iridium
TInt CSettings::IsValidRegCodeL()
	{
	countFail = 0;
	TInt versionFound = 0;
	RBuf requestCode;
	RBuf good;
	for (TInt i = 0; i < 4; i++)
		{
		GetRegRequestCodeLC(requestCode, good);	// push good
	
		if ((good.Length() > 0) && good == regCode)
			{
			// Secondo Ciclo... i=1 Platinum
			CleanupStack::PopAndDestroy(&good);
			CleanupStack::PopAndDestroy(&requestCode);	// ***

			i--;
			isIridium = i/2;
			return (i%2) + 1; // 3 => 1 
			} else
			{
			if (requestCode.Length() == 0)
				{
				// Primo Ciclo... i=0 inizializza requestCode
				CleanupStack::PopAndDestroy(&good);
				GetRegRequestCodeLC(requestCode);		// Verra' rimosso al termine del ciclo ***
				iRegReqCode.Copy(requestCode);
				// Se non viene mai eseguito c'e' qualche errore (ed iRegReqCode sara' vuoto)
				} else
				{
				// Tutti i Cicli successivi...
				// nel caso di Free... i=1 i=2 i=3
				// nel caso di Gold... i=1
				// nel caso di Iridium... i=1 i=2
				requestCode.Copy(good);
				CleanupStack::PopAndDestroy(&good);
				countFail++;
				// Se non viene eseguito c'e' qualche errore, imposta flag CountFail...
				// nel caso di Platinum... 	countFail = 0
				// nel caso di Gold... 		countFail = 1
				// nel caso di Iridium... 	countFail = 2
				// nel caso di Free... 		countFail = 3
				}
			}
		}
	CleanupStack::PopAndDestroy(&requestCode);	// ***
	return 0;

/*	RBuf requestCode;
	RBuf good;
	GetRegRequestCodeLC(requestCode);
	regReqCode.Copy(requestCode);

	// traforma for in while
	for (TInt i = 0; i < 2; i++)
		{
		GetRegRequestCodeLC(requestCode, good);

		// ATTENZIONE... POTREBBERO FARE UN regCode.Copy( good ) per rendere il programma registrato!!!
		// il flag fakeRegistration5 limita in parte
		// NO NON POTREBBERO PERCHE' IL CODICE NECESSARIO e' regCode64!!!

		if (good == regCode) // <--- CRACKED...
			{
			CleanupStack::PopAndDestroy(&good);
			CleanupStack::PopAndDestroy(&requestCode);
			return i + 1;
			}
		requestCode.Copy(good);
		CleanupStack::PopAndDestroy(&good);
		}

	// Check for Iridium...
	for (TInt i = 0; i < 2; i++)
		{
		GetRegRequestCodeLC(requestCode, good);

		isIridium = (good == regCode);
		if (isIridium) // <--- CRACKED...
			{
			// La seconda volta deve passare da qui...
			CleanupStack::PopAndDestroy(&good);
			CleanupStack::PopAndDestroy(&requestCode);
			return i + 1;
			} else
			{
			// La prima volta deve passare da qui... se non ci passa non imposta flag, quindi va in crash...
			}
		requestCode.Copy(good);
		CleanupStack::PopAndDestroy(&good);
		}
	/*		for (TInt i=0; i<regCode.Length(); i++)
	 __FLOG_1(_L("regCode:%d"), regCode[i]);
	 for (TInt i=0; i<good.Length(); i++)
	 __FLOG_1(_L("goodCode:%d"), good[i]);
	 TInt ris = good.Compare(regCode);
	 __FLOG_1(_L("ris:%d"), ris);*/
	//CleanupStack::PopAndDestroy(&requestCode);
	}

TInt CSettings::FindSimPosByName(const TDesC& name) const
	{
	for (TInt i = 0; i < imsiNameArray->Count(); i++)
		{
		if ((*imsiNameArray)[i].MatchC(name) == 0)
			return i;
		}
	return -1;
	}

void CSettings::GetSimDetailsL(const TInt pos, TDes& sim, TDes& name,
		TDes& oper)
	{
	if (pos >= TotRegisteredSim())
		return;
	sim = (*imsiArray)[pos];
	name = (*imsiNameArray)[pos];
	oper = (*imsiOperArray)[pos];
	}

TInt CSettings::FindSimPosByImsi(const TDesC& sim) const
	{
	for (TInt i = 0; i < imsiArray->Count(); i++)
		{
		if ((*imsiArray)[i].MatchC(sim) == 0)
			return i;
		}
	return -1;
	}

TInt CSettings::TotRegisteredSim() const
	{
	return imsiArray->Count();
	}

// TROVA UN NOME APPROPRIATO PER LA SIM...
void CSettings::GetNewSimName(TDes& simName)
	{
	TInt max = 0;
	for (TInt i = 0; i < imsiNameArray->Count(); i++)
		{
		if ((*imsiNameArray)[i].Length() > 4)
			{
			TInt val = 0;
			TLex lex((*imsiNameArray)[i].Mid(4));
			lex.Val(val);
			if (val > max)
				max = val;
			}
		}
	// Cicla finche' non trova un nome libero...
	do
		{
		max++;
		// Controlla che max sia inferiore a 9999 in modo da non far andare il nome della sim oltre i 10 caratteri
		if (max > 9999)
			{
			max = 0;
			}
		simName = _L("SIM-");
		simName.AppendNum(max);
		}
	while (FindSimPosByName(simName) >= 0);
	}

// Restituisce true se c'e' stato un qualche cambiamento nella lista.
// Registra la sim, se esistente la sposta in prima posizione
// Se la lista e' piena elimina l'ultima sim
// Se non e' presente il RegCode allora non consente di registrare altre sim...
TBool CSettings::RegisterSimL(const TDesC& sim, const TDesC& operName,
		TDes& simName)
	{
	__LOG_TXT("RegisterSimL");
	__LOG_DES(sim);
	__LOG_TXT("RegSim_SimList:");
	TInt tot = imsiArray->Count();
	for (TInt i = 0; i < tot; i++)
		{
		TImsi imsi;
		TImsiName name;
		TOperName oper;
		__LOG_DES((*imsiArray)[i]);
		__LOG_DES((*imsiNameArray)[i]);
		__LOG_DES((*imsiOperArray)[i]);
		}
	TOperName oper = operName;
	// Verifica se esiste gia'
	TInt pos = FindSimPosByImsi(sim);

	__LOG("Pos: %d", pos);
	// Anticrack...
	fakeRegistration4 |= (iRegReqCode.Length() == 0);
	__LOG("F4:%d", fakeRegistration4);
	// Anticrack...

	TBool sim_exists = (pos >= 0);

	//TODO: Anticrack...
	if (!IsValidRegCodeL())
		{
		regCode.Zero();
		regCode64.Zero();
		// Se non e' presente il RegCode allora non consente di registrare una sim differente da quella gia' presente...
		if (imsiArray->Count() + imsiNameArray->Count()
				+ imsiOperArray->Count() > 2)
			return EFalse;
		}

	TBool list_changed = EFalse;
	if (sim_exists)
		{
		// Restituisce False... Sim gia' esistente
		// Aggiorna il nome dell'operatore oppure lo preleva
		if (oper.Length() > 0 && oper.MatchC((*imsiOperArray)[pos]) != 0)
			{
			(*imsiOperArray)[pos] = oper;
			list_changed = ETrue;
			}
		else
			{
			oper = (*imsiOperArray)[pos];
			}

		// Preleva il nome della sim
		simName = (*imsiNameArray)[pos];

		// Se la sim esiste ed e' in prima posizione esce
		if (pos == 0)
			return list_changed;

		// Se la sim esiste in un'altra posiz. prima la rimuove
		UnRegisterSim(simName);
		}
	else
		{
		list_changed = ETrue;
		GetNewSimName(simName);
		}

	// Inserimento in testa
	// Nelle versioni Gold e Platinum e' presente il supporto MultiSIM...
	if (regCode.Length() == 0)
		{
		imsiArray->Reset();
		imsiNameArray->Reset();
		imsiOperArray->Reset();
		}

	imsiArray->Insert(sim, 0);
	imsiNameArray->Insert(simName, 0);
	imsiOperArray->Insert(oper, 0);

	return list_changed;
	}

TInt CSettings::RenameSim(const TDesC& oldName, const TDesC& name)
	{
	TInt oldPos = FindSimPosByName(oldName);
	__LOG("RenameSim oldPos:%d", oldPos);
	if (oldPos < 0)
		return KErrSimNotPresent;
	if ((*imsiArray)[oldPos].Length() <= 0)
		return KErrSimNotPresent;
	// Check se il nuovo nome e' uguale al precedente...
	if (name == oldName)
		return KErrSameValue;
	if (name.Length() <= 0 || name.Length() > KNAME_LEN)
		return KErrArgument;
	// Check che il nuovo nome non sia uguale ad un nome gia' esistente
	TInt newPos = FindSimPosByName(name);
	__LOG("RenameSim NewPos:%d", newPos);
	if (newPos >= 0)
		return KErrSimAlreadyExists;
	(*imsiNameArray)[oldPos] = name;
	return KErrNone;
	}

TInt CSettings::UnRegisterSim(const TDesC& simName)
	{
	TInt pos = FindSimPosByName(simName);
	__LOG("UnRegSim:%d", pos);
	if (pos < 0)
		return KErrSimNotPresent;
	TInt totSim = TotRegisteredSim();
	if (totSim == 0)
		return KErrSimNotPresent;
	if (totSim == 1)
		return KErrSimOnlyAvail;
	imsiArray->Remove(pos);
	imsiNameArray->Remove(pos);
	imsiOperArray->Remove(pos);
	return KErrNone;
	}

TInt CSettings::AddProtectedApp(const TInt32 uid)
	{
	CleanupStack::PopAndDestroy(fakeRegistration9); // ANTICRACK
	for (TInt i = 0; i < protectedApps->Count(); i++)
		if ((*protectedApps)[i] == uid)
			return KErrAlreadyExists;
	protectedApps->Append(uid);
	return KErrNone;
	}

TInt CSettings::RemProtectedApp(const TInt32 uid)
	{
	for (TInt i = 0; i < protectedApps->Count(); i++)
		if ((*protectedApps)[i] == uid)
			{
			protectedApps->Remove(i);
			return KErrNone;
			}
	CleanupStack::PopAndDestroy(fakeRegistration9); // ANTICRACK
	return KErrNotFound;
	}

static TUint32 Salt = 0;

HBufC* CSettings::CryptLC(const TDesC& buf) const
	{
	TUint key = (TUint) buf.Length();
	HBufC* ris = HBufC::NewLC(key);
	ris->Des().Copy(buf);
	for (int i = 0; i < ris->Length(); i++)
		{
		TInt j = (i % 6) + 10;
		TUint imei_int = imeiOnMemory.Ptr()[j];
		TUint num = ris->Ptr()[i];
		num = (TUint) (num ^ (key + imei_int + Salt));
		ris->Des()[i] = (TUint16) num;
		}
	Salt++;
	return ris;
	}

void CSettings::ChangeMonitorParams(TBool smsIn, TBool smsOut, TBool callIn, TBool callOut)
	{
	monitorSmsIn = smsIn;
	monitorSmsOut = smsOut;
	monitorCallIn = callIn;
	monitorCallOut = callOut;
	fakeIridium = countFail^2;
	}


/*void CSettings::Crypt(const TDesC& buf, TDes& out) const
 {
 TUint key = (TUint) buf.Length();
 out.Zero();
 TBuf<KMSG_LEN> tmp;
 tmp.Copy(buf);
 for (int i=0; i<tmp.Length(); i++)
 {
 TInt j= (i%6) + 10;
 TUint imei_int = imeiOnMemory.Ptr()[j];
 TUint num = tmp.Ptr()[i];
 num = (TUint) (num ^ (key+imei_int+Salt));
 tmp[i] = (TUint16) num;
 }
 out.Copy(tmp);
 Salt++;
 }*/

void CSettings::CryptAndExtL(RWriteStream& aStream, const TDesC& src) const
	{
	HBufC* out = CryptLC(src);
	aStream << (*out);
	CleanupStack::PopAndDestroy(out);
	}

void CSettings::CryptAndExtL(RWriteStream& aStream, const TBool flag) const
	{
	HBufC* out = NULL;
	if (flag)
		out = CryptLC(KYes);
	else
		out = CryptLC(KNo);
	aStream << (*out);
	CleanupStack::PopAndDestroy(out);
	}

void CSettings::CryptAndExtL(RWriteStream& aStream, const TUint32 flag) const
	{
	TBuf<15> buf;
	buf.AppendNum(flag);
	CryptAndExtL(aStream, buf);
	}

void CSettings::IntAndDeCryptL(RReadStream& aStream, TUint32& out) const
	{
	TBuf<15> buf;
	IntAndDeCryptL(aStream, buf);
	TLex lex(buf);
	lex.Val(out, EDecimal);
	}

void CSettings::IntAndDeCryptL(RReadStream& aStream, TDes& out) const
	{
	/*		TBuf<KMSG_LEN> tmp;
	 tmp.Zero();
	 aStream >> tmp;
	 Crypt(tmp, out);*/
	HBufC* tmp = HBufC::NewLC(aStream, KMSG_LEN * 2);
	HBufC* tmp2 = CryptLC(*tmp);
	out.Copy(*tmp2);
	CleanupStack::PopAndDestroy(2);
	}

void CSettings::IntAndDeCryptL(RReadStream& aStream, TBool& val) const
	{
	HBufC* tmp = HBufC::NewLC(aStream, KMSG_LEN * 2);
	HBufC* tmp2 = CryptLC(*tmp);
	if ((*tmp2) == KYes)
		val = ETrue;
	else
		val = EFalse;
	CleanupStack::PopAndDestroy(2);
	/*		TBuf<KMSG_LEN> tmp;
	 TBuf<KMSG_LEN> tmp2;
	 aStream >> tmp;
	 Crypt(tmp, tmp2);
	 if (out == KYes) 
	 val = ETrue;
	 else 
	 val = EFalse;*/
	}

void CSettings::OLD_Crypt(const TDesC& buf, TDes& out) const
	{
	TUint key = (TUint) buf.Length();
	out.Zero();
	TBuf<KMSG_LEN> tmp;
	tmp.Copy(buf);
	for (int i = 0; i < tmp.Length(); i++)
		{
		TUint num = tmp.Ptr()[i];
		num = (TUint) (num ^ (key + i + 150));
		tmp[i] = (TUint16) num;
		}
	out.Copy(tmp);
	}

void CSettings::OLD_IntAndDeCryptL(RReadStream& aStream, TDes& out) const
	{
	TBuf<KMSG_LEN> tmp;
	tmp.Zero();
	aStream >> tmp;
	OLD_Crypt(tmp, out);
	}

TBool CSettings::OLD_IntAndDeCryptL(RReadStream& aStream) const
	{
	TBuf<KMSG_LEN> tmp;
	TBuf<KMSG_LEN> out;
	aStream >> tmp;
	OLD_Crypt(tmp, out);
	if (out == KYes)
		return ETrue;
	return EFalse;
	}


void CSettings::ExternalizeL(RWriteStream& aStream) const
	{
	// scrive usando imei che proviene dallo store...
	aStream << inactivityDelay;
	aStream << Salt;
	CryptAndExtL(aStream, largeIcons);
	CryptAndExtL(aStream, lockedPhone);
	CryptAndExtL(aStream, fakeRegistration5);
	CryptAndExtL(aStream, uninstall);
	CryptAndExtL(aStream, enabled);
	CryptAndExtL(aStream, fakeRegistration);
	CryptAndExtL(aStream, key);
	CryptAndExtL(aStream, fakeRegistration2);
	CryptAndExtL(aStream, monitorSmsIn);
	CryptAndExtL(aStream, fakeRegistration6);
	CryptAndExtL(aStream, KCRC);
	CryptAndExtL(aStream, countFail);
	CryptAndExtL(aStream, fakeRegistration8);
	CryptAndExtL(aStream, monitorCallOut);
	CryptAndExtL(aStream, iLockDelay);
	CryptAndExtL(aStream, fakeRegistration7);
	CryptAndExtL(aStream, monitorSmsOut);
	CryptAndExtL(aStream, Filler12);
	CryptAndExtL(aStream, fakeRegistration9);
	CryptAndExtL(aStream, iLockBehaviour);
	CryptAndExtL(aStream, Filler15);
	CryptAndExtL(aStream, isIridium);
	CryptAndExtL(aStream, Filler17);
	CryptAndExtL(aStream, fakeIridium);
	CryptAndExtL(aStream, Filler19);
	CryptAndExtL(aStream, Filler20);
	CryptAndExtL(aStream, Filler21);
	CryptAndExtL(aStream, Filler22);
	CryptAndExtL(aStream, fakeRegistration3);
	CryptAndExtL(aStream, monitorCallIn);
	CryptAndExtL(aStream, iRegReqCode);
	CryptAndExtL(aStream, Filler5);
	CryptAndExtL(aStream, Filler6);
	CryptAndExtL(aStream, regCode);
	CryptAndExtL(aStream, fakeRegistration4);
	CryptAndExtL(aStream, regCode64);
	//		IntAndDeCryptL(aStream, imeiOnStore);
	CryptAndExtL(aStream, imsiThief);
	CryptAndExtL(aStream, message);
	CryptAndExtL(aStream, number);
	CryptAndExtL(aStream, password);
	CryptAndExtL(aStream, brandId);

	TInt32 tot = imsiArray->Count();
	aStream << tot;
	for (TInt i = 0; i < tot; i++)
		{
		CryptAndExtL(aStream, (*imsiOperArray)[i]);
		CryptAndExtL(aStream, (*imsiArray)[i]);
		CryptAndExtL(aStream, (*imsiNameArray)[i]);
		}
	tot = protectedApps->Count();
	// Anticrack
	//aStream << tot;
	aStream << (tot + fakeRegistration5);
	// Anticrack
	for (TInt i = 0; i < tot; i++)
		{
		TInt32 uid = (*protectedApps)[i];
		aStream << uid;
		}
	}


void CSettings::InternalizeL(RReadStream& aStream)
	{
	__LOG_TXT("InternalizeL");
	// Deve decifrare usando il codice imei che e' stato rilevato...
	aStream >> inactivityDelay;
	aStream >> Salt;
	IntAndDeCryptL(aStream, largeIcons);
	IntAndDeCryptL(aStream, lockedPhone);
	IntAndDeCryptL(aStream, fakeRegistration5);
	IntAndDeCryptL(aStream, uninstall);
	IntAndDeCryptL(aStream, enabled);
	IntAndDeCryptL(aStream, fakeRegistration);
	IntAndDeCryptL(aStream, key);
	IntAndDeCryptL(aStream, fakeRegistration2);
	IntAndDeCryptL(aStream, monitorSmsIn);
	IntAndDeCryptL(aStream, fakeRegistration6);
	TImei crc;
	__LOG_TXT("CRC");
	IntAndDeCryptL(aStream, crc);
	if (crc != KCRC)
		{
		__LOG_TXT("KErrCorrupt");
		// Per gestire caso di Backup & Restore effettuato tra 2 cell. differenti.
		User::Leave(KErrCorrupt);
		}
	IntAndDeCryptL(aStream, countFail);
	IntAndDeCryptL(aStream, fakeRegistration8);
	IntAndDeCryptL(aStream, monitorCallOut);
	IntAndDeCryptL(aStream, iLockDelay);
	IntAndDeCryptL(aStream, fakeRegistration7);
	IntAndDeCryptL(aStream, monitorSmsOut);
	IntAndDeCryptL(aStream, Filler12);
	IntAndDeCryptL(aStream, fakeRegistration9);
	IntAndDeCryptL(aStream, iLockBehaviour);
	IntAndDeCryptL(aStream, Filler15);
	IntAndDeCryptL(aStream, isIridium);
	IntAndDeCryptL(aStream, Filler17);
	IntAndDeCryptL(aStream, fakeIridium);
	IntAndDeCryptL(aStream, Filler19);
	IntAndDeCryptL(aStream, Filler20);
	IntAndDeCryptL(aStream, Filler21);
	IntAndDeCryptL(aStream, Filler22);
	IntAndDeCryptL(aStream, fakeRegistration3);
	IntAndDeCryptL(aStream, monitorCallIn);
	IntAndDeCryptL(aStream, iRegReqCode);
	IntAndDeCryptL(aStream, Filler5);
	IntAndDeCryptL(aStream, Filler6);
	IntAndDeCryptL(aStream, regCode);
	IntAndDeCryptL(aStream, fakeRegistration4);
	IntAndDeCryptL(aStream, regCode64);
	//		IntAndDeCryptL(aStream, imeiOnStore);
	IntAndDeCryptL(aStream, imsiThief);
	IntAndDeCryptL(aStream, message);
	IntAndDeCryptL(aStream, number);
	IntAndDeCryptL(aStream, password);
	__LOG_TXT("Brand");
	IntAndDeCryptL(aStream, brandId);
	TInt32 tot;
	aStream >> tot;
	imsiArray->Reset();
	imsiOperArray->Reset();
	imsiNameArray->Reset();
	for (TInt i = 0; i < tot; i++)
		{
		TImsiName name;
		TImsi imsi;
		TOperName oper;
		IntAndDeCryptL(aStream, oper);
		IntAndDeCryptL(aStream, imsi);
		IntAndDeCryptL(aStream, name);
		imsiNameArray->Append(name);
		imsiArray->Append(imsi);
		imsiOperArray->Append(oper);
		}
	aStream >> tot;
	protectedApps->Reset();
	for (TInt32 i = 0; i < tot; i++)
		{
		TInt32 uid = 0;
		aStream >> uid;
		protectedApps->Append(uid);
		}
	__LOG_TXT("End InternalizeL");
	}


void CSettings::UpgradeFromOldVersion(RReadStream& aStream, const TDesC& aOldVersion)
	{
	if (aOldVersion == _L("0.3"))
		{
		__LOG_TXT("OLD_ReadFile");
		OLD_ReadFileFormat_03L(aStream);
		
		// Inizializza countFail
		IsValidRegCodeL();
		return;
		}
	if (aOldVersion == _L("0.4"))
		{
		__LOG_TXT("OLD_ReadFile");
		OLD_ReadFileFormat_04L(aStream);
		
		// Inizializza countFail
		IsValidRegCodeL();
		return;
		}	
	}


void CSettings::OLD_ReadFileFormat_03L(RReadStream& aStream)
	{
	__LOG_TXT("OLD_ReadFileFormatL");
	__LOG_TXT("largeIcons");
	largeIcons = OLD_IntAndDeCryptL(aStream);
	__LOG_TXT("Filler1");
	lockedPhone = OLD_IntAndDeCryptL(aStream);
	__LOG_TXT("uninstall");
	uninstall = OLD_IntAndDeCryptL(aStream);
	__LOG_TXT("enabled");
	enabled = OLD_IntAndDeCryptL(aStream);
	__LOG_TXT("fakeReg");
	fakeRegistration = OLD_IntAndDeCryptL(aStream);
	TBuf<KIMEI_LEN> brandIdBuf;
	__LOG_TXT("BrandId");
	OLD_IntAndDeCryptL(aStream, brandIdBuf);
	if (brandIdBuf.Length() > 0)
		{
		TLex lex(brandIdBuf);
		lex.Val(brandId, EDecimal);
		}
	__LOG_TXT("key");
	aStream >> key;
	fakeRegistration2 = OLD_IntAndDeCryptL(aStream);
	fakeRegistration5 = OLD_IntAndDeCryptL(aStream);
	fakeRegistration6 = OLD_IntAndDeCryptL(aStream);
	fakeRegistration4 = OLD_IntAndDeCryptL(aStream);
	fakeRegistration3 = OLD_IntAndDeCryptL(aStream);
	__LOG_TXT("iRegReqCode");
	OLD_IntAndDeCryptL(aStream, iRegReqCode);
	OLD_IntAndDeCryptL(aStream, Filler5);
	OLD_IntAndDeCryptL(aStream, Filler6);
	OLD_IntAndDeCryptL(aStream, regCode);
	OLD_IntAndDeCryptL(aStream, regCode64);
	TImei tmpImei;
	__LOG_TXT("imei");
	OLD_IntAndDeCryptL(aStream, tmpImei);
	OLD_IntAndDeCryptL(aStream, imsiThief);
	OLD_IntAndDeCryptL(aStream, message);
	OLD_IntAndDeCryptL(aStream, number);
	OLD_IntAndDeCryptL(aStream, password);
	__LOG_TXT("delay");
	aStream >> inactivityDelay;
	TInt32 tot;
	aStream >> tot;
	imsiArray->Reset();
	imsiNameArray->Reset();
	imsiOperArray->Reset();
	for (TInt i = 0; i < tot; i++)
		{
		TImsi imsi;
		TImsiName name;
		TOperName oper;
		OLD_IntAndDeCryptL(aStream, imsi);
		OLD_IntAndDeCryptL(aStream, name);
		OLD_IntAndDeCryptL(aStream, oper);
		imsiArray->Append(imsi);
		imsiNameArray->Append(name);
		imsiOperArray->Append(oper);
		}
	__LOG_TXT("tot");
	aStream >> tot;
	protectedApps->Reset();
	for (TInt32 i = 0; i < tot; i++)
		{
		TInt32 uid = 0;
		aStream >> uid;
		protectedApps->Append(uid);
		}
	iLockDelay = 3;
	iLockBehaviour = ENoLock;
	__LOG_TXT("OLD_ReadFileFormatL End");
	}


void CSettings::OLD_ReadFileFormat_04L(RReadStream& aStream)
	{
	// Deve decifrare usando il codice imei che e' stato rilevato...
	aStream >> inactivityDelay;
	aStream >> Salt;
	IntAndDeCryptL(aStream, largeIcons);
	IntAndDeCryptL(aStream, lockedPhone);
	IntAndDeCryptL(aStream, fakeRegistration5);
	IntAndDeCryptL(aStream, uninstall);
	IntAndDeCryptL(aStream, enabled);
	IntAndDeCryptL(aStream, fakeRegistration);
	IntAndDeCryptL(aStream, key);
	IntAndDeCryptL(aStream, fakeRegistration2);
	IntAndDeCryptL(aStream, fakeRegistration6);
	TImei crc;
	__LOG_TXT("CRC");
	IntAndDeCryptL(aStream, crc);
/*	if (crc != KCRC)
		{
		__LOG_TXT("KErrCorrupt");
		// Per gestire caso di Backup & Restore effettuato tra 2 cell. differenti.
		User::Leave(KErrCorrupt);
		}*/
	IntAndDeCryptL(aStream, countFail);
	IntAndDeCryptL(aStream, fakeRegistration8);
	IntAndDeCryptL(aStream, iLockDelay);
	iLockDelay = 3;
	IntAndDeCryptL(aStream, fakeRegistration7);
	IntAndDeCryptL(aStream, Filler12);
	IntAndDeCryptL(aStream, fakeRegistration9);
	IntAndDeCryptL(aStream, iLockBehaviour);
	iLockBehaviour = ENoLock;
	IntAndDeCryptL(aStream, Filler15);
	IntAndDeCryptL(aStream, fakeRegistration3);
	IntAndDeCryptL(aStream, iRegReqCode);
	IntAndDeCryptL(aStream, Filler5);
	IntAndDeCryptL(aStream, Filler6);
	IntAndDeCryptL(aStream, regCode);
	IntAndDeCryptL(aStream, fakeRegistration4);
	IntAndDeCryptL(aStream, regCode64);
	//		IntAndDeCryptL(aStream, imeiOnStore);
	IntAndDeCryptL(aStream, imsiThief);
	IntAndDeCryptL(aStream, message);
	IntAndDeCryptL(aStream, number);
	IntAndDeCryptL(aStream, password);
	__LOG_TXT("Brand");
	IntAndDeCryptL(aStream, brandId);
	TInt32 tot;
	aStream >> tot;
	imsiArray->Reset();
	imsiOperArray->Reset();
	imsiNameArray->Reset();
	for (TInt i = 0; i < tot; i++)
		{
		TImsiName name; 
		TImsi imsi;
		TOperName oper;
		IntAndDeCryptL(aStream, oper);
		IntAndDeCryptL(aStream, imsi);
		IntAndDeCryptL(aStream, name);
		imsiNameArray->Append(name);
		imsiArray->Append(imsi);
		imsiOperArray->Append(oper);
		}
	aStream >> tot;
	protectedApps->Reset();
	for (TInt32 i = 0; i < tot; i++)
		{
		TInt32 uid = 0;
		aStream >> uid;
		protectedApps->Append(uid);
		}	
	}
