#ifndef __SRVERR_H__
#define __SRVERR_H__

#include <e32err.h>

const TInt KErrPassNotSet = 1;
const TInt KErrPassShort = 2;
const TInt KErrNumberNotSet = 3; 
const TInt KErrSimOnlyAvail  = 4; 
const TInt KErrSimAlreadyExists = 5;	// La sim che si tenta di registrare esiste gia'
const TInt KErrSimNotPresent = 6;		// Non e' presente una sim nel cell.
const TInt KErrMessageNotSet = 7;
const TInt KErrSameValue = 8;
const TInt KErrUidNotFound = 9;
const TInt KErrUidAlreadyExists = 10;

#endif

