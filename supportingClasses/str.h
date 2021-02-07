#ifndef STR_H
#define STR_H
#include <iostream>

class str
{
	char *data;
	int length;

public:
	str() : data(nullptr), length(0) {}
	str(const char *inp);
	str(const str &other);
	~str();
	void clear();

	friend std::ostream &operator<<(std::ostream &os, const str &at);
	void print();

	int len();
	char &operator[](int index);
	bool is_empty();

	str &operator=(const str &other);
	str &operator=(const char *other);
	str &operator+=(const str &other);
	str &operator+=(const char *other);

	bool operator==(const str &other);
	bool operator!=(const str &other);

	int find(const str &other); //searches the first occurrence of the sequence
	int find(const char other); //searches the first occurrence of the symbol

	void cutThis(int beg, int end);
	str cutInNew(int beg, int end);
};

#endif