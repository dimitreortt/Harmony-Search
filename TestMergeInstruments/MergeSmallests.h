#pragma once

#include "Harmony Search/Instrument.h"

#include <vector>

struct IVecInfo {
  Instrument* smallest;     // pointer to the smallest instrument
  Instrument* secSmallest;  // pointer to the  second smallest instrument
  size_t biggestSize;            // average size of instruments
};

std::vector<Instrument*>
mergeSmallests(std::vector<Instrument*>& iVector);

void
fullMergeSmallests(std::vector<Instrument*>& iVector);
