#include "MyString.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
using namespace TK;

int main() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MyString s1("Hello ");
    MyString s2("World");
    MyString s3 = s1 + s2;
    MyString sub = s3.substring(6, 11);

    cout << "s3: " << s3 << endl;
    cout << "Length (including space): " << s3.getLength() << endl;
    cout << "Character at index 0 (First letter): " << s3.charAt(0) << endl;

    // Check comparison and copy operations
    if (s1 == MyString("Hello ")) 
    {
        cout << "s1 equals 'Hello ', the comparison operator works correctly." << endl;
    }

    if (s2 == MyString("World"))
    {
        cout << "s2 equals 'World', the comparison operator works correctly." << endl;
    }

    if (s3 == MyString(s1 + s2))
    {
        cout << "s3 equals 'Hello World', the comparison operator works correctly." << endl;
    }

    if (s1 != s2) 
    {
        cout << "s1 and s2 are not equal, the comparison operator works correctly." << endl;
    }

    if (s3 == MyString("Hello World"))
    {
        cout << "The concatenation works correctly (s1 + s2 = s3)." << endl;
    }

    if (s3.charAt(0) == 'H' && s3.charAt(6) == 'W') 
    {
        cout << "charAt() works correctly." << endl;
    }

    if (sub == MyString("World")) 
    {
        cout << "substring() works correctly." << endl;
    }

    if (s3.getLength() == 11) 
    {
        cout << "For 'Hello World', or other phases with the string length of 11, getLength() works correctly." << endl;
    }

    return 0;

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}