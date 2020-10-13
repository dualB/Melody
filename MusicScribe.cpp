#include "MusicParser.h"

char _InComBuffer[2] = {};

MusicParser::MusicParser(Stream *stream, Print *debug)
{
	_stream = stream;
	_debug = debug;
	_current.duration = 0;
	_dots = 0;
	_silence = false;
	_current.frequency = 0;
	_InComBuffer[1] = '\0';
}
MusicParser::MusicParser(char *str, Print *debug)
{
	_stream = new StreamOfString(str);
	_debug = debug;
	_current.duration = 0;
	_dots = 0;
	_silence = false;
	_current.frequency = 0;
	_InComBuffer[1] = '\0';
}
bool MusicParser::hasNext()
{
	return decode();
}
Note MusicParser::next()
{
	_debug->print(_InComBuffer);
	_debug->print(" : ");
	_debug->print(_index);
	_debug->print(", d=");
	_debug->println(_current.duration);
	return _current;
}
bool MusicParser::decode()
{
	bool hasNote = false;
	_silence = false;
	while (_stream->available() && !hasNote)
	{
		char _cur = _stream->read();
		if (_cur == 'c' || _cur == 'C')
		{
			_InComBuffer[0] = _cur;
			_index = -9;
			hasNote = true;
		}
		else if (_cur == 'd' || _cur == 'D')
		{
			_InComBuffer[0] = _cur;
			_index = -7;
			hasNote = true;
		}
		else if (_cur == 'e' || _cur == 'E')
		{
			_InComBuffer[0] = _cur;
			_index = -5;
			hasNote = true;
		}
		else if (_cur == 'f' || _cur == 'F')
		{
			_InComBuffer[0] = _cur;
			_index = -4;
			hasNote = true;
		}
		else if (_cur == 'g' || _cur == 'G')
		{
			_InComBuffer[0] = _cur;
			_index = -2;
			hasNote = true;
		}
		else if (_cur == 'a' || _cur == 'A')
		{
			_InComBuffer[0] = _cur;
			_index = 0;
			hasNote = true;
		}
		else if (_cur == 'b' || _cur == 'B')
		{
			_InComBuffer[0] = _cur;
			_index = 2;
			hasNote = true;
		}
		else if (_cur == 'r' || _cur == 'R')
		{
			_InComBuffer[0] = _cur;
			_index = 0;
			_silence = true;
			hasNote = true;
		}
	}
	if (hasNote)
	{
		_current.duration = BASE_DURATION;
		_dots = 0;
		bool invalid = false;
		while (_stream->available() && !invalid)
		{
			char peek = _stream->peek();
			if (peek == '#')
			{
				_stream->read();
				_index++;
			}
			else if (peek == '|')
			{
				_stream->read();
				_index--;
			}
			else if (peek == '_')
			{
				_stream->read();
				_index -= 12;
			}
			else if (peek == '*')
			{
				_stream->read();
				_index += 12;
			}
			else if (peek == '+')
			{
				_stream->read();
				_current.duration *= 2;
			}
			else if (peek == '-')
			{
				_stream->read();
				_current.duration /= 2;
			}
			else if (peek == '.')
			{
				_stream->read();
				_dots++;
			}
			else
			{
				invalid = true;
			}
		}
	}

	int half = _current.duration / 2;
	for (int i = 0; i < _dots; i++)
	{
		_current.duration += half;
		half /= 2;
	}
	_current.frequency = getFrequency(_index);
	return hasNote;
}

unsigned int MusicParser::getFrequency(int index)
{
	if (_silence)
	{
		return 1;
	}
	const unsigned int frequenceDeBaseNote[] = {
		16,
		17,
		18,
		19,
		21,
		22,
		23,
		25,
		26,
		28,
		29,
		31,
		33,
		35,
		37,
		39,
		41,
		44,
		46,
		49,
		52,
		55,
		58,
		62,
		65,
		69,
		73,
		78,
		82,
		87,
		93,
		98,
		104,
		110,
		117,
		123,
		131,
		139,
		147,
		156,
		165,
		175,
		185,
		196,
		208,
		220,
		233,
		247,
		262,
		277,
		294,
		311,
		330,
		349,
		370,
		392,
		415,
		440,
		466,
		494,
		523,
		554,
		587,
		622,
		659,
		698,
		740,
		784,
		831,
		880,
		932,
		988,
		1047,
		1109,
		1175,
		1245,
		1319,
		1397,
		1480,
		1568,
		1661,
		1760,
		1865,
		1976,
		2093,
		2217,
		2349,
		2489,
		2637,
		2794,
		2960,
		3136,
		3322,
		3520,
		3729,
		3951,
		4186,
		4435,
		4699,
		4978,
		5274,
		5588,
		5920,
		6272,
		6645,
		7040,
		7459,
		7902,
		8372,
		8870,
		9397,
		9956,
		10548,
		11175,
		11840,
		12544,
		13290,
		14080,
		14917,
		15804,
		16744,
		17740,
		18795,
		19912,
		21096,

	};

	int finalIndex = index + 57;
	if (finalIndex < 0 || finalIndex >= 125)
	{
		return 1;
	}
	return frequenceDeBaseNote[finalIndex];
}