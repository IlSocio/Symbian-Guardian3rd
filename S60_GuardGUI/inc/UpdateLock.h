/*
============================================================================
 Name        : UpdateLock.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : UpdateLock declaration
============================================================================
*/

#ifndef UPDATELOCK_H
#define UPDATELOCK_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

/**
*  UpdateLock
* 
*/
class UpdateLock
{
public: // Constructors and destructor
	static TBool NeedsUpdateL();
	static void DoneUpdateL();

private:
	static void WriteLastUpdateDayL(TInt day);
	static TInt32 ReadLastUpdateDayL();
};

#endif // UPDATELOCK_H
