#ifndef ModifierIndex_h
#define ModifierIndex_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierIndex : public Modifier
{

public:
	ModifierIndex(int deltaIndex,Melody * note=nullptr);
	int getNoteIndex();

protected:
private:
	unsigned int _deltaIndex;
};

#endif
