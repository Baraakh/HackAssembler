#pragma once
#include <iostream>
#include <string>
#include <map>
#include "clsInstruction.h";
using namespace std;

class clsInstructionsTranslator
{
private:

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

	map<string, string> _MapDest;

	map<string, string> _MapComp;

	map<string, string> _MapJump;

public:

	clsInstructionsTranslator()
	{
		_MapDest = { {"0", "000"},
				{"M", "001"},
				{"D", "010"},
				{"MD", "011"},
				{"A", "100"},
				{"AM", "101"},
				{"AD", "110"},
				{"AMD", "111"}};

		_MapJump = { {"0", "000"},
				{"JGT", "001"},
				{"JEQ", "010"},
				{"JGE", "011"},
				{"JLT", "100"},
				{"JNE", "101"},
				{"JLE", "110"},
				{"JMP", "111"} };

		_MapComp = { {"0", "0101010"},
				{"1", "0111111"},
				{"-1", "0111010"},
				{"D", "0001100"},
				{"A", "0110000"},
				{"M", "1110000"},
				{"!D", "0001101"},
				{"!A", "0110001"},
				{"!M", "1110001"},
				{"-D", "0001111"},
				{"-A", "0110011"},
				{"-M", "1110011"},
				{"D+1", "0011111"},
				{"A+1", "0110111"},
				{"M+1", "1110111"},
				{"D-1", "0001110"},
				{"A-1", "0110010"},
				{"M-1", "1110010"},
				{"D+A", "0000010"},
				{"D+M", "1000010"},
				{"D-A", "0010011"},
				{"D-M", "1010011"},
				{"A-D", "0000111"},
				{"M-D", "1000111"},
				{"D&A", "0000000"},
				{"D&M", "1000000"},
				{"D|A", "0010101"},
				{"D|M", "1010101"}};
	}

	string ConvertInstructionToBinary(clsInstruction* instruction)
	{

		if (clsInstruction::aInstruction == instruction->instructionType())
		{
			vector<string> aInstructionElements = instruction->getInstructionElements();

			string strBinValue = decTo15Bin(aInstructionElements[0]);

			return ("0" + strBinValue);
		}
		else if (clsInstruction::cInstruction == instruction->instructionType())
		{
			vector<string> cInstructionElements = instruction->getInstructionElements();

			return "111" + _MapComp[cInstructionElements[1]] + _MapDest[cInstructionElements[0]] + _MapJump[cInstructionElements[2]];
		}
	}


};

