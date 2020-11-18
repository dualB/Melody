#include "Melody.h"

Melody::Melody(char *score)
{
	setScore(score);
	setTempo(DEFAULT_TEMPO);
	restart();
}
Melody::Melody(char *score, unsigned int tempo)
{
	setScore(score);
	setTempo(tempo);
	restart();
}

Melody::Melody(String score)
{
	setScore(score);
	setTempo(DEFAULT_TEMPO);
	restart();
}
Melody::Melody(String score, unsigned int tempo)
{
	setScore(score);
	setTempo(tempo);
	restart();
}

bool Melody::setTempo(unsigned int tempo)
{
	if (tempo == 0)
	{
		return false;
	}
	_tempo = tempo;
	_base_duration = 1000 * 60 / _tempo;
	return true;
}

unsigned int Melody::getTempo()
{
	return _tempo;
}

bool Melody::setScore(char *score)
{
	_Sequence = SequenceParser::parse(score);
	return true;
}

bool Melody::setScore(String score)
{
	_Sequence = SequenceParser::parse(score);
	return true;
}

bool Melody::hasNext()
{
	return _Sequence->hasNext();
}

void Melody::restart()
{
	_Sequence->restart();
	_index = -1;
}

void Melody::next()
{
	_Sequence->next();
	_index++;
}

int Melody::length()
{
	return _Sequence->length();
}
int Melody::index()
{
	return _index;
}
unsigned int Melody::getFrequency()
{
	if (_Sequence->isRest())
	{
		return 0;
	}
	return NoteToSound::getFrequency(_Sequence->getNoteIndex());
}

unsigned long Melody::getDuration()
{
	return NoteToSound::getDuration(_base_duration, _Sequence->getDurationNumerator(), _Sequence->getDurationDenominator());
}

int Melody::getLoudness()
{
	return _Sequence->getIntensityIndex();
}
