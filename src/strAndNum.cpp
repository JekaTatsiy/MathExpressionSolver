#include <assert.h>
#include "../strAndNum.h"

bool belong(int beginValue, int endValue, int targetValue)
{
	return targetValue >= beginValue && targetValue <= endValue;
}

double toNumber(std::string str)
{
	std::string::iterator it = str.begin();
	std::string::iterator dot = str.end();

	if (*it == '-')
		it++;

	int pointPos = std::distance(str.begin(), std::find(str.begin(), str.end(), '.'));

	double num = 0;
	int p;

	for (int i(0); i < str.length(); i++)
		if (i != pointPos)
		{
			p = pointPos - i - 1 + int(i > pointPos);
			num += double(str[i] - 48) * pow(double(10), double(p));
		}

	return num * (it == str.begin() ? 1 : -1);
}

std::string toString(double num, int precision)
{
	bool sign = num < 0 ? true : false;
	int val = num * pow(10, precision) * (sign ? -1 : 1);
	std::string res;
	do
	{
		if (res.size() == size_t(precision))
			res.insert(res.begin(), '.');
		res.insert(res.begin(), numToChar(val % 10));
		val /= 10;
	} while (val != 0);
	if (sign)
		res.insert(res.begin(), '-');
	return res;
}

char numToChar(int num)
{
	if (belong(48, 57, num))
		return num - 48;
	else
		return '\n';
}

bool inBrackets(std::string str, int pos)
{
	int L = 0;
	int R = 0;

	std::count_if(str.begin(), str.begin() + pos,
				  [&L](char c) {  L += (c == '('); L -= (c == ')'); return true; });
	std::count_if(str.begin() + pos + 1, str.end(),
				  [&R](char c) {  R += (c == '('); R -= (c == ')'); return true; });
	if (L == 0 && R == 0)
		return false;
	if (L + R == 0)
		return true;

	return false;
}

std::string delBrackets(std::string str)
{
	if (*str.begin() != '(' || *str.rbegin() != ')')
		return str;

	int brackets = 0;
	for (size_t i(0); i < str.size(); i++)
	{
		if (str[i] == '(')
			brackets++;
		if (str[i] == ')')
			brackets--;
		if (brackets == 0 && i != 0 && i != str.size() - 1)
			return str;
	}
	if (brackets == 0)
		return delBrackets(std::string(str.begin() + 1, str.end() - 1));
	else
	{
		assert(!"����୮� ������⢮ ᪮���");
		return "";
	}
}

bool isNumber(std::string str)
{
	bool existDot = false;
	for (char i : str)
		if (belong(int('0'), int('9'), i))
		{
		}
		else if (i == '.')
			if (existDot == false)
				existDot = true;
			else
				return false;
		else
			return false;

	return true;
}

bool isVariable(std::string str)
{
	return isSmalVariable(str)||isBigVariable(str);
}

bool isSmalVariable(std::string str)
{
	bool endChar = false;
	for (char i : str)
	{
		if (belong(int('a'), int('z'), i) && !endChar)
			;
		else if (belong(int('a'), int('z'), i) && endChar)
			return false;
		else if (belong(int('0'), int('1'), i) && !endChar)
			endChar = true;
		else if (belong(int('0'), int('1'), i) && endChar)
			;
		else
			return false;
	}
	return true;
}


bool isBigVariable(std::string str)
{
	bool endChar = false;
	for (char i : str)
	{
		if (belong(int('A'), int('Z'), i) && !endChar)
			;
		else if (belong(int('A'), int('Z'), i) && endChar)
			return false;
		else if (belong(int('0'), int('1'), i) && !endChar)
			endChar = true;
		else if (belong(int('0'), int('1'), i) && endChar)
			;
		else
			return false;
	}
	return true;
}

bool isFunction(std::string str)
{
	if (std::find(str.begin(), str.end(), '(') == str.end() || std::find(str.begin(), str.end(), ')') == str.end())
		return false;
	for (size_t i(0); i < str.size() && str[i] != '('; i++)
		if (!belong(int('a'), int('z'), str[i]) && !belong(int('A'), int('Z'), str[i]))
			return false;
	return true;
}
