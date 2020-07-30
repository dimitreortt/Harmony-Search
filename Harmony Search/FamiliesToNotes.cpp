#include "FamiliesToNotes.h"
#include <iostream>

using namespace std;

void
addNotes(vector<int> posg1, vector<int> posg2, vector<Note*>* nv, list<Pair*> pairs)
{
	if (posg1.size() > 1 && posg2.size() > 1) {		
		for (int i = 0; i < posg1.size(); i++) {
			//for (int j = 0; j < posg2.size(); j++) {
			int j = 0; // found after throughout inspection
			int bufg1 = posg1[i];
			int bufg2 = posg2[j];

			posg1.erase(posg1.begin() + i);
			posg2.erase(posg2.begin() + j);

			Pair* p = new Pair{ bufg1, bufg2 };
			pairs.push_back(p);

			addNotes(posg1, posg2, nv, pairs);
			pairs.remove(p);

			posg1.insert(posg1.begin() + i, bufg1);
			posg2.insert(posg2.begin() + j, bufg2);

			//}
		}
	}//fim if
	else
	{
		for (int i = 0; i < posg1.size(); i++) {
			for (int j = 0; j < posg2.size(); j++) {

				Pair* p = new Pair{ posg1[i], posg2[j] };
				pairs.push_back(p);

				nv->push_back(new Note{ pairs });
				pairs.remove(p);				
			}
		}
	}// fim else
}// fim addNotes

long long int fat(int x)
{
  int i = x;
  int result = 1;
  while (i > 1)
    result *= i--;  

  return result;
}

long long int numOfPossib(int major, int minor)
{
  return fat(major) / fat(major - minor);
}

vector<Note*>
createNoteVector(vector<int> posg1, vector<int> posg2)
{
	vector<Note*> nv;
	list<Pair*> l;
  /*cout << "num of possibilities: ";
  cout << numOfPossib(posg1.size(), posg2.size());*/
	addNotes(posg1, posg2, &nv, l);	

	return nv;
}
