#include "profile.hpp"

#include <iostream>
using namespace std;

namespace TK
{
    App::App() {}

    void App::printMenu()
    {
        cout << "Hello Ta, please select the menu" << endl;
        cout << "----------------------------" << endl;
        cout << "1: Calculate the area of a circle " << endl;
        cout << "2: Calculate the area of a triangle " << endl;
        cout << "3: Calculate the area of a square " << endl;
        cout << "0: Exit GeoCal" << endl;
        cout << "----------------------------" << endl;
        cout << "please select : ";
    }

    float App::cirCal(float r)
    {
        return 3.1415 * (r * r);
    }

    float App::triCal(float l, float h)
    {
        return 0.5f * (l * h);
    }

    float App::squaCal(float h, float w)
    {
        return h * w ;
    }

}
