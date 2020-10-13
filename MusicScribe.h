#ifndef MusicParser_h
#define MusicParser_h

#define SYMBOLE_DIESE '#'
#define SYMBOLE_BEMOL '_'

#define SYMBOLE_UNE_DEMI '$'
#define SYMBOLE_UN_QUART '!'
#define SYMBOLE_TROIS_QUART '%'

#define BASE_DURATION 500

#include "Arduino.h"

struct Note
{

	unsigned int frequency;
	unsigned long duration;
};

/******************************************************************************
* Definitions
******************************************************************************/
class MusicParser
{

public:
	MusicParser(char *str, Print *debug=nullptr);
	MusicParser(Stream *stream, Print *debug=nullptr);

	bool hasNext();
	Note next();

protected:
	unsigned int getFrequency(int);

private:
	class StreamOfString : public Stream //Inspired by
	{
	public:
		StreamOfString(char *str) : string(str), _cur(0), _length(0)
		{
			for (int i = 0; str[i] != '\0'; i++)
			{
				_length++;
			}
		}
		 int available() { return _length - _cur; }
		 int read() { return _cur < _length ? string[_cur++] : -1; }
		 int peek() { return _cur < _length ? string[_cur] : -1; }
		 void flush(){};
		 size_t write(uint8_t c)
		{
			return 0;
		};

	private:
		char *string;
		unsigned int _cur;
		unsigned int _length;
	}; // definition of nested class
	Stream *_stream;
	Print *_debug;
	unsigned int _dots;
	bool _silence;
	int _index;
	Note _current;
	bool decode();
};

#endif
