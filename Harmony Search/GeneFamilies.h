#pragma once

#include <vector>
#include <string>

class FmlyItem
{
private:
	int _key;
	std::vector<int> _positions;

public:
	FmlyItem(int token, int position) : _key(token), _positions(std::vector<int>{position}) {}
	void append(int newPos)	{ _positions.push_back(newPos);	}
	int key() { return this->_key; }
	std::vector<int> positions() { return _positions; }
};

//dictionary {gene: (positions_in_G1, positions_in_G2)}
class Fmly
{
private:
	std::vector<FmlyItem*> _items;

public:
	std::vector<FmlyItem*>
	items()	{return this->_items;}
	
	//build the dictionary
	Fmly(std::vector<int> g)
	{
		for (int pos = 0; pos < g.size(); pos++)
		{
			auto token = g[pos];
			auto item = getItem(token);
			//se o token esta na familia
			if (item)
				item->append(pos);
			else //senao
				_items.push_back(new FmlyItem(token, pos));
		}
	}

	FmlyItem*
	getItem(int token)
	{
		for (auto item : _items)
		{
			if (item->key() == token) // integer comparison
				return item;
		}
		return nullptr;
	}

};//fim Fmly

class GlobalFamilyItem
{
public:
	GlobalFamilyItem(int key, std::vector<int> posg1, std::vector<int> posg2) :
		_key{ key }, _positionsG1{ posg1 }, _positionsG2{ posg2 }{};

	int key() { return _key; }
	std::vector<int> posg1() { return _positionsG1; }
	std::vector<int> posg2() { return _positionsG2; }

	~GlobalFamilyItem() {};

private:
	int _key;
	std::vector<int> _positionsG1;
	std::vector<int> _positionsG2;
};

//dictionary {geneName : [list of positions of geneName in g1], [list of positions of geneName in g2]}
class GlobalFamilies
{
public:
	GlobalFamilies(Fmly& fmly1, Fmly& fmly2)
	{
		for (auto itemOne : fmly1.items())
		{
			if (auto itemTwo = fmly2.getItem(itemOne->key()))
			{
				_items.push_back(new GlobalFamilyItem(itemOne->key(), itemOne->positions(), itemTwo->positions()));
			}
		}
	}

	std::vector<GlobalFamilyItem*> items() { return _items; }
	~GlobalFamilies() {};

private:
	std::vector<GlobalFamilyItem*> _items;
}; // fim GlobalFamilies

void
printGlobalFamilies(GlobalFamilies* gf);

std::vector<int>
readGenome(const std::string gName);

GlobalFamilies*
extractGlobalFamilies(const std::string g1File, const std::string g2File);
