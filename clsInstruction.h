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

