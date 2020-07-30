#include "Logs.h"
#include "Assets.h"
#include "MyIO.h"

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

ofstream outharmony;

void endLog(ofstream* out)
{
  *out << "\n\n";
  out->close();
}

void formatLog(vector<Instrument*>* iVector, ofstream& out)
{
  out.open("formatIVectorLog", std::ios_base::app);
  out << "This is a new IVector. Size: " << iVector->size();
  out << "I's sizes: ";
  for (auto& i : *iVector)
  {
    out << i->size() << " ";
    cout << i->size() << " ";
  }
  out << "\n";

  out << "Number of possibilities: ";
  out << numberOfPossibilities(*iVector) << " ";
}

ofstream* testMergeLog(vector<Instrument*>& iVector)
{
  ofstream out;
  out.open("testMergeInstrumentsLog", std::ios_base::app);
  out << "This is a new TestMergeLog.";
  showIvector(out, iVector);
  return &out;
}

void startLog(ofstream& out, const string& g1, const string& g2, int id)
{
  out.open("Aproach" + to_string(id) + "Log", std::ios_base::app);
  out << "#### APROACH " << id << "####\n";
  out << "Comparing " << g1 << " and " << g2 << "\n";
}

void startLogByName(ofstream& out, const string& g1, const string& g2, const string& outFile)
{
  out.open(outFile, std::ios_base::app);
  out << "#### APROACH 4 ####\n";
  out << "Comparing " << g1 << " and " << g2 << "\n";
  cout << "Log opened correctly!" << outFile << "\n";

}
extern ofstream outharmony;

void startOutHarmony(std::string outfile) {
  outharmony.open(outfile, std::ios_base::app);
}

void closeOutHarmony() {
  outharmony.close();
}