#include "Instrument.h"
#include "Note.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Instrument::Instrument(vector<Note*> bw)
{
	bandWidth = bw;
	hasMoreThanOneNote = bw.size() > 1 ? true : false;
	hasMoreThanTwoNotes = bw.size() > 2 ? true : false;
	id = 0;

	for (Note* note : bandWidth)
	{
		note->setParent(this);
	}
}

Note*
Instrument::improviseNote()
{
	//int randomPosition = rand();
	if (bandWidth.size() == 0)
	{
		cout << "bwsize == 0! exiting...";
		exit(1);
	}
	if(this->hasMoreThanOneNote)
		return bandWidth[(uint32_t)rand() % bandWidth.size()];
	return bandWidth[0];
}

Note*
Instrument::left(Note* note)
{
	if (!hasMoreThanOneNote)
	{
		if(note == bandWidth[0])
			return note;
		cout << "Error in Instrument::left: Comparison not allowed! Exiting...";
		exit(1);
	}
	for (auto i = bandWidth.begin(); i != bandWidth.end(); i++)
	{
		if (*i == note)
		{
			return i == bandWidth.begin() ? *i : *--i;
		}
	}
	std::cout << "Instrument.left() is undefined! Exiting...";
	exit(1);
}

Note*
Instrument::right(Note* note)
{
	if (!hasMoreThanOneNote)
	{
		if (note == bandWidth[0])
			return note;
		cout << "Error in Instrument::right: Comparison not allowed! Exiting...";
		exit(1);
	}
	for (auto i = bandWidth.begin(); i != bandWidth.end(); i++)
	{
		if (*i == note)
		{
			auto temp = i; i++;
			return i == bandWidth.end() ? *temp : *i;
		}
	}
	std::cout << "Instrument.right() is undefined! Exiting...";
	exit(1);
}

void Instrument::setId(int newId)
{
	id = newId;
}

Instrument::~Instrument()
{
	for (int i = 0; i < bwSize; i++) {
		//Note note = bandWidth[i];
		delete bandWidth[i];
	}
}
