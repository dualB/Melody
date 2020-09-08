#ifndef Melody_h

#define Melody_h


#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Melody : public Note
{

public:
	Melody();
	~Melody();
	virtual bool hasNext()=0;
	virtual void restart()=0;
	virtual void next()=0;
	virtual int length()=0;

};

#endif
