#ifndef STRING_H
#define STRING_H
#endif 

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;

class TCharArray
{
protected:
    size_t len;
    const char* pMem;

public:
    TCharArray(const char* str) {
        pMem = str;
        len = strlen(str);
    }

    const char& at(const size_t n) const {

        return pMem[n];

    }

};

class String :public TCharArray {

public:
    String() : TCharArray("") {}
    String(const char* str) : TCharArray(str) {}
        
    const char* GetString();
    int GetLen();
    void SetString(const char* str);

    const char& operator[](const int index);
    friend std::ostream& operator<< (std::ostream& out, const String& str);
    String& operator+(String& str);
    friend bool operator== (const String& s21, const String& s2);
    friend bool operator!= (const String& s21, const String& s2);
    friend bool operator> (const String& s1, const String& s2);
    friend bool operator< (const String& s1, const String& s2);

};

void String::SetString(const char* str) { pMem = str;}
const char* String::GetString() {return TCharArray::pMem;}
int String::GetLen() {return len;}

std::ostream& operator<< (std::ostream& out, const String& str) {
    for (int i = 0; i < str.len; i++) {

        out << str.at(i);

    }

    return out;
}

const char& String::operator[](const int index) {
    
    if (index >= len) { throw - 1; }

    return TCharArray::at(index);}
String& String::operator+(String& str) {
    String result;
    size_t len1 = GetLen();
    size_t len2 = str.len;
    size_t len3 = len1 + len2;
    char* resultStr = new char[len3];
    strcpy(resultStr, GetString());
    strcat(resultStr, str.pMem);
    result.SetString(resultStr);
    str = result;

    return str;
}
bool operator== (const String& s1, const String& s2) {
    return (s1.pMem == s2.pMem);
}
bool operator!= (const String& s1, const String& s2) {
    return !(s1.pMem == s2.pMem);
}
bool operator> (const String& s1, const String& s2) {

    string s1_str(s1.pMem);
    string s2_str(s2.pMem);
    return s1_str > s2_str;
}
bool operator< (const String& s1, const String& s2) {

    string s1_str(s1.pMem);
    string s2_str(s2.pMem);

    return s1_str < s2_str;

}
