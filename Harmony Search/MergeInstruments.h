#pragma once
#include <vector>
#include "Instrument.h"

//ivector retornado deve ter size = 1!
std::vector<Instrument*>
becomeOne(Instrument* i1, Instrument* i2);

std::vector<Instrument*>
mergeInstruments(std::vector<Instrument*> iVector, size_t start, size_t end, size_t maxSize, bool& madeChanges);

std::vector<Instrument*>
gatherInstruments(std::vector<Instrument*> v1, std::vector<Instrument*> v2);
