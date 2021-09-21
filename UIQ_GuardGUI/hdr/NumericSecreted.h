// NumericEdwin.h
//

#ifndef NUMERICSECRETED_H
#define NUMERICSECRETED_H

#include <EIKSECED.H>
 
/**
A very simple editor that accepts numeric chars only.
*/
class CNumericSecreted : public CEikSecretEditor
	{
public:
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TCoeInputCapabilities InputCapabilities() const;
	};

#endif // NUMERICEDWIN_H
