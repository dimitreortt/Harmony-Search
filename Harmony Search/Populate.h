#pragma once
#include <vector>
#include <list>
#include "Note.h"

inline std::list<Pair*> populatePairList(int j)
{
	std::list<Pair*> pList;
	for (int i = 0; i < 3; i++)
	{
		pList.push_back(new Pair{ 20 - i, j-- });
	}
	return pList;
}

inline std::vector<Note*> populateNoteVector(int j)
{
	std::vector<Note*> nVector;
	for (int i = j; i < 2 + j; i++)
	{
		std::list<Pair*> plist = populatePairList(i);
		nVector.push_back(new Note{ plist });
	}
	return nVector;
}