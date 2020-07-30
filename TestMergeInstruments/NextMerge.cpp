#include "Harmony Search/MergeInstruments.h"
#include "Harmony Search/CreateInstruments.h"
#include "NextMerge.h"

using namespace std;

// does one more merge in iVector, if that changes, it runs HS for new iVector
bool nextMerge(vector<Instrument*>& iVector, MergeInfo& mi, ofstream* out)
{
  //int newNumber;
  bool madeChanges = false;
  iVector = mergeInstruments(iVector, 0, iVector.size() - 1, mi.maxSize, madeChanges);
  //showIvector(cout, iVector);
  if (madeChanges)
  {
    // runHS(iVector, mi);
  }
  else
  {
    //cout << "This merge has made no changes!\n";
  }
  return madeChanges;
}

void fullNextMerge(vector<Instrument*>& iVector, MergeInfo& mi, ofstream* out)
{
  while (nextMerge(iVector, mi, out));
  setNotesIndexes(iVector);
}