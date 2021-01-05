#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;


bool InfoCard::operator==(const InfoCard &i1) const
{
    return name == i1.name;
}
bool InfoCard::operator <(const InfoCard &i1) const
{
    if (frequency < i1.frequency) return false;
    else if (frequency > i1.frequency) return true;
    else return name < i1.name;
}

bool compName(const InfoCard &i1, const InfoCard &i2)
{
    return i1.name < i2.name;
}

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

int CarPark::clientPosition(const string & name) const
{
    InfoCard info;
    info.name = name;
    return sequentialSearch(clients, info);
}

unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if (pos == -1) throw ClientDoesNotExist(name);
    return clients[pos].frequency;
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    info.frequency = 0;
    clients.push_back(info);
    return true;
}

bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    freePlaces--;
    clients[pos].frequency++;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}

InfoCard CarPark::getClientAtPos(unsigned p) const
{
    if (p >= clients.size()) throw PositionDoesNotExist(p);
    return clients[p];
}

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

void CarPark::sortClientsByName()
{
    sort(clients.begin(), clients.end(), compName);
}

vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    sortClientsByFrequency();
    vector<string> names;

    for (auto & client : clients)
        if (client.frequency >= f1 && client.frequency <= f2)
            names.push_back(client.name);

    return names;
}

ostream & operator<<(ostream & os, const CarPark & cp)
{
    for(const auto & c: cp.clients)
        os << "name: " << c.name << " present: " << c.present << " frequency: " << c.frequency << endl;
    return os;
}
