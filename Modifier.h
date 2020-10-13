#ifndef Modifier_h
#define Modifier_h

#include "Melody.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Modifier : public Melody
{

public:
	Modifier(Melody *melody = nullptr);
	void set(Melody *);
	Melody *get();

	bool hasNext() { return get()->hasNext(); };
	void restart() { get()->restart(); }
	void next() { get()->next(); };
	int length() { return get()->length(); };

	int getNoteIndex() { return get()->getNoteIndex(); }
	bool isRest() { return get()->isRest(); }
	unsigned int getDurationNumerator() { return get()->getDurationNumerator(); }
	unsigned int getDurationDenominator() { return get()->getDurationDenominator(); }
	int getIntensityIndex() { return get()->getIntensityIndex(); }

protected:
private:
	Melody *_base;
};

#endif
