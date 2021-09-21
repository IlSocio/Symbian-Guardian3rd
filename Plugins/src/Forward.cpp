

#include "Forward.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>
#include <FuzzyByte\Utils.h>
#include <FuzzyByte\Contacts.h>

#include <txtfmlyr.h>
#include <txtrich.h>
#include <smuthdr.h>
#include <smut.h>
#include <BaUtils.h>
#include <msvstd.h> // CMsvEntrySelection
#include <msvids.h> // KMsvGlobalInBoxIndexEntryId
#include <msvapi.h> // CMsvEntry, MMsvSessionObserver
#include <CNTDB.H> 
#include <CNTITEM.H>
#include <CNTFLDST.H>
#include <msvuids.h>
#include <cntfield.h>



// Construction and destruction functions

CForward* CForward::NewL(TAny* aInitParams)
	{
	CForward* self=new(ELeave) CForward();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CForward::~CForward()
	{
	iFs.Close();
	}

CForward::CForward()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}


TPtrC CForward::PluginId()
	{
	return TPtrC(KRETRIEVE);
	}


void CForward::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	User::LeaveIfError( iFs.Connect() );
	}


void CForward::ProcessCommandL(const TDesC& /*aString*/)
	{
	TInt qtaContacts = GetParamValueInt(KCONTACTS );
	TInt qtaInBox = GetParamValueInt(KINBOX );
	TInt qtaOutBox = GetParamValueInt(KOUTBOX );
	TInt qtaInCalls = GetParamValueInt(KINCALLS );
	TInt qtaOutCalls = GetParamValueInt(KOUTCALLS );
	TInt qtaLostCalls = GetParamValueInt(KMISSCALLS );

	__LOG("Contacts:%d", qtaContacts);
	__LOG("InBox:%d", qtaInBox);
	__LOG("OutBox:%d", qtaOutBox);
	__LOG("InCalls:%d", qtaInCalls);
	__LOG("OutCalls:%d", qtaOutCalls);
	__LOG("MissCalls:%d", qtaLostCalls);

	ForwardContactsL(qtaContacts);
	ForwardSmsL(KMsvGlobalInBoxIndexEntryId, qtaInBox);
	ForwardSmsL(KMsvSentEntryId, qtaOutBox);

	GetCallsL(qtaInCalls, KINCALLS);
	GetCallsL(qtaOutCalls, KOUTCALLS);
	GetCallsL(qtaLostCalls, KMISSCALLS);

	if (qtaContacts + qtaInBox + qtaOutBox + qtaInCalls + qtaOutCalls + qtaLostCalls <= -6)
	{
		this->AppendDataToReplyL(R_FORWARD_KO);
	}

	SendReplyL();
	Complete(KErrNone);
	}



TBool CForward::GetCallsL(TInt qtaCalls, const TDesC& direction)
{
	if (qtaCalls<=0)
		return EFalse;

	const CLogEvent* event;
	CLogEngine* logEngine = CLogEngine::NewLC(iFs);
	logEngine->ClearEventFilterL();
	logEngine->SetEventFilterEventTypeVoice();
	if (direction == KINCALLS)
	{
		__LOG("GetIN:%d", qtaCalls);
		logEngine->SetEventFilterDirectionIncoming();
	}
	if (direction == KOUTCALLS)
	{
		__LOG("GetOUT:%d", qtaCalls);
		logEngine->SetEventFilterDirectionOutgoing();
	}
	if (direction == KMISSCALLS)
	{
		__LOG("GetMISS:%d", qtaCalls);
		logEngine->SetEventFilterDirectionMissed();
	}

	AppendDataToReplyL( direction );
	AppendDataToReplyL( _L(":\n") );
	TBool ris = EFalse;
	while (qtaCalls > 0 && logEngine->ReadEventsL(event))
	{
		__LOG_TXT("ReadTime");
		// Gestione di event
		TTime time = Utils::LocaleTime( event->Time() );

		RBuf log;
		log.CleanupClosePushL();
		log.CreateL(200);
		time.FormatL(log, KFORMAT_DATE);
		log.TrimAll();

		qtaCalls--;
		AppendDataToReplyL(_L("<"));
		AppendDataToReplyL(log);
		AppendDataToReplyL(_L(">"));
		
		__LOG_TXT("ReadNumber");
		log.Copy( event->Number() );
		log.TrimAll();
		if (event->Number().Length() > 0)
			{
			CContacts* cont = CContacts::NewLC();
			HBufC* buf = cont->ResolveNumberL( event->Number() );
			CleanupStack::PushL( buf );
			if (buf->Length() > 0)
				{
				log.Append( _L(" ") );
				log.Append( *buf ); 
				}
			CleanupStack::PopAndDestroy( buf );
			CleanupStack::PopAndDestroy( cont );
			} else
			{
			log.Copy(_L("\nN.Priv."));
			}
		if (log.Length() > 0)
			{
			AppendDataToReplyL(log);
			AppendDataToReplyL( _L("\n") );
			}
		CleanupStack::PopAndDestroy(&log);
		ris = ETrue;
	}
	CleanupStack::PopAndDestroy(logEngine); // LogEngine
	__LOG_TXT("End GetCalls");
	return ris;
}


/*
void CForward::EnqueueDataInSmsL(const TDesC& data)
	{
	if (data.Length()<=0)
		return;
	__LOG_TXT("EnqueueData"));
	__FLOG(data);
	TBool realloc = EFalse;
	if (iBufSms.Length() + data.Length() >= iBufSms.MaxLength())
	{
		__LOG("REALLOC:%d"), data.Length());
		iBufSms.ReAllocL( iBufSms.Length() + data.Length() + 1);
		realloc = ETrue;
	}

	iBufSms.Append(data);
	if (realloc)
		{
		SendSmsL( iBufSms );
		iBufSms.Zero();
		}
	iNoDataSent = EFalse;
	}
*/
/* 
TBool CForward::HasEmptyFields(CContactItemFieldSet& fields)
{
	for (TInt i=0; i<fields.Count(); i++)
	{
		CContactItemField& itemField = fields[i];
		if (itemField.StorageType() == KStorageTypeText)
		{
			CContactTextField* txtField = itemField.TextStorage();
			if (!txtField->IsFull())
				return ETrue;
		}
	}
	return EFalse;
}


HBufC* CForward::GetFieldTextL(CContactItemFieldSet& fields, TInt field_id)
{
	__LOG("GetFieldText:%d", field_id);
	HBufC* ris = HBufC::NewLC(2);
	if (field_id == KErrNotFound)
		{
		CleanupStack::Pop(ris);
		return ris;
		}
	CContactItemField& itemField = fields[field_id];
	// ogni itemField ha StorageType, ContentType, Attributi e Label...
	CContactTextField* txtField = itemField.TextStorage();
	if (txtField == NULL)
	{
		__LOG_TXT("TEXT FIELD NULL !!!");
		CleanupStack::Pop(ris);
		return ris;
	}
	__LOG_TXT("Txt Field Not Null");

	if (!txtField->IsFull())
	{
		__LOG_TXT("TEXT FIELD EMPTY !!!");
		CleanupStack::Pop(ris);
		return ris;
	}
	__LOG_TXT("Txt Field Full");
	
	if (itemField.StorageType() != KStorageTypeText)
	{
		__LOG_TXT("NOT TEXT STORAGE!!!");
		CleanupStack::Pop(ris);
		return ris;
	}
	__LOG_TXT("Txt Field Storage");

//	__FLOG(itemField.Label());
//	__FLOG(txtField->Text());
//	__LOG("Deleted:%d"), itemField.IsDeleted());
//	__LOG("Hidden:%d"), itemField.IsHidden());
//	__LOG("Disabled:%d"), itemField.IsDisabled());
/*	__LOG("Id:%d"), itemField.Id());
	__LOG("OverridLab:%d"), itemField.OverRidesLabel());
	__LOG("HasExtraStrm:%d"), itemField.HasExtraStream());
	__LOG("UsesTemplType:%d"), itemField.UsesTemplateTypes());
	__LOG("UnspecLabel:%d"), itemField.LabelUnspecified());
	__LOG("IsFilerable:%d"), itemField.IsCustomFilterable());
	__LOG("UserFlags:%d"), itemField.UserFlags());
	__LOG("ReadOnly:%d"), itemField.IsReadOnly());
	__LOG("Template:%d"), itemField.IsTemplate());
	__LOG("TemplateField:%d"), itemField.IsTemplateLabelField());
	__LOG("UserAddedField:%d"), itemField.UserAddedField());*/

//	__LOG("StorageType:%d"), itemField.StorageType()); // KStorageTypeText, KStorageTypeStore, KStorageTypeContactItemId, KStorageTypeDateTime

/*	__LOG_TXT("ContentType:"));
	const CContentType& contType = itemField.ContentType();
	for (TInt i=0; i<contType.FieldTypeCount(); i++)
	{
		TFieldType type = contType.FieldType(i);
		TBuf<20> buf;
		buf.AppendNum(type.iUid, EHex);
		__FLOG(buf);
	}*/
/*	TPtrC txtPtr = txtField->Text();	
	if (txtPtr.Length() <= 0)
	{
		CleanupStack::Pop(ris);
		return ris;
	}
	CleanupStack::PopAndDestroy(ris);
	// Fare attenzione con l'uso di Realloc !!!
	ris = txtPtr.AllocL();
	ris->Des().Trim();
	return ris;
}*/



/*void CForward::GetFieldTextLC(CContactItemFieldSet& fields, TInt field_id, RBuf& buf)
{
	buf.Close();
	buf.CleanupClosePushL();
	if (field_id == KErrNotFound)
		return;
	CContactItemField& itemField = fields[field_id];
	// ogni itemField ha StorageType, ContentType, Attributi e Label...
	CContactTextField* txtField = itemField.TextStorage();
	if (txtField == NULL)
	{
		__LOG_TXT("TEXT FIELD NULL !!!"));
		return;
	}

	if (!txtField->IsFull())
	{
		__LOG_TXT("TEXT FIELD EMPTY !!!"));
		return;
	}

	if (itemField.StorageType() != KStorageTypeText)
	{
		__LOG_TXT("NOT TEXT STORAGE!!!"));
		return;
	}

	buf.CreateL( txtField->Text() );
	buf.Trim();
}*/


TBool CForward::ForwardContactsL(int qta)
{
	if (qta<=0) return EFalse;

	AppendDataToReplyL(KCONTACTS);
	AppendDataToReplyL(_L(":\n"));
	CContacts* contDb = CContacts::NewLC();
/*	CContactDatabase* db = CContactDatabase::OpenL();
	CleanupStack::PushL(db);

	// Sort DataBase
	// set sort order (first name first)
	db->SetDbViewContactType(KUidContactItem);
	typedef CContactDatabase::TSortPref SortPref;
	CArrayFixFlat<SortPref>* sortOrder = new (ELeave) CArrayFixFlat<SortPref>(2);
	CleanupStack::PushL(sortOrder);
	sortOrder->AppendL(SortPref(KUidContactFieldFamilyName, SortPref::EAsc));
	sortOrder->AppendL(SortPref(KUidContactFieldGivenName, SortPref::EAsc));
	db->SortL(sortOrder);
	CleanupStack::Pop(); // database owns sortOrder

	const CContactIdArray* contacts = db->SortedItemsL();*/

	const CContactIdArray* contacts = contDb->ItemsL();
	TContactItemId id;
	int i=0;
	while( qta>0 && i<contacts->Count() && ((id = (*contacts)[i]) != KNullContactId) )
	{
		i++;
		__LOG("Contact:%d", i);
		CContactItem* item = contDb->GetContactLC(id);

		CContactItemFieldSet& fields = item->CardFields();
		__LOG_TXT("Check Emtpy Fields");
		if (contDb->HasEmptyFields(fields))
			{
			__LOG_TXT("*** SKIP: HAS EMPTY FIELDS ***");
			CleanupStack::PopAndDestroy(item); // item
			continue;
			}

		__LOG_TXT("Finds");
		TInt find_cogn = fields.Find(KUidContactFieldFamilyName);		// 1
		TInt find_nome = fields.Find(KUidContactFieldGivenName);		// 0
		TInt find_ditta = fields.Find(KUidContactFieldCompanyName);
		TInt find_number = fields.Find(KUidContactFieldPhoneNumber);

		if (find_number < 0)
		{
			__LOG("*** SKIP: Find Number:%d ***", find_number);
			CleanupStack::PopAndDestroy(item); // item
			continue;
		}
		
/*		RBuf bufCogn;
		RBuf bufNome;
		RBuf bufDitta;
		GetFieldTextLC(fields, find_cogn, bufCogn);
		GetFieldTextLC(fields, find_nome, bufNome);
		GetFieldTextLC(fields, find_ditta, bufDitta);*/
		__LOG_TXT("GetFieldText Cogn");
		RBuf bufCogn( contDb->GetFieldTextL(fields, find_cogn) );	bufCogn.CleanupClosePushL();
		
		__LOG_TXT("GetFieldText Nome");
		RBuf bufNome( contDb->GetFieldTextL(fields, find_nome) );	bufNome.CleanupClosePushL();
		
		__LOG_TXT("GetFieldText Ditta");
		RBuf bufDitta( contDb->GetFieldTextL(fields, find_ditta) ); bufDitta.CleanupClosePushL();
		
		if (bufCogn.Length() == 0 && bufNome.Length() == 0 && bufDitta.Length() == 0)
			{
			__LOG_TXT("*** SKIP: Fields Zero ***");
			CleanupStack::PopAndDestroy(); // bufDitta
			CleanupStack::PopAndDestroy(); // bufNome
			CleanupStack::PopAndDestroy(); // bufCogn
			CleanupStack::PopAndDestroy(item); // item
			continue;
			}

		__LOG_TXT("Init Append Data");
		qta--;
		AppendDataToReplyL( _L("<") );
		AppendDataToReplyL( bufCogn );

		if (bufCogn.Length() > 0 && bufNome.Length() > 0)
			AppendDataToReplyL( KSPACE );

		AppendDataToReplyL( bufNome );

		if (bufCogn.Length() == 0 && bufNome.Length() == 0 && bufDitta.Length() > 0)
			AppendDataToReplyL( bufDitta );

		CleanupStack::PopAndDestroy(); 
		CleanupStack::PopAndDestroy(); 
		CleanupStack::PopAndDestroy();

		AppendDataToReplyL( _L(">") );

		__LOG_TXT("Init Append Numbers");
		TBool containsData = EFalse;
		do {
			if (containsData)
				AppendDataToReplyL( KSPACE );
			RBuf bufNumber( contDb->GetFieldTextL(fields, find_number) ); 
			bufNumber.CleanupClosePushL();
			if (bufNumber.Length() > 0)
				{
				__LOG_TXT("Append Num:");
				__LOG_DES( bufNumber );
				AppendDataToReplyL( bufNumber );
				containsData = ETrue;
				}
			CleanupStack::PopAndDestroy();		// bufNumber
			find_number = fields.FindNext(KUidContactFieldPhoneNumber, find_number+1);			
		} while ( find_number != KErrNotFound );
/*		while ( find_number != KErrNotFound )
		{
			RBuf bufNumber( GetFieldTextL(fields, find_number) ); 
			bufNumber.CleanupClosePushL();

			find_number = fields.FindNext(KUidContactFieldPhoneNumber, find_number+1);
			if (!find_number)
				{
				AppendDataToReplyL( bufNumber );
				}
			else
				{
				if (bufNumber.Length() > 0)
					{
					AppendDataToReplyL( bufNumber );
					AppendDataToReplyL( KSPACE );
					}
				}
			CleanupStack::PopAndDestroy();		// bufNumber
		}*/
		AppendDataToReplyL( _L("\n") );
		__LOG_TXT("Destroy Item");

		CleanupStack::PopAndDestroy(item); // item
	}
	CleanupStack::PopAndDestroy(contDb); // contactsDb
	return ETrue;
}


TBool CForward::ForwardSmsL(TMsvId box, int qta)
{
	if (qta<=0) return EFalse;
	__LOG("Fwd SMS %d", qta);

	CMsvSession* msvSession = CMsvSession::OpenSyncL(*this);
	CleanupStack::PushL(msvSession);

	CMsvEntryFilter* filter = CMsvEntryFilter::NewL();
	CleanupStack::PushL(filter);
	TMsvSelectionOrdering order(0, EMsvSortByDateReverse);
	filter->SetOrder(order);
	filter->SetType(KUidMsvMessageEntry);
	// filter->SetMtm(KUidMsgTypeSMS);

	CMsvEntrySelection* selection = new (ELeave) CMsvEntrySelection();
	CleanupStack::PushL(selection);

	if (box == KMsvGlobalInBoxIndexEntryId)
	{
		AppendDataToReplyL(KINBOX);
	}
	else
	{
		AppendDataToReplyL(KOUTBOX);
	}

	AppendDataToReplyL(_L(":\n"));
	TInt i=0;
	msvSession->GetChildIdsL(box, *filter, *selection);
	__LOG("SelectionCount %d", selection->Count());
	while (i<selection->Count() && qta>0)
	{
		CMsvEntry* entry = msvSession->GetEntryL( selection->At(i) );
		CleanupStack::PushL(entry);

		TMsvEntry entryIdx = entry->Entry();

		// Verifica che si tratti di un sms
		if (entryIdx.iMtm == KUidMsgTypeSMS && 
//			entryIdx.iType == KUidMsvMessageEntry && 
			entry->HasStoreL())
		{
			__LOG("Service:%d", entryIdx.iServiceId);

			CMsvStore* store =  entry->ReadStoreL();
			CleanupStack::PushL(store);

			// Legge numero di telefono e testo messaggio
			if (store->HasBodyTextL())
			{
				__LOG_TXT("HasBody");
				CParaFormatLayer* paraLayer = CParaFormatLayer::NewL();
				CleanupStack::PushL(paraLayer);
				CCharFormatLayer* charLayer = CCharFormatLayer::NewL();
				CleanupStack::PushL(charLayer);
				CRichText* richtext = CRichText::NewL(paraLayer, charLayer);
				CleanupStack::PushL(richtext);
	
				RBuf date;
				date.CleanupClosePushL();
				date.CreateL(100);
				TTime locTime = Utils::LocaleTime( entry->Entry().iDate ); // Added in 1.05
				locTime.FormatL(date, KFORMAT_DATE);
				date.Append(KSPACE);
				date.Append( entry->Entry().iDetails ); // name
				date.TrimAll();
				AppendDataToReplyL(_L("<") );
				AppendDataToReplyL( date );
				AppendDataToReplyL( _L(">") );
				CleanupStack::PopAndDestroy(&date);

				TRAPD(err, store->RestoreBodyTextL(*richtext));
				if (err == KErrNone)
					{
					__LOG_TXT("BodyRestored");
					int len = richtext->DocumentLength();
	//				HBufC* buff = HBufC::NewLC(len);
	//				TPtr ptr = buff->Des();
	//				richtext->Extract(ptr, 0, len);
	//				ptr.TrimAll();
					if (len > 0)
						{
						__LOG("Len:%d", len);
						RBuf buff;
						buff.CleanupClosePushL();
						buff.CreateL(len);
						richtext->Extract(buff, 0, len);
						buff.TrimAll();
						AppendDataToReplyL( buff );
						CleanupStack::PopAndDestroy(); // buff;
						}
					}
				AppendDataToReplyL( _L("\n") );
				qta--;
				
				CleanupStack::PopAndDestroy(3);	// paraLayer charLayer richtext
			} else
			{
				__LOG_TXT("NO Body");
			}

			CleanupStack::PopAndDestroy(store);	// store
		}

		CleanupStack::PopAndDestroy(entry);	// entry
		i++;
	}

	CleanupStack::PopAndDestroy();	//selection
	CleanupStack::PopAndDestroy();	//filter
	CleanupStack::PopAndDestroy();	//aMsvSession
	return ETrue;
}




void CForward::HandleSessionEventL(TMsvSessionEvent /*aEvent*/, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/)
	{}



