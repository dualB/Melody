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
	Note *next();

public:
	Note *_note;
	bool _played;
};

#endif
