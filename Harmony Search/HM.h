// OVERVIEW: HM.h
// ========
// Class definition for Harmony Memory.
//
// Author(s): Dimitre Ortt
// Last revision: 20/04/2020

#pragma once 

#include "Instrument.h"
#include "Harmony.h"
#include "Note.h"
#include <vector>

class HM
{
private:
	std::vector<Instrument*> iVector;
	std::list<Harmony*> hList;
	size_t _dim;
	int _HMS;

public:

	HM(int size, size_t dim) : _HMS(size), _dim{ 0 } {}
  HM(int size, std::vector<Instrument*> iv) : _HMS(size) { initialize(iv); };
	void initialize(std::vector<Instrument*>);
	void addIfGoodEnough(Harmony*);
  std::list<Harmony*>::iterator findPosition(Harmony* h);
  bool hasH(Harmony*);
  uint32_t currentBestQuality();
	Harmony* improviseHM();
	Note* improviseAt(int idx);
  std::list<Harmony*> gethList() { return hList; };
	~HM();
};