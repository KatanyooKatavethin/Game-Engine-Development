#include "Spaceship.hpp"
#include "Weapons.hpp"
#include "Crewmates.hpp"
#include <cassert>

using namespace std; 

void repairShip(SpaceShip& ship) 
{
    cout << "\n[Repairing Ship]\n";
    ship.repair();
}

SpaceShip cloneShip(const SpaceShip& ship) 
{
    cout << "\n[Cloning Ship]\n";
    return ship; 
}

void displayStatus(SpaceShip ship) 
{
    cout << "\n[Displaying Ship Status]\n";
    ship.display();
}

void upgradeWeapon(Weapon* weapon) 
{
    cout << "\n[Upgrading Weapon]\n";
    weapon->fire(); 
}

int main() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto enterprise = make_shared<SpaceShip>("USS Enterprise (NCC1701)");

    enterprise->addWeapon(make_unique<Laser>());
    enterprise->addWeapon(make_unique<Plasma>());
    enterprise->addWeapon(make_unique<Missile>());

    Crew captain(enterprise, "Kirk");
    Crew helmsman(enterprise, "Sulu");
    Crew chiefEngineer(enterprise, "Scotty");

    captain.performDuty();
    helmsman.performDuty();
    chiefEngineer.performDuty();

    cout << "\n[Firing Weapons]\n";
    enterprise->fireWeapons();

    displayStatus(*enterprise);    
    repairShip(*enterprise);      
    SpaceShip copy = cloneShip(*enterprise);
    copy.display();

    cout << "\n[Test upgradeWeapon function]";
    Missile testMissile;
    upgradeWeapon(&testMissile);

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}