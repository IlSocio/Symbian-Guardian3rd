// MMLIST.H
//
// Copyright (c) 2000-2004 Symbian Software Ltd.  All rights reserved.
//

/** @file mmlist.h
Multimode ETel API v1.0

Header file for phone list classes
*/

#ifndef _MMLIST_H_
#define _MMLIST_H_

#include <etelmm.h>
#include <e32base.h>
#include <etel3rdparty.h>


// Vedi TTelAddress
	class TMobileAddress
		{
	public:
		TMobileAddress();
			
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
			
	public:
		/** Type of number.
		
		@see TMobileTON */
		CTelephony::TTelNumberTON iTypeOfNumber;
		/** Number plan.
		
		@see TMobileNPI */
		CTelephony::TTelNumberNPI iNumberPlan;
		/** Telephone number. */
		TBuf<100> iTelNumber;
		};


	class TMultimodeType
		{
	public:
		TInt ExtensionId() const;
	protected:
		TMultimodeType();
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	protected:
		TInt iExtensionId;
		};


	class TMobileSmspEntryV1 : public TMultimodeType

	/** Defines a set of SMS parameters. 
	@publishedPartner
	@released
	*/
		{
	public:
		TMobileSmspEntryV1();
	public:
		void InternalizeL(RReadStream& aStream);
		void ExternalizeL(RWriteStream& aStream) const;
	public:
	/** The slot index where this SMSP entry is stored in the SIM's SMSP file. */
		TInt iIndex;
	/** A bit-wise sum of the constants defined in TMobileSmspStoreValidParams, that 
	specifies which parameters are valid within this entry. */
		TUint32	iValidParams;
	/** Default protocol ID. Coded according to GSM 03.40. */
		TUint8 iProtocolId;
	/** Default data coding scheme. Coded according to GSM 03.40. */
		TUint8 iDcs;
	/** Default validity period, in relative format and coded on 8 bits as defined 
	by GSM 03.40. */
		TUint8 iValidityPeriod;
	/** Reserved for future use. */
		TUint8 iReservedFiller;
	/** Default destination for outgoing SMS.
	
	@see RMobilePhone::TMobileAddress */
		TMobileAddress iDestination;
	/**		Default service centre for outgoing SMS.
	
	@see RMobilePhone::TMobileAddress */
		TMobileAddress iServiceCentre;
	/** The alpha-tag associated with this SMSP entry, expressed as Unicode characters. */
		TBuf<30> iText;
		};




class CMobilePhoneListBase : public CBase
/**
A base class within a thin-template implementation.

Implements the methods for "read-only" access to a list class.
Entries are stored in a CArrayFixFlat<TAny>.

@publishedPartner
@released
*/

	{
public:
	~CMobilePhoneListBase();
	
	TInt Enumerate() const;
	TInt MaxNumberEntries() const;
	void SetMaxNumberEntries(TInt aMax);

	void StoreL(TDes8& aDes);
	void RestoreL(const TDesC8& aBuf);
	CBufBase* StoreLC();

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;

	enum 
		{
		KMaxEntriesNotSet = - 1
		};

	enum
		{
		EBadRange,
		EListIndexOutOfRange,
		EListMaxNumberReached
		};

protected:
	CMobilePhoneListBase(TInt aLength, TInt aGranularity);
	const TAny* GetEntryL(TInt aIndex) const;
	void AddEntryL(const TAny* aEntry);
	/** Pure virtual function that should internalise entry *aPtr from the aStream 
	read stream. This member function is used by InternalizeL to internalise the 
	separate entries in the stream.
	
	@param aPtr On return, pointer to the object that will contain the entry.
	@param aStream The read stream containing the entry to be internalized. */
	virtual void InternalizeEntryL(TAny* aPtr,RReadStream& aStream) const=0;
	/** Pure virtual function that should externalise entry *aPtr into the aStream 
	write stream. This member function is used by ExternalizeL to externalise 
	the separate entries in the list.
	
	@param aPtr Pointer to the entry to be written to the stream
	@param aStream On return, the write stream. */
	virtual void ExternalizeEntryL(const TAny* aPtr,RWriteStream& aStream) const=0;

protected:
	CArrayFixFlat<TAny> iList;
	TInt iMaxNumber;
	};




class CMobilePhoneEditableListBase : public CMobilePhoneListBase
/**
A base class within a thin-template implementation

Implements the methods for "write" access to a list class

@publishedPartner
@released
*/
{
public:
	~CMobilePhoneEditableListBase();

	void DeleteEntryL(TInt aIndex);
protected:
	void InsertEntryL(TInt aIndex, const TAny* aEntry);
	CMobilePhoneEditableListBase(TInt aLength, TInt aGranularity);
};



template<class T>
class CMobilePhoneEditableList : public CMobilePhoneEditableListBase
/**
A template class within a thin-template implementation

Provides the type-safe wrappers for "read-write" access to the
CMobilePhoneEditableListBase list class

@publishedAll
@released
*/
{
protected:
	inline CMobilePhoneEditableList();
public:
	inline void AddEntryL(const T& aEntry);
	inline const T& GetEntryL(TInt aIndex) const; 
	inline void InsertEntryL(TInt aIndex, const T& aEntry);
	inline void ChangeEntryL(TInt aIndex, const T& aEntry);

private:
	void InternalizeEntryL(TAny* aPtr,RReadStream& aStream) const
	{aStream >> *(new(aPtr) T);} // use in place new to construct T
	void ExternalizeEntryL(const TAny* aPtr,RWriteStream& aStream) const
		{aStream << *static_cast<const T*>(aPtr);}
};


class CMobilePhoneSmspList : public CMobilePhoneEditableList<TMobileSmspEntryV1>
/**
An instantiation of the list thin-template.

Used to hold the "read-write" list of SMS parameter entries retrieved from the phone.

@see RMobileSmsMessaging::TMobileSmspEntryV1
@publishedPartner
@released
*/
{
public:
	static CMobilePhoneSmspList* NewL();
	~CMobilePhoneSmspList ();
protected:
	CMobilePhoneSmspList();
private:
	void ConstructL();
};


/*class CMobilePhoneSmspList : public CBase
{
public 
	TMobileSmspEntryV1
protected:
	CArrayFixFlat<TMobileSmspEntryV1> iList;
	TInt iMaxNumber;
};*/

#endif










