// NumericEdwin.h
//

#ifndef NUMERICEDWIN_H
#define NUMERICEDWIN_H

#include <eikedwin.h>

/**
A very simple editor that accepts numeric chars only.
*/
class CNumericEdwin : public CEikEdwin
	{
public:
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TCoeInputCapabilities InputCapabilities() const;
	};

#endif // NUMERICEDWIN_H
