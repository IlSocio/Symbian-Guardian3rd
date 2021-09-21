#ifndef __LOGENGINEOBS_H__
#define __LOGENGINEOBS_H__

// INCLUDE FILES
#include <logwrap.h>

// CLASS DECLARATION
class MLogEngineObserver
	{
public:
	virtual void NotifyEventReadL(const CLogEvent& aEvent) = 0;
	};

#endif

// End of file
