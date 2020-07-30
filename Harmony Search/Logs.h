#pragma once

#include "Instrument.h"
#include <vector>
#include <string>
#include <fstream>

void endLog(std::ofstream* out);

void formatLog(std::vector<Instrument*>* iVector, std::ofstream& out);

std::ofstream* 
testMergeLog(std::vector<Instrument*>& iVector);

void 
startLog(std::ofstream& out, const std::string& g1, const std::string& g2, int id);

void
startLogByName(std::ofstream& out, const std::string& g1, const std::string& g2, const std::string& outFile);

extern std::ofstream outharmony;
void startOutHarmony(std::string);
void closeOutHarmony();