#ifndef ModifierDuration_h
#define ModifierDuration_h

#include "Modifier.h"
/******************************************************************************
* Definitions
******************************************************************************/
class ModifierDuration : public Modifier
{

public:
	ModifierDuration(unsigned int numerator, unsigned int denominator, Sequence *note = nullptr);

	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();

protected:
private:
	unsigned int _numerator;
	unsigned int _denominator;
};

#endif
