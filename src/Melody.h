#ifndef Melody_h
#define Melody_h

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
	Melody(char *);
	Melody(char *, unsigned int);
	Melody(String);
	Melody(String, unsigned int);
	bool setTempo(unsigned int);
	bool setScore(char *);
	bool setScore(String);
	unsigned int getTempo();
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
	Sequence *_Sequence;
	int _index;
	
};

#endif
