#ifndef Sequence_h
#define Sequence_h


#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Sequence : public Note
{

public:
	Sequence();
	~Sequence();
	virtual bool hasNext()=0;
	virtual void restart()=0;
	virtual void next()=0;
	virtual int length()=0;
};

#endif
