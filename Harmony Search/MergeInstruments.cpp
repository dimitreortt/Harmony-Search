#include "MergeInstruments.h"
#include "Note.h"
#include <iostream>
#include <list>

using namespace std;

//ivector retornado deve ter size = 1!
vector<Instrument*>
becomeOne(Instrument* i1, Instrument* i2)
{
  if (i1->size() < 2 || i2->size() < 2) {
    cout << "ASSERT ERROR! Instrument must have size > 2! Exiting in becomeOne...";
    exit(1);
  }

  vector<Note*> nv;
  for (auto note1 : i1->bw())
  {
    for (auto note2 : i2->bw())
    {
      list<Pair*> pList = note1->listOfPairs;

      for (auto p : note2->listOfPairs)
        pList.push_back(p);

      nv.push_back(new Note(pList));
    }
  }
  vector<Instrument*> iVector{ new Instrument(nv) };
  return iVector;
}

vector<Instrument*>
gatherInstruments(vector<Instrument*> v1, vector<Instrument*> v2)
{
  v1.reserve(v1.size() + distance(v2.begin(), v2.end()));
  v1.insert(v1.end(), v2.begin(), v2.end());

  return v1;
}

vector<Instrument*>
mergeInstruments(vector<Instrument*> iVector, size_t start, size_t end, size_t maxSize, bool& madeChanges)
{
  size_t size = end - start + 1;
  if (size > 2)
  {
    size_t start1 = start;
    size_t end1 = start + (size / 2) - 1;
    size_t start2 = end1 + 1;
    size_t end2 = end;

    auto a = mergeInstruments(iVector, start1, end1, maxSize, madeChanges);
    auto b = mergeInstruments(iVector, start2, end2, maxSize, madeChanges);
    auto iv = gatherInstruments(a, b);
    // debugMI(start1, end1, start2, end2, iv);
    return gatherInstruments(a, b);
  }
  else if (size == 2)
  {
    size_t bSize1 = iVector[start]->size();
    size_t bSize2 = iVector[end]->size();

    auto i1 = iVector[start];
    auto i2 = iVector[end];
    /* if (start == 0 && end == 1)
     {
       cout << "first and second here\n";
       cout << "bsize1: " << bSize1 << ", bsize2: " << bSize2 << "\n";

     }*/
    if (i1->size() * i2->size() <= maxSize)
    {
      // cout << "I made changes!";
      madeChanges = true;
      auto i = becomeOne(i1, i2);
      // cout << ", i size: " << i[0]->size();
      return i;
    }
    else
    {
      return vector<Instrument*> {iVector[start], iVector[end]};
    }
  }
  else if (size == 1)
  {
    return vector<Instrument*> {iVector[start]};
  }
  else
  {
    cout << "Assert error! Unaccepted parameters! Exiting in mergeInstruments...";
    exit(1);
  }
}

