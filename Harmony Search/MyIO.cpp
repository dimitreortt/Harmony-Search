#include "MyIO.h"
#include "HM.h"
#include <time.h>
#include <iostream>
#include <ctime>

using namespace std;

void printPairs(Note* note)
{
  for (auto pair : note->listOfPairs)
  {
    cout << "(" << pair->posG1 << "," << pair->posG2 << ") ";
  }
  cout << "fim..\n";
}

void printNotes(vector<Note*> nList)
{
  cout << "\nNumber of notes is: " << nList.size();
  for (auto note : nList)
  {
    cout << "\n notesize: " << note->size;
    printPairs(note);
  }
}

void printInstruments(vector<Instrument*> iVector)
{
  cout << "\nNumber of Instruments is: " << iVector.size();
  for (auto i : iVector)
  {
    cout << "\n instrumentSize: " << i->bw().size();
    printNotes(i->bw());
  }
}

//void debugGf(GlobalFamilies* gf)
//{
//  for (auto gfitem : gf->items())
//  {
//    printVector(gfitem->posg1());
//    printVector(gfitem->posg2());
//    cout << "Debugging Gf"; //exit(1);
//  }
//  exit(1);
//}

void printHM(HM* hm)
{
  cout << "\nQualities in HM: ";
  for (auto h : hm->gethList())
  {
    cout << h->quality() << " ";
  }
}

//void getInputFiles(string& g1file, string& g2file)
//{
//  cout << "Enter the genomes input files:\n";
//  cin >> g1file;
//  cin >> g2file;
//  cout << "here";
//}

void showIvector(ostream& out, vector<Instrument*>& iVector)
{
  out << "IVector size : " << iVector.size();
  out << ", I's sizes: ";
  for (auto& i : iVector)
    out << i->size() << " ";

  out << "\n";

  /*out << "Number of possibilities: ";
  out << numberOfPossibilities(iVector) << "\n";*/
}