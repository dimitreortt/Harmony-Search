#include "MergeSmallests.h"
#include "Harmony Search/MergeInstruments.h"
#include "Harmony Search/CreateInstruments.h"

#include <iostream>

using namespace std;

struct IVecInfo getIVecInfo(vector<Instrument*>& iVector)
{
  IVecInfo iv{ iVector[0], nullptr, 0 };

  size_t menor = 0xfffe, secMenor = 0xffff;
  for (auto& i : iVector)
  {
    auto is = i->size();
    if (is < secMenor)
    {
      if (is < menor)
      {
        secMenor = menor;
        menor = is;
        iv.secSmallest = iv.smallest;
        iv.smallest = i;
      }
      else
      {
        secMenor = is;
        iv.secSmallest = i;
      }
    }
    // check biggest
    if (is > iv.biggestSize)
      iv.biggestSize = is;
  }
  return iv;
}

void
getMeAnIterator(vector<Instrument*>& iVector, Instrument* i, vector<Instrument*>::iterator& inst)
{
  for (inst = iVector.begin(); inst != iVector.end(); inst++)
  {
    if (*inst == i)
      return;
  }
  cout << "Assert Error! No instruments matched! Exiting in getMeAnIterator...";
  exit(1);
}

void pops(vector<Instrument*>& iVector, Instrument* i)
{
  vector<Instrument*>::iterator it;
  /*auto it = getMeAnIterator(iVector, i);*/
  getMeAnIterator(iVector, i, it);
  //cout << "Popping element in position: " << distance(iVector.begin(), it) << ", and size: " << (*it)->size() << "\n";
  iVector.erase(it);
}

//
void popSmallests(vector<Instrument*>& iVector, IVecInfo& i)
{
  //cout << "Size before popping: " << iVector.size() << "\n";

  pops(iVector, i.smallest);
  pops(iVector, i.secSmallest);

  //cout << ",\nSize after popping: " << iVector.size() << ".\n";
}

// only for debugging purposes
void doPop(vector<Instrument*>& iVector, IVecInfo& i)
{
  cout << "\nDo you want to pop these two instruments? If so, press 1: ";
  int pop;
  cin >> pop;
  if (pop == 1)
    popSmallests(iVector, i);
}

void doMerge(vector<Instrument*>& iVector, IVecInfo& info)
{
  vector<Instrument*>::iterator it, it2;
  getMeAnIterator(iVector, info.smallest, it);
  getMeAnIterator(iVector, info.secSmallest, it2);
  auto iv = becomeOne(*it, *it2);

  //cout << "Popping elements from vector to be merged...\n";
  popSmallests(iVector, info);
  //cout << "Inserting merged Instrument of size " << iv[0]->size() << " into the end of vector...\n\n";
  iVector = gatherInstruments(iVector, iv);
}

vector<Instrument*>
mergeSmallests(vector<Instrument*>& iVector)
{
  auto i = getIVecInfo(iVector);
  /*cout << "Smallest: " << i.smallest->size();
  cout << "\n2ºSmallest: " << i.secSmallest->size();
  cout << "\nBiggestSize: " << i.biggestSize << "\n";*/
  //doPop(iVector, i);
  doMerge(iVector, i);
  return iVector;
}

void fullMergeSmallests(vector<Instrument*>& iVector)
{
  auto info = getIVecInfo(iVector);
  size_t size = info.smallest->size() * info.secSmallest->size();
  while (size <= info.biggestSize + info.biggestSize / 10)
  {
    //cout << "Invoking mergeSmallests()\n";
    mergeSmallests(iVector);
    //showIvector(cout, iVector);
    info = getIVecInfo(iVector);
    size = info.smallest->size() * info.secSmallest->size();
  }
  setNotesIndexes(iVector);
  cout << "fullMergeSmallests() done.\n";
}