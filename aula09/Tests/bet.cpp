#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


bool Bet::contains(unsigned num) const {
    auto it = numbers.find(num);
    return !(it == numbers.end());
}

void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    numbers.clear();
    int i = 0;
    while(n)
    {
        pair<tabHInt::iterator, bool> res = numbers.insert(values[i]);
        if (res.second) n--;
        i++;
    }
}

unsigned Bet::countRights(const tabHInt& draw) const
{
    unsigned rights = 0;
	auto it = draw.begin();
	while(it != draw.end())
	{
	    if(contains(*it)) rights++;
	    it++;
	}
	return rights;
}

