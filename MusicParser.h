#ifndef MusicParser_h
#define MusicParser_h

#include "Arduino.h"
#include "Melody.h"
#include "MelodyParser.h"
#include "SimpleMelody.h"
#include "MelodyToSound.h"

#define DEFAULT_TEMPO 120
/******************************************************************************
* Definitions
******************************************************************************/
class MusicParser
{

public:
	MusicParser();
	bool setTempo(unsigned int);
	unsigned int getTempo();
	bool setPartition(char *);
	bool hasNext();
	void restart();
	void next();
	int length();

	unsigned int getFrequency();
    unsigned long getDuration();
	int getLoudness();

private:
	unsigned int _tempo;
	unsigned int _base_duration;
	Melody* _melody;
};

#endif
