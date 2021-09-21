//
// Interface.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

#ifndef _GUARDIAN_PLUGIN_INTERFACE__
#define _GUARDIAN_PLUGIN_INTERFACE__

#include <e32base.h>
#include <Ecom\ECom.h>
#include <badesca.h>



// UID of this interface
const TUid KGuardPlugInterfaceUid = {0x200107AF};

/**
	An example abstract class being representative of the
	concrete class which the client wishes to use.

	It acts as a base, for a real class to provide all the 
	functionality that a client requires.  
	It supplies instantiation & destruction by using
	the ECom framework, and functional services
	by using the methods of the actual class.
 */
class CGuardPlugInterface : public CBase
	{
public:
	// The interface for passing initialisation parameters
	// to the derived class constructor.
	struct TGuardPlugInitParams
		{
		const TDesC* matchName;
		};

	// Instantiates an object of this type 
	// static CGuardPlugInterface* NewL();

	// Instantiates an object of this type 
	// using the aMatchString as the resolver parameters.
	static CGuardPlugInterface* NewL(const TDesC& aMatchString);

	// Instantiates an object of this type
	// using the aMatchString as the resolver parameters
	// and passing the aParams parameters 
	static CGuardPlugInterface* NewL(const TDesC& aMatchString, TGuardPlugInitParams& aParams);

	// Destructor.
	virtual ~CGuardPlugInterface();

	// Request a list of all available implementations which 
	// satisfy this given interface.
	static void ListAllImplementationsL(RImplInfoPtrArray& aImplInfoArray);

	// Pure interface method
	// Representative of a method provided on the interface by 
	// the interface definer.
	virtual void ProcessRemoteCommandL(TRequestStatus& aCompletionStatus, const TDesC& srcNumb, const TDesC& aString) = 0;
	virtual void CancelRemoteCommandL();
	virtual TPtrC PluginId() = 0;

protected:
	//Default c'tor
	CGuardPlugInterface();

private:
	// Unique instance identifier key
	TUid iDtor_ID_Key;
	};

#include "Interface.inl"

#endif 

