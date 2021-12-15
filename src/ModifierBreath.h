#ifndef ModifierBreath_h
#define ModifierBreath_h

#include "Modifier.h"
/******************************************************************************
 * Definitions
 ******************************************************************************/
class ModifierBreath : public Modifier
{

public:
	ModifierBreath(unsigned int denom, Sequence *note = nullptr);
	bool hasNext();
	void restart();
	void next();
	int length();
	bool isRest() ;
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();

protected:

private:
	unsigned int _numerator;
	unsigned int _denominator;
	bool _isBreathingNow;
	bool _isTie;
};

#endif
