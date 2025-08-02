#include "Spaceship.hpp"
#include <iostream>

using namespace std;

SpaceShip::SpaceShip(string n) : name(move(n)), health(100) {}

void SpaceShip::addWeapon(unique_ptr<Weapon> weapon) 
{
    weapons.push_back(move(weapon));
}

void SpaceShip::fireWeapons() const 
{
    for (const auto& weapon : weapons) 
    {
        weapon->fire();
    }
}

void SpaceShip::repair() 
{
    health = 100;
    cout << name << " repaired.\n";
}

void SpaceShip::display() const 
{
    cout << "Ship: " << name << ", Health: " << health << '\n';
}

std::string SpaceShip::getName() const { return name; }
int SpaceShip::getHealth() const { return health; }


SpaceShip::SpaceShip(const SpaceShip& other)
    : name(other.name), health(other.health) 
{
    for (const auto& weapon : other.weapons) 
    {
        weapons.push_back(weapon->clone());  
    }
}