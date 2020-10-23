#ifndef Streamer_h
#define Streamer_h

/******************************************************************************
* Definitions
******************************************************************************/
class Streamer
{
public:
    Streamer(char *str) : _str(str), _current(0), _length(0)
    {
        for (int i = 0; _str[i] != '\0'; i++)
        {
            _length++;
        }
    }
    int available() { return _length - _current; }
    int read() { return _current < _length ? _str[_current++] : -1; }
    int peek() { return _current < _length ? _str[_current] : -1; }

private:
    char *_str;
    unsigned int _current;
    unsigned int _length;
};

#endif
