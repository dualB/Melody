#ifndef ModifierIntensity_h
#define ModifierIntensity_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierIntensity : public Modifier
{

public:
	ModifierIntensity(int deltaIntensity);
	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensity();

protected:
private:
	unsigned int _deltaIntensity;
};

#endif
