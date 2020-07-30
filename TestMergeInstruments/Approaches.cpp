#include "Approaches.h"
#include "MergeInfo.h"
#include "NextMerge.h"
#include "MergeSmallests.h"
#include "TestMergeInstruments.h"
#include "Harmony Search/Logs.h"
#include "Harmony Search/Instrument.h"
#include "Harmony Search/CreateInstruments.h"
#include "Harmony Search/MyIO.h"
#include "Harmony Search/Assets.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void aproach1(string& g1, string& g2)
{
  vector<Instrument*> iVector = createUnformatedIVector(g1, g2);
  showIvector(cout, iVector);

  ofstream out;
  out.open("Aproach1Log", std::ios_base::app);

  cout << "\n\n#### APROACH 1 ####\n\n";
  out << "\n\n#### APROACH 1 ####\n\n";
  out << "Comparing " << g1 << " and " << g2 << "\n";

  out << "Antes: ";
  showIvector(out, iVector);

  // Aproach 1: 
  MergeInfo mi = initMergeInfo();
  fullNextMerge(iVector, mi, &out);
  fullMergeSmallests(iVector);

  out << "Depois: ";
  showIvector(out, iVector);
  runHS(iVector, mi, out);

  endLog(&out);
}

void doAp1(vector<Instrument*>& iVector, MergeInfo mi, ofstream& out)
{
  out << "Antes: ";
  cout << "Antes: ";
  showIvector(out, iVector);
  showIvector(cout, iVector);

  // Aproach 1: 
  fullNextMerge(iVector, mi, &out);
  fullMergeSmallests(iVector);

  out << "Depois: ";
  cout << "Depois: ";
  showIvector(out, iVector);
  showIvector(cout, iVector);
}

void aproach2(string& g1, string& g2)
{
  vector<Instrument*> iVector = createUnformatedIVector(g1, g2);
  showIvector(cout, iVector);

  ofstream out;
  out.open("Aproach2Log", std::ios_base::app);
  out << "Comparing " << g1 << " and " << g2 << "\n";
  showIvector(out, iVector);
  cout << "debug2";

  MergeInfo mi = initMergeInfo();

  cout << "\n\n#### APROACH 2 ####\n\n";
  out << "\n\n#### APROACH 2 ####\n\n";
  // Aproach 2: 
  // fullNextMerge(iVector, mi, &out);
  fullMergeSmallests(iVector);
  runHS(iVector, mi, out);

  endLog(&out);
}

void aproach3(string& g1, string& g2, char** argv)
{
  cout << "#### APROACH 3 ####\n\n";

  //MergeInfo mi = initMergeInfo();
  string miFile{ argv[2] };
  MergeInfo mi = MiExtractor(miFile);

  ofstream out;
  startLog(out, g1, g2, 3);

  vector<Instrument*> iVector = createUnformatedIVector(g1, g2);

  // Aproach 1
  doAp1(iVector, mi, out);
  runHS(iVector, mi, out);

  endLog(&out);
}

void writeOutput(time_t start, ofstream& out, MergeInfo& mi)
{
  // Measure time
  double timeTaken = timeSpent((clock_t)start, clock());

  // Write output
  out << "\n";
  out << "Tempo de execucao : " << timeTaken << setprecision(5) << "\n";
  showMi(mi, out);
  out << "- - - Fim - - -" << "\n";

  // End output
  endLog(&out);
}

void prepareInput(MergeInfo& mi, string mifile,
  vector<Instrument*>& iv, string& g1, string& g2) 
{
  // Get parameters for execution
  mi = MiExtractor(mifile);
  // Create Instruments
  iv = createUnformatedIVector(g1, g2);
}

void startOutputFile(string& g1, string& g2, ofstream& out) {
  string gname1{ extractGenomeNameFromFullPath(g1) };
  string gname2{ extractGenomeNameFromFullPath(g2) };
  string outputFilename{ "HSOutputs/Log" + gname1 + gname2 };

  cout << "O nome do arquivo de saida eh: " << outputFilename << " ";

  out.open(outputFilename);
}

void aproach4(string& g1, string& g2, char** argv)
{
  // Start timer
  time_t start = clock();

  // Prepare input
  MergeInfo mi;
  vector<Instrument*> iVector;
  prepareInput(mi, string{ argv[2] }, iVector, g1, g2);

  // Start output file
  ofstream out;
  startOutputFile(g1, g2, out);    
  
  //startLogByName(out, g1, g2, string{ argv[3] }); // emprestei o argv[3] para o teste das harmonias!

  // Aproach 1
  doAp1(iVector, mi, out);
  
  runDynamicHS(iVector, mi, out);
  //runHS(iVector, mi, out);
  //printInstruments(iVector);

  writeOutput(start, out, mi);
}