#include <iostream>
#include <vector>
#include "clsHackParser.h"
using namespace std;

int main()
{
	
	clsInstruction* instruction = clsHackParser::parseInstruction("  D=D-M;JMP // test  ");

	if (clsInstruction::aInstruction == instruction->instructionType())
	{
			cout << "A instruction" << endl;
			vector<string> aInstructionElements = instruction->getInstructionElements();
			cout << "Value: " << aInstructionElements[0] << endl;
	}
	else if (clsInstruction::cInstruction == instruction->instructionType())
	{
			cout << "C instruction" << endl;
			vector<string> cInstructionElements = instruction->getInstructionElements();
			cout << "Dest: " << cInstructionElements[0] << " Comp: " << cInstructionElements[1] << " Jump: " << cInstructionElements[2] << endl;
	}

    return 0;
}

