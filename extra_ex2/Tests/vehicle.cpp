#include "vehicle.h"
#include <iostream>

using namespace std;


Vehicle::Vehicle(string b, int m, int y) {
    brand = b;
    month = m;
    year = y;
}


MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) : Vehicle(b, m, y) {
    fuel = f;
    cylinder = cyl;
}

Car::Car(string b, int m, int y, string f, int cyl): MotorVehicle(b, m, y, f, cyl)
{

}