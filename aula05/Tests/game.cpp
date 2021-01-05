#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game()
{
	this->kids.clear();
}

Game::Game(list<Kid>& l2)
{
	this->kids = l2;
}

void Game::addKid(const Kid &k1)
{
 	kids.push_back(k1);
}

list<Kid> Game::getKids() const
{
	return this->kids;
}


string Game::write() const
{
	stringstream oss;
	list<Kid>::const_iterator it = kids.begin();
	list<Kid>::const_iterator ite = kids.end();
	while ( it != ite )
	{
		oss << it->write() << endl;
		it++;
	}
	return oss.str();
}


Kid& Game::loseGame(string phrase)
{
	int nw = numberOfWords(phrase)-1;
	list<Kid>::iterator it = kids.begin();
	list<Kid>::iterator ite = kids.end();
	while (kids.size()>1)
	{
		int nk = kids.size();
		int p = nw%nk;
		for (int i=1; i<=p ; i++) {
			it++;
			if (it == ite ) it = kids.begin();
		}
		cout << "leaves: " << it->write() << endl;
		it = kids.erase(it);
		if (it == ite ) it = kids.begin();
	}
	return *it;
}


list<Kid>& Game::reverse()
{
	/*
	list<Kid> l1;
	list<Kid>::iterator it = kids.begin();
	list<Kid>::iterator ite = kids.end();
	while ( it != ite )
	{
		Kid *k=new Kid(*it);
		l1.push_front(*k);
		it ++;
	}
	kids = l1;
	*/
	kids.reverse();
	return this->kids;
}


list<Kid> Game::removeOlder(unsigned id)
{
	list<Kid> l1;
	list<Kid>::iterator it = kids.begin();
	list<Kid>::iterator ite = kids.end();
	while ( it != ite )
	{
		if ( it->getAge() > id )
		{
			l1.push_back(*it);
			it=kids.erase(it);
		}
		else
			it++;
	}
	return l1;
}


void Game::setKids(const list<Kid>& l1)
{
	this->kids = l1;
}


bool Game::operator==(Game& g2)
{
	if( this->kids.size() != g2.kids.size() ) return false;

	list<Kid>::iterator it1 = this->kids.begin();
	list<Kid>::iterator ite = this->kids.end();
	list<Kid>::iterator it2 = g2.kids.begin();

	for(; it1 != ite; it1++, it2++){
		if( !((*it1) == (*it2)) ) return false;
	}
	return true;
}


list<Kid> Game::shuffle() const
{
	list<Kid> tempList = this->kids;
	list<Kid> newList;

	int rPos;
	/* initialize random seed: */
	srand(time(NULL) );

	while( !tempList.empty() ){
		/* generate a random position: */
		rPos = rand() % tempList.size();
		list<Kid>::iterator it = tempList.begin();
		for(unsigned i = 0; i < rPos; i++, it++);
		newList.push_back(*it);
		tempList.erase(it);
	}

	return newList;
}
