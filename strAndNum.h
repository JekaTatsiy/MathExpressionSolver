#ifndef STR_AND_NUM_H
#define STR_ADN_NUM_H

#include <string>
#include <cmath>
#include <algorithm>

bool belong(int beginValue, int endValue, int targetValue);

double toNumber(std::string str);
std::string toString(double num, int precision);
char numToChar(int num);

bool inBrackets(std::string str, int pos);
std::string delBrackets(std::string str);

bool isNumber(std::string str);
bool isVariable(std::string str);
bool isFunction(std::string str);

#endif
