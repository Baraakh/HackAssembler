#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "clsInstruction.h";
#include "strUtilities.h";
using namespace std;

class clsInstructionsTranslator
{
private:
	class symbolTable
	{
	private:

		map<string, string> _SymbolTable;

		int variableAllocationCounter = 16;

	public:

		symbolTable()
		{
			_SymbolTable = { {"R0", "0"},
				{"R1", "1"},
				{"R2", "2"},
				{"R3", "3"},
				{"R4", "4"},
				{"R5", "5"},
				{"R6", "6"},
				{"R7", "7"},
				{"R8", "8"},
				{"R9", "9"},
				{"R10", "10"},
				{"R11", "11"},
				{"R12", "12"},
				{"R13", "13"},
				{"R14", "14"},
				{"R15", "15"},
				{"SCREEN", "16384"},
				{"KBD", "24576"},
				{"SP", "0"},
				{"LCL", "1"},
				{"ARG", "2"},
				{"THIS", "3"},
				{"THAT", "4"} };
		}

		void setLabel(string key, string value)
		{
			_SymbolTable[key] = value;
		}

		string getSymbolValue(string key)
		{
			// check type of symbol

			if (_SymbolTable.find(key) != _SymbolTable.end())
			{
				return _SymbolTable[key];
			}
			
			_SymbolTable[key] = to_string(variableAllocationCounter);
			variableAllocationCounter++;

			return _SymbolTable[key];
		}

	};

	map<string, string> _MapDest;

	map<string, string> _MapComp;

	map<string, string> _MapJump;

	string inputFileLocation;

	symbolTable _SymbolTable;

	void FirstPass()
	{
		fstream assemblyFile;
		assemblyFile.open(this->inputFileLocation, ios::in);//read Mode

		if (assemblyFile.is_open())
		{

			string Line;
			int currentLineNumber = 0;

			while (getline(assemblyFile, Line))
			{

				// check for label, so we can save it 
				string instruction = trim(removeComments(Line));

				if (instruction == "") continue; // means that the Line is simply a whitespace or comment 

				size_t openlabelSymbolIndex = instruction.find("(");

				if (openlabelSymbolIndex != string::npos)
				{
					size_t closelabelSymbolIndex = instruction.find(")");

					string labelSymbol = instruction.substr(openlabelSymbolIndex + 1, closelabelSymbolIndex - (openlabelSymbolIndex + 1));

					_SymbolTable.setLabel(labelSymbol, to_string(currentLineNumber));

					continue;
				}

				currentLineNumber++;

			}

			assemblyFile.close();

		}
	}

public:

	clsInstructionsTranslator(string inputFileLocation)
	{
		this->inputFileLocation = inputFileLocation;

		FirstPass();

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

			string strBinValue;

			if (!is_number(aInstructionElements[0]))
			{
				strBinValue = decTo15Bin(_SymbolTable.getSymbolValue(aInstructionElements[0]));
			}
			else
			{
				strBinValue = decTo15Bin(aInstructionElements[0]);
			}
			
			return ("0" + strBinValue);
		}
		else if (clsInstruction::cInstruction == instruction->instructionType())
		{
			vector<string> cInstructionElements = instruction->getInstructionElements();

			return "111" + _MapComp[cInstructionElements[1]] + _MapDest[cInstructionElements[0]] + _MapJump[cInstructionElements[2]];
		}
	}

};

