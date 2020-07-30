#include "CreateInstruments.h"
#include "MergeInstruments.h"
#include "Populate.h"
#include "GeneFamilies.h"
#include "Logs.h"
#include "FamiliesToNotes.h"

#include <fstream>
#include <iostream>

using namespace std;

// Global variable to store one sized instruments
vector<Note*> sizeOnes;

//create simple iVector only for test purposes
vector<Instrument*>
createInstruments()
{
	vector<Note*> nVector = populateNoteVector(0);
	//printNotes(nVector);

	Instrument* i = new Instrument(nVector);
	i->setId(70);
	vector<Instrument*> iVector{ i };

	return iVector;
}

int findOnes(vector<Instrument*> iVector)
{
  int idx;
  for (idx = 0; idx < iVector.size(); idx++)
  {
    if (iVector[idx]->bw().size() == 1)
      return idx;
  }
  return idx;
}

void
splitInstrumentVector(vector<Instrument*>* iVector)
{
  for (auto i : *iVector)
  {
    //sum += i->bw()[0]->listOfPairs.size();
    if (i->bw().size() == 1)
    {
      sizeOnes.push_back(i->bw()[0]);
    }
  }

  int idx = findOnes(*iVector);
  while (idx != iVector->size())
  {
    iVector->erase(iVector->begin() + idx);
    idx = findOnes(*iVector);
  }
}

int
getNumOfTwos(vector<Instrument*> iVector)
{
  int twos = 0;
  for (auto i : iVector)
  {
    if (i->bw().size() == 2)
      twos++;
  }
  return twos;
}

void
formatIVector(vector<Instrument*>* iVector)
{
  int idealSize = 12;
  int maxSize = 24;
  bool madeChanges;

  ofstream out;
  formatLog(iVector, out);
  do
  {
    madeChanges = false;
    *iVector = mergeInstruments(*iVector, 0, iVector->size() - 1, maxSize, madeChanges);

  } while (madeChanges);

  //endLog(out); 
  //out->close();
}

void setNotesIndexes(vector<Instrument*>& iVector)
{
  for (auto i = 0; i < iVector.size(); i++)
  {
    auto inst = iVector[i];
    auto is = inst->size();
    auto ibw = inst->bw();
    for (auto j = 0; j < is; j++)
      ibw[j]->idx = j;
  }
}

vector<Instrument*>&
createInstruments(const std::string g1, const std::string g2, vector<Instrument*>* iVector)
{
  //vector<Instrument*> iVector;
  sizeOnes.clear();

  int idCount = 0;

  auto gf = extractGlobalFamilies(g1, g2);

  for (auto gfitem : gf->items())
  {
    auto nv = createNoteVector(gfitem->posg1(), gfitem->posg2());
    auto newInstrument = new Instrument{ nv };
    newInstrument->setId(idCount++);
    iVector->push_back(newInstrument);
  }
  // debugGf(gf);
  //printInstruments(iVector);

  splitInstrumentVector(iVector);
  formatIVector(iVector);
  setNotesIndexes(*iVector);

  return *iVector;
}

vector<Instrument*>
createUnformatedIVector(string& g1, string& g2)
{
  vector<Instrument*> iVector;
  sizeOnes.clear();

  int idCount = 0;

  auto gf = extractGlobalFamilies(g1, g2);

  for (auto gfitem : gf->items())
  {
    auto nv = createNoteVector(gfitem->posg1(), gfitem->posg2());
    auto newInstrument = new Instrument{ nv };
    newInstrument->setId(idCount++);
    iVector.push_back(newInstrument);
  }
  splitInstrumentVector(&iVector);
  //showIvector(cout, iVector);
  std::cout << "UIVector done!\n";
  // formatIVector(&iVector); -- //
  return iVector;
}