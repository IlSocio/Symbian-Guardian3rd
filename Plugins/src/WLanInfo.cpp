
// 00:0C:F6:2C:36:86

#include "wlaninfo.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>

#include <wlancdbcols.h>
#include <wlanmgmtclient.h> 
#include <wlanscaninfo.h>
#include <CHARCONV.H>
#include <FeatDiscovery.h>
#include <Featureinfo.h>


CWLanInfo* CWLanInfo::NewL(TAny* aInitParams)
	{
	CWLanInfo* self=new(ELeave) CWLanInfo();
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CWLanInfo::~CWLanInfo()
	{
	}

CWLanInfo::CWLanInfo()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CWLanInfo::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	}

TPtrC CWLanInfo::PluginId()
	{
	return TPtrC(KWLANINFO);
	}


HBufC* CWLanInfo::GetSsidLC(const TUint8* data, TUint8 len)
	{
	TPtrC8 ptrIE(data, len);
	HBufC* hRes = HBufC::NewLC(len*2);
	TPtr resultPtr = hRes->Des();
	
	CCnvCharacterSetConverter* converter = CCnvCharacterSetConverter::NewLC();
	converter->PrepareToConvertToOrFromL( KCharacterSetIdentifierSms7Bit, iFs );	
	converter->SetReplacementForUnconvertibleUnicodeCharactersL( _L8(".") );

	RBuf8 ascii;
	ascii.CreateL( len*2 );
	ascii.CleanupClosePushL();

	RBuf unicode;
	unicode.CreateL(len);
	unicode.CleanupClosePushL();
	unicode.Copy( ptrIE );
	converter->ConvertFromUnicode(ascii, unicode);
	resultPtr.Copy( ascii );
	CleanupStack::PopAndDestroy(); // unicode
	
	CleanupStack::PopAndDestroy();	// ascii
	
	CleanupStack::PopAndDestroy( converter );
	return hRes;
	}

void CWLanInfo::ProcessCommandL(const TDesC& aString)
	{
	__LOG_TXT("ProcessCommandL");
	TBool hasWLAN =
			CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdProtocolWlan);
	if (!hasWLAN)
		{
		__LOG_TXT("WLanNotAvail");
		this->AppendDataToReplyL(R_WLAN_NOTSUPPORTED);
		this->SendReplyL();
		Complete(KErrNone);
		return;
		}

	TBool advanced = ( iDataUpper.Find( KADVANCED ) >= 0 );

	CWlanMgmtClient* client=CWlanMgmtClient::NewL();
	CleanupStack::PushL(client);
	CWlanScanInfo* scanInfo=CWlanScanInfo::NewL();
	CleanupStack::PushL(scanInfo);
	client->GetScanResults(*scanInfo);

	TInt totLan=0;
	for (scanInfo->First(); !scanInfo->IsDone(); scanInfo->Next() )
		totLan++;

	__LOG("TotLan:%d", totLan);
	AppendDataToReplyL( R_WLAN_OK );
	if (totLan == 0)
		{
		AppendDataToReplyL( R_WLAN_NOTFOUND );
		}
	else
		{
		TBuf<4> buff;
		buff.AppendNum(totLan);
		AppendDataToReplyL( R_WLAN_FOUND );
		AppendDataToReplyL( buff );
		}
	AppendDataToReplyL( KCRLF );

	
	for (scanInfo->First(); !scanInfo->IsDone(); scanInfo->Next() )
		{
		AppendDataToReplyL( KCRLF );
		
		TBuf<50> buff;
		TWlanBssid bssid;
		scanInfo->Bssid(bssid);
		buff.Zero();
		for (TInt i=0; i<bssid.Length(); i++)
			{
			if (buff.Length() > 0)
				buff.Append(_L(":"));
			buff.AppendFormat(_L("%02X"), bssid[i]);
			}
		
		AppendDataToReplyL( R_WLAN_BSSID );
		AppendDataToReplyL( buff );
		AppendDataToReplyL( KCRLF );

		TUint8 ieLen(0);
		const TUint8* ieData( NULL);
		__LOG_TXT("InfoElement");
		TInt ret = scanInfo->InformationElement( 0, ieLen, &ieData);
		if (ret == KErrNone && ieLen > 0)
			{
			HBufC* ssid = GetSsidLC( ieData, ieLen );
			//HBufC* tmpBuf = HBufC::NewLC( ieLen );
			//TPtrC8 ptrIE(ieData, ieLen);
			//__FLOG(_T8("Copy"));
			//tmpBuf->Des().Copy(ptrIE);
			AppendDataToReplyL( R_WLAN_SSID );
			AppendDataToReplyL( ssid->Des() );
			AppendDataToReplyL( KCRLF );
			CleanupStack::PopAndDestroy( ssid );
			}

		//In general if the least significant bit of the capbility field 
		//is 1 then the network is of "Infrastructure Type" or else if the 
		//capability field is 0 then the network is of "Ad-hoc type"

		TUint16 capability=scanInfo->Capability();
		// * Get capability of the BSS (see IEEE 802.11 section 7.3.1.4.
		// * @param aIE        Id of the IE. See 802dot11.h

		const static TInt ESS = 1;
		//const static TInt IBSS = 1<<1;

		TInt lanType=capability & ESS;

		// Mode / Modalita' / Architecture
		AppendDataToReplyL( R_WLAN_MODE );
		if (lanType==1)
			AppendDataToReplyL( R_WLAN_MODE_BSS ); // _L("Infrastructure")); // BSS (Infrastruttura)
		else
			AppendDataToReplyL( R_WLAN_MODE_IBSS ); // IBSS
		AppendDataToReplyL( KCRLF );

		if (!advanced)
			continue;
		
		AppendDataToReplyL( R_WLAN_SECURITY );
		TInt securityMode=scanInfo->SecurityMode();
		switch (securityMode)
			{
			case EWlanConnectionSecurityOpen:
				{
				AppendDataToReplyL( R_WLAN_SEC_OPEN );
				break;
				}
			case EWlanConnectionSecurityWep:
				{
				AppendDataToReplyL( R_WLAN_SEC_WEP );
				break;
				}
			case EWlanConnectionSecurity802d1x:
				{
				AppendDataToReplyL( R_WLAN_SEC_802 );
				break;
				}
			case EWlanConnectionSecurityWpa:
				{
				AppendDataToReplyL( R_WLAN_SEC_WPA );
				break;
				}
			case EWlanConnectionSecurityWpaPsk:
				{
				AppendDataToReplyL( R_WLAN_SEC_WPAPSK );
				break;
				}
			default:
				{
				AppendDataToReplyL( R_WLAN_SEC_UNK );
				break;
				}
			}
		AppendDataToReplyL(KCRLF);

		
		// DS Parameter Set element
		ret = scanInfo->InformationElement( 3, ieLen, &ieData);
		if (ret == KErrNone && ieLen>0)
			{
			TBuf<10> out;
			TPtrC8 ptrIE(ieData, ieLen);
			out.AppendNum( *ieData);
			AppendDataToReplyL( R_WLAN_CHANNEL );
			AppendDataToReplyL(out);
			AppendDataToReplyL( KCRLF );
			}

		buff.Zero();
		buff.AppendNum( scanInfo->BeaconInterval() );
		buff.Append(_L("ms"));
		AppendDataToReplyL( R_WLAN_BEACON );
		AppendDataToReplyL( buff );
		AppendDataToReplyL( KCRLF );

		// RXLevel 	== ??? RSSI (SignalQuality) ???
		buff.Zero();
		buff.Append(_L(" -"));
		buff.AppendNum( scanInfo->RXLevel() );
		buff.Append(_L("dBm"));
		AppendDataToReplyL( R_WLAN_RXLEVEL );
		AppendDataToReplyL( buff );
		AppendDataToReplyL( KCRLF );		
		}
	__LOG_TXT("Pop ScanInfo");
	CleanupStack::PopAndDestroy(scanInfo);
	__LOG_TXT("Pop Client");
	CleanupStack::PopAndDestroy(client);

	this->SendReplyL();
	Complete(KErrNone);
	}

