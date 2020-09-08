#include "SonateParser.h"

#include "SimpleMelody.h"
#include "SingleNoteMelody.h"
#include "EmptyMelody.h"
#include "RealNote.h"
#include "Modifier.h"
#include "ModifierDuration.h"
#include "ModifierRepetition.h"
#include "ModifierIntensity.h"
#include "ModifierIndex.h"

SonateParser::SonateParser()
{
}

Melody *SonateParser::parse(Stream *stream)
{

    Melody *melody = parseMelody(stream);
    while (stream->available())
    {
        stream->read();
    }
    if (melody->length() == 0)
    {
        return new EmptyMelody();
    }
    return melody;
}
Melody *SonateParser::parse(char *text)
{
    return parse(new StreamOfString(text));
}

Melody *SonateParser::parseMelody(Stream *stream)
{

    SimpleMelody *melody = new SimpleMelody();

    bool keep = true;
    while (keep)
    {

        parseWS(stream);
        if (isName(stream->peek()))
        {
            melody->addMelody(parseNote(stream));
        }
        else if (isGroupBegin(stream->peek()))
        {
            Serial.println("IT A GROUP!");
            melody->addMelody(parseGroup(stream));
        }
        else
        {
            keep = false;
        }
    }

    return melody;
}

void SonateParser::parseWS(Stream *stream)
{
    while (isWS(stream->peek()))
    {
        Serial.print(" WS ");
        stream->read();
    }
}

Melody *SonateParser::parseGroup(Stream *stream)
{
    stream->read(); // Should be '('
    Melody *melody = parseMelody(stream);
    parseWS(stream);
    if (isGroupEnd(stream->peek()))
    {
        //ok
        Serial.println(")!");
        stream->read();
    }
    else
    {
        Serial.print(stream->peek());
        Serial.println("...problem!");
        return melody; //problem..
    }
    parseWS(stream);
    if (isModifier(stream->peek()))
    {
        return parseModifier(stream, melody);
    }
    else
    {
        return melody;
    }
}

Melody *SonateParser::parseNote(Stream *stream)
{
    SingleNoteMelody *snm = new SingleNoteMelody(noteOf(stream->read()));
    Serial.println("Parse note...");
    parseWS(stream);
    if (isModifier(stream->peek()))
    {
        Serial.print("trouvé ");
        Serial.print(isModifier(stream->peek()) ? " OUI  " : " NON ");
        Serial.println(stream->peek());
        return parseModifier(stream, snm);
    }
    else
    {
        return snm;
    }
}
Melody *SonateParser::parseModifier(Stream *stream, Melody *original)
{
    Melody *cur = original;
    Serial.println("Parse modifier...");

    while (isModifier(stream->peek()))
    {
        char c = stream->read();
        switch (c)
        {
        case SYMBOL_SEMITONE_UP:
        case SYMBOL_SEMITONE_DOWN:
            Serial.println("ICI index");
            cur = new ModifierIndex(c == SYMBOL_SEMITONE_UP ? +1 : -1, cur);
            break;
        case SYMBOL_OCTAVE_UP:
        case SYMBOL_OCTAVE_DOWN:
            Serial.println("ICI index oct");
            cur = new ModifierIndex(c == SYMBOL_OCTAVE_UP ? +12 : -12, cur);
            break;
        case SYMBOL_DURATION_DOUBLE:
        case SYMBOL_DURATION_HALF:
        case SYMBOL_DURATION_THREE_QUARTER:
            Serial.println("ICI duration");
            cur = new ModifierDuration(c == SYMBOL_DURATION_THREE_QUARTER ? 3 : c == SYMBOL_DURATION_DOUBLE ? 2 : 1,
                                       c == SYMBOL_DURATION_THREE_QUARTER ? 2 : c == SYMBOL_DURATION_DOUBLE ? 1 : 2,
                                       cur);
            break;
        case SYMBOL_DYNAMICS_PIANO:
        case SYMBOL_DYNAMICS_FORTE:
            Serial.println("ICI intensité");
            cur = new ModifierIntensity(c == SYMBOL_DYNAMICS_FORTE ? +1 : -1, cur);
            break;
        case SYMBOL_REPEAT_BEGIN_UPPERCASE:
        case SYMBOL_REPEAT_BEGIN_LOWERCASE:
            Serial.println("ICI repeat");
            cur = parseRepetition(stream, cur);
            break;
        case SYMBOL_DURATION_TUPLETS_BEGIN:
            Serial.println("ICI tuplets");
            cur = parseTuplet(stream, cur);
            break;
        }
        parseWS(stream);
    }

    return cur;
}

Melody *SonateParser::parseTuplet(Stream *stream, Melody *original)
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
Melody *SonateParser::parseRepetition(Stream *stream, Melody *original)
{
    parseWS(stream);
    unsigned int repetition = parseInteger(stream);
    return new ModifierRepetition(repetition, original);
}
unsigned int SonateParser::parseInteger(Stream *stream)
{

    unsigned int number = 0;
    while (isNumber(stream->peek()))
    {
        number *= 10;
        number += (int)(stream->read() - '0');
    }

    return number;
}

bool SonateParser::isWS(char c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

bool SonateParser::isName(char c)
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

bool SonateParser::isGroupBegin(char c)
{
    return c == SYMBOL_GROUP_BEGIN;
}
bool SonateParser::isGroupEnd(char c)
{
    return c == SYMBOL_GROUP_END;
}

bool SonateParser::isNumber(char c)
{
    return isdigit(c);
}
bool SonateParser::isModifier(char c)
{
    return c == SYMBOL_SEMITONE_UP || c == SYMBOL_SEMITONE_DOWN ||
           c == SYMBOL_OCTAVE_UP || c == SYMBOL_OCTAVE_DOWN ||
           c == SYMBOL_DURATION_DOUBLE || c == SYMBOL_DURATION_HALF || c == SYMBOL_DURATION_THREE_QUARTER ||
           c == SYMBOL_DURATION_TUPLETS_BEGIN ||
           c == SYMBOL_DYNAMICS_PIANO || c == SYMBOL_DYNAMICS_FORTE ||
           c == SYMBOL_REPEAT_BEGIN_UPPERCASE || c == SYMBOL_REPEAT_BEGIN_LOWERCASE;
}

static RealNote *noteA = new RealNote(0, false);
static RealNote *noteB = new RealNote(2, false);
static RealNote *noteC = new RealNote(-9, false);
static RealNote *noteD = new RealNote(-7, false);
static RealNote *noteE = new RealNote(-5, false);
static RealNote *noteF = new RealNote(-4, false);
static RealNote *noteG = new RealNote(-2, false);
static RealNote *rest = new RealNote(0, true);

Note *SonateParser::noteOf(char c)
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