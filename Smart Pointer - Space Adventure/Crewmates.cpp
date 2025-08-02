#include "Crewmates.hpp"
#include <iostream>

using namespace std;

Crew::Crew(shared_ptr<SpaceShip> ship, string r)
    : assignedShip(move(ship)), role(move(r)) {}

void Crew::performDuty() const 
{
    cout << role << " performing duty on the " << assignedShip->getName() << "\n";
}
