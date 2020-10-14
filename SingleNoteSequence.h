#ifndef SingleNoteSequence_h
#define SingleNoteSequence_h

#include "Sequence.h"
#include "Note.h"
/******************************************************************************
* Definitions
******************************************************************************/

class SingleNoteSequence : public Sequence
{

public:
	SingleNoteSequence(Note *);
	~SingleNoteSequence();

	bool hasNext();
	void restart();
	void next();
	int length();


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
