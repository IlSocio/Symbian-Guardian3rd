
#include "NumericSecreted.h"

TKeyResponse CNumericSecreted::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyResponse response = EKeyWasNotConsumed;
	if(aKeyEvent.iCode>='0' && aKeyEvent.iCode<='9')
        {
		response = CEikSecretEditor::OfferKeyEventL(aKeyEvent, aType);
		}
	return response;
	}

TCoeInputCapabilities CNumericSecreted::InputCapabilities() const
	{
	TCoeInputCapabilities cap = CEikSecretEditor::InputCapabilities();
	cap.SetCapabilities(TCoeInputCapabilities::EDialableCharacters);
	return cap;
	}
