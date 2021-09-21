// NumericEdwin.cpp
//

#include "NumericEdwin.h"

TKeyResponse CNumericEdwin::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyResponse response = EKeyWasNotConsumed;
	if(aKeyEvent.iCode>='0' && aKeyEvent.iCode<='9')
        {
		response = CEikEdwin::OfferKeyEventL(aKeyEvent, aType);
		}
	return response;
	}

TCoeInputCapabilities CNumericEdwin::InputCapabilities() const
	{
	TCoeInputCapabilities cap = CEikEdwin::InputCapabilities();
	cap.SetCapabilities(TCoeInputCapabilities::EDialableCharacters);
	return cap;
	}
