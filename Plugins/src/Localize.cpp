
#include "localize.h"
#include "common.h"

#include <Plugins_200112df.rsg>
#include <FuzzyByte\Guardian\client.h>

// Construction and destruction functions


 
CLocalize* CLocalize::NewL(TAny* aInitParams)
	{
	CLocalize* self=new(ELeave) CLocalize(); 
	CleanupStack::PushL(self);
	self->ConstructL(aInitParams);
	CleanupStack::Pop(self);
	return self;
	}

CLocalize::~CLocalize()
	{
	if (iStarter)
		delete iStarter;
	if (iCellIdAfterTimer)
		delete iCellIdAfterTimer;
	if (iCellIdSmsIntervalTimer)
		delete iCellIdSmsIntervalTimer;
	if (iGPS)
		delete iGPS;
	if (iPhone)
		delete iPhone;
	}


CLocalize::CLocalize()
// Store input/output parameters
	{
	// See ConstructL() for initialisation completion.
	}

void CLocalize::ConstructL(TAny* aInitParams)
// Safely complete the initialization of the constructed object
	{
	BaseConstructL(aInitParams);
	iStarter = CTimeOutTimer::NewL(*this);
	iCellIdAfterTimer = CTimeOutTimer::NewL(*this);
	iCellIdSmsIntervalTimer = CTimeOutTimer::NewL(*this);

	__LOG_TXT("Mid ConstructL");
	iPhone = CPhone::NewL();
	iGPS = NULL;
	__LOG_TXT("End ConstructL");
//	CGuardPlugInterface::TGuardPlugInitParams* initParams = (CGuardPlugInterface::TGuardPlugInitParams*)aInitParams;
	}


TPtrC CLocalize::PluginId()
	{
	return TPtrC(KLOCALIZE);
	}


/*#define KSECOND 1000000
#define KMINUTE KSECOND*60*/


void CLocalize::ProcessCommandL(const TDesC& aString)
	{
/*	TRAPD(err, iGPS = CActivePositioner::NewL(*this));
	if (err != KErrNone)
	{
		__FLOG_1(_T8("Server Error:%d"), err);
		RBuf buf;
		buf.CleanupClosePushL();
		buf.CreateL(100);
		buf.Append( _L("Localize Command: Error - GPS Server Not Ready: ") );
		buf.AppendNum(err);
		SendSmsL(buf);
		CleanupStack::PopAndDestroy();	// buf
		Complete(err);
		return;
		// UseCell...
	}*/
	
	iUseAGPS = (iDataUpper.Find(KAGPS) >= 0);		

	iQtySent = 0;
	iUseCellIdAfterMin = -1;
	iUseCellIdAfterMin = GetParamValueInt(KUSECELLAFTER);	// Tempo totale di attesa per Search + Fix...
	if (iUseCellIdAfterMin.Int() >= 0)
		iCellIdAfterTimer->AfterTime(iUseCellIdAfterMin);
	// Fixed: perche' non puo' superare i 30minuti... usare At() invece di After...
	// Its range is +-2147483647, which is +-35 minutes, 47 seconds.
	// Pero' attenzione perche' usando At() esso sara' influenzato dai cambi dell'orario.
	
	iQty=GetParamValueInt(KQUANTITY);						// Quantita' di invii da effettuare...
	if (iQty < 1) iQty = 1;

	iSendIntervalMin = GetParamValueInt(KINTERVAL);				// minuti di distanza tra un invio e l'altro...
	if (iSendIntervalMin.Int() < 1) iSendIntervalMin = 1;

	TTimeIntervalMicroSeconds32 ms(1000);
	iStarter->AfterTime(ms);
	}

/*
	-1) Il cell ha un GPS int./ext. ma non voglio aspettare il FIX xche' magari impiega troppo tempo...  (Specifico il tempo di attesa per passare al Cell-Id, che puo' anche essere infinito)
	-2) Il cell non ha un GPS int./ext. ma potrebbe averlo in futuro (Specifico il tempo di attesa per passare al Cell-Id)
*/

// Occhio, deve essere sempre divisore di 60 (secondi in un minuto)
#define FIVE 5

void CLocalize::TimerExpiredL(TAny* src)
{
	__LOG_TXT("TimerExpired");
	// -1) Il cell ha un GPS int./ext. ma non voglio aspettare il FIX xche' magari impiega troppo tempo...  (Specifico il tempo di attesa per passare al Cell-Id, che puo' anche essere infinito)
	// -2) Oppure sono gia' trascorsi i Minuti di attesa per il Fix
	// Se vale -1 significa che attende all'infinito...
	if (src == iCellIdAfterTimer || src == iCellIdSmsIntervalTimer) // SEND CellID
	{
		__LOG_TXT("PollGPS Cancel");
		// Annulla la creazione di GPS
		iStarter->Cancel();   
		// Non dovrebbe essere necessario, ma per precauzione annulla il timeout cell.id
		iCellIdAfterTimer->Cancel();
		// Annulla l'eventuale precedente richiesta di posizione GPS...
		if (iGPS)
			iGPS->Cancel();
		iQtySent++;
		TBool isLast = (iQtySent >= iQty);
		SendCellIdL(isLast);
		if (isLast)
		{
			__LOG_TXT("IsLast");
			Complete(KErrNone);
			return;
		}

		__LOG_TXT("After Interval");
		// Intervallo in minuti per il prossimo invio del CellId...
		iCellIdSmsIntervalTimer->AfterTime(iSendIntervalMin);
		return;
	}
	// src = iPollGPSModuleTimer

	if (!iGPS)
	{
		TRAPD(err, iGPS = CGPSPosition::NewL(*this));
		__LOG("GPS Server Connect:%d", err);
	}

	if (!iGPS)
	{
		iStarter->AfterTime( TTimeIntervalSeconds(3) );
		return;
	}

	iGPS->WaitForAvailableModuleId(iUseAGPS);
	
//		hasGPS_Module = iGPS->ReceiveData(iInterval * 60);	// Riceve dati ad intervalli di xxx minuti...
}
 

void CLocalize::HandleGPSModuleNotificationL(TInt error)
	{
	if (error == KErrNone)
		{
		iLowAccuracyFlag = EFalse;
		// E' presente un modulo GPS...
		iGPS->ReceiveGpsData(iSendIntervalMin.Int() * 60);	// Riceve dati ad intervalli di xxx minuti...

		__LOG_TXT("HasGPS Module");
		// Arriveranno i dati tramite la HandleGPSPosition oppure ci sara' l'HandleGPSError...		
		return;
		}
	}

 
void CLocalize::HandleGPSPositionL(TPosition position)
{
	__LOG_TXT("HandleGpsPosition");
	
	TReal32 accur = position.HorizontalAccuracy(); 
	if (Math::IsNaN(accur))
		{		 
		__LOG_TXT("Accuracy: NaN");
		}
	else
		{		
		__LOG("Accuracy: %d", (int)accur);
		}
	
	
	if ( !Math::IsNaN(accur) && accur > 1000)
		{
		// TODO: Test
		// The current accuracy is not good, get a new location ASAP, sets 1 minute interval
		iGPS->ReceiveGpsData(1 * 60);
		iLowAccuracyFlag = ETrue;
		return;
		}

	if (iLowAccuracyFlag)
		{
		// The accuracy wasn't good but now it's fine... Restore the original inteval.
		iGPS->ReceiveGpsData(iSendIntervalMin.Int() * 60);
		iLowAccuracyFlag = EFalse;
		// exit because when calling the ReceiveGpsData it will receive immediately a GPS location
		return;
		}
	
	// Annulla il timer per l'uso del Cell-Id...
	iCellIdAfterTimer->Cancel();
	iQtySent++;
	TBool isLast = (iQtySent >= iQty);
	SendGPSIdL(isLast, position);
	if (isLast)
	{
		iGPS->Cancel();
		Complete(KErrNone);
	}
}


void CLocalize::HandleGPSErrorL(TInt error)
{
	__LOG("GPS Error:%d", error);
	// Forse e' passato il tempo concesso per il fix e non c'e' stato alcun FIX...
	// Rischedula una ricerca del modulo GPS...
	iGPS->WaitForAvailableModuleId(iUseAGPS);
	// Se non e' gia' in corso, fa partire il timer per l'uso del Cell-Id
	if (!iCellIdAfterTimer->IsActive() && iUseCellIdAfterMin.Int() >= 0)
		iCellIdAfterTimer->AfterTime(iUseCellIdAfterMin);
}


void CLocalize::SendCellIdL(TBool isLast)
{
	__LOG_TXT("SendCellId"); 
	TUint cell;
	TUint area;
	TCountry country;
	TOperName oper;
	TNetwork network;
//	TBuf<CTelephony::KNetworkCountryCodeSize> country;
//	TBuf<CTelephony::KNetworkLongNameSize> oper;
	iPhone->GetCellID(cell, area, network, country, oper);

	TInt resID = 0;
	if (isLast)
	{
		resID = R_LOCALIZE_COMPLETED;
		// buf.Append(_L("\n\nLocalize Command: Completed!"));
	} else
	{
		resID = R_LOCALIZE_OK;
		// buf.Append(_L("Localize Command: Ok -\n"));
	}
	AppendDataToReplyL( resID );

	AppendDataToReplyL( R_LOCALIZE_CELL );
	TBuf<10> buf;
	buf.AppendNum(cell);
	AppendDataToReplyL( buf );

	AppendDataToReplyL( R_LOCALIZE_AREA );
	buf.Zero();
	buf.AppendNum(area);
	AppendDataToReplyL( buf );
	
	AppendDataToReplyL( R_LOCALIZE_NETWORK );
	AppendDataToReplyL( network );
	
	AppendDataToReplyL( R_LOCALIZE_COUNTRY );
	AppendDataToReplyL( country );
	
//	iResReader->ReadL(R_LOCALIZE_OPERATOR, txt);
//	buf.Append(txt);	buf.Append(oper);	
	SendReplyL();
}


void CLocalize::SendGPSIdL(TBool isLast, TPosition position)
{
	__LOG_TXT("SendGPSId");
/* caratteri necessari
18 height
+ 2\n
14 lat + 1
14 lon + 1
+ 2\n
15 lat + 1
15 lon + 1
*/
	TReal64 alt = position.Altitude();
	TReal64 lat = position.Latitude();
	TReal64 lon = position.Longitude();
	Math::Round(alt, alt, 0);
	Math::Round(lat, lat, 6);
	Math::Round(lon, lon, 6);
    //TInt intAlt = static_cast<TInt>(alt);

	TBuf<20> latBuf;
	TBuf<20> lonBuf;
	GetDegreesString(lat, latBuf);
	GetDegreesString(lon, lonBuf);

	TRealFormat fmt(11, 6);
	fmt.iPoint = TChar('.');

	TBuf<50> bufLatLon;
	bufLatLon.AppendNum(lat, fmt);
	bufLatLon.Append(_L(","));
	bufLatLon.AppendNum(lon, fmt);

	TInt resID = 0;
	if (isLast)
	{
		resID = R_LOCALIZE_COMPLETED;
		// buf.Append(_L("\n\nLocalize Command: Completed!"));
	} else
	{
		resID = R_LOCALIZE_OK;
		// buf.Append(_L("Localize Command: Ok -\n"));
	}
	AppendDataToReplyL( resID );

//	buf.Append(_L("Height: "));
/*	buf.Append(_L("\nLat: "));
	buf.AppendNum(lat, fmt);
	buf.Append(_L("\nLon: "));
	buf.AppendNum(lon, fmt);*/

	AppendDataToReplyL(_L("http://maps.google.com/maps?q="));
	AppendDataToReplyL(bufLatLon);

	// China FIX - Begin
	if (lat >= 18 && lat <= 54 && lon >= 37 && lon <= 135)
		{
		AppendDataToReplyL(_L("&t=h"));
		}
	// China FIX - End
	
	AppendDataToReplyL(_L("&output=html\n\n"));
	// iResReader->ReadL(R_LOCALIZE_HEI, txt);
	// buf.Append(txt);
    	// buf.AppendNum(intAlt);
	// iResReader->ReadL(R_LOCALIZE_MET, txt);
	// buf.Append(txt);
	AppendDataToReplyL(_L("Lat:"));
	AppendDataToReplyL(latBuf);
	AppendDataToReplyL(_L("\nLon:"));
	AppendDataToReplyL(lonBuf);

	SendReplyL();
}


void CLocalize::CancelCommandL()
{
	__LOG_TXT("CancelRemoteCommand");
	if (iStarter)
		iStarter->Cancel();
	if (iCellIdAfterTimer)
		iCellIdAfterTimer->Cancel();
	if (iCellIdSmsIntervalTimer)
		iCellIdSmsIntervalTimer->Cancel();
	if (iGPS)
		iGPS->Cancel();
}


// Degrees sign delimeter used in formatting methods
_LIT(KDelimDegree,"\x5E"); // "^" symbol

// Dot delimeter used in formatting methods
_LIT(KDelimDot,"\x2e"); // "." symbol

// Plus sign delimeter used in formatting methods
_LIT(KDelimPlus,"\x2b"); // "+" symbol

// Minus sign delimeter used in formatting methods
_LIT(KDelimMinus,"\x2d"); // "-" symbol

// Quotation sign delimeter used in formatting methods
_LIT(KDelimQuot,"\x22"); // "\"" symbol

// Apostrophe sign delimeter used in formatting methods
_LIT(KApostrophe,"\x27"); // "'" symbol

_LIT(KNan,"NaN");

// 37,322741 OK
// -122,017697 -Inf...
// -122,017698 -Inf...

void CLocalize::GetDegreesString(const TReal64& aDegrees, TDes& aDegreesString) const
    {
    const TReal KSecondsInMinute = 60.0;
    const TInt KNumWidth = 2;

    // If the aDegree is a proper number
    if ( Math::IsNaN(aDegrees) )
        {
        // The conversion can not be done, return NaN
        aDegreesString = KNan;
		return;
        }

    // Positive float of the degrees
    TReal64 realDegrees = aDegrees;
    // Integer part of the degrees
    TInt intDegrees = static_cast<TInt>(realDegrees);

    // Convert to positive values
    if ( intDegrees < 0 )
        {
        intDegrees = -intDegrees;
        realDegrees = -realDegrees;
        }

    // Minutes
    TReal64 realMinutes = (realDegrees - intDegrees) * KSecondsInMinute;
    TInt intMinutes = static_cast<TInt>(realMinutes);

    // Seconds
    TReal64 realSeconds = (realMinutes - intMinutes) * KSecondsInMinute;
    TInt intSeconds = static_cast<TInt>(realSeconds);

    // Check the sign of the result
    if ( aDegrees >= 0 )
        {
        aDegreesString.Append(KDelimPlus);
        }
    else
        {
        aDegreesString.Append(KDelimMinus);
        }

    // Add the degrees
    TInt64 value = intDegrees;
    aDegreesString.AppendNum(value);

    // Add the separator
    aDegreesString.Append(KDelimDegree);

    // Add the minutes
    value = intMinutes;
    aDegreesString.AppendNum(value);

    // Add the separator
    aDegreesString.Append(KApostrophe);

    // Add the seconds
    value = intSeconds;
    aDegreesString.AppendNum(value);

    // Add the separator
    aDegreesString.Append(KDelimDot);

    // Get six last digits
    realSeconds -= intSeconds;

	// Arrotonda
	Math::Round(realSeconds, realSeconds, KNumWidth);
    realSeconds *= 1000;

    // Add the seconds
    aDegreesString.AppendNumFixedWidth(static_cast<TInt>(realSeconds), EDecimal, KNumWidth);

    // Add the separator
    aDegreesString.Append(KDelimQuot);
}
