#pragma once

#include "Instrument.h"
#include <vector>
#include <ctime>

long long int numberOfPossibilities(std::vector<Instrument*>& iVector);

double
timeSpent(clock_t start, clock_t end);
