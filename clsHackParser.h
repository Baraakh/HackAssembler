#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsInstruction.h";
#include "strUtilities.h";
#include "clsInstructionsTranslator.h"
using namespace std;

class clsHackParser
{
private:

	static bool isAInstruction(string str)
	{
		return str[0] == '@';
	}

	static bool isCInstruction(string str)
	{
		return !(isAInstruction(str));
	}

	static string getAInstructionValue(string str)
	{
		return str.substr(1, str.length() - 1);
	}

	static vector<string> getCInstruction(string str)
	{

		vector<string> CInstructionParts;

		size_t dest = str.find("=");
		if (dest != string::npos)
		{
			CInstructionParts.push_back(str.substr(0, dest));
		}
		else
		{
			dest = -1;
			CInstructionParts.push_back("0");
		}

		size_t comp = str.find(";");
		if (comp != string::npos)
		{
			CInstructionParts.push_back(str.substr(dest + 1, comp - (dest + 1)));
		}
		else
		{
			CInstructionParts.push_back(str.substr(dest + 1, str.length() - dest + 1));
			CInstructionParts.push_back("0");
			return CInstructionParts;
		}

		// check for jump
		for (short i = comp + 1; i < str.length(); i++)
		{
			CInstructionParts.push_back(str.substr(comp + 1, str.length() - comp + 1));
		}

		return CInstructionParts;
	}

public:

	static clsInstruction* parseInstruction(string strInstruction)
	{
		string instruction = trim(removeComments(strInstruction));

		if (instruction == "") return nullptr;

		if (instruction[0] == '(') return nullptr; // if it's a label then Ignore it.

		if (isAInstruction(instruction))
		{
			return new aInstruction(getAInstructionValue(instruction));
		}
		else if (isCInstruction(instruction))
		{
			vector<string> vCInstruction = getCInstruction(instruction);

			return new cInstruction(vCInstruction[0], vCInstruction[1], vCInstruction[2]);
		}
	}

};