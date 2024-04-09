#include "String.h"
using namespace std;

StringArray::StringArray() : length(0), arr(nullptr){};

StringArray::StringArray(const int &len) : length(len)
{
    if (length <= 0)
    {
        throw invalid_argument("Length should be greater than 0.");
    }
    arr = new String *[len];
    for (int i = 0; i < len; i++)
    {
        arr[i] = new String();
    }
};

StringArray::StringArray(const int &len, const String *stringArr) : length(len), arr(new String *[len])
{
    if (length <= 0)
    {
        throw invalid_argument("Length should be greater than 0.");
    }
    if (!stringArr)
    {
        throw invalid_argument("String Array can't be empty.");
    }
    arr = new String *[len];
    for (int i = 0; i < len; i++)
    {
        arr[i] = new String(stringArr[i]);
    }
};

StringArray &StringArray::operator=(const StringArray &rhs)
{
    if (this == &rhs)
        return *this;
    delete[] arr;
    length = rhs.length;
    arr = new String *[length];
    for (int i = 0; i < length; i++)
    {
        arr[i] = new String(*rhs.arr[i]);
    }
    return *this;
}

int StringArray::GetLength()
{
    return length;
}

StringArray &StringArray::Remove(const int &index)
{
    if (index < 0 || index >= length)
    {
        throw invalid_argument("Index out of Range.");
    }
    delete arr[index];
    String **newArr = new String *[length - 1];
    for (int i = 0, j = 0; i < length; i++)
    {
        if (i != index)
        {
            newArr[j++] = arr[i];
        }
    }
    delete[] arr;
    arr = newArr;
    length--;
    return *this;
}

String StringArray::PopBack()
{
    String out = *arr[length - 1];
    delete arr[length - 1];
    length--;
    String **newArr = new String *[length];
    for (int i = 0; i < length; i++)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    return out;
}

StringArray &StringArray::PushBack(const String &str)
{
    String **newArr = new String *[length + 1];
    for (int i = 0; i < length; i++)
    {
        newArr[i] = arr[i];
    }
    newArr[length++] = new String(str);
    delete[] arr;
    arr = newArr;
    return *this;
}

StringArray &StringArray::Swap(const int &index1, const int &index2)
{
    if (index1 < 0 || index1 >= length)
    {
        throw invalid_argument("Index 1 out of Range.");
    }
    if (index2 < 0 || index2 >= length)
    {
        throw invalid_argument("Index 2 out of Range.");
    }
    if (index1 == index2)
        return *this;
    String *temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
    return *this;
}

String &StringArray::operator[](const int &index)
{
    if (index < 0 || index >= length)
    {
        throw invalid_argument("Index out of Range.");
    }
    return *arr[index];
}

StringArray::~StringArray()
{
    for (int i = 0; i < length; i++)
    {
        delete arr[i];
    }
    delete[] arr;
}