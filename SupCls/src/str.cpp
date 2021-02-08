#include "../str.h"

USING_MATSOLV

int strlen(const char *line)
{
    int i = 0;
    for (; line[i] != '\0'; i++)
        ;
    return i;
}

str::str(const char *inp)
{
    length = strlen(inp);
    this->data = new char[length + 1];
    for (int i = 0; i < length; i++)
        this->data[i] = inp[i];
    this->data[length] = '\0';
}

str::str(const str &other) : str(other.data) {}

str::~str()
{
    clear();
}

/*std::ostream &operator<<(std::ostream &os, const str &at)
{
    for (int i = 0; i < at.length; os << at.data[i], i++)
        ;
    return os;
}

void str::print()
{
    std::cout << *this << std::endl;
}*/

str &str::operator=(const char *other)
{
    if (this->data != nullptr)
        delete[] data;
    this->data = new char[length + 1];
    for (int i = 0; i < length; i++)
        this->data[i] = other[i];
    this->data[length] = '\0';
    return *this;
}
str &str::operator=(const str &other)
{
    *this = other.data;
    return *this;
}
str &str::operator+=(const char *other)
{
    int newLength = length + strlen(other);
    char *newStr = new char[newLength + 1];
    int i = 0;
    for (; i < this->length; i++)
        newStr[i] = this->data[i];
    for (int j = 0; j < strlen(other); j++, i++)
        newStr[i] = other[j];
    newStr[newLength] = '\0';
    delete[] this->data;
    this->data = newStr;
    length = newLength;
    return *this;
}
str &str::operator+=(const str &other)
{
    *this += other.data;
    return *this;
}

int str::len()
{
    return length;
}

bool str::operator==(const str &other)
{
    if (this->length != other.length)
        return false;
    for (int i = 0; i < length; i++)
        if (this->data[i] != other.data[i])
            return false;
    return true;
}
bool str::operator!=(const str &other)
{
    return !(this->operator==(other));
}
char &str::operator[](int index)
{
    return this->data[index];
}
bool str::is_empty()
{
    return (this->data == nullptr) || (data[0] == '\0');
}
void str::clear()
{
    delete[] this->data;
    length = 0;
    data = nullptr;
}

int str::find(const str &other) //searches the first occurrence of the sequence
{
    for (int i = 0; i < length; i++)
    {
        if (data[i] == other.data[0])
            for (int j = 0; j < other.length; j++)
            {
                if (data[i + j] != other.data[j])
                    break;
                if (j == other.length - 1)
                    return i;
            }
    }

    return -1;
}

int str::find(const char other) //searches the first occurrence of the symbol
{
    for (int i = 0; i < length; i++)
        if (data[i] == other)
            return i;
    return -1;
}

void str::cutThis(int beg, int end)
{
    if (beg > end || beg < 0 || end < 0 || beg > length || end > length)
        return;
    char *newData = new char[end - beg + 2];
    for (int i = beg; i <= end; i++)
        newData[i - beg] = data[i];
    length=end-beg+1;
    delete[] data;
    data=newData;
    return;
}
str str::cutInNew(int beg, int end)
{
    str res;
    if (beg > end || beg < 0 || end < 0 || beg > length || end > length)
        return res;
    char *newData = new char[end - beg + 2];
    for (int i = beg; i <= end; i++)
        newData[i - beg] = data[i];
    res.length=end-beg+1;
    res.data=newData;
    return res;
}
