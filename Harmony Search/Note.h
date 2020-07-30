#pragma once

#include <list>

//forward definition
class Instrument;

struct Pair
{
	int posG1;
	int posG2;

	Pair(int a, int b) : posG1(a), posG2(b) {}
	bool operator<(const Pair& pairObj) { return posG1 < pairObj.posG1; };
};

struct Note
{
	size_t size;
	//int id;
	//Pair ** listOfPairs;
	std::list<Pair*> listOfPairs;
	Instrument* _parent;
  uint32_t idx; // index in _parent's vec of notes

	Note(std::list<Pair*>& pairs)
	{
		size = pairs.size();
		listOfPairs = pairs;
		//_parent = nullptr;
	}

	void
	setParent(Instrument* parent)
	{
		_parent = parent;
	}  

  Note*
  left()
  {
    if (_parent)
      //return _parent->left(this);
    //cout << "Assert Error! Note's parent not defined. Exiting in Note::left()...";
    exit(1);
  }

  Note*
  right()
  {
    if (_parent)
      //return _parent->right(this);
    //cout << "Assert Error! Note's parent not defined. Exiting in Note::right()...";
    exit(1);
  }

  Note* shiftRight(uint32_t);
  Note* shiftLeft(uint32_t);
};
