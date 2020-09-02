#ifndef MusicScribe_h
#define MusicScribe_h

#define SYMBOLE_DIESE '#'
#define SYMBOLE_BEMOL '_'

#define SYMBOLE_UNE_DEMI '$'
#define SYMBOLE_UN_QUART '!'
#define SYMBOLE_TROIS_QUART '%'

#include "Arduino.h"

struct Note
{
	int index; 
	unsigned int frequency;
	unsigned int dots;
	unsigned long duration;
};

/******************************************************************************
* Definitions
******************************************************************************/
class MusicScribe
{

public:
	MusicScribe(Stream *stream,Print *debug);

	bool hasNext();
	Note next();

protected:
private:
	Stream* _stream;
	Print* _debug;
	Note _current;
	bool decode();
};

#endif
