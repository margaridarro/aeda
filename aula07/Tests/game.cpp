#include "game.h"
#include <sstream>


ostream &operator << (ostream &os, Circle &c1)
{
    string stateStr;
    if (c1.state) stateStr="true"; else stateStr="false";
    os << c1.points << "-" << stateStr  << "-" << c1.nVisits << endl;
    return os;
}

BinaryTree<Circle> Game::initiateGame(int pos, int level, vector<int> &points, vector<bool> &states)
{
    Circle c1(points[pos],states[pos]);
    if (level==0) return BinaryTree<Circle>(c1);
    BinaryTree<Circle> leftChild = initiateGame(2 * pos + 1, level - 1, points, states);
    BinaryTree<Circle> rightChild = initiateGame(2 * pos + 2, level - 1, points, states);
    return BinaryTree<Circle>(c1, leftChild, rightChild);
}

Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game=initiateGame(0,h,points,states);
}

string Game::writeGame()
{
    BTItrLevel<Circle> it(game);
    stringstream gameStr("");
    while (!it.isAtEnd()){
        gameStr << it.retrieve();
        it.advance();
    }

	return gameStr.str();
}

int Game::move()
{
    int pos = 1, nPoints = 1, n, i;
    bool state;
    BTItrLevel<Circle> it(game);
    if (it.isAtEnd()) return nPoints;
    while(!it.isAtEnd())
    {
        Circle &c = it.retrieve();
        if (c.getState()) n = pos + 1;
        else n = pos;
        c.changeState();
        c.incNVisits();
        nPoints = c.getPoints();
        i = 0;
        while (i < n && !it.isAtEnd())
        {
            it.advance();
            i++;
        }
        if(!it.isAtEnd()) pos += n;
        else break;
    }
    return nPoints;
}

int Game::mostVisited()
{
    BTItrLevel<Circle> it(game);
    it.advance();
    int visits = it.retrieve().getNVisits();
	while (!it.isAtEnd())
	{
	    if(visits < it.retrieve().getNVisits())
	        visits = it.retrieve().getNVisits();
	    it.advance();
	}
	return visits;
}
