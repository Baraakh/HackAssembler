#pragma once
#include <iostream>
#include <string>
using namespace std;

string removeComments(string str)
{
	size_t found = str.find("//");

	if (found != string::npos)
	{
		return str.substr(0, found);
	}

	return str;
}

string trimLeft(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			return str.substr(i, str.length() - i);
		}
	}

	return "";
}

string trimRight(string str)
{
	for (int i = str.length() - 1; -1 < i; i--)
	{
		if (str[i] != ' ')
		{
			return str.substr(0, i + 1);
		}
	}

	return "";
}

string trim(string str)
{
	return trimRight(trimLeft(str));
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

string decTo15Bin(string Dec)
{
	string strBin = "";

	int num = stoi(Dec);

	while (num > 0)
	{
		int temp = num % 2;

		strBin += to_string(temp);

		num /= 2;
	}

	if (strBin.size() < 15)
	{
		int emptyBitsLenght = 15 - strBin.size();

		for (int i = 0; i < emptyBitsLenght; i++)
		{
			strBin += "0";
		}
	}

	reverse(strBin.begin(), strBin.end());

	return strBin;
}



