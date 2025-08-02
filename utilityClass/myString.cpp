#include "MyString.hpp"
#include <cstring>     
#include <stdexcept>  

using namespace std;
namespace TK
{
    // The constructors
    // Default constructor
    MyString::MyString() : data(new char[1]), length(0)
    {
        data[0] = '\0';
    }

    // Constructor from C-string
    MyString::MyString(const char* str)
    {
        if (str)
        {
            length = strlen(str);
            data = new char[length + 1];
            strcpy_s(data, length + 1, str);
        }
        else
        {
            data = new char[1];
            data[0] = '\0';
            length = 0;
        }
    }

    // Copy constructor
    MyString::MyString(const MyString& other) : length(other.length), data(new char[other.length + 1])
    {
        strcpy_s(data, length + 1, other.data);
    }


    // The destructor
    MyString::~MyString()
    {
        delete[] data;
    }


    // Assignment operator
    MyString& MyString::operator=(const MyString& other)
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy_s(data, length + 1, other.data);
        }
        return *this;
    }

    // Basic operations
    size_t MyString::getLength() const
    {
        return length;
    }
    const char* MyString::getCString() const
    {
        return data;
    }

    // Basic string functions 
    char MyString::charAt(size_t index) const
    {
        if (index >= length)
        {
            throw out_of_range("Warning: Index out of range!");
        }
        return data[index];
    }
    int MyString::compare(const MyString& other) const
    {
        return strcmp(data, other.data);
    }
    bool MyString::equals(const MyString& other) const
    {
        return strcmp(data, other.data) == 0;
    }
    bool MyString::isEmpty() const
    {
        return length == 0;
    }
    MyString MyString::substring(size_t start, size_t end) const
    {
        if (start > end || end > length)
        {
            throw out_of_range("Warning: Invalid substring range!");
        }
        size_t subLength = end - start;
        char* subData = new char[subLength + 1];
        strncpy_s(subData, subLength + 1, data + start, subLength);
        subData[subLength] = '\0';

        MyString result(subData);
        delete[] subData;
        return result;
    }


    //The operators
    // Character access
    char MyString::operator[](size_t index) const
    {
        return charAt(index);
    }

    // Concatenation
    MyString MyString::operator+(const MyString& other) const
    {
        size_t newLength = length + other.length;
        char* newData = new char[newLength + 1];
        strcpy_s(newData, newLength + 1, data);
        strcat_s(newData, newLength + 1, other.data);

        MyString result(newData);
        delete[] newData;
        return result;
    }

    // The comparison operators
    //Equality
    bool MyString::operator==(const MyString& other) const
    {
        return equals(other);
    }

    // Inequality
    bool MyString::operator!=(const MyString& other) const
    {
        return !equals(other);
    }

    // Less than
    bool MyString::operator<(const MyString& other) const
    {
        return compare(other) < 0;
    }

    // Greater than
    bool MyString::operator>(const MyString& other) const
    {
        return compare(other) > 0;
    }

    // Stream output operator
    ostream& operator<<(ostream& os, const MyString& str)
    {
        os << str.data;
        return os;
    }
}