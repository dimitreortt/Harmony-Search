#include "RunHS.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int RunHS(int argc, char** argv)
{
  std::cout << "Entrei mainHS";
  srand((unsigned)time(NULL));
  clock_t start, end;
  /*
    const string g1 = "Buchnera aphidicola APS";
    const string g2 = "Wigglesworthia glossinidia brevipalpis";*/

    /*const string g1 = "Buchnera aphidicola APS";
    const string g2 = "Haemophilus influenzae Rd"; */

    /*const string g1 = "Pseudomonas aeruginosa PA01";
    const string g2 = "Salmonella typhimurium LT2";*/

  const string g1 = "32Exact_1";
  const string g2 = "32Exact_2";

  // get input
  string g1file, g2file;
  getInputFiles(g1file, g2file);
  std::cout << g2file;

  std::cout << "f";
  vector<Instrument*> iVector;
  createInstruments(g1file, g2file, &iVector);
  std::cout << "s";
  // set output file
  ofstream outFile;
  string outName;
  cin >> outName;
  outFile.open(outName, std::ios_base::app);
  outFile << "\n\nResults from test with " << g1file << " and " << g2file << "; 30 executions, 10000 iterations each.\n";

  for (int i = 0; i < 30; i++) {
    HS* hs = new HS(0.1f, 0.50f, iVector, 20, 10000);

    start = clock();
    //cout << hs->run() << " ";
    outFile << hs->run() << " ";
    // outFile << Common-Intervals-Program() << " ";

    end = clock();
    //timeSpent(start, end);
  }
  return 0;
}
