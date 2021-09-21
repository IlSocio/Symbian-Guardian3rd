// SMSUSTRM.INL
//
// Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.

/**
* @file SMSUSTRM.INL
* contains the inline functions of the RSmsSocketBuf class
*/

inline TInt RSmsSocketBuf::Lag(TRead) const
/**
@return how much the socket is lagging for read
If positive the buffer needs to read more from the socket in order to be synchronised
@publishedAll
@released
*/
	{
	return Ptr(ERead)-End(ERead);
	}

inline TInt RSmsSocketBuf::Lag(TWrite) const
/**
@return how much the socket is lagging for write
If positive the buffer need to write more to the socket in order to be synchronised
@publishedAll
@released
*/
	{
	return Ptr(EWrite)-iBuffer;
	}

