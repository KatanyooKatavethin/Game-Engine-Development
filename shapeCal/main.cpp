#include <iostream>
#include <iomanip>
#include "profile.hpp"

using namespace std;
using namespace TK;

int main()
{

    App app = App();
    int select = 0;
    float r, l, h, w, b ;

    while (true)
    {
        unsigned int select = 0;
        app.printMenu();
        cin >> select;
        

        switch (select)
        {
         case 0:
            cout << "Exit GeoCal";
            break;

         case 1:
            cout << "Commencing circle calculation" << endl;
            cout << "Enter the circle's radius: " << endl;
            cin >> r;
            cout << fixed << setprecision(2);
            cout << "Answer: " << app.cirCal(r) << endl;
            cout << " " << endl;
            break;

         case 2:
            cout << "Commencing triangle calculation" << endl;
            cout << "Enter the triangle's base length: " << endl;
            cin >> l;
            cout << "Enter the triangle's height: " << endl;
            cin >> h;
            cout << fixed << setprecision(2);
            cout << "Answer: " << app.triCal(l,h) << endl;
            cout << " " << endl;
            break;

         case 3:
             cout << "Commencing square calculation" << endl;
             cout << "Enter the square's height: " << endl;
             cin >> h;
             cout << "Enter the square's width: " << endl;
             cin >> w;
             cout << fixed << setprecision(2);
             cout << "Answer: " << app.squaCal(h, w) << endl;
             cout << " " << endl;
             break;

         default:
             cout << "default option" << endl;
        }

        if (select == 0)
        {
            break;
        }

    }
}

