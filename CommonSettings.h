// CommonSettings.h
//
// Copyright (C) Symbian Ltd 2000-2005. All rights reserved.
//

#ifndef __COMMONSETTINGS_H__
#define __COMMONSETTINGS_H__

#include <MetaDatabase.h>
#include <CommsDatTypesV1_1.h>
using namespace CommsDat;

#include "ProxyDialog.h"
#include "IPAddressDialog.h"
#include "DNSAddressDialog.h"
#include "LoginDialog.h"

/**
* This class holds common settings for an IAP.
* @internalComponent
*/
class CCommonSettings : public CBase, public MProxyDialogSupplier, public MIPAddressDialogSupplier, public MDNSAddressDialogSupplier, public MLoginDialogSupplier
	{
	public:
		enum TSettingsConnectionType
			{
			EGPRS,
			EDialOut,
			EBTPan,
			EBTInternetPan,
			EBTLocalPan
			};
	public:
		virtual ~CCommonSettings();
		static CCommonSettings* NewL(TSettingsConnectionType aType);
		static CCommonSettings* NewL(CMDBSession* aDatabase, TUint32 aId);
		virtual void WriteToDatabaseL(CMDBSession* aDatabase, TBool aCreateNewServiceRecord, TBool aCreateNewNetworkRecord);
		virtual void ReadFromDatabaseL(CMDBSession* aDatabase, TUint32 aId);
		virtual void ReadDefaultsL() = 0;		
		void ReadTsyNameL(CMDBSession* aDatabase);
		TPtrC ServiceTypeL() const;
	protected:
		CCommonSettings();
		virtual const TPtrC GetTableName() const = 0;
		virtual const TPtrC GetBearerName() const = 0;
		virtual TInt GetBearerIndexL(CMDBSession* aDatabase) const = 0;
		virtual void DoWriteToDatabaseL(CMDBSession* aDatabase, CCDIAPRecord* aTable) = 0;
		virtual void DoReadFromDatabaseL(CMDBSession* aDatabase, CCDIAPRecord* aTable) = 0;
		CCDProxiesRecord* WriteToProxyTableL(CMDBSession* aDatabase) const;
		void ReadFromProxyTableL(CMDBSession* aDatabase);
		HBufC* CopyAndReplaceLC(const HBufC* aString, TUint16 aFrom, TUint16 aTo) const;		
	public: // From MProxyPageSupplier
		void SetProxyUseServer(TBool aFlag);
		void SetProxyServerAddress(HBufC* aAddress);
		void SetProxyServerPort(TUint32 aPort);
		void SetProxyExceptions(HBufC* aExceptions);
		TBool GetProxyUseServer();
		const HBufC* GetProxyServerName();
		TUint32 GetProxyServerPort();
		const HBufC* GetProxyExceptions();
	public: // From MIPAddressDialogSupplier
		void SetLoginIPAddressFromServer(TBool aFlag);
		void SetLoginIPAddress(const TDesC& aAddress);
		void SetLoginGateway(const TDesC& aGateway);
		void SetLoginNetmask(const TDesC& aNetmask);
		TBool GetLoginIPAddressFromServer();
		const TDesC& GetLoginIPAddress();
		const TDesC& GetLoginGateway();
		const TDesC& GetLoginNetmask();
	public: // From MDNSAddressDialogSupplier
		void SetLoginDNSAddressFromServer(TBool aFlag);
		void SetLoginDNSAddress1(const TDesC& aAddress);
		void SetLoginDNSAddress2(const TDesC& aAddress);
		TBool GetLoginDNSAddressFromServer();
		const TDesC& GetLoginDNSAddress1();
		const TDesC& GetLoginDNSAddress2();
	public: // From MLoginDialogSupplier
		void SetEnablePPPExtensions(TBool aFlag);
		void SetAllowPlainText(TBool aFlag);
		TBool GetEnablePPPExtensions();
		TBool GetAllowPlainText();
#pragma message("Fix getter/setters in CCommonSettings")
//lint --e{1925} suppress "Symbol is a public data member"
	public:
		TBool iChanged;
		TBool iNewRecord;
		TBool iNewServiceRecord;
		TBool iNewNetworkRecord;
		TBool iNewProxyRecord;
		TUint32 iIAPId;
		TUint32 iIAPServiceId;
		TUint32 iIAPNetworkId;
		TSettingsConnectionType iConnectionType;
		
		TBuf<KMaxTextLength> iAccountName;
		TBuf<KMaxMedTextLength> iIFAuthName;
		TBuf<KMaxMedTextLength> iIFAuthPass;
		TBuf<KMaxTextLength> iIPNameServer1;
		TBuf<KMaxTextLength> iIPNameServer2;
		TBuf<KMaxTextLength> iIPAddr;
		TBuf<KMaxTextLength> iGateway;
		TBuf<KMaxTextLength> iNetmask;
		TBuf<KMaxTextLength> iTsyName;
		TBool	iIPAddrFromServer;
		TBool	iIPDnsAddrFromServer;
		TBool	iEnableLCPExtensions;
		TBool	iDisablePlainTextAuth;
		TBool	iProxyUseProxyServer;
		HBufC*	iProxyServerName;
		TUint32	iProxyPortNumber;
		HBufC*	iProxyExceptions;
	};

#endif //__COMMONSETTINGS_H__
