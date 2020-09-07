#ifndef ModifierDuration_h
#define ModifierDuration_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierDuration : public Modifier
{

public:
	ModifierDuration(unsigned int numerator, unsigned int denominator);
	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensity();

protected:
private:
	unsigned int _numerator;
	unsigned int _denominator;
};

#endif
