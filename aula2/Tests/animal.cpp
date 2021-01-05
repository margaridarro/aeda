#include "animal.h"
#include <sstream>
using namespace std;


Animal::Animal(string name, int age){
    this-> name = name;
    this-> age = age;
}

bool Dog:: isYoung() const{
    if(age < 5) return true;
    return false;
}

Dog::Dog(string name, int age, string breed) : Animal(name, age){
    this-> name = name;
    this-> age = age;
    this-> breed = breed;

}

Flying::Flying(int maxv, int maxa){
    maxVelocity = maxv;
    maxAltitude = maxa;
}

Bat::Bat(string name, int age, int maxv, int maxa) : Animal(name, age), Flying(maxv, maxa){}

bool Bat::isYoung() const
{
    if(age < 4) return true;
    return false;
}

/*
 * getters & setters
 */

string Animal::getName() const {
    return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

int Animal::getYoungest() {
    return youngest;
}