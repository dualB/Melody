#ifndef Melody_h

#define Melody_h


#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Melody 
{

public:
	Melody();
	~Melody();
	virtual bool hasNext()=0;
	virtual void restart()=0;
	virtual Note* next()=0;

};

#endif
