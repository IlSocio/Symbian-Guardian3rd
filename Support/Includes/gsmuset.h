// GSMUSET.H
//
// Copyright (c) Symbian Software Ltd. 1999-2005.  All rights reserved.
//
/**@file
This file contains the class definition for TSmsUserDataSettings
@publishedAll
@released
*/

#ifndef __GSMUSET_H__
#define __GSMUSET_H__

#include "gsmuelem.h"

class TSmsUserDataSettings
/** Operations on TP-UD User Data. */
	{
public:
	IMPORT_C TSmsUserDataSettings::TSmsUserDataSettings();

	inline TSmsDataCodingScheme::TSmsAlphabet Alphabet() const;
	inline void SetAlphabet(TSmsDataCodingScheme::TSmsAlphabet aAlphabet);
	inline TBool TextCompressed() const;
	inline void SetTextCompressed(TBool aCompressed);
	IMPORT_C TBool TextConcatenated(TBool* aIs16Bit=NULL) const;
	IMPORT_C void SetTextConcatenated(TBool aConcatenated,TBool aIs16Bit=EFalse);

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	enum TSmsUserDataSettingsFlags
		{
		ESmsFlagCompressed=0x01,
		ESmsFlagConcatenated=0x02,
		ESmsFlagConcatenatedUsing16BitReference=0x04
		};
private:	
	TSmsDataCodingScheme::TSmsAlphabet iAlphabet;
	TInt iFlags;
	};


#include "gsmuset.inl"

#endif // !defined __GSMUSET_H__
