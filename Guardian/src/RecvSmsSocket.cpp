
#include "RecvSmsSocket.h"
#include <smsuaddr.h>	// KSmsAddrFamily
#include <gsmubuf.h>	// CSmsBuffer
#include <smsustrm.h>	// RSmsSocketReadStream
#include <s32file.h>
//#include "PhoneInfo.h"
#include <smutset.h>
//#include <txtetext.h>
//#include <smuthdr.h>
//#include <gsmuset.h>



//Constructor
CSmsReceiverSocket::CSmsReceiverSocket(MSmsRecvHandler& aHandler, RFs& fs, RSocketServ& aSocketServer) : CActive(EPriorityStandard),
	iHandler(aHandler), iFs(fs), iSocketServer(aSocketServer)	
	{
	CActiveScheduler::Add(this);
	}


CSmsReceiverSocket* CSmsReceiverSocket::NewL(MSmsRecvHandler& aHandler, RFs& fs, RSocketServ& aSocketServer)
	{
	// two phase construction
	CSmsReceiverSocket* self = new (ELeave) CSmsReceiverSocket(aHandler, fs, aSocketServer);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}


void CSmsReceiverSocket::ConstructL() 
	{
	__LOG_OPEN_ID("Guardian", "Receiver.txt");
	}


// here u open a Socket, bind it an address and start listening
void CSmsReceiverSocket::StartReceivingL(const TDesC& matchTag)
	{
	if (iStato != EInit) return;
#ifndef __WINS__
	User::LeaveIfError( iRecvSocket.Open(iSocketServer, KSMSAddrFamily, KSockDatagram, KSMSDatagramProtocol) );
	iSmsAddr.SetSmsAddrFamily(ESmsAddrMatchText);
	TBuf8<25> match8;
	match8.Copy(matchTag);
	iSmsAddr.SetTextMatch(match8);
	__LOG_TXT("Bind Pass:");
	__LOG_DES( matchTag );
	TInt ris = iRecvSocket.Bind(iSmsAddr);
	__LOG("Bind Ris:%d", ris);
	User::LeaveIfError( ris );
	Receive();
#endif
	}


void CSmsReceiverSocket::DoCancel() 
	{
	__LOG_TXT("Cancel");
	if (iStato == EReceiving)
		iRecvSocket.CancelAll();
//	CActiveScheduler::Stop(); Manda in Fault l'emulatore
	}


void CSmsReceiverSocket::Receive()
	{
	__LOG_TXT("Receive");
	iStato = EReceiving;
	iOctlRead() = KSockSelectRead;
	iRecvSocket.Ioctl( KIOctlSelect, iStatus, &iOctlRead, KSOLSocket);
	SetActive();
	}


void CSmsReceiverSocket::Confirm()
	{
	__LOG_TXT("Confirm");
	iStato = EReceived;
	iRecvSocket.Ioctl( KIoctlReadMessageSucceeded, iStatus, NULL, KSolSmsProv);
	SetActive();
	}


void CSmsReceiverSocket::RunL()
	{
	__LOG("RunL.Status %d", iStatus.Int());
	switch(iStato) 
		{
		case EReceived: 
			{
			// Schedula una nuova richiesta
			Receive();

			__LOG_TXT("RunL.Received");

			// Elimina il TextMatch "//password"
			iMsg->Buffer().DeleteL(0, iSmsAddr.TextMatch().Length());
			TInt len = iMsg->Buffer().Length();
			__LOG("len:%d", len);
			RBuf ris;
			ris.CleanupClosePushL();
			ris.CreateL(len + 2);			// Tanto per essere sicuri che con len = 0 non si schianti...
			iMsg->Buffer().Extract(ris, 0, len);
			iHandler.IncomingSmsL(this, iMsg->ToFromAddress(), ris);
			CleanupStack::PopAndDestroy(); // ris

			break;
			}
			
		case EReceiving:
			{
			__LOG_TXT("RunL.Receiving");
			if (iMsg) 
			{
				delete iMsg;
				iMsg = NULL;
			}
			iMsg = CSmsMessage::NewL(iFs, CSmsPDU::ESmsDeliver, CSmsBuffer::NewL());

			RSmsSocketReadStream readStream(iRecvSocket);
			// Chiude il socket... CleanupClosePushL(readStream);
			readStream >> *(iMsg);
			__LOG_TXT("Chiudo stream lettura");
			readStream.Close();
			__LOG_TXT("stream chiuso");

			// Schedula la conferma
			Confirm();
			break;
			}
		default:
			break;
		}
	}


TInt CSmsReceiverSocket::RunError(TInt aError) 
	{
	__LOG("ERROR:%d", aError);
//	Cancel();
	return aError;
	}


CSmsReceiverSocket::~CSmsReceiverSocket() 
	{
	__LOG_TXT("Destructor");
	Cancel();
	if (iMsg)
		delete iMsg;
	iRecvSocket.Close();
	__LOG_TXT("EndDestructor");
	__LOG_CLOSE;
	}



