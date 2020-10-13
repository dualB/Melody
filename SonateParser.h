#ifndef SonateParser_h
#define SonateParser_h

#define SYMBOL_SEMITONE_UP '#'
#define SYMBOL_SEMITONE_DOWN ','

#define SYMBOL_OCTAVE_UP '*'
#define SYMBOL_OCTAVE_DOWN '_'

#define SYMBOL_GROUP_BEGIN '('
#define SYMBOL_GROUP_END ')'

#define SYMBOL_DURATION_DOUBLE '+'
#define SYMBOL_DURATION_HALF '-'
#define SYMBOL_DURATION_THREE_QUARTER '.'

#define SYMBOL_DURATION_TUPLETS_BEGIN '/'
#define SYMBOL_DURATION_TUPLETS_SEPARATOR ':'

#define SYMBOL_DYNAMICS_PIANO '>'
#define SYMBOL_DYNAMICS_FORTE '<'

#define SYMBOL_REPEAT_BEGIN_UPPERCASE 'X'
#define SYMBOL_REPEAT_BEGIN_LOWERCASE 'x'

#define SYMBOL_NOTE_A_UPPERCASE 'A'
#define SYMBOL_NOTE_A_LOWERCASE 'a'

#define SYMBOL_NOTE_B_UPPERCASE 'B'
#define SYMBOL_NOTE_B_LOWERCASE 'b'

#define SYMBOL_NOTE_C_UPPERCASE 'C'
#define SYMBOL_NOTE_C_LOWERCASE 'c'

#define SYMBOL_NOTE_D_UPPERCASE 'D'
#define SYMBOL_NOTE_D_LOWERCASE 'd'

#define SYMBOL_NOTE_E_UPPERCASE 'E'
#define SYMBOL_NOTE_E_LOWERCASE 'e'

#define SYMBOL_NOTE_F_UPPERCASE 'F'
#define SYMBOL_NOTE_F_LOWERCASE 'f'

#define SYMBOL_NOTE_G_UPPERCASE 'G'
#define SYMBOL_NOTE_G_LOWERCASE 'g'

#define SYMBOL_NOTE_REST_UPPERCASE 'R'
#define SYMBOL_NOTE_REST_LOWERCASE 'r'

#define SYMBOL_WHITESPACE_SPACE ' '
#define SYMBOL_WHITESPACE_LINEFEED '\n'
#define SYMBOL_WHITESPACE_CARRIAGE_RETURN '\r'
#define SYMBOL_WHITESPACE_HORIZONTAL_TAB '\t'

#include "Melody.h"
#include "Modifier.h"
#include "Stream.h"
#include "Arduino.h"
/******************************************************************************
* Definitions
******************************************************************************/
class SonateParser
{

public:
    SonateParser();
    Melody *parse(Stream *);
    Melody *parse(char *);

protected:
private:
    bool isWS(char);
    bool isModifier(char);
    bool isNumber(char);
    bool isNote(char);
    bool isName(char);
    bool isGroupBegin(char);
    bool isGroupEnd(char);

    Note *noteOf(char);
    Melody *parseMelody(Stream *);
    Melody *parseGroup(Stream *);
    Melody *parseNote(Stream *);
    Melody *parseModifier(Stream *, Melody *);
    Melody *parseRepetition(Stream *, Melody *);
    Melody *parseTuplet(Stream *, Melody *);

    unsigned int parseInteger(Stream *);
    void parseWS(Stream *);

    class StreamOfString : public Stream
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
    }; 
};

#endif
