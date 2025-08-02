#include <iostream>
//Build a light - weight utility string class.Make sure to follow C++ best practice, to test your class extensively, and checking your memory leaks.
//------------------------------------------------

using namespace std;
namespace TK
{
    class MyString
    {
    private:
        char* data;
        size_t length;

    public:
        // Constructors
        MyString();
        MyString(const char* str);
        MyString(const MyString& other);

        // Destructor
        ~MyString();

        // Assignment operator
        MyString& operator=(const MyString& other);

        // Basic operations
        size_t getLength() const;
        const char* getCString() const;

        // Basic string functions 
        char charAt(size_t index) const;
        int compare(const MyString& other) const;
        bool equals(const MyString& other) const;
        bool isEmpty() const;
        MyString substring(size_t start, size_t end) const;

        // Operators
        char operator[](size_t index) const;
        MyString operator+(const MyString& other) const;
        bool operator==(const MyString& other) const;
        bool operator!=(const MyString& other) const;
        bool operator<(const MyString& other) const;
        bool operator>(const MyString& other) const;

        // Friend function for stream output
        friend ostream& operator<<(ostream& os, const MyString& str);
    };
}