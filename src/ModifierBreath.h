#ifndef ModifierBreath_h
#define ModifierBreath_h

#include "Modifier.h"
/******************************************************************************
 * Definitions
 ******************************************************************************/
class ModifierBreath : public Modifier
{

public:
	ModifierBreath(unsigned int denom,unsigned int num, Sequence *note = nullptr);
	bool hasNext();
	void restart();
	void next();
	bool isRest();
	int isTieOrBreath();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();

protected:
private:
	unsigned int _numerator;
	unsigned int _denominator;
	bool _isBreathingNow;
};

#endif
