/*
============================================================================
 Name        : Installer.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CInstaller implementation
============================================================================
*/

#include "Installer.h"
#include <MSVAPI.H>
#include <sendas2.h>
#include <TXTRICH.H>
#include <MMsvAttachmentManager.h>
#include <msvids.h>
#include <msvuids.h>
#include <FuzzyByte\logging.h>


#ifdef __UIQ__
	#include <QikSendAs.h>
	TUid KSenduiMtmIrUid = KUidIrMtm;
	TUid KSenduiMtmBtUid = KUidBtMtm;
#else
	// __SERIES60_3X__
	#include <SENDUICONSTS.H>
	#include <sendui.h>
	#include <tsendingcapabilities.h>
	#include <btmsgtypeuid.h>
	#include <irmsgtypeuid.h>
#endif

CInstaller::CInstaller()
{
	// No implementation required
}


CInstaller::~CInstaller()
{
}

CInstaller* CInstaller::NewLC()
{
	CInstaller* self = new (ELeave)CInstaller();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CInstaller* CInstaller::NewL()
{
	CInstaller* self=CInstaller::NewLC();
	CleanupStack::Pop(self); // self;
	return self;
}

void CInstaller::ConstructL()
{

}


void CInstaller::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3){}


TBool CInstaller::Get_BT_IRDA_InboxFileL(TDes& path)
{
	__FLOG_DECLARATION_MEMBER;
	__FLOG_OPEN("guardian", "inst.txt");

	CMsvSession* msvSession = CMsvSession::OpenSyncL(*this);
	CleanupStack::PushL(msvSession);

	CMsvEntryFilter* filter = CMsvEntryFilter::NewL();
	CleanupStack::PushL(filter);
	TMsvSelectionOrdering order(0, EMsvSortByDateReverse);
	filter->SetOrder(order);
	filter->SetType(KUidMsvMessageEntry);
//	filter->SetType(KUidMsvAttachmentEntry);

	CMsvEntrySelection* selection = new (ELeave) CMsvEntrySelection();
	CleanupStack::PushL(selection);

	msvSession->GetChildIdsL(KMsvGlobalInBoxIndexEntryId, *filter, *selection);
	__FLOG_1(_T8("GetChildIdsL:%d"), selection->Count());
	if (selection->Count() <= 0)
	{
		__FLOG(_T8("count<0"));
		CleanupStack::PopAndDestroy(3); // selection, filter, session
		return EFalse;
	}
	CMsvEntry* entry = msvSession->GetEntryL( selection->At(0) );
	CleanupStack::PushL(entry);
	TMsvEntry entryIdx = entry->Entry();



// entryIdx.iMtm != KSenduiMtmPop3Uid &&
// entryIdx.iMtm != KSenduiMtmImap4Uid &&

//	if (entryIdx.iMtm != KUidMsgTypeIrUID &&
//		entryIdx.iMtm != KUidMsgTypeBt)
	if (entryIdx.iMtm != KSenduiMtmIrUid &&
		entryIdx.iMtm != KSenduiMtmBtUid )
	{
		__FLOG(_T8("Bad MTM"));
		CleanupStack::PopAndDestroy(4); // entry, selection, filter, session
		return EFalse;
	}

	TBuf<20> buf;
	buf.AppendNum(entryIdx.iMtm.iUid, EHex);			// OK
	__FLOG(buf);
	__FLOG_1(_T8("Service:%d"), entryIdx.iServiceId);	// OK 4103
	buf.Zero();
	buf.AppendNum(entryIdx.iType.iUid, EHex);
	__FLOG(buf);										// OK 10000F6A
	__FLOG(entryIdx.iDescription);						// NOOOO test.sisx
	__FLOG(entryIdx.iDetails);							// Bluetooth
	__FLOG_1(_T8("Size:%d"), entryIdx.iSize);			// Size...


// *** CMsvEntry Punta al primo messaggio

	CMsvEntrySelection* btChildren = entry->ChildrenL();
	CleanupStack::PushL(btChildren);
	TInt count=btChildren->Count();
	if (count != 1)
	{
		__FLOG_1(_T8("Count:%d"), count);
		CleanupStack::PopAndDestroy(5); // entry, selection, filter, session, btChildren
		return EFalse;
	}


// *** Passa a lavorare sull'entry BT

	TMsvId btAtt = (*btChildren)[0];
	entry->SetEntryL(btAtt); // switch context to CHILD entry

	if (!entry->HasStoreL())
	{
		__FLOG(_T8("NoStore"));
		CleanupStack::PopAndDestroy(5); // entry, selection, filter, session, btChildren
		return EFalse;
	}

	CMsvStore* store = entry->ReadStoreL();
	CleanupStack::PushL(store);

	entryIdx = entry->Entry();
	buf.AppendNum(entryIdx.iMtm.iUid, EHex);			// OK 10009ed5
	__FLOG(buf);
	__FLOG_1(_T8("Service:%d"), entryIdx.iServiceId);	// OK 4103
	buf.Zero();
	buf.AppendNum(entryIdx.iType.iUid, EHex);
	__FLOG(buf);										// 10000F6B
	__FLOG(entryIdx.iDescription);						// x-epoc/x-sisx-app
	__FLOG(entryIdx.iDetails);
	__FLOG_1(_T8("Size:%d"), entryIdx.iSize);

			// get the attachment...

//	__FLOG(_T8("GetAttach"));
	MMsvAttachmentManager &attMngr = store->AttachmentManagerL();
	CMsvAttachment* attInfo = attMngr.GetAttachmentInfoL(0);
	CleanupStack::PushL(attInfo);

	__FLOG_1(_L("infosize:%d"), attInfo->Size());
// Magari rimuoverlo nella final... Tanto c'e' poi il check su UID
/*	_LIT8(KSISX, "x-epoc/x-sisx-app");
	if (attInfo->MimeType().MatchC(KSISX) != 0)
	{
		__FLOG(_T8("Not SISX"));
		CleanupStack::PopAndDestroy(attInfo);
		CleanupStack::PopAndDestroy(store);
		CleanupStack::PopAndDestroy(5); // entry, selection, filter, session, btChildren
		return EFalse;
	}*/

//	TInt size = attInfo->Size();
/*	__FLOG_1(_T8("Size:%d"), size);
	if (size < 300000 || size > 500000)
	{
		CleanupStack::PopAndDestroy(attInfo);
		CleanupStack::PopAndDestroy(store);
		CleanupStack::PopAndDestroy(5); // entry, selection, filter, session, btChildren
		return EFalse;
	}*/
	// Nome del file
	path.Append( attInfo->AttachmentName() );
	__FLOG(path);

	CleanupStack::PopAndDestroy(attInfo);

// get the attachment...
	RBuf8 buf8;
	buf8.CleanupClosePushL();

	RFile file = attMngr.GetAttachmentFileL(0);
	TInt size;
	file.Size(size);
	buf8.Create(size);
	__FLOG_1(_L("filesize:%d"),size);
//	__FLOG(_T8("Read"));
	file.Read(buf8, size);
	file.Close();
	__FLOG(_L("Letto"));

//	__FLOG(_T8("DoReplace"));
//	__FLOG(path);
	RFs fs;
	User::LeaveIfError( fs.Connect() );
	CleanupClosePushL(fs);
	fs.MkDirAll(path);
	__FLOG(_L("Replace"));
	User::LeaveIfError( file.Replace(fs, path, EFileWrite|EFileShareReadersOrWriters) );
	__FLOG(_L("Done"));
//	__FLOG(_T8("Write"));
	file.Write(0, buf8);
	__FLOG(_L("Wrote"));
	file.Close();
	CleanupStack::PopAndDestroy(&fs); // fs
	CleanupStack::PopAndDestroy(&buf8); // Buf8
// get the attachment...

	__FLOG(_L("store"));
	CleanupStack::PopAndDestroy(store);

	__FLOG(_L("Last 5"));
	CleanupStack::PopAndDestroy(5); // entry, selection, filter, session, btChildren

	__FLOG(_L("End"));
	__FLOG_CLOSE;
	return ETrue;
}
