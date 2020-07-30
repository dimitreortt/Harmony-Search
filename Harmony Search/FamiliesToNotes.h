#pragma once 

#include <vector>
#include "Note.h"

void
addNotes(std::vector<int> posg1, std::vector<int> posg2, std::vector<Note*>* nv, std::list<Pair*> pairs);

std::vector<Note*>
createNoteVector(std::vector<int> posg1, std::vector<int> posg2);