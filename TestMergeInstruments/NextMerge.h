#pragma once

#include "Harmony Search/Instrument.h"
#include "MergeInfo.h"

#include <string>
#include <vector>
#include <fstream>

bool 
nextMerge(std::vector<Instrument*>& iVector, MergeInfo& mi, std::ofstream* out);

void 
fullNextMerge(std::vector<Instrument*>& iVector, MergeInfo& mi, std::ofstream* out);
