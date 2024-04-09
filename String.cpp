#include "String.h"
using namespace std;

const int TEMP_STRING_BUFFER_SIZE = 100;

String::String() : length(0), str(new char[1]{0}){};

String::String(const String &str2) : length(str2.length)
{
    str = CloneString(str2.str);
}

String::String(const char &c) : length(1), str(new char[2]{c, 0}){};

String::String(const char *str2)
{
    length = GetStringLength(str2);
    str = CloneString(str2);
}

String::~String()
{
    delete[] str;
}

String &String::operator=(const String &str2)
{
    if (this == &str2)
        return *this;
    delete[] str;
    length = str2.length;
    str = CloneString(str2.str);
    return *this;
}

String &String::operator=(const char *str2)
{
    delete[] str;
    length = GetStringLength(str2);
    str = CloneString(str2);
    return *this;
}

String &String::operator+=(const String &str2)
{
    char *temp = str;
    str = ConcatenateString(str, str2.str);
    length = GetStringLength(str);
    delete[] temp;
    return *this;
}

String String::operator+(const String &str2)
{
    String out;
    delete[] out.str;
    out.str = ConcatenateString(str, str2.str);
    out.length = GetStringLength(out.str);
    return out;
}

String operator+(const char *str, const String &str2)
{
    String out;
    delete[] out.str;
    out.str = String::ConcatenateString(str, str2.str);
    out.length = String::GetStringLength(out.str);
    return out;
}

String operator+(const char &str, const String &str2)
{
    return String(str) + str2;
}

int String::Compare(const String &str2) const
{
    return CompareString(str, str2.str);
}

int String::Compare(const char *str2) const
{
    return CompareString(str, str2);
}

bool String::operator==(const String &str2) const
{
    return (this->Compare(str2) == 0);
}
bool String::operator>(const String &str2) const
{
    return (this->Compare(str2) == 1);
}
bool String::operator>=(const String &str2) const
{
    return (this->Compare(str2) != -1);
}
bool String::operator<(const String &str2) const
{
    return (this->Compare(str2) == -1);
}
bool String::operator<=(const String &str2) const
{
    return (this->Compare(str2) != 1);
}
bool String::operator!=(const String &str2) const
{
    return (this->Compare(str2) != 0);
}

int String::GetLength() const
{
    return length;
}

const char *String::GetConstCharArray() const
{
    return str;
}

String String::GetSubstring(const int& begin, int len) const
{
    if (begin < 0 || begin >= length)
    {
        throw invalid_argument("Starting Index out of range");
    }
    if (len < 0 || begin + len > length)
    {
        len = length - begin;
    }
    String out;
    out.length = len;
    out.str = new char[len + 1]{0};
    for (int i = 0, j = begin; i < len; i++, j++)
    {
        out.str[i] = str[j];
    }
    return out;
}

int String::ToInteger() const
{
    int num = 0;
    int sign = 1;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == '-' && sign == 1)
        {
            sign *= -1;
            continue;
        }
        if (str[i] >= '0' && str[i] <= '9')
        {
            num *= 10;
            num += str[i] - '0';
            continue;
        }
        break;
    }
    return sign * num;
}

int String::GetStringLength(const char *str)
{
    if (!str)
        return 0;
    int size = 0;
    while (str[size] != 0)
        size++;
    return size;
}

char *String::CloneString(const char *str)
{
    int size = GetStringLength(str);
    char *outString = new char[size + 1];
    if (size == 0)
    {
        outString[0] = 0;
        return outString;
    }
    for (int i = 0; i <= size; i++)
    {
        outString[i] = str[i];
    }
    return outString;
}

int String::CompareString(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i])
        i++;
    if (str1[i] > str2[i])
        return 1;
    if (str1[i] < str2[i])
        return -1;
    return 0;
}

char *String::ConcatenateString(const char *str1, const char *str2)
{
    int len1 = GetStringLength(str1);
    int len2 = GetStringLength(str2);
    char *newString = new char[len1 + len2 + 1];
    for (int i = 0; i < len1; i++)
    {
        newString[i] = str1[i];
    }
    for (int i = 0; i < len2; i++)
    {
        newString[len1 + i] = str2[i];
    }
    newString[len1 + len2] = 0;
    return newString;
}

String String::ReadStringFromFile(ifstream &infile, const char &delim)
{
    char buffer[TEMP_STRING_BUFFER_SIZE];
    infile.getline(buffer, TEMP_STRING_BUFFER_SIZE - 1, delim);
    return buffer;
}

String String::FromInteger(int num)
{
    String out;
    if (num == 0)
    {
        return "0";
    }
    bool isNeg = false;
    if (num < 0)
    {
        isNeg = true;
        num *= -1;
    }
    while (num > 0)
    {
        out = (num % 10)+'0' + out;
        num /= 10;
    }
    return ((isNeg) ? "-" : "") + out;
}

ostream &operator<<(ostream &out, const String &str)
{
    out << str.str;
    return out;
}

ifstream &operator>>(ifstream &infile, String &str)
{
    char buffer[TEMP_STRING_BUFFER_SIZE];
    infile >> buffer;
    str = buffer;
    return infile;
}