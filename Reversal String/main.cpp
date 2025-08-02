#include <iostream>

using namespace std;

void reverseString(char* thePointer);

void reverseString(char* thePointer)
{
    int i = strlen(thePointer) - 1; 
    while (i >= 0)
    {
        cout << *(thePointer + i);
        i--; 
    }
}

int main()
{
    char g[100] = "";
    cout << "Enter a string (Only 100 Characters): ";
    cin.getline(g, 100);
    cout << "Original string: " << g << endl;
    char* pointerG = g;
    cout << "Reversed string: ";
    reverseString(pointerG);
    return 0;
}