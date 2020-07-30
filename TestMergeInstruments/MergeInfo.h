#pragma once

#include "Harmony Search/Instrument.h"

#include <cstdint>
#include <fstream>
#include <vector>

struct MergeInfo
{
  uint32_t idealSize = 0;
  uint32_t maxSize = 0;
  uint32_t HMS = 0;
  uint32_t bwMin = 0;
  uint32_t bwMax = 0;
  uint32_t numIterations = 0;
  float PAR = 0.0f;
  float parMin = 0.0f;
  float parMax = 0.0f;
  float HMCR = 0.0f;
  float hmcrMin = 0.0f;
  float hmcrMax = 0.0f;

};

void showMi(MergeInfo& mi, std::ostream& out);
void debugMI(int start1, int end1, int start2, int end2, std::vector<Instrument*> iv);
void setMergeInfo(MergeInfo& mi);
MergeInfo MiExtractor(const std::string& miFile);
MergeInfo initMergeInfo();

