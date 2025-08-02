#pragma once
#include <memory>
#include <string>
#include "Spaceship.hpp"

using namespace std;

class Crew 
{
    shared_ptr<SpaceShip> assignedShip;
    string role;
public:
    Crew(shared_ptr<SpaceShip> ship, string r);
    void performDuty() const;
};

