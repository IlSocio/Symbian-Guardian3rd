// MMRETRIEVE.H
//
// Copyright (c) 2000-2004 Symbian Software Ltd.  All rights reserved.
//

/** @file mmretrieve.h
Multimode ETel API v1.0

Header file for asynchronous list retrieval classes
*/

#ifndef _MMRETRIEVE_H_
#define _MMRETRIEVE_H_

#include <etelmm.h>
#include <mmlist.h>

#include <e32base.h>



class CAsyncRetrieveVariableLengthBuffer : public CActive
/**
Base class for generic actions in retrieving a variable length buffer in two phases.

@publishedPartner
@released
*/
	{
protected:

	//
	// Start the retrieval
	//

	IMPORT_C void Start(TRequestStatus& aReqStatus, TDes8* aPhase1Request, TDes8* aPhase2Request);
	CAsyncRetrieveVariableLengthBuffer();
	virtual ~CAsyncRetrieveVariableLengthBuffer();

	IMPORT_C TBool CompleteIfInUse(TRequestStatus& aReqStatus);
	IMPORT_C void FreeBuffer();

private:
	virtual void RestoreListL();
	virtual void Get(TInt aIpc, TRequestStatus& aReqStatus, TDes8& aDes1, TDes8& aDes2) = 0;
	virtual void CancelReq(TInt aIpc1,TInt aIpc2) = 0;

	IMPORT_C virtual void DoCancel();
	IMPORT_C virtual void RunL();

	void StartPhase2L();

protected:
	enum {
		EIdle,
		ERetrievePhase1,
		ERetrievePhase2
		} iState;

	CBufBase* iResultsBuf;
	TPtr8 iResultsPtr;
	TInt iIpcPhase1;
	TInt iIpcPhase2;
	TInt iIpcCancel;
private:
	TRequestStatus* iUserStatus;
	TDes8* iPhase1RequestData;
	TDes8* iPhase2RequestData;
	TPckgBuf<TInt> iBufferSize;
	};



class CAsyncRetrieveWithClientIds : public CAsyncRetrieveVariableLengthBuffer
/**
Base class that adds passing of client ID within each phase of the retrieval.

This class is not intended for public use.

@publishedPartner
@released
*/
	{
protected:
	CAsyncRetrieveWithClientIds(TInt aSessionHandle, TInt aSubSessionHandle);
protected:
	TPckgBuf<RMobilePhone::TClientId> iId;
	};



class CAsyncRetrieveStoreList : public CAsyncRetrieveWithClientIds
/**
Class that specialises in retrieving lists from phone store classes.

@publishedPartner
@released
*/
	{
public:
	CAsyncRetrieveStoreList(RMobilePhoneStore& aStore);
	~CAsyncRetrieveStoreList();
	virtual void Get(TInt aIpc, TRequestStatus& aReqStatus, TDes8& aDes1, TDes8& aDes2);
	virtual void CancelReq(TInt aIpc1, TInt aIpc2);

	/** Starts the 2 phase retrieval.
	
	@param aReqStatus On return, KErrNone if successful. */
	IMPORT_C void Start(TRequestStatus& aReqStatus);

protected:
	RMobilePhoneStore& iStore;
	};



class CAsyncRetrievePhoneList : public CAsyncRetrieveWithClientIds
/**
Class that specialises in retrieving lists from a phone or network

@publishedPartner
@released
*/
	{
public:
	IMPORT_C CAsyncRetrievePhoneList(RMobilePhone& aPhone);
	IMPORT_C ~CAsyncRetrievePhoneList();
	IMPORT_C virtual void Get(TInt aIpc, TRequestStatus& aReqStatus, TDes8& aDes1, TDes8& aDes2);
	IMPORT_C virtual void CancelReq(TInt aIpc1, TInt aIpc2);

protected:
	RMobilePhone& iPhone;
	};



class CRetrieveMobilePhoneDetectedNetworks : public CAsyncRetrievePhoneList
/**
Retrieves a list of all networks that are currently detected by 
the phone. 

Each detected network will be represented by an entry in the list 
class CMobilePhoneNetworkList or CMobilePhoneNetworkListV2 depending on which 
API method is used. 

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object.

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneDetectedNetworks* NewL(RMobilePhone& aPhone);
	IMPORT_C ~CRetrieveMobilePhoneDetectedNetworks();

	IMPORT_C void Start(TRequestStatus& aReqStatus);
	IMPORT_C void StartV2(TRequestStatus& aReqStatus);

	IMPORT_C CMobilePhoneNetworkList* RetrieveListL();
	IMPORT_C CMobilePhoneNetworkListV2* RetrieveListV2L();

protected:
	CRetrieveMobilePhoneDetectedNetworks(RMobilePhone& aPhone);
	void ConstructL();

	virtual void RestoreListL();

private:
	CMobilePhoneNetworkList* iResults;
	CMobilePhoneNetworkListV2* iResultsV2;
	TInt iListExtensionId;
	};



class CRetrieveMobilePhoneCFList : public CAsyncRetrievePhoneList
/** Retrieves the Call Forwarding status list from the phone.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object.

@publishedPartner
@released 
*/
	{
public:

	// for use by client-side API code and TSY only

	struct TGetCallForwardingRequest
		{
		RMobilePhone::TClientId iClient;
		RMobilePhone::TMobilePhoneCFCondition iCondition;
		RMobilePhone::TMobileInfoLocation iLocation;
		RMobilePhone::TMobileService iServiceGroup;
		};

public:
	IMPORT_C static CRetrieveMobilePhoneCFList* NewL(RMobilePhone& aPhone);
	IMPORT_C ~CRetrieveMobilePhoneCFList();

	IMPORT_C void Start(TRequestStatus& aReqStatus, 
						RMobilePhone::TMobilePhoneCFCondition aCondition, 
						RMobilePhone::TMobileInfoLocation aLocation = RMobilePhone::EInfoLocationCachePreferred); /** @deprecated 7.0s.  Deprecated use other overload*/
	
	IMPORT_C void Start(TRequestStatus& aReqStatus, 
						RMobilePhone::TMobilePhoneCFCondition aCondition, 
						RMobilePhone::TMobileService aServiceGroup,
						RMobilePhone::TMobileInfoLocation aLocation = RMobilePhone::EInfoLocationCachePreferred
						);

	IMPORT_C CMobilePhoneCFList* RetrieveListL();

protected:
	CRetrieveMobilePhoneCFList(RMobilePhone& aPhone);
	void ConstructL();

	virtual void RestoreListL();

private:
	CMobilePhoneCFList* iResults;
	TPckgBuf<TGetCallForwardingRequest> iCFRequestData;
	};




class CRetrieveMobilePhoneCBList : public CAsyncRetrievePhoneList
/** Retrieves the Call Barring status list from the phone.

The following are all described as applicable to both GSM and CDMA because 
although it is not possible to interrogate CDMA networks for call barring 
service status there is nothing inherently "GSM" about these types. So if 
the phone has attempted to internally support Call Barring in CDMA mode then 
these types are applicable.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use this object. 
@publishedPartner
@released
*/
	{
public:

	// for use by client-side API code and TSY only

	struct TGetCallBarringRequest
		{
		RMobilePhone::TClientId iClient;
		RMobilePhone::TMobilePhoneCBCondition iCondition;
		RMobilePhone::TMobileInfoLocation iLocation;
		};


public:
	IMPORT_C static CRetrieveMobilePhoneCBList* NewL(RMobilePhone& aPhone);
	IMPORT_C ~CRetrieveMobilePhoneCBList();

	IMPORT_C void Start(TRequestStatus& aReqStatus, 
						RMobilePhone::TMobilePhoneCBCondition aCondition, 
						RMobilePhone::TMobileInfoLocation aLocation = RMobilePhone::EInfoLocationCachePreferred);
						
	IMPORT_C CMobilePhoneCBList* RetrieveListL();

protected:
	CRetrieveMobilePhoneCBList(RMobilePhone& aPhone);
	void ConstructL();

	virtual void RestoreListL();

private:
	CMobilePhoneCBList* iResults;
	TPckgBuf<TGetCallBarringRequest> iCBRequestData;
	TInt iListExtensionId;
	};




class CRetrieveMobilePhoneCWList : public CAsyncRetrievePhoneList
/**
Retrieves the Call Waiting status list from the phone.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use this object.

@publishedPartner
@released
*/
	{
public:

	// for use by client-side API code and TSY only

	struct TGetCallWaitingRequest
		{
		RMobilePhone::TClientId iClient;
		RMobilePhone::TMobileInfoLocation iLocation;
		};

public:
	IMPORT_C static CRetrieveMobilePhoneCWList* NewL(RMobilePhone& aPhone);
	IMPORT_C ~CRetrieveMobilePhoneCWList();

	IMPORT_C void Start(TRequestStatus& aReqStatus,RMobilePhone::TMobileInfoLocation aLocation = RMobilePhone::EInfoLocationCachePreferred);

	IMPORT_C CMobilePhoneCWList* RetrieveListL();

protected:
	CRetrieveMobilePhoneCWList(RMobilePhone& aPhone);
	void ConstructL();

	virtual void RestoreListL();

private:
	CMobilePhoneCWList* iResults;
	TPckgBuf<TGetCallWaitingRequest> iCWRequestData;
	};



class CRetrieveMobilePhoneCcbsList : public CAsyncRetrievePhoneList
/** Retrieve a list of all active CCBS requests from the phone.

Each CCBS request will be represented by an entry in CMobilePhoneCcbsList. 
The client is able to use the member functions of this class to enumerate 
and read the CCBS request entries.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of CRetrieveMobilePhoneCcbsList.

@publishedPartner
@released 
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneCcbsList* NewL(RMobilePhone& aPhone);
	IMPORT_C ~CRetrieveMobilePhoneCcbsList();

	IMPORT_C void Start(TRequestStatus& aReqStatus);

	IMPORT_C CMobilePhoneCcbsList* RetrieveListL();

protected:
	CRetrieveMobilePhoneCcbsList(RMobilePhone& aPhone);
	void ConstructL();

	virtual void RestoreListL();

private:
	CMobilePhoneCcbsList* iResults;
	};



class CRetrieveMobilePhoneSmsList : public CAsyncRetrieveStoreList
/** Reads stored, fixed length SMS message list from the phone or SIM message store

Instead of reading each message individually, a client may be able to retrieve 
multiple messages currently stored in one go. This functionality will be available 
if the TSY supports reading all SMS. The SMS storage capabilities are returned 
within the iCaps field of RMobilePhoneStore::TMobilePhoneStoreInfoV1 and this 
will inform a client what type(s) of storage access the TSY supports. These 
capabilities will also indicate whether the SMS store contains GSM/WCDMA or 
CDMA SMS messages. When all SMS entries in a store are read in one go, a list 
(CMobilePhoneGsmSmsList or CMobilePhoneCdmaSmsList) object will be returned 
to the client. This object will contain the message entries and the client 
is able to use the function members of the list class to enumerate and read 
the message entries. 

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object. 

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneSmsList* NewL(RMobilePhoneStore& aStore, RMobileSmsStore::TMobileSmsEntryExtensionId aType);
	IMPORT_C ~CRetrieveMobilePhoneSmsList();

	enum
		{
		KValueNotUsed = -1
		};

	struct TBatchRequestData
		{
		RMobilePhone::TClientId iClient;
		RMobileSmsStore::TMobileSmsEntryExtensionId iEntryType;
		TBool iBatchRequest;
		TInt iStartIndex;
		TInt iBatchSize;
		};
		
	IMPORT_C void Start(TRequestStatus& aReqStatus);
	IMPORT_C void StartBatch(TRequestStatus& aReqStatus, TInt aStartIndex, TInt aBatchSize);

	IMPORT_C CMobilePhoneGsmSmsList* RetrieveGsmListL();
	IMPORT_C CMobilePhoneCdmaSmsList* RetrieveCdmaListL();

protected:
	CRetrieveMobilePhoneSmsList(RMobilePhoneStore& aStore, RMobileSmsStore::TMobileSmsEntryExtensionId aType);
	void ConstructL();
	void InitiateRequest(TRequestStatus& aReqStatus, TBool aBatch, TInt aStartIndex, TInt aBatchSize);

	virtual void RestoreListL();

private:
	CMobilePhoneGsmSmsList* iGsmResults;
	CMobilePhoneCdmaSmsList* iCdmaResults;
	RMobileSmsStore::TMobileSmsEntryExtensionId iEntryType;
	TPckgBuf<TBatchRequestData> iRequestData;
	};



class CRetrieveMobilePhoneSmspList : public CAsyncRetrieveWithClientIds
/** Reads SMS parameter list from the SIM's SMSP store.

Instead of reading each SMSP entry individually, a client will retrieve all 
the entries currently stored in one go. A list object (CMobilePhoneSmspList) 
will be returned to the client. The list object that is returned to the client 
will contain an entry for each set of SMS parameters.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object. 

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneSmspList* NewL(RMobileSmsMessaging& aMessaging);
	IMPORT_C ~CRetrieveMobilePhoneSmspList();

	IMPORT_C CMobilePhoneSmspList* RetrieveListL();
	IMPORT_C void Start(TRequestStatus& aReqStatus);

protected:
	CRetrieveMobilePhoneSmspList(RMobileSmsMessaging& aMessaging);
	void ConstructL();
	virtual void RestoreListL();

private:
	virtual void Get(TInt aIpc, TRequestStatus& aReqStatus, TDes8& aDes1, TDes8& aDes2);
	virtual void CancelReq(TInt aIpc1, TInt aIpc2);

private:
	RMobileSmsMessaging& iMessaging;
	CMobilePhoneSmspList* iResults;
	};



class CRetrieveMobilePhoneBroadcastIdList : public CAsyncRetrieveWithClientIds
/** Reads CBMI list from the phone. This list may be stored on SIM.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this class. 

@publishedPartner
@released
*/
	{
public:
		// for use by client-side API code and TSY only

	struct TGetBroadcastIdRequest
		{
		RMobileBroadcastMessaging::TMobileBroadcastIdType iIdType;
		RMobilePhone::TClientId iClient;
		};

public:
	IMPORT_C static CRetrieveMobilePhoneBroadcastIdList* NewL(RMobileBroadcastMessaging& aMessaging);
	IMPORT_C ~CRetrieveMobilePhoneBroadcastIdList();

	IMPORT_C CMobilePhoneBroadcastIdList* RetrieveListL();
	IMPORT_C void Start(TRequestStatus& aReqStatus, RMobileBroadcastMessaging::TMobileBroadcastIdType aIdType);

protected:
	CRetrieveMobilePhoneBroadcastIdList(RMobileBroadcastMessaging& aMessaging);
	void ConstructL();
	virtual void RestoreListL();

private:
	virtual void Get(TInt aIpc, TRequestStatus& aReqStatus, TDes8& aDes1, TDes8& aDes2);
	virtual void CancelReq(TInt aIpc1, TInt aIpc2);

protected:
	RMobileBroadcastMessaging& iMessaging;
	CMobilePhoneBroadcastIdList* iResults;
	TPckgBuf<TGetBroadcastIdRequest> iBroadcastIdRequestData;
	};



class CRetrieveMobilePhoneNamList : public CAsyncRetrieveStoreList
/** The phone's NAM store.

Instead of reading each NAM entry individually, a client may be able to retrieve 
all the parameters in one NAM in one go.

This functionality will be available if the TSY supports reading all entries 
in one NAM. The NAM storage capabilities are returned within the iCaps field 
of RMobilePhoneStore::TMobilePhoneStoreInfoV1 and this will inform a client 
what type(s) of storage access the TSY supports. When all entries in one NAM 
are read in one go, a CMobilePhoneNamList object will be returned to the client.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object. 

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneNamList* NewL(RMobilePhoneStore& aStore);
	IMPORT_C ~CRetrieveMobilePhoneNamList();

	struct TNamRequestData
		{
		RMobilePhone::TClientId iClient;
		TInt iNamId;
		};

	IMPORT_C CMobilePhoneNamList* RetrieveListL();
	IMPORT_C CMobilePhoneNamListV4* RetrieveListV4L();
	IMPORT_C void Start(TRequestStatus& aReqStatus, TInt aNamId);
	IMPORT_C void StartV4(TRequestStatus& aReqStatus, TInt aNamId);

protected:
	CRetrieveMobilePhoneNamList(RMobilePhoneStore& aStore);
	void ConstructL();
	
	virtual void RestoreListL();

private:
	/* pointer to results containing V1 NAM list */
	CMobilePhoneNamList* iResults;
	/* pointer to results containing V4 NAM list */	
	CMobilePhoneNamListV4* iResultsV4;
	/* will be KETelExtMultimodeV1 if results are currently a V1 NAM list,
	   KETelExtMultimodeV4 if they are currently a V4 NAM list */
	TInt iListExtensionId;
	TPckgBuf<TNamRequestData> iRequestData;
	};


class CRetrieveMobilePhoneONList : public CAsyncRetrieveStoreList
/**
Reads Own Number list from the phone or SIM's Own Number store.

Instead of reading each own number entry individually, a client may be able 
to retrieve all the own numbers in one go.

This functionality will be available if the own number store's capabilities 
include KCapsWholeStore. These capabilities are returned within the iCaps 
field of RMobilePhoneStore::TMobilePhoneStoreInfoV1 and this will inform a 
client what type(s) of storage access the TSY supports for that store.

When all entries in own number store are read in one go, a CMobilePhoneONList 
object will be returned to the client. 

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object. 

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneONList* NewL(RMobilePhoneStore& aStore);
	IMPORT_C ~CRetrieveMobilePhoneONList();

	IMPORT_C CMobilePhoneONList* RetrieveListL();
	IMPORT_C void Start(TRequestStatus& aReqStatus);

protected:
	CRetrieveMobilePhoneONList(RMobilePhoneStore& aStore);
	void ConstructL();
	
	virtual void RestoreListL();

private:
	CMobilePhoneONList* iResults;
	};



class CRetrieveMobilePhoneENList : public CAsyncRetrieveStoreList
/**
Reads Emergency Number list from the phone or SIM store.

Instead of reading each emergency number entry individually, a client may be 
able to retrieve all the numbers in one go from SIM and/or NAM.

This functionality will be available if the TSY supports reading all entries 
in one go. The emergency number store's capabilities are returned within the 
iCaps field of RMobilePhoneStore::TMobilePhoneStoreInfoV1 and this will inform 
a client what type(s) of storage access the TSY supports.

When all entries in SIM and/or NAM are read in one go, a CMobilePhoneENList 
object will be returned to the client. The CMobilePhoneENList object that 
is returned to the client will contain the SIM and/or NAM entries and the 
client is able to use the function members of CMobilePhoneENList to enumerate 
and read the entries.

Due to the probable time taken to retrieve a list, clients must use an asynchronous 
approach based around the use of this object. 

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhoneENList* NewL(RMobilePhoneStore& aStore);
	IMPORT_C ~CRetrieveMobilePhoneENList();

	IMPORT_C CMobilePhoneENList* RetrieveListL();
	IMPORT_C void Start(TRequestStatus& aReqStatus);

protected:
	CRetrieveMobilePhoneENList(RMobilePhoneStore& aStore);
	void ConstructL();
	
	virtual void RestoreListL();

private:
	CMobilePhoneENList* iResults;
	};
	
class  CRetrieveMobilePhonePreferredNetworks  : public CAsyncRetrievePhoneList
/**
Retrieves the preferred stored network list from the USIM.

@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CRetrieveMobilePhonePreferredNetworks* NewL(RMobilePhone& aPhone);
	IMPORT_C ~CRetrieveMobilePhonePreferredNetworks();

	IMPORT_C CMobilePhoneStoredNetworkList* RetrieveListL();
	IMPORT_C void Start(TRequestStatus& aReqStatus);

protected:
	CRetrieveMobilePhonePreferredNetworks(RMobilePhone& aPhone);
	void ConstructL();
	
	virtual void RestoreListL();

private:
	CMobilePhoneStoredNetworkList* iResults;	
	};


#endif
