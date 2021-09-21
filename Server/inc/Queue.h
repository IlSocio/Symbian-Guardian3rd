/*
 ============================================================================
 Name		: Queue.h
 Author	  : Marco Bellino
 Version	 : 1.0
 Copyright   : Guardian-Mobile
 Description : CQueue declaration
 ============================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
 *  CQueue
 * 
 */
class CQueue : public CBase
	{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CQueue();

	/**
	 * Two-phased constructor.
	 */
	static CQueue* NewL();

	/**
	 * Two-phased constructor.
	 */
	static CQueue* NewLC();
	
	void EnqueueL(const TDesC& filename);
	HBufC* Dequeue();
	void Clear();
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CQueue();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
private:
	RPointerArray<HBufC>	iQueue;
	};

#endif // QUEUE_H
