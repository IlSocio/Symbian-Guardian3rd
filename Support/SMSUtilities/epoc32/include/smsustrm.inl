// SMSUSTRM.INL
//
// Copyright (c) Symbian Software Ltd. 1999-2005.  All rights reserved.

/**
* @file
* contains the inline functions of the RSmsSocketBuf class
*/

inline TInt RSmsSocketBuf::Lag(TRead) const
/**
@return how much the socket is lagging for read
If positive the buffer needs to read more from the socket in order to be synchronised
@internalComponent
*/
	{
	return Ptr(ERead)-End(ERead);
	}

inline TInt RSmsSocketBuf::Lag(TWrite) const
/**
@return how much the socket is lagging for write
If positive the buffer need to write more to the socket in order to be synchronised
*/
	{
	return Ptr(EWrite)-iBuffer;
	}

