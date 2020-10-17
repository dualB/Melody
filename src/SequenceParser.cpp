#include "SequenceParser.h"

#include "SimpleSequence.h"
#include "SingleNoteSequence.h"
#include "EmptySequence.h"
#include "RealNote.h"
#include "Modifier.h"
#include "ModifierDuration.h"
#include "ModifierRepetition.h"
#include "ModifierIntensity.h"
#include "ModifierIndex.h"

static RealNote *noteA = new RealNote(0, false);
static RealNote *noteB = new RealNote(2, false);
static RealNote *noteC = new RealNote(-9, false);
static RealNote *noteD = new RealNote(-7, false);
static RealNote *noteE = new RealNote(-5, false);
static RealNote *noteF = new RealNote(-4, false);
static RealNote *noteG = new RealNote(-2, false);
static RealNote *rest = new RealNote(0, true);

SequenceParser::SequenceParser()
{
}

Sequence *SequenceParser::parse(Stream *stream)
{

    Sequence *Sequence = parseSequence(stream);
    while (stream->available())
    {
        stream->read();
    }
    if (Sequence->length() == 0)
    {
        return new EmptySequence();
    }
    return Sequence;
}
Sequence *SequenceParser::parse(char *text)
{
    return parse(new StreamOfCharArray(text));
}

Sequence *SequenceParser::parseSequence(Stream *stream)
{

    SimpleSequence *Sequence = new SimpleSequence();

    bool keep = true;
    while (keep)
    {

        parseWS(stream);
        if (isName(stream->peek()))
        {
            Sequence->addSequence(parseNote(stream));
        }
        else if (isGroupBegin(stream->peek()))
        {
            Sequence->addSequence(parseGroup(stream));
        }
        else
        {
            keep = false;
        }
    }

    return Sequence;
}

void SequenceParser::parseWS(Stream *stream)
{
    while (isWS(stream->peek()))
    {
        stream->read();
    }
}

Sequence *SequenceParser::parseGroup(Stream *stream)
{
    stream->read(); // Should be '('
    Sequence *sequence = parseSequence(stream);
    parseWS(stream);
    if (isGroupEnd(stream->peek()))
    {
        //ok
        stream->read();
    }
    else
    {
        return sequence; //problem..
    }
    parseWS(stream);
    if (isModifier(stream->peek()))
    {
        return parseModifier(stream, sequence);
    }
    else
    {
        return sequence;
    }
}

Sequence *SequenceParser::parseNote(Stream *stream)
{
    SingleNoteSequence *snm = new SingleNoteSequence(noteOf(stream->read()));

    parseWS(stream);
    if (isModifier(stream->peek()))
    {

        return parseModifier(stream, snm);
    }
    else
    {
        return snm;
    }
}
Sequence *SequenceParser::parseModifier(Stream *stream, Sequence *original)
{
    Sequence *cur = original;

    while (isModifier(stream->peek()))
    {
        char c = stream->read();
        switch (c)
        {
        case SYMBOL_SEMITONE_UP:
        case SYMBOL_SEMITONE_DOWN:

            cur = new ModifierIndex(c == SYMBOL_SEMITONE_UP ? +1 : -1, cur);
            break;
        case SYMBOL_OCTAVE_UP:
        case SYMBOL_OCTAVE_DOWN:

            cur = new ModifierIndex(c == SYMBOL_OCTAVE_UP ? +12 : -12, cur);
            break;
        case SYMBOL_DURATION_DOUBLE:
        case SYMBOL_DURATION_HALF:
        case SYMBOL_DURATION_THREE_HALF:

            cur = new ModifierDuration(c == SYMBOL_DURATION_THREE_HALF ? 3 : c == SYMBOL_DURATION_DOUBLE ? 2 : 1,
                                       c == SYMBOL_DURATION_THREE_HALF ? 2 : c == SYMBOL_DURATION_DOUBLE ? 1 : 2,
                                       cur);
            break;
        case SYMBOL_DYNAMICS_PIANO:
        case SYMBOL_DYNAMICS_FORTE:
            cur = new ModifierIntensity(c == SYMBOL_DYNAMICS_FORTE ? +1 : -1, cur);
            break;
        case SYMBOL_REPEAT_BEGIN_UPPERCASE:
        case SYMBOL_REPEAT_BEGIN_LOWERCASE:
            cur = parseRepetition(stream, cur);
            break;
        case SYMBOL_DURATION_TUPLETS_BEGIN:
            cur = parseTuplet(stream, cur);
            break;
        }
        parseWS(stream);
    }

    return cur;
}

Sequence *SequenceParser::parseTuplet(Stream *stream, Sequence *original)
{
    parseWS(stream);
    unsigned int denominateur = parseInteger(stream);
    parseWS(stream);
    if (stream->peek() != SYMBOL_DURATION_TUPLETS_SEPARATOR)
    {
        return original;
    }
    else
    {
        stream->read();
    }
    parseWS(stream);
    unsigned int numerateur = parseInteger(stream);

    return new ModifierDuration(numerateur, denominateur, original);
}
Sequence *SequenceParser::parseRepetition(Stream *stream, Sequence *original)
{
    parseWS(stream);
    unsigned int repetition = parseInteger(stream);
    return new ModifierRepetition(repetition, original);
}
unsigned int SequenceParser::parseInteger(Stream *stream)
{

    unsigned int number = 0;
    while (isNumber(stream->peek()))
    {
        number *= 10;
        number += (int)(stream->read() - '0');
    }

    return number;
}

bool SequenceParser::isWS(char c)
{
    return c == SYMBOL_WHITESPACE_SPACE ||
           c == SYMBOL_WHITESPACE_LINEFEED ||
           c == SYMBOL_WHITESPACE_CARRIAGE_RETURN ||
           c == SYMBOL_WHITESPACE_HORIZONTAL_TAB ||
           c == SYMBOL_WHITESPACE_HORIZONTAL_BAR;
}

bool SequenceParser::isName(char c)
{
    return c == SYMBOL_NOTE_A_UPPERCASE || c == SYMBOL_NOTE_A_LOWERCASE ||
           c == SYMBOL_NOTE_B_UPPERCASE || c == SYMBOL_NOTE_B_LOWERCASE ||
           c == SYMBOL_NOTE_C_UPPERCASE || c == SYMBOL_NOTE_C_LOWERCASE ||
           c == SYMBOL_NOTE_D_UPPERCASE || c == SYMBOL_NOTE_D_LOWERCASE ||
           c == SYMBOL_NOTE_E_UPPERCASE || c == SYMBOL_NOTE_E_LOWERCASE ||
           c == SYMBOL_NOTE_F_UPPERCASE || c == SYMBOL_NOTE_F_LOWERCASE ||
           c == SYMBOL_NOTE_G_UPPERCASE || c == SYMBOL_NOTE_G_LOWERCASE ||
           c == SYMBOL_NOTE_REST_UPPERCASE || c == SYMBOL_NOTE_REST_LOWERCASE;
}

bool SequenceParser::isGroupBegin(char c)
{
    return c == SYMBOL_GROUP_BEGIN;
}
bool SequenceParser::isGroupEnd(char c)
{
    return c == SYMBOL_GROUP_END;
}

bool SequenceParser::isNumber(char c)
{
    return isdigit(c);
}
bool SequenceParser::isModifier(char c)
{
    return c == SYMBOL_SEMITONE_UP || c == SYMBOL_SEMITONE_DOWN ||
           c == SYMBOL_OCTAVE_UP || c == SYMBOL_OCTAVE_DOWN ||
           c == SYMBOL_DURATION_DOUBLE || c == SYMBOL_DURATION_HALF || c == SYMBOL_DURATION_THREE_QUARTER ||
           c == SYMBOL_DURATION_TUPLETS_BEGIN ||
           c == SYMBOL_DYNAMICS_PIANO || c == SYMBOL_DYNAMICS_FORTE ||
           c == SYMBOL_REPEAT_BEGIN_UPPERCASE || c == SYMBOL_REPEAT_BEGIN_LOWERCASE;
}

Note *SequenceParser::noteOf(char c)
{

    switch (c)
    {
    case SYMBOL_NOTE_A_UPPERCASE:
    case SYMBOL_NOTE_A_LOWERCASE:
        return noteA;
    case SYMBOL_NOTE_B_UPPERCASE:
    case SYMBOL_NOTE_B_LOWERCASE:
        return noteB;
    case SYMBOL_NOTE_C_UPPERCASE:
    case SYMBOL_NOTE_C_LOWERCASE:
        return noteC;
    case SYMBOL_NOTE_D_UPPERCASE:
    case SYMBOL_NOTE_D_LOWERCASE:
        return noteD;
    case SYMBOL_NOTE_E_UPPERCASE:
    case SYMBOL_NOTE_E_LOWERCASE:
        return noteE;
    case SYMBOL_NOTE_F_UPPERCASE:
    case SYMBOL_NOTE_F_LOWERCASE:
        return noteF;
    case SYMBOL_NOTE_G_UPPERCASE:
    case SYMBOL_NOTE_G_LOWERCASE:
        return noteG;
    case SYMBOL_NOTE_REST_UPPERCASE:
    case SYMBOL_NOTE_REST_LOWERCASE:
    default:
        return rest;
    }
}