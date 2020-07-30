#include "TestMergeInstruments.h"
#include "NextMerge.h"
#include "MergeSmallests.h"
#include "Harmony Search/HS.h"
#include "Harmony Search/MyIO.h"
#include "Harmony Search/Logs.h"
#include "Harmony Search/CreateInstruments.h"

#include <iostream>

using namespace std;

void runHS(vector<Instrument*>& iVector, MergeInfo& mi, ofstream& out)
{
  HS hs{ mi.PAR, mi.HMCR, iVector, mi.HMS, mi.numIterations };

  int quality = hs.run();
  //showMi(mi, out);
  //showIvector(out, iVector);
  out << "O resultado da execucao de HS com estes parametros e:\n";
  out << quality << "\n";
}

void runDynamicHS(vector<Instrument*>& iVector, MergeInfo& mi, ofstream& out)
{
  HS hs{ mi.hmcrMin, mi.hmcrMax, mi.parMin, mi.parMax, mi.bwMax, mi.bwMin, iVector, mi.HMS, mi.numIterations };

  int quality = hs.runDynamic();
  //showMi(mi, out);
  //showIvector(out, iVector);
  out << "O resultado da execucao de HS com estes parametros e:\n";
  out << quality << "\n";
  //outharmony << quality << "\n";
}

int pickOption()
{
  int option = 0;

  cout << "\nO que deseja fazer? As opcoes sao:\n";
  cout << "1 - Reiniciar o teste.\n";
  cout << "2 - Configurar parametros.\n";
  cout << "3 - Executar proximo merge.\n";
  cout << "4 - Mostrar parametros.\n";
  cout << "5 - Mostrar iVector.\n";
  cout << "6 - Executar HS com estes parametros.\n";
  cout << "7 - Executar proximo merge e executar HS.\n";
  cout << "8 - Executar FullMergeSmallests.\n";
  cout << "9 - Executar FullNextMerge.\n";

  cout << "\n0 - Sair.\n";
  cout << "\n";

  cin >> option;

  return option;
}

void testMergeInstruments(string& g1, string& g2)
{
  vector<Instrument*> iVector = createUnformatedIVector(g1, g2);
  showIvector(cout, iVector);
  ofstream* out = testMergeLog(iVector);

  MergeInfo mi = initMergeInfo();

  while (true)
  {
    int option = pickOption();
    switch (option)
    {
    case 1:
      iVector = createUnformatedIVector(g1, g2);
      showIvector(cout, iVector);
      break;
    case 2:
      setMergeInfo(mi);
      showMi(mi, cout);
      break;
    case 3:
      nextMerge(iVector, mi, out);
      break;
    case 4:
      showMi(mi, cout);
      break;
    case 5:
      showIvector(cout, iVector);
      break;
    case 6:
      runHS(iVector, mi, *out);
      break;
    case 7:
      nextMerge(iVector, mi, out);
      runHS(iVector, mi, *out);
      break;
    case 8:
      fullMergeSmallests(iVector);
      break;
    case 9:
      fullNextMerge(iVector, mi, out);
      break;
    case 0:
      endLog(out);
      cout << "Saindo da execucao!";
      return;
    default:
      break;
    }
  }

  endLog(out);
}