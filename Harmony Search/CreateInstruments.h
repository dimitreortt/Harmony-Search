#pragma once

#include <vector>
#include <string>
#include "Instrument.h"

//create simple iVector only for test purposes
std::vector<Instrument*>
createInstruments();

void setNotesIndexes(std::vector<Instrument*>& iVector);

std::vector<Instrument*>&
createInstruments(const std::string g1, const std::string g2, std::vector<Instrument*>* iVector);

std::vector<Instrument*>
createUnformatedIVector(std::string& g1, std::string& g2);