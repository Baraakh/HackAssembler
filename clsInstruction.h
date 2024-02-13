#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsInstruction
{
private:

public:

	enum instructionType {aInstruction = 0, cInstruction = 1};

	vector<string> getInstructionElements()
	{
		return _VInstructionElments;
	}

	virtual enum instructionType instructionType() = 0;

protected:

	vector<string> _VInstructionElments;
};

class aInstruction : public clsInstruction
{
private:

public:

	aInstruction(string value)
	{
		clsInstruction::_VInstructionElments.push_back(value);
	}

	enum instructionType instructionType()
	{
		return clsInstruction::aInstruction;
	}
};

class cInstruction : public clsInstruction
{
private:

public:

	cInstruction(string dest, string comp, string jump)
	{
		clsInstruction::_VInstructionElments.push_back(dest);
		clsInstruction::_VInstructionElments.push_back(comp);
		clsInstruction::_VInstructionElments.push_back(jump);
	}

	enum instructionType instructionType()
	{
		return clsInstruction::cInstruction;
	}
};

