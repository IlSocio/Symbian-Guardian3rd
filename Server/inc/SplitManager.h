/*
 ============================================================================
 Name		: SplitManager.h
 Author	  : Marco Bellino
 Version	 : 1.0
 Copyright   : Guardian-Mobile
 Description : CSplitManager declaration
 ============================================================================
 */

#ifndef SPLITMANAGER_H
#define SPLITMANAGER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <gsmuelem.h>
#include <CHARCONV.H>


// CLASS DECLARATION

/**
 *  CSplitManager
 * 
 */
class CSplitManager : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CSplitManager();

	/**
	 * Two-phased constructor.
	 */
	static CSplitManager* NewL(RFs& fs);

	/**
	 * Two-phased constructor.
	 */
	static CSplitManager* NewLC(RFs& fs);
	
	void SetBuffer(const TDesC& buffer, TBool split);
		
	TBool MoveNextL();
	void GetCurrent(TPtrC& aMessage, TSmsDataCodingScheme::TSmsAlphabet& aAlphabet);
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CSplitManager(RFs& fs);

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

private:
	RFs& iFs;
	TPtrC iBufferLeft;
	TPtrC iCurrentMsg;
	TSmsDataCodingScheme::TSmsAlphabet iAlphabet;
	TBool iSplit;
	CCnvCharacterSetConverter* iConverter;
	};

#endif // SPLITMANAGER_H
