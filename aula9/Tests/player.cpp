#include "player.h"

void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const
{
    unsigned c = 0;
	auto bet_it = bets.begin();
	while(bet_it != bets.end()){
	    if (bet_it->contains(num))
	        c++;
	    bet_it++;
	}
	return c;
}

tabHBet Player::drawnBets(const tabHInt& draw) const
{
    tabHBet ht;
    ht.clear();
    auto bets_it = bets.begin();
    while(bets_it != bets.end()){
        if (bets_it->countRights(draw) > 3)
            ht.insert(*bets_it);
        bets_it++;
    }
    return ht;
}
