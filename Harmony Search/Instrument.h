#pragma once

#include <vector>

struct Note;

class Instrument
{
private:
	int bwSize;
	std::vector<Note*> bandWidth;
public:
	int id;
	bool hasMoreThanOneNote;
	bool hasMoreThanTwoNotes;
	Instrument(std::vector<Note*>);
	Note* improviseNote();
	Note* left(Note*);
	Note* right(Note*);
	std::vector<Note*> bw() { return bandWidth; };
	size_t size() { return bandWidth.size(); }
	void setId(int);
	~Instrument();
};

