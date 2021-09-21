/*
 ============================================================================
 Name		: SplitManager.cpp
 Author	  : Marco Bellino
 Version	 : 1.0
 Copyright   : Guardian-Mobile
 Description : CSplitManager implementation
 ============================================================================
 */

#include "SplitManager.h"

CSplitManager::CSplitManager(RFs& fs) : CBase(), iFs(fs)
	{
	// No implementation required
	}

CSplitManager::~CSplitManager()
	{
	if (iConverter)
		delete iConverter;
	}

CSplitManager* CSplitManager::NewLC(RFs& fs)
	{
	CSplitManager* self = new (ELeave)CSplitManager(fs);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSplitManager* CSplitManager::NewL(RFs& fs)
	{
	CSplitManager* self=CSplitManager::NewLC(fs);
	CleanupStack::Pop(); // self;
	return self;
	}

void CSplitManager::ConstructL()
	{
	SetBuffer(TPtrC(), ETrue);
	iConverter = CCnvCharacterSetConverter::NewL();
	iConverter->PrepareToConvertToOrFromL( KCharacterSetIdentifierSms7Bit, iFs );
	}


void CSplitManager::SetBuffer(const TDesC& buffer, TBool split)
	{
	iSplit = split;
	iBufferLeft.Set( buffer );
	iCurrentMsg.Set( TPtrC() );
	}


TBool CSplitManager::MoveNextL()
	{
	if (iBufferLeft.Length() <= 0)
		{
		iCurrentMsg.Set( TPtrC() );
		return EFalse;
		}
	
	if (!iSplit)
		{
		iCurrentMsg.Set( iBufferLeft );
		
		RBuf8 buf7Bit;
		buf7Bit.CleanupClosePushL();
		buf7Bit.Create( iCurrentMsg.Length() * 2 );
		
		TInt totUnconv = 0;
		TInt posUnconv = 0;
		TInt res = iConverter->ConvertFromUnicode(buf7Bit, iCurrentMsg, totUnconv, posUnconv);
		iAlphabet = TSmsDataCodingScheme::ESmsAlphabet7Bit;
		if (totUnconv > 0 || res != 0)
			iAlphabet = TSmsDataCodingScheme::ESmsAlphabetUCS2;
		
		CleanupStack::PopAndDestroy(); // buf7Bit		
		iBufferLeft.Set( iBufferLeft.Mid(iCurrentMsg.Length()) );
		return ETrue;
		}
	
	iCurrentMsg.Set( iBufferLeft.Left(160) );
	
	RBuf8 buf7Bit;
	buf7Bit.CleanupClosePushL();
	buf7Bit.Create( iCurrentMsg.Length() * 2 );
	
	TInt totUnconv = 0;
	TInt posUnconv = 0;
	TInt res = iConverter->ConvertFromUnicode(buf7Bit, iCurrentMsg, totUnconv, posUnconv);
	
	iAlphabet = TSmsDataCodingScheme::ESmsAlphabet7Bit;	
	if (posUnconv < 70 && totUnconv > 0)
		{
		iAlphabet = TSmsDataCodingScheme::ESmsAlphabetUCS2;
		iCurrentMsg.Set( iCurrentMsg.Left(70) );
		}
	if (posUnconv >= 70)
		{
		iCurrentMsg.Set( iCurrentMsg.Left(posUnconv) );
		buf7Bit.Zero();
		res = iConverter->ConvertFromUnicode(buf7Bit, iCurrentMsg, totUnconv, posUnconv);
		// Aggiorna buf7Bit, in modo da evitare situazioni in cui c'e' un carattere che non si converte nella posizione 80 e buf7Bit sfora...		
		}
	
	// Fit in 160...
	TInt overflowChars = buf7Bit.Length() - 160;
	if (iAlphabet == TSmsDataCodingScheme::ESmsAlphabet7Bit && overflowChars > 0)
	{
		// come minimo bisogna rimuovere la meta' di overflowChars... 
		// rimuoverli tutti potrebbe essere eccessivo.
		TInt charsToRemove = (overflowChars / 2);
		do 
		{	
			charsToRemove++;
			TPtrC msgToRemove( iCurrentMsg.Right(charsToRemove) );
			buf7Bit.Zero();
			iConverter->ConvertFromUnicode(buf7Bit, msgToRemove, totUnconv, posUnconv);
		} while (buf7Bit.Length() < overflowChars);
		iCurrentMsg.Set( iCurrentMsg.Left( iCurrentMsg.Length() - charsToRemove) );
	}
	
	CleanupStack::PopAndDestroy(); // buf7Bit
	iBufferLeft.Set( iBufferLeft.Mid(iCurrentMsg.Length()) );
	return ETrue;
	}


void CSplitManager::GetCurrent(TPtrC& aMessage, TSmsDataCodingScheme::TSmsAlphabet& aAlphabet)
	{
	aMessage.Set( iCurrentMsg );
	aAlphabet = iAlphabet;
	}
