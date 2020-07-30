// OVERVIEW: HM.cpp
// ========
// Source file for Harmony Memory implementation.
//
// Author(s): Dimitre Ortt
// Last revision: 09/04/2020

#include "HM.h"
#include "MyIO.h"
#include <iostream>

using namespace std;

void
HM::initialize(vector<Instrument*> iVec)
{
	iVector = iVec;
	_dim = iVector.size();
	for (int i = 0; i < _HMS; i++)
	{
		vector<Note*> nVector;
		for (auto i : iVector)
		{
			auto note = i->improviseNote();
			nVector.push_back(note);
		}
		Harmony* newHarmony = new Harmony(nVector);

		//add newHarmony to HM in correct position
		auto it = findPosition(newHarmony);

		hList.insert(it, newHarmony);
	}
}

void
HM::addIfGoodEnough(Harmony* h)
{	
  //if (hasH(h)) return;  

	//find position in list
	auto it = findPosition(h);
	
  //insert in the list and remove worst
	if (it != hList.end()) {
		hList.insert(it, h);
		hList.pop_back();
    //printHM(this);
	}
}

list<Harmony*>::iterator
HM::findPosition(Harmony* h)
{
	auto it = hList.begin();
	auto e = hList.end();
	auto q = h->quality();
	while (it != e && (*it)->quality() >= q)
		it++;	

	return it;
}


bool HM::hasH(Harmony* h)
{
  bool has = false;
  for (auto hmny : hList)
    if (hmny == h)
      has = true;
  return has;
}

Harmony*
HM::improviseHM() {
	vector<Note*> nv;
	for (int i = 0; i < _dim; i++)
	{
		if(iVector[i]->hasMoreThanTwoNotes)
		{
			int randPosition = (int)rand() % _HMS;
			auto it = hList.begin();

      advance(it, randPosition);
      if(it == hList.end())
      {
        cout << "ERROR in improviseHM! Exiting...";
        exit(1);
      }			
			nv.push_back((*it)->noteVector()[i]);
		}
		else if(iVector[i]->hasMoreThanOneNote)
		{
			nv.push_back(iVector[i]->bw()[0]);
		}
		else
		{
			nv.push_back(iVector[i]->bw()[0]);
		}
	}
	Harmony* newHarmony = new Harmony(nv);

	return newHarmony;
}

Note* 
HM::improviseAt(int idx)
{
  auto pos = rand() % _HMS;
  auto it = hList.begin();
  std::advance(it, pos);
  return (*it)->noteVector()[idx];
}

uint32_t
HM::currentBestQuality()
{	
	return (*(hList.begin()))->quality();
}

HM::~HM()
{
}

