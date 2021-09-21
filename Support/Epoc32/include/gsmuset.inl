// GSMUSET.INL
//
// Copyright (c) Symbian Software Ltd. 2003-2005.  All rights reserved.
//

/** @file
 */


inline TSmsDataCodingScheme::TSmsAlphabet TSmsUserDataSettings::Alphabet() const
/** Gets the Alphabet for the User Data.

@return Alphabet */
	{
	return iAlphabet;
	}

inline void TSmsUserDataSettings::SetAlphabet(TSmsDataCodingScheme::TSmsAlphabet aAlphabet)
/** Sets the Alphabet for the User Data.

@param aAlphabet Alphabet */
	{
	iAlphabet=aAlphabet;
	}

inline TBool TSmsUserDataSettings::TextCompressed() const
/** Tests if the message text is compressed.

@return True if the message text is compressed */
	{
	return iFlags&ESmsFlagCompressed;
	}

inline void TSmsUserDataSettings::SetTextCompressed(TBool aCompressed)

/** Sets if the message text is compressed.

@param aCompressed True if the message text is compressed */
	{
	iFlags=aCompressed? iFlags|ESmsFlagCompressed: iFlags&(~ESmsFlagCompressed);
	}

