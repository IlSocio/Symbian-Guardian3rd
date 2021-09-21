

#ifndef WebUpdate_H
#define WebUpdate_H

#include <e32base.h>
#include <e32cons.h>
#include <e32uid.h>
#include <f32file.h>
#include <FuzzyByte\FileLogger.h>
#include <FuzzyByte\httpengine.h>
#include <FuzzyByte\asyncwaiter.h>


// INCLUDES
//#include "WebClientObserver.h"

//class CWebClientEngine;


class CWebUpdate : public CBase //, private MWebClientObserver
    {
    public:
        static CWebUpdate* NewL();
        static CWebUpdate* NewLC();
        TInt Connect();
        void Close();
		TInt IsThereAnUpdatedVersionL(TUint32 isReg, TUint32 brandId, const TDesC& imei, TDes8& url, TBool& updateAvail);
		TInt DownloadUpdatedVersionL(const TDesC8& downloadURL, RFs& fs, const TDesC& filename);
		void CancelDownloadL();

		/**
        * ConstructL()
        * Perform the second phase construction of a CWebClientAppUi object.
        */
        void ConstructL();

        CWebUpdate();

        /**
        * ~CWebClientAppUi()
        * Destructor for CWebClientAppUi.
        */
        ~CWebUpdate();

    private:
		TInt GetResponseSize(const TDesC8& data);
		void GetResponseURL(const TDesC8& webData, TDes8& url);

//        void ClientEventL( const TWebClientEvents event, const TDesC& descr );
//		void ClientErrorL( const TInt error, const TDesC& aErrorData );
//        void ClientBodyReceivedL( const TDesC8& aBodyData );

    private: // Data
    	CHttpEngine*       iClient;
    	CAsyncWaiter*	   iWaiter;
    	CHttpSession* 	   iSession;
    	RSocketServ		   iSocketServ;
    	__LOG_DECLARATION_MEMBER
        };

#endif // WEBCLIENTAPPUI_H

