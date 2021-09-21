
#include <ECom.h>
#include <EComErrorCodes.h>
#include <EComResolverParams.h>
#include <ImplementationInformation.h>
#include <PublicRegistry.h>

#include "PluginResolver.h"

CPlugResolver* CPlugResolver::NewL(MPublicRegistry& aRegistry)
	{
	return new(ELeave) CPlugResolver(aRegistry);
	}

CPlugResolver::~CPlugResolver()
	{
	if(iImplementationInfoArray)
		{
		iImplementationInfoArray->Reset();
		delete iImplementationInfoArray;
		}
	}

CPlugResolver::CPlugResolver(MPublicRegistry& aRegistry)
: CResolver(aRegistry)
	{
	// Do nothing here
	}

TUid CPlugResolver::IdentifyImplementationL(TUid aInterfaceUid, 
	const TEComResolverParams& aAdditionalParameters) const
	{
	RImplInfoArray& implementationsInfo = iRegistry.ListImplementationsL(aInterfaceUid);
	TUid found = KNullUid;
	if(implementationsInfo.Count())
		{
		found = Resolve(implementationsInfo, aAdditionalParameters);
		}
	return found;
	}

TUid CPlugResolver::Resolve(const RImplInfoArray& aImplementationsInfo, 
	const TEComResolverParams& aAdditionalParameters) const
	{
	// Loop through the implementations matching on type
	const TInt count = aImplementationsInfo.Count();
	for(TInt index = 0; index < count; ++index)
		{
		const CImplementationInformation& impData = *aImplementationsInfo[index];
		// As soon as we get a match on the datatype then return uid of the 
		// implementation found.
		if (Match(impData.DataType(),						// The Datatype of this implementation
				  aAdditionalParameters.DataType(),			// The type we are trying to find
				  aAdditionalParameters.IsWildcardMatch()))	// If wildcards should be used
			return impData.ImplementationUid();
		}

	return KNullUid;
	}

RImplInfoArray* CPlugResolver::ListAllL(TUid aInterfaceUid, 
	const TEComResolverParams& aAdditionalParameters) const
	{
	// Use the member var to create the array so that we get proper cleanup behaviour
	iImplementationInfoArray = new(ELeave) RImplInfoArray;
	RImplInfoArray* retList = iImplementationInfoArray;

	RImplInfoArray& fullList = iRegistry.ListImplementationsL(aInterfaceUid);

	const TBool useWildcards = aAdditionalParameters.IsWildcardMatch();
	const TDesC8& matchType = aAdditionalParameters.DataType();
	const TInt numImps = fullList.Count();
	for(TInt index = 0; index < numImps; ++index)
		{
		if(Match(fullList[index]->DataType(), matchType, useWildcards))
			{
			User::LeaveIfError(retList->Append(fullList[index]));
			}
		}

	// Reset the member variable because we are passing ownership back
	iImplementationInfoArray = NULL;
	return retList;
	}

TBool CPlugResolver::Match(const TDesC8& aImplementationType, 
	const TDesC8& aMatchType, 
	TBool aUseWildcards) const
	{
	TInt matchPos = KErrNotFound;

	_LIT8(dataSeparator, "||");
	const TInt separatorLength = dataSeparator().Length();

	// Look for the section separator marker '||'
	TInt separatorPos = aImplementationType.Find(dataSeparator);
	if(separatorPos == KErrNotFound)
		{
		// Match against the whole string
		if(aUseWildcards)
			matchPos = aImplementationType.Match(aMatchType);
		else
			matchPos = aImplementationType.Compare(aMatchType);
		}
	else
		{
		// Find the first section, up to the separator
		TPtrC8 dataSection = aImplementationType.Left(separatorPos);
		TPtrC8 remainingData = aImplementationType.Mid(separatorPos + separatorLength);
		// Match against each section in turn
		while(separatorPos != KErrNotFound)
			{
			// Search this section
			if(aUseWildcards)
				matchPos = dataSection.Match(aMatchType);
			else
				matchPos = dataSection.Compare(aMatchType);

			// If we found it then no need to continue, so return
			if(matchPos != KErrNotFound)
				return ETrue;

			// Move on to the next section
			separatorPos = remainingData.Find(dataSeparator);
			if(separatorPos != KErrNotFound)
				{
				dataSection.Set(remainingData.Left(separatorPos));
				remainingData.Set(remainingData.Mid(separatorPos + separatorLength));
				}
			else
				dataSection.Set(remainingData);
			}

		// Check the final part
		if(aUseWildcards)
			matchPos = dataSection.Match(aMatchType);
		else
			matchPos = dataSection.Compare(aMatchType);

		}
	return matchPos != KErrNotFound;
	}
