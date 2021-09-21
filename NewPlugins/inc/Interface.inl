//
// Interface.inl
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

// Set default to be first implementation found by resolver
_LIT8(KDefaultImplementation,"*");

inline CGuardPlugInterface::CGuardPlugInterface()
	{
	}

inline CGuardPlugInterface::~CGuardPlugInterface()
	{
	// Destroy any instance variables and then
	// inform the framework that this specific 
	// instance of the interface has been destroyed.
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}


inline void CGuardPlugInterface::CancelRemoteCommandL()
	{
	}


inline CGuardPlugInterface* CGuardPlugInterface::NewL(const TDesC& aMatchString)
	{
	// Set up some empty initialisation parameters
	TGuardPlugInitParams initParams;
	initParams.matchName = &aMatchString;
	return NewL(aMatchString, initParams);
	}


inline CGuardPlugInterface* CGuardPlugInterface::NewL(const TDesC& aMatchString, TGuardPlugInitParams& aParams)
	{
	TBuf8<30> aMatch8;
	aMatch8.Copy(aMatchString);

	// Set up the interface find for the default resolver.
	TEComResolverParams resolverParams;
	resolverParams.SetDataType(aMatch8);
	resolverParams.SetWildcardMatch(EFalse);		// Allow wildcard matching

	// The CreateImplementationL method will return the created item.
	TAny* interf = REComSession::CreateImplementationL(KGuardPlugInterfaceUid,
												_FOFF(CGuardPlugInterface, iDtor_ID_Key),
												&aParams,
												resolverParams);
	CGuardPlugInterface* ris = REINTERPRET_CAST(CGuardPlugInterface*, interf);
	return ris;
	}


inline void CGuardPlugInterface::ListAllImplementationsL(RImplInfoPtrArray& aImplInfoArray)
	{
	REComSession::ListImplementationsL(KGuardPlugInterfaceUid, aImplInfoArray);
	}


