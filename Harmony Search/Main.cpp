#include <iostream>
#include <vector>
#include "Instrument.h"
#include "Populate.h"
#include "MyIO.h"
#include "Harmony.h"
#include "HM.h"
#include "HS.h"
#include "CreateInstruments.h"

using namespace std;

int main(int argc, char ** argv) {
  
  Instrument i{ populateNoteVector(5) };
  vector<Instrument*> iv{ &i };// = createInstruments();
  printInstruments(iv);

  /*HS(float hmcrMin, float hmcrMax, float parMin, float parMax, uint32_t bwMax, uint32_t bwMin,
    std::vector<Instrument*> iVector, uint32_t HMS, uint32_t numInterations);*/

  HS hs{ 0.3f, 0.99f, 0.5f, 0.9f, 10, 1, iv, 5, 50 };
  cout << hs.runDynamic();
  printHM(hs.getHM());

  return 0;
}