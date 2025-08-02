#include <iostream>
#include "dynamicArray.hpp"
#include <cassert>

using namespace std;
using namespace TK;

void check_capacity(const DynamicArray<int>& arr) 
{
    if (arr.capacity() > 10) 
    {
        cout << "The vector buffer is full, the size has now been doubled: Current capacity = " << arr.capacity() << endl;
    }
}

int main() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    DynamicArray<int> arr;

    cout << "Initial capacity size: " << arr.capacity() << "\n";

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(8);
    arr.push_back(9);
    arr.push_back(10);
    arr.push_back(11);


    check_capacity(arr);
    cout << "--------------------------------------------" << "\n";
    cout << "" << "\n";

    cout << "First element: " << arr.front() << "\n";
    cout << "Last element: " << arr.back() << "\n";
    cout << "Size: " << arr.size() << ", Capacity: " << arr.capacity() << "\n";
    cout << "--------------------------------------------" << "\n";
    cout << "" << "\n";
    arr.dump();
    cout << "--------------------------------------------" << "\n";
    cout << "" << "\n";

    size_t beforePopCapacity = arr.capacity();
    arr.pop_back();  
    size_t afterPopCapacity = arr.capacity();

    cout << "Removed one element using pop_back()\n";
    cout << "Size after removal: " << arr.size() << "\n"; 
    cout <<  "Capacity: " << afterPopCapacity << "\n";

    if (beforePopCapacity == afterPopCapacity)
        cout << "Size of the capacity did not shrink after removing an element.\n";
    if (beforePopCapacity > afterPopCapacity)
    {
        cout << "Size of the capacity shrank after removing an element.\n";
    }
    cout << "--------------------------------------------" << "\n";
    cout << "" << "\n";

    return 0;

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}