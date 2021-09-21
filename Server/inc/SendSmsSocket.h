
/*
 Livello intermedio smsstack via RSocket (smsprot.prt)
*/

#ifndef __SENDSMSSOCKET_H__
#define __SENDSMSSOCKET_H__

#include <FuzzyByte\FileLogger.h>


#include <e32base.h>	// CActive
#include <es_sock.h>	// RSocket
#include <f32file.h>	// RFs
#include <gsmumsg.h>	// CSmsMessage
#include <smsuaddr.h>	// TSmsAddr
#include <MSVAPI.H>
#include <MTCLREG.H>
#include "splitmanager.h"
#include "queue.h"
#include <FuzzyByte\timeouttimer.h>

#define MAX_SEND_RETRY 10

//_LIT(KOutBoxDir, "Outbox\\");



class MSmsSendHandler
	{
	public:
		virtual void SmsSentL()=0;
		virtual void AllSmsWereSentL()=0;
	};


class CSmsSenderSocket : public CActive, public MMsvSessionObserver, public MTimeOutNotifier
	{

	enum TSendStatus
		{
		EIdle,
		ESending
		};

	public:
        virtual void TimerExpiredL(TAny* src);
		static CSmsSenderSocket* NewL(RSocketServ& aSocketServer, RFs& fs, MSmsSendHandler* aHandler, const TDesC& outPath);
		virtual ~CSmsSenderSocket();
		TInt ScheduleSendingSmsL(const TDesC& aNumber, const TDesC& aMessage, TBool split = ETrue);
		void ClearOutBox();
		void HandleSessionEventL(TMsvSessionEvent aEvent, TAny *aArg1, TAny *aArg2, TAny *aArg3);

	protected:
		static TInt CallBack_SendBadMessageL(TAny*);
		void ConstructL();

	private:
		TInt DoScheduleSendingSmsL(const TDesC& aNumber, const TDesC& aMessage, TSmsDataCodingScheme::TSmsAlphabet aAlphabet);
		CSmsSenderSocket(RSocketServ& aSocketServer, RFs& fs, MSmsSendHandler* aHandler, const TDesC& outPath);
		void GetScaL(RBuf& aSCA);
		void CleanNumber(TDes& aNumber);
		
	private: // from CActive
		TBool SendGoodMessageL();
		TInt SendBadMessageL();
		void RunL();
		TInt RunError(TInt aError);
		void DoCancel();
		void DoSendCurrentMessageL();
		//TBool FindFirstFile(const TDesC& aPattern, TDes& aFileName);

	private:
		RFs iFs;
		CQueue*	iGoodQueue;
		CQueue*	iBadQueue;
		RSocketServ* iSocketServer;
		MSmsSendHandler* iHandler;
		RBuf iOutBoxPath;	// 100
		RBuf iSca;			// 20
		RBuf iFileName;		// 100
		CPeriodic* iPeriodic;
		TSendStatus iStato;
		RSocket iSendSocket;				//own
		TPckgBuf<TUint> iOctlWrite;			//own
		CSplitManager* iSplitManager;		// own
		CTimeOutTimer* iTimer;
		__LOG_DECLARATION_MEMBER
	};


#endif

