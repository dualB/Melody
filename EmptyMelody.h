#ifndef EmptyMelody_h

#define EmptyMelody_h

#include "Melody.h"
#include "Note.h"

/******************************************************************************
* Definitions
******************************************************************************/

class EmptyMelody : public Melody
{

public:
	EmptyMelody();
	~EmptyMelody();
	
	bool hasNext();
	void restart();
	void next();
	int length();

	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensity();



};

#endif
