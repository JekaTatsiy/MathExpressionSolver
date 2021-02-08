#ifndef STR_AND_NUM_H
#define STR_ADN_NUM_H

#include <string>
#include <algorithm>
#include <cmath>
#include <assert.h>


bool belong(int beginValue, int endValue, int targetValue);

double toNumber(std::string str);
int charToNumber(char sym);
std::string toString(double num, int precision);
char numToChar(int num);

bool inBrackets(std::string str, int pos);
std::string delBrackets(std::string str);

bool isNumber(std::string str);
bool isVariable(std::string str);
bool isSmalVariable(std::string str);
bool isBigVariable(std::string str);
bool isFunction(std::string str);

#endif
