#pragma once
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Weapon
{
protected:
    string type;
    int power;

public:
    Weapon(std::string t, int p) : type(move(t)), power(p) {}
    virtual void fire() = 0;
    virtual unique_ptr<Weapon> clone() const = 0; 
    virtual ~Weapon() = default;
};

class Laser : public Weapon
{
public:
    Laser();
    void fire() override;
    unique_ptr<Weapon> clone() const override;
};

class Plasma : public Weapon
{
public:
    Plasma();
    void fire() override;
    unique_ptr<Weapon> clone() const override;
};

class Missile : public Weapon
{
public:
    Missile();
    void fire() override;
    unique_ptr<Weapon> clone() const override;
};