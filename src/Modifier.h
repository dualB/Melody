#ifndef Modifier_h
#define Modifier_h

#include "Sequence.h"
/******************************************************************************
* Definitions
******************************************************************************/
class Modifier : public Sequence
{

public:
	Modifier(Sequence *Sequence = nullptr);
	void set(Sequence *);
	Sequence *get();

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
	Sequence *_base;
};

#endif
