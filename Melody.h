#ifndef Melody_h
#define Melody_h

#include "Arduino.h"
#include "Sequence.h"
#include "SequenceParser.h"
#include "SimpleSequence.h"
#include "NoteToSound.h"

#define DEFAULT_TEMPO 120
/******************************************************************************
* Definitions
******************************************************************************/
class Melody
{

public:
	Melody();
	Melody(char *);
	Melody(char *,unsigned int);
	bool setTempo(unsigned int);
	unsigned int getTempo();
	bool setScore(char *);
	bool hasNext();
	void restart();
	void next();
	int length();
	int index();

	unsigned int getFrequency();
    unsigned long getDuration();
	int getLoudness();

private:
	unsigned int _tempo;
	unsigned int _base_duration;
	Sequence* _Sequence;
	int _index;
};

#endif
