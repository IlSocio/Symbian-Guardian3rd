

#ifndef WebRegister_H
#define WebRegister_H

#include <e32base.h>
#include <e32cons.h>
#include <e32uid.h>

// INCLUDES
#include <FuzzyByte\httpsession.h>
#include <FuzzyByte\httpengine.h>
#include <FuzzyByte\AsyncWaiter.h>


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


class CWebRegister : public CBase
    {
    public:
        static CWebRegister* NewL();
        static CWebRegister* NewLC();
		TInt SendRegistrationRequestL(TUint32 brandId, TDesC& licenseID, const TDesC8& customApplicationData, TDes& regCode, TResponseID& resp);
		void CancelRegistrationRequestL();

		TInt Connect();
		void Close();
		/**
        * ConstructL()
        * Perform the second phase construction of a CWebClientAppUi object.
        */
        void ConstructL();

        /**
        * CWebClientAppUi()
        * First phase construction of CWebClientAppUi.
        */
        CWebRegister();

        /**
        * ~CWebClientAppUi()
        * Destructor for CWebClientAppUi.
        */
        ~CWebRegister();

    private:
		TResponseID GetResponseStatus(const TDesC8& data);
		void GetResponseRegist(const TDesC8& data, TDes& regcode);


    private: // Data
		CHttpSession* 	   iSession;
        CHttpEngine*       iClient;
        CAsyncWaiter*	   iWaiter;
        RSocketServ		   iSocketServ;
        };

#endif // WEBCLIENTAPPUI_H

