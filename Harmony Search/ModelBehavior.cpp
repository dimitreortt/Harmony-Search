#include "HS.h"
#include "Note.h"
#include "Harmony.h"
#include <vector>
#include "MyIO.h"
#include "Logs.h"
#include <iostream>
#include <fstream>

using namespace std;

void saveHarmonySample(std::vector<Note*> nv) {
  //auto harmony = new Harmony(nv);

  // Todo:
  // save as int vectors

  //open file
  //ofstream out;
  //out.open("Harmonias-Baphi-Wglos", std::ios_base::app);

  
  for (auto note : nv) {
    //printPairs(note);

    // p cada par da nota:
    //   escreve o par num arquivo

    for (auto pair : note->listOfPairs)
    {
      outharmony << "(" << pair->posG1 << "," << pair->posG2 << ") ";

    }
  }
  std::cout << '\n';

  outharmony << "\n\nFim da harmonia!";
  cout << "\n\nFim da harmonia!";
  //outharmony.close();
  /*for match in harmony
    write match to file
    remember value from genome
      to do that you create Instrument.geneId*/
  
}