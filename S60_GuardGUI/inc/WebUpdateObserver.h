#ifndef __WebUpdateObserver_H
#define __WebUpdateObserver_H

#include <e32base.h>
#include <e32cons.h>
#include <e32uid.h>



/*
  enum TResponseID
		{
		EErrNone,
		EGenericError,						// Da Gestire... "Errore Generico"
        EInvalidIMEI,
        ESoftwareIDNotFound,
        ELicenseIDNotActivated,
        ELicenseIDHasDifferentSoftware,
        ELicenseIDNotFound,					// Da Gestire... "LicenseID non valido"
        ELicenseIDHasDifferentIMEI,			// Da Gestire... "LicenseID gia' registrato"
        EBannedFor10Minutes,				// Da Gestire... "Troppe richieste, riprovare piu' tardi"
        EUnknownDataReceived,				// Da Gestire... "Errore nella risposta del server, riprovare piu' tardi"
		ETransmissionError,					// Da Gestire... "Errore nella comunicazione, riprovare piu' tardi"
		EMaxResponseId
		};



class MWebUpdateObserver 
    {
    public:
        virtual void GotErrorResponseL( const TResponseID response, const TDesC& messsage ) = 0;
        virtual TBool GotRegCodeL( const TDesC& aRegCode ) = 0;
	};*/


#endif

