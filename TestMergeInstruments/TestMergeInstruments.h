#pragma once

#include "Harmony Search/Instrument.h"
#include "MergeInfo.h"

#include <string>
#include <vector>
#include <fstream>

void testMergeInstruments(std::string& g1, std::string& g2);

void runHS(std::vector<Instrument*>& iVector, MergeInfo& mi, std::ofstream& out);

void runDynamicHS(std::vector<Instrument*>& iVector, MergeInfo& mi, std::ofstream& out);



