#include "Harmony.h"
#include "CommonIntervals.h"

#include <iostream>
#include <algorithm>

using namespace std;

Harmony::Harmony(vector<Note*> nv)
{
	_noteVector = nv;
	measureQuality();
	//cout << "antes";
}

void Harmony::swap(Note* a, Note* b) {
	for (int i = 0; i < _noteVector.size(); i++)
	{
		if (_noteVector[i] == a)
		{
			_noteVector[i] = b;
			return;
		}
	}
	cout << "Harmony::swap() failed!!";
	exit(1);
}

uint32_t Harmony::quality() const
{
	return _quality;
}

//extern int getNumCIs(Harmony*);

void
Harmony::measureQuality()
{
	_quality = getNumCIs(this); 
	//cout << "(quality: " << _quality << ") ";
}

vector<Note*>::iterator
Harmony::begin()
{
	return _noteVector.begin();
}

vector<Note*>::iterator
Harmony::end()
{
	return _noteVector.end();
}

bool
Harmony::operator <(const Harmony& h)
{
	return _quality < h.quality();
}

vector<Note*>
Harmony::noteVector() const
{
	return _noteVector;
}

extern void getSequences(Harmony* h, vector<int>& seq1, vector<int>& seq2);

bool 
Harmony::operator==(const Harmony& harmonyObj)
{
  vector<int> seq1;
  vector<int> seq2;
  getSequences(this, seq1, seq2);

  vector<int> seq3;
  vector<int> seq4;

  auto h = harmonyObj;
  getSequences(&h, seq3, seq4);

  if (seq1 == seq3 && seq2 == seq4)
    return true;
  return false;
}

Harmony::~Harmony()
{
}
