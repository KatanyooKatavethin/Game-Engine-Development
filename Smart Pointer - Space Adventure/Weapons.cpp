#include "Weapons.hpp"
#include <iostream>
#include <memory>

using namespace std;

Laser::Laser() : Weapon("Laser", 10) {}

void Laser::fire()
{
    cout << "Firing laser with power " << power << "\n";
}

unique_ptr<Weapon> Laser::clone() const
{
    return make_unique<Laser>(*this);
}

Plasma::Plasma() : Weapon("Plasma", 20) {}

void Plasma::fire()
{
    cout << "Firing plasma with power " << power << "\n";
}

unique_ptr<Weapon> Plasma::clone() const
{
    return make_unique<Plasma>(*this);
}

Missile::Missile() : Weapon("Missile", 50) {}

void Missile::fire()
{
    cout << "Launching missile with power " << power << "\n";
}

unique_ptr<Weapon> Missile::clone() const
{
    return make_unique<Missile>(*this);
}