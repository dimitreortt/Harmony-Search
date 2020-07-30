#include "CommonIntervals.h"
#include "HS.h" // saveHarmonySamples
#include <algorithm>
#include <iostream>

using namespace std;

void
printVector(vector<int> v)
{
	cout << "\nvec.size: " << v.size() << endl;
	for (int i : v)
	{
		cout << i << " ";
	}
	cout << endl;
}

// (Uno, 2000) Fast algorithms to enumerate all Common Intervals
int
LHP(vector<int> seq1, vector<int> seq2)
{
	//cout << "\n\nEntrei em LHP, os vetores sao: " << seq1.size() << " " << seq2.size() << "\n";
	//printVector(seq1);
	//printVector(seq2);
	
	//printVector(seq1);
	//cout << "\n\n";
	//printVector(seq2);
	//exit(1);

	if (seq1.size() != seq2.size())
	{
		printVector(seq1);
		printVector(seq2);
		cout << "\nThe Harmony given is not a Maximum Matching, exiting in LHP!";
		exit(1);
	}

	size_t size = seq1.size();

	static bool show = true;
	if (show) cout << "\nO numero de intervalos comuns de tamanho 1 eh: " << size << "\n", show = false;

	// build dictionary pi_AB
	vector<int> pi_AB;
	for (auto it = seq1.begin(); it != seq1.end(); it++)
	{
		auto it_pos = find(seq2.begin(), seq2.end(), *it);
		int index = (int)std::distance(seq2.begin(), it_pos);

		pi_AB.push_back(index);
	}

	//for (auto value : seq1) {
	//	// find position of value in seq2
	//	auto pos = find(seq2.begin(), seq2.end(), value);

	//	// push this position to pi_AB vector
	//	pi_AB.push_back((int)std::distance(seq2.begin(), pos));
	//}
	
	for (auto value : pi_AB) {
		//cout << value << ' ';
	}

	//calculate number of CIs
	int numberOfCIs = 0;
	int l, u;
	for (int x = 0; x < size; x++)
	{
		l = u = pi_AB[x];

		// for (int y = x + 1; y < size; y++)
		for (int y = x; y < size; y++)
		{
			l = min(l, pi_AB[y]);
			u = max(u, pi_AB[y]);

			//check length condition
			/*if (u - l > min(size - x, size - 3))
				break;*/

				//check holepoint condition
				//for()

			if (u - l - (y - x) == 0)
			{
				//cout << "\nGlória Deus, Entrei aqui";
				//exit(1);
				//output([x,y], [l,u]);

				//cout << "\n([" << x << "," << y << "], [" << l << "," << u << "]) ";
				numberOfCIs += 1;
			}
		}
	}

	return numberOfCIs;
}

vector<Pair*>
gatherPairs(vector<Note*> notes)
{
	vector<Pair*> gatherPairs;
	for (auto noteIt = notes.begin(); noteIt != notes.end(); noteIt++)
	{
		for (auto pairIt = (*noteIt)->listOfPairs.begin(); pairIt != (*noteIt)->listOfPairs.end(); pairIt++)
		{
			gatherPairs.push_back(*pairIt);
		}
	}

	return gatherPairs;
}

bool
comparePairs(Pair* p1, Pair* p2)
{
	return (p1->posG1 < p2->posG1);
}

int
findMax1(vector<Pair*> pairs)
{
	int max = 0;
	for (auto p : pairs)
	{
		if (p->posG1 > max)
			max = p->posG1;
	}
	return max;
}

int
findMax2(vector<Pair*> pairs)
{
	int max = 0;
	for (auto p : pairs)
	{
		if (p->posG2 > max)
			max = p->posG2;
	}
	return max;
}

void getSequences(Harmony* h, vector<int>& seq1, vector<int>& seq2)
{
	auto notes = h->noteVector();

	// add notes of size one previously kept apart
	notes.reserve(notes.size() + distance(sizeOnes.begin(), sizeOnes.end()));
	notes.insert(notes.end(), sizeOnes.begin(), sizeOnes.end());

	// gather pairs
	auto allPairs = gatherPairs(notes);

	// sort pairs with posG1 as parameter
	std::sort(allPairs.begin(), allPairs.end(), comparePairs);

	// reserve space in vectors and set with zeros
	//vector<int> seq1(findMax1(allPairs) + 1, 0);
	//vector<int> seq2(findMax2(allPairs) + 1, 0);
	auto size1 = findMax1(allPairs) + 1;
	for (auto i = 0; i < size1; i++)
		seq1.push_back(0);

	auto size2 = findMax2(allPairs) + 1;
	for (auto i = 0; i < size2; i++)
		seq2.push_back(0);


	//saveHarmonySample(notes);

	// rename genes
	int i = 1;
	for (auto pair : allPairs)
	{
		seq1[pair->posG1] = i;
		seq2[pair->posG2] = i;
		i++;
	}

	// The removal of the zeros represents the step of wiping out
	// the unmaped genes in both genomes!

	// erase zeros from vectors
	seq1.erase(std::remove(seq1.begin(), seq1.end(), 0), seq1.end());
	seq2.erase(std::remove(seq2.begin(), seq2.end(), 0), seq2.end());
}

int
getNumCIs(Harmony* h)
{
  //cout << "\nin getNumcis s1: " << sizeOnes.size();
  vector<int> seq1;
  vector<int> seq2;

  getSequences(h, seq1, seq2);

  // return number of common intervals with LHP method
  return LHP(seq1, seq2);
}
