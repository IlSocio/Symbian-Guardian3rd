// GPRSSettings.h
//
// Copyright (C) Symbian Ltd 2000-2005. All rights reserved.
//

#ifndef __GPRSSETTINGS_H__
#define __GPRSSETTINGS_H__

#include "CommonSettings.h"
#include "internet.hrh"


/**
 * This class holds settings for a GPRS IAP.
 * @internalComponent
 */
class CGPRSSettings : public CCommonSettings
	{
	public:
		CGPRSSettings();
		virtual ~CGPRSSettings();
		virtual TBool HasGatewayAndNetmask();
		static TInt GetBearerIndexIntL(CMDBSession* aDatabase);
	protected: // From CCommonSettings
		const TPtrC GetTableName() const;
		const TPtrC GetBearerName() const;
		TInt GetBearerIndexL(CMDBSession* aDatabase) const;
		void DoWriteToDatabaseL(CMDBSession* aDatabase, CCDIAPRecord* aTable);
		void DoReadFromDatabaseL(CMDBSession* aDatabase, CCDIAPRecord* aTable);
		void ReadDefaultsL();
	public:
		void SetUserPwdRequired(TBool aFlag);
		void SetAddress(const TDesC& aAddress);
		TBool GetUserPwdRequired() const;
		const TDesC& GetAddress() const;
	private:
		TBuf<KMaxMedTextLength> iAccessPointName;
		TBool	iUserPwdRequired;
	};

#endif //__GPRSSETTINGS_H__
