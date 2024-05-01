#pragma once
#include <iostream>
#include <fstream>

#ifndef TEMP_STRING_BUFFER_SIZE
#define TEMP_STRING_BUFFER_SIZE 100
#endif

class StringArray;

class String
{
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend std::istream &operator>>(std::istream &, String &);
    friend String operator+(const char *, const String &);
    friend String operator+(const char &, const String &);

private:
    int length;
    char *str;

    static int GetStringLength(const char *);
    static char *CloneString(const char *);
    static int CompareString(const char *, const char *);

    static char *ConcatenateString(const char *, const char *);
    static char LowerCaseCharacter(const char &);
    static char UpperCaseCharacter(const char &);

public:
    String();
    String(const String &);
    String(const char &);
    String(const char *);
    ~String();

    String &operator=(const String &);
    String &operator=(const char *);

    String operator+(const String &) const;
    String &operator+=(const String &);

    int Compare(const String &) const;
    int Compare(const char *) const;
    bool operator==(const String &) const;
    bool operator>(const String &) const;
    bool operator>=(const String &) const;
    bool operator<(const String &) const;
    bool operator<=(const String &) const;
    bool operator!=(const String &) const;

    int GetLength() const;
    const char *GetConstCharArray() const;
    String GetSubstring(const int &, int = -1) const;
    StringArray Split(const char & = 0) const;
    int ToInteger() const;
    int Find(const String &) const;

    String &ToLowerCase();
    String &ToUpperCase();
    String LowerCase() const;
    String UpperCase() const;

    bool StartsWith(const String &) const;
    bool EndsWith(const String &) const;

    static String GetStringFromStream(std::istream &, const int & = TEMP_STRING_BUFFER_SIZE, const char & = '\n');
    static String FromInteger(int);
};

class StringArray
{
private:
    int length;
    String **arr;

public:
    StringArray();
    StringArray(const int &);
    StringArray(const int &, const String *);

    StringArray(const StringArray &);
    StringArray &operator=(const StringArray &);

    int GetLength() const;

    StringArray &Remove(const int &);
    String PopBack();
    StringArray &PushBack(const String &);
    StringArray &Swap(const int &, const int &);
    String At(const int &) const;
    String Join(const String & = "") const;
    String &operator[](const int &);

    ~StringArray();
};