#include "MusicParser.h"

MusicParser::MusicParser()
{
	_melody = new SimpleMelody();
}

bool MusicParser::setTempo(unsigned int tempo)
{
	if (tempo == 0)
	{
		return false;
	}
	_tempo = tempo;
	_base_duration = 1000 * 60 / _tempo;
	return true;
}

unsigned int MusicParser::getTempo()
{
	return _tempo;
}

bool MusicParser::setPartition(char * partition)
{
	delete _melody;
	MelodyParser * parser = new MelodyParser();
	_melody = parser->parse(partition);
	delete parser;
	return true;

}

bool MusicParser::hasNext()
{
	return _melody->hasNext();
}

void MusicParser::restart()
{
	 _melody->restart();
}

void MusicParser::next()
{
	_melody->next();
}

int MusicParser::length()
{
	return _melody->length();
}

unsigned int MusicParser::getFrequency()
{
	return MelodyToSound::getFrequency(_melody->getNoteIndex());
}

unsigned long MusicParser::getDuration()
{
	return MelodyToSound::getDuration(_base_duration,_melody->getDurationNumerator(),_melody->getDurationDenominator());
}

int MusicParser::getLoudness()
{
	return _melody->getIntensityIndex();
}
