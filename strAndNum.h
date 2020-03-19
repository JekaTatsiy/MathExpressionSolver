#pragma once
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
bool isfunction(std::string str);
