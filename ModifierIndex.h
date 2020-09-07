#ifndef ModifierIndex_h
#define ModifierIndex_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierIndex : public Modifier
{

public:
	ModifierIndex(int deltaIndex);
	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensity();

protected:
private:
	unsigned int _deltaIndex;
};

#endif
