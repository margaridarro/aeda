#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;


Client::Client() {
    numGifts = (rand() % 5) + 1;
}

unsigned Client::getNumGifts() const {
    return numGifts;
}

Counter::Counter(unsigned wt): wrappingTime(wt)
{
    numAttendedClients = 0;
    actualTime = 0;
    nextEnter = (rand() % 20) + 1;
    nextLeave = 0;
}

unsigned Counter::getActualTime() const {
    return actualTime;
}

unsigned Counter::getNextEnter() const {
    return nextEnter;
}

unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}


unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

unsigned Counter::getNextLeave() const {
    return nextLeave;
}

Client & Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    return clients.front();
}

void Counter::enter()
{
    cout << "time= " << actualTime<< endl;
    Client client;
    if (clients.empty())
        nextLeave = actualTime + client.getNumGifts() * wrappingTime;
    clients.push(client);
    cout << "entering a new client with " << client.getNumGifts() << " gifts" << endl;
    nextEnter = actualTime + (rand() %20) + 1;
}

void Counter::leave()
{
    cout << "time = " << actualTime << endl;
    Client client;
    try
    {
        client = getNextClient();
    }
    catch (EmptyQueue &e)
    {
        cout << e.getMsg() << endl;
        return;
    }
    clients.pop();
    cout << "client attended: " << client.getNumGifts() << " gifts" << endl;
    numAttendedClients++;
    if (!clients.empty())
        nextLeave = actualTime + clients.front().getNumGifts() * wrappingTime;
}

//TODO
void Counter:: nextEvent()
{
    if (!clients.empty() && nextLeave <= nextEnter)
    {
        actualTime = nextLeave;
        leave();
    }
    else
    {
        actualTime = nextEnter;
        enter();
    }
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
    out << "number of attended clients: " << c2.numAttendedClients << endl;
    out << "number of waiting clients: " << c2.clients.size() << endl;
    return out;
}


