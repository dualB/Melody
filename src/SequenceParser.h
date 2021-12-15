#ifndef SequenceParser_h
#define SequenceParser_h

#define SYMBOL_SEMITONE_UP '#'
#define SYMBOL_SEMITONE_DOWN ','

#define SYMBOL_OCTAVE_UP '*'
#define SYMBOL_OCTAVE_DOWN '_'

#define SYMBOL_GROUP_BEGIN '('
#define SYMBOL_GROUP_END ')'

#define SYMBOL_DURATION_DOUBLE '+'
#define SYMBOL_DURATION_HALF '-'
#define SYMBOL_DURATION_THREE_HALF '.'

#define SYMBOL_INTERPRETATION_BREATH '!'
#define SYMBOL_INTERPRETATION_TIE '='

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
#define SYMBOL_WHITESPACE_HORIZONTAL_BAR '|'


#include "Sequence.h"
#include "Modifier.h"
#include "Streamer.h"

/******************************************************************************
* Definitions
******************************************************************************/
class SequenceParser
{

public:
    static Sequence *parse(Streamer *);
    static Sequence *parse(const char *);
    static Sequence *parse(String);

protected:
    SequenceParser();   
private:
    static bool isWS(char);
    static bool isModifier(char);
    static bool isNumber(char);
    static bool isNote(char);
    static bool isName(char);
    static bool isGroupBegin(char);
    static bool isGroupEnd(char);

    static Note *noteOf(char);
    static Sequence *parseSequence(Streamer *);
    static Sequence *parseGroup(Streamer *);
    static Sequence *parseNote(Streamer *);
    static Sequence *parseModifier(Streamer *, Sequence *);
    static Sequence *parseBreath(Streamer *, Sequence *);
    static Sequence *parseRepetition(Streamer *, Sequence *);
    static Sequence *parseTuplet(Streamer *, Sequence *);

    static unsigned int parseInteger(Streamer *);
    static void parseWS(Streamer *);

};

#endif
