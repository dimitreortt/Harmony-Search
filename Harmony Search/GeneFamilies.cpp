#include "GeneFamilies.h"
#include <iostream>
#include <fstream>

using namespace std;

void
printGlobalFamilies(GlobalFamilies* gf)
{
	auto gfitems = gf->items();
	cout << "\nThe size of globalFamilies is: " << gfitems.size();
	for (auto item : gfitems)
	{
		cout << "\nNext item:\nKey: " << item->key() << "\nposg1: ";
		for (auto pos : item->posg1())
		{
			cout << pos << " ";
		}
		cout << "\nposg2: ";
		for (auto pos : item->posg2())
		{
			cout << pos << " ";
		}
		cout << "\n";
	}
}

vector<int>
readGenome(const string gName)
{
	vector<int> genome;
	ifstream inFile;
  //gName = const std::string("genome\\" + gName);// +std::string(gName);

  // this line must be changed with the correct path to the input files
	// const string g("C:\\Users\\dimio\\OneDrive\\Documentos\\UFMS\\TCC\\Harmony-Search\\Harmony Search\\Simple Genomes-Losangles\\Separated\\" + gName);
	// const string g("C:\\Users\\dimio\\OneDrive\\Documentos\\UFMS\\TCC\\Harmony-Search\\Harmony Search\\Genomes\\" + gName);
	const string g(gName);

	inFile.open(g);
	if (!inFile) {
		cout << "Unable to open file " << g;
		exit(1); // terminate with error
	}

	int x;
	while (inFile >> x) {
		//cout << x << endl;//sum = sum + x;
		genome.push_back(x);
	}

	return genome;
}

GlobalFamilies*
extractGlobalFamilies(const string g1File, const string g2File)
{
	vector<int> genoma1 = readGenome(g1File);
	vector<int> genoma2 = readGenome(g2File);

	Fmly fmlyg1{ genoma1 };
	Fmly fmlyg2{ genoma2 };

	GlobalFamilies* gFmly = new GlobalFamilies{ fmlyg1, fmlyg2 };

	return gFmly;
}