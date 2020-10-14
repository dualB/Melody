#ifndef ModifierRepetition_h
#define ModifierRepetition_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierRepetition : public Modifier
{

public:
	ModifierRepetition(unsigned int, Sequence *note = nullptr);
	 bool hasNext();
	 void restart();
	 void next();
	 int length();
protected:
private:
	unsigned int _times;
	unsigned int _count;
};

#endif
