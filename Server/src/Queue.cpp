/*
 ============================================================================
 Name		: Queue.cpp
 Author	  : Marco Bellino
 Version	 : 1.0
 Copyright   : Guardian-Mobile
 Description : CQueue implementation
 ============================================================================
 */

#include "Queue.h"

CQueue::CQueue()
	{
	// No implementation required
	} 

CQueue::~CQueue()
	{
	Clear();
	iQueue.Close();
	}

CQueue* CQueue::NewLC()
	{
	CQueue* self = new (ELeave)CQueue(); 
	CleanupStack::PushL(self);
	self->ConstructL();  
	return self;
	}

CQueue* CQueue::NewL()
	{
	CQueue* self=CQueue::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CQueue::ConstructL()
	{

	}


void CQueue::EnqueueL(const TDesC& filename)
	{
	HBufC* buf = filename.AllocL();
	iQueue.Append( buf );
	}


HBufC* CQueue::Dequeue()
	{
	if (iQueue.Count() <= 0)
		return NULL;
	HBufC* buf = iQueue[0];
	iQueue.Remove(0);
	return buf;
	}


void CQueue::Clear()
	{
	HBufC* buf = NULL;
	while ((buf = Dequeue()) != NULL)
		{
		delete buf;
		buf = NULL;
		}
	}



