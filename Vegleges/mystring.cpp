#include "mystring.h"
#include "memtrace.h"

MyString::MyString(const char *str)
{
    len = strlen(str);
    pData = new char[len + 1];
    strcpy(pData, str);
}

MyString::MyString(const char c)
{
    len = 1;
    pData = new char[len + 1];
    pData[0] = c;
    pData[len] = '\0';
}

MyString::MyString(const MyString &s)
{
    len = s.len;
    pData = new char[len + 1];
    strcpy(pData, s.pData);
}

MyString &MyString::operator=(const MyString &s)
{
    if (this != &s)
    {
        delete[] pData;
        len = s.len;
        pData = new char[len + 1];
        strcpy(pData, s.pData);
    }
    return *this;
}

MyString MyString::operator+(const MyString &s) const
{
    MyString temp;
    temp.len = len + s.len;
    delete[] temp.pData;
    temp.pData = new char[temp.len + 1];
    strcpy(temp.pData, pData);
    strcat(temp.pData, s.pData);
    return temp;
}

MyString MyString::operator+(const char c) const
{
    return *this + MyString(c);
}

MyString &MyString::operator+=(const MyString &s)
{
    *this = *this + s;
    return *this;
}

MyString &MyString::operator+=(const char c)
{
    *this = *this + c;
    return *this;
}

char &MyString::operator[](size_t index)
{
    if (index >= len)
    {
        throw std::out_of_range("Tul nagy index!");
    }
    return pData[index];
}

const char &MyString::operator[](size_t index) const
{
    if (index >= len)
    {
        throw std::out_of_range("Tul nagy index!");
    }
    return pData[index];
}

bool MyString::operator==(const MyString &s) const
{
    return strcmp(pData, s.pData) == 0;
}

bool MyString::operator!=(const MyString &s) const{
        return !(*this == s);
    }

bool MyString::operator<(const MyString &s) const
{
    return strcmp(pData, s.pData) < 0;
}

bool MyString::operator>(const MyString &s) const
{
    return strcmp(pData, s.pData) > 1;
}

const char *MyString::c_str() const
{
    return pData;
}

MyString::~MyString()
{
    delete[] pData;
}

std::ostream &operator<<(std::ostream &os, const MyString &s)
{
    return os << s.c_str();
}

std::istream &operator>>(std::istream &is, MyString &s)
{
    char ch;
    s = MyString("");
    is.setf(std::ios_base::skipws);
    while (is >> ch)
    {
        is.unsetf(std::ios_base::skipws);
        if (isspace(ch) && ch != ' ')
        {
            is.putback(ch);
            break;
        }
        else
        {
            s += ch;
        }
    }
    is.setf(std::ios_base::skipws);
    return is;
}

size_t MyString::size()const{
    return len;
}
