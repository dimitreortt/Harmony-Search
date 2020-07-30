#pragma once 

#include <vector>
#include "Note.h"
#include "Harmony.h"

extern std::vector<Note*> sizeOnes;

void
printVector(std::vector<int> v);

int
LHP(std::vector<int> seq1, std::vector<int> seq2);

std::vector<Pair*>
gatherPairs(std::vector<Note*> notes);

//bool
//comparePairs(Pair* p1, Pair* p2);
//
//int
//findMax1(std::vector<Pair*> pairs);
//
//int
//findMax2(std::vector<Pair*> pairs);

void 
getSequences(Harmony* h, std::vector<int>& seq1, std::vector<int>& seq2);

int
getNumCIs(Harmony* h);