// SMSUADDR.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

/**
@file smsuaddr.h Defines types for SMS adressing and the class TSmsAddr
@publishedAll
@released
*/

#if !defined(SMSUADDR_H__)
#define SMSUADDR_H__

#include <es_sock.h>
#include <etelmm.h>

/** SMS sockets family identifier.*/
const TUint KSMSAddrFamily = 0x010;
/** SMS sockets protocol ID. */
const TUint KSMSDatagramProtocol = 0x02;
/** The maximum number of SAPs the SMS sockets protocol supports. */
const TInt KSMSNumberSockets = 0x100;
/** SMS sockets service flags. */
const TUint KSMSDatagramServiceInfo = KSIConnectionLess | KSIMessageBased ;

/**
@internalComponent
*/
_LIT(KSmsDatagram,"SMS Datagram");

/** Specifies SMS sockets protocol level for the provider in the aLevel argument of RSocket::Ioctl(). */
const TUint KSolSmsProv = 0x100; 

/** Ioctl command for deleting SMS messages.

For this command, the aDesc argument of RSocket::Ioctl() should be NULL. 

@capability WriteUserData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlDeleteSmsMessage        = 0x0300; 

/** Ioctl command for counting stored SMS messages.

For this command, the aDesc argument of RSocket::Ioctl() should be a packaged 
TUint. On completion, this holds the count of messages enumerated. 

@capability ReadUserData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlEnumerateSmsMessages    = 0x0301;

/** Ioctl command to indicate to the protocol that the client received messages 
successfully.

For this command, the aDesc argument of RSocket::Ioctl() should be NULL. 

@capability ReadUserData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlReadMessageSucceeded    = 0x0304; 

/** Ioctl command to indicate to the protocol that the client failed to receive 
messages successfully.

For this command, the aDesc argument of RSocket::Ioctl() should be NULL. 

@capability ReadUserData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlReadMessageFailed       = 0x0305; 

/** Ioctl command for sending SMS messages.

For this command, the aDesc argument of RSocket::Ioctl() should be a packaged 
TUint. 

@capability NetworkServices
@capability WriteUserData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlSendSmsMessage          = 0x0306; 

/** Ioctl command for writing SMS messages to SIM.

For this command, the aDesc argument of RSocket::Ioctl() may be NULL or may hold a packaged 
descriptor large enough to store information on slots for the message. This descriptor will 
be populated upon completion of the request and shall be used by the client to update the 
CSmsMessage object that has been written, by invoking its UpdateSlotsL() method. This has 
to be done if the client wants to be able to delete this message from the store at some 
point, unless it opts to enumerate messages before deletion takes place. 

@capability WriteUserData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlWriteSmsMessage         = 0x0307; 

/** Ioctl command for enumerating SMS parameter sets.

For this command, the aDesc argument of RSocket::Ioctl() should be NULL. 

@capability ReadDeviceData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlReadSmsParams           = 0x0308; 

/** Ioctl command for completing SMSP list read request.

For this command, the aDesc argument of RSocket::Ioctl() should be NULL. 

@capability ReadDeviceData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlCompleteReadSmsParams   = 0x0309; 

/** Ioctl command ofr writing SMS parameter sets.

For this command, the aDesc argument of RSocket::Ioctl() should be NULL. 

@capability WriteDeviceData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlWriteSmsParams          = 0x0310; 

/** KIOctlSelect completion status if a modem is present. 

@capability WriteDeviceData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlSelectModemPresent    = 0x400; 

/** KIOctlSelect completion status if a modem is not present.

@capability WriteDeviceData
@ref RSocket::Ioctl(TUint aLevel,TUint aName,TDes8* aOption)
*/
const TUint KIoctlSelectModemNotPresent = 0x401; 

//ahe TODO
//typedef TBuf<KGsmMaxTelNumberSize> TSmsServiceCenterAddress;

/** Buffer to hold Service Center address. */
typedef TBuf<14> TSmsServiceCenterAddress;
/** Package buffer for TSmsServiceCenterAddress objects. */
typedef TPckgBuf<TSmsServiceCenterAddress> TSmsServiceCenterAddressBuf;

//note: Maintainers, please do *not* change the order of these enums!
/** SMS address family for a socket.
@publishedAll
@released */
enum TSmsAddrFamily
	{
	ESmsAddrUnbound                = 0, ///< Not bound yet.
	ESmsAddrSendOnly               = 1, ///< Only for sending, no reception.
	ESmsAddrMessageIndication      = 2, ///< Matches on IEI 0x01 and DCS 0x1100xxxx, 0x1101xxxx and 0x1110xxxx.
	ESmsAddrMatchIEI               = 3, ///< For matching Information Element Identifiers (IEI)
	ESmsAddrMatchText              = 4, ///< For matching any text patterns
	ESmsAddrRecvAny                = 5, ///< Receive all messages. Only one client can use this.
	ESmsAddrStatusReport           = 6, ///< For receiving Status Reports.
	ESmsAddrLocalOperation         = 7, ///< For local SIM operations.
	ESmsAddrApplication8BitPort    = 8, ///< For sock port identification.
	ESmsAddrApplication16BitPort   = 9, ///< For sock port identification.
	ESmsAddrEmail			  	   = 10 ///< for matching of email messages.
	};



class TSmsAddr : public TSockAddr
/**
SMS address for a socket.
@publishedAll
@released
*/
	{
public:
	enum { EMaxTextMatchLength = 24 };
public:
	IMPORT_C TSmsAddr();
	IMPORT_C TSmsAddrFamily SmsAddrFamily() const;
	IMPORT_C void SetSmsAddrFamily(TSmsAddrFamily aFamily);
	IMPORT_C TInt IdentifierMatch() const;
	IMPORT_C void SetIdentifierMatch(TInt aIdentifier);
	IMPORT_C TPtrC8 TextMatch() const;
	IMPORT_C void SetTextMatch(const TDesC8& aText);
	IMPORT_C TBool operator==(const TSmsAddr& aAddr) const;
	};


#endif // SMSUADDR_H__
