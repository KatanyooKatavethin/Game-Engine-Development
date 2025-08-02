#include <iostream>
#include <iomanip>
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include "profile.hpp"

using namespace TK; 
using namespace std;

int main()
{
    App app = App();
    int select = 0;
    float r, l, h, w ;

	Circle c = Circle();

    Triangle t = Triangle();

    Square s = Square();
    
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
            c.setRadius(r);
            cout << fixed << setprecision(2);
            cout << "Answer: " << c.getArea() << endl;
            cout << "(Calculation: PI x radius x radius = 3.141 x " << r << " x " << r << " = " << 3.141f * r * r << ")" << endl;
            cout << " " << endl;
            break;

        case 2:
            cout << "Commencing triangle calculation" << endl;
            cout << "Enter the triangle's height: " << endl;
            cin >> h;
            cout << "Enter the triangle's base length: " << endl;
            cin >> l;
            t.setHBL(h,l);
            cout << fixed << setprecision(2);
            cout << "Answer: " << t.getArea() << endl;
            cout << "(Calculation: 1/2 x height x base length = 1/2 x " << h << " x " << l << " = " << 0.5f * h * l << ")" << endl;
            cout << " " << endl;
            break;

        case 3:
            cout << "Commencing square calculation" << endl;
            cout << "Enter the square's height: " << endl;
            cin >> h;
            cout << "Enter the square's width: " << endl;
            cin >> w;
            s.setHW(h, w);
            cout << fixed << setprecision(2);
            cout << "Answer: " << s.getArea() << endl;
            cout << "(Calculation: height x width = " << h << " x " << w << " = " << h * w << ")" << endl;
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
