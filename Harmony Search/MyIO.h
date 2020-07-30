#pragma once

#include "Note.h"
#include "Instrument.h"
#include <vector>
#include <fstream>

class HM;

void printPairs(Note* note);

void printNotes(std::vector<Note*> nList);

void printInstruments(std::vector<Instrument*> iVector);

void printHM(HM* hm);
//
////void debugGf(GlobalFamilies* gf);
//
//void getInputFiles(string& g1file, string& g2file);

void 
showIvector(std::ostream& out, std::vector<Instrument*>& iVector);
//
//#endif