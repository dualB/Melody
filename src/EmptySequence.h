#ifndef EmptySequence_h
#define EmptySequence_h

#include "Sequence.h"
#include "Note.h"

/******************************************************************************
* Definitions
******************************************************************************/

class EmptySequence : public Sequence
{

public:
	EmptySequence();
	~EmptySequence();
	
	bool hasNext();
	void restart();
	void next();
	int length();

	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensityIndex();



};

#endif
