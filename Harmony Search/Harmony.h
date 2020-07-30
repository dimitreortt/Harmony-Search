// OVERVIEW: HM.h
// ========
// Class definition for Harmony.
//
// Author(s): Dimitre Ortt
// Last revision: 20/03/2020

#pragma once

#include <vector>
#include "Note.h"

class Harmony
{
private:
	//int _dim;
	uint32_t _quality;
	std::vector<Note*> _noteVector;

public:
	Harmony(std::vector<Note*>);
	uint32_t quality() const;
	std::vector<Note*> noteVector() const;
	std::vector<Note*>::iterator begin();
	std::vector<Note*>::iterator end();
	void swap(Note* a, Note* b);
	bool operator <(const Harmony& harmonyObj);
	bool operator ==(const Harmony& harmonyObj);
	void measureQuality();
	~Harmony();
};