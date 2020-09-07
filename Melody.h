#ifndef Melody_h

#define Melody_h


#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Melody 
{

public:
	virtual bool hasNext();
	virtual void restart();
	virtual Note next();

};

#endif
