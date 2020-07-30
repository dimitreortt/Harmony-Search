#include "MergeInfo.h"
#include <iostream>

using namespace std;

void showMi(MergeInfo& mi, ostream& out)
{
  out << "\n#--------------------------------------#\n";
  out << "\nOs parametros em MergeInfo sao:\n";
  out << "Tamanho ideal: " << mi.idealSize << "\n";
  out << "Tamanho maximo: " << mi.maxSize << "\n";
  out << "HMS: " << mi.HMS << "\n";
  out << "PAR: " << mi.PAR << "\n";
  out << "parMax: " << mi.parMax << "\n";
  out << "parMin: " << mi.parMin << "\n";
  out << "HMCR: " << mi.HMCR << "\n";
  out << "hmcrMin: " << mi.hmcrMin << "\n";
  out << "hmcrMax: " << mi.hmcrMax << "\n";
  out << "bwMin: " << mi.bwMin << "\n";
  out << "bwMax: " << mi.bwMax << "\n";
  out << "Numero de Iteracoes: " << mi.numIterations << "\n";

  out << "\n#--------------------------------------#\n";

  out << "\n";
}

void 
debugMI(int start1, int end1, int start2, int end2, vector<Instrument*> iv)
{
  cout << "\n";
  cout << "Insinde mergeInstruents(): " << start1 << " " << end1 << " " << start2 << " " << end2;
  cout << " ";
  cout << "Instruments sizes: ";

  for (auto i : iv)
    cout << i->size() << " ";
  
  cout << "\n";
}

void setMergeInfo(MergeInfo& mi)
{
  cout << "Entre com o tamanho ideal: ";
  cin >> mi.idealSize;
  cout << "Entre com o tamanho maximo: ";
  cin >> mi.maxSize;
  cout << "Entre com o HMS: ";
  cin >> mi.HMS;
  cout << "Entre com o PAR: ";
  cin >> mi.PAR;
  cout << "Entre com o HMCR: ";
  cin >> mi.HMCR;
  cout << "Entre com o numero de iteracoes: ";
  cin >> mi.numIterations;
}

MergeInfo MiExtractor(const string& miFile)
{
  MergeInfo mi;

  ifstream in;
  in.open(miFile);

  if (!in)
  {
    cout << "Exiting in MiExtractor...";
    exit(1);
  }

  in >> mi.HMS;
  in >> mi.numIterations;
  in >> mi.HMCR;
  in >> mi.hmcrMin;
  in >> mi.hmcrMax;
  in >> mi.PAR;
  in >> mi.parMin;
  in >> mi.parMax;
  in >> mi.bwMin;
  in >> mi.bwMax;
  in >> mi.maxSize;

  cout << "MiExtractor successfully finished.";
  showMi(mi, cout);
  return mi;
}

MergeInfo initMergeInfo()
{
  MergeInfo mi;

  mi.idealSize = 12;
  mi.maxSize = 1944;
  mi.HMS = 40;
  mi.HMCR = 0.60f;
  mi.PAR = 0.5f;
  mi.numIterations = 1000000;

  return mi;
}