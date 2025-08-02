#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Weapons.hpp"

using namespace std;

class SpaceShip 
{
    string name;
    int health;
    vector< unique_ptr<Weapon>> weapons;
public:
    SpaceShip(std::string n);
    SpaceShip(const SpaceShip& other);
    void addWeapon(unique_ptr<Weapon> weapon);
    void fireWeapons() const;
    void repair();
    void display() const;
    string getName() const;
    int getHealth() const;
};

