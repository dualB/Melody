#include "MusicScribe.h"

char _InComBuffer[2] = {};

MusicScribe::MusicScribe(Stream *stream, Print *debug)
{
	_stream = stream;
	_debug = debug;
	_current.duration = 0;
	_current.dots = 0;
	_current.frequency = 0;
	_InComBuffer[1] = '\0';
}
bool MusicScribe::hasNext()
{
	return decode();
}
Note MusicScribe::next()
{
	_debug->print(_InComBuffer);
	_debug->print(" : ");
	_debug->print(_current.index);
	_debug->print(", d=");
	_debug->println(_current.duration);
	return _current;
}
bool MusicScribe::decode()
{
	bool hasNote = false;
	while (_stream->available() && !hasNote)
	{
		char _cur = _stream->read();
		if (_cur == 'c' || _cur == 'C')
		{
			_InComBuffer[0] = _cur;
			_current.index = -9;
			hasNote = true;
		}
		else if (_cur == 'd' || _cur == 'D')
		{
			_InComBuffer[0] = _cur;
			_current.index = -7;
			hasNote = true;
		}
		else if (_cur == 'e' || _cur == 'E')
		{
			_InComBuffer[0] = _cur;
			_current.index = -5;
			hasNote = true;
		}
		else if (_cur == 'f' || _cur == 'F')
		{
			_InComBuffer[0] = _cur;
			_current.index = -4;
			hasNote = true;
		}
		else if (_cur == 'g' || _cur == 'G')
		{
			_InComBuffer[0] = _cur;
			_current.index = -2;
			hasNote = true;
		}
		else if (_cur == 'a' || _cur == 'A')
		{
			_InComBuffer[0] = _cur;
			_current.index = 0;
			hasNote = true;
		}
		else if (_cur == 'b' || _cur == 'B')
		{
			_InComBuffer[0] = _cur;
			_current.index = 2;
			hasNote = true;
		}
	}
	if (hasNote)
	{
		_current.duration = 250;
		_current.dots = 0;
		bool invalid = false;
		while (_stream->available() && !invalid)
		{
			char peek = _stream->peek();
			if (peek == '#')
			{
				_stream->read();
				_current.index++;
			}
			else if (peek == '|')
			{
				_stream->read();
				_current.index--;
			}
			else if (peek == '_')
			{
				_stream->read();
				_current.index -= 12;
			}
			else if (peek == '*')
			{
				_stream->read();
				_current.index += 12;
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
				_current.dots++;
			}
			else
			{
				invalid = true;
			}
		}
	}

	int half = _current.duration / 2;
	for (int i = 0; i < _current.dots; i++)
	{
		_current.duration += half;
		half /= 2;
	}
	_current.frequency = 440 +10 * _current.index;
	return hasNote;
}
