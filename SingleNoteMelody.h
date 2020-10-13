#ifndef SingleNoteMelody_h

#define SingleNoteMelody_h

#include "Melody.h"
#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/

class SingleNoteMelody : public Melody
{

public:
	SingleNoteMelody(Note *);
	~SingleNoteMelody();

	bool hasNext();
	void restart();
	void next();
	int length() ;
	
	int getNoteIndex();
	bool isRest();
	unsigned int getDurationNumerator();
	unsigned int getDurationDenominator();
	int getIntensityIndex();

public:
	Note *_note;
	bool _hasNext;

};

#endif
