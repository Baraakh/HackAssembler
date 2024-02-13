#include <iostream>
#include <vector>
#include "clsHackParser.h";
#include "clsInstructionsTranslator.h";
using namespace std;


int main()
{
	

	clsInstruction* instruction = clsHackParser::parseInstruction("  MD=D+1 // test  ");

	clsInstructionsTranslator translator;

	cout << translator.ConvertInstructionToBinary(instruction) << endl;
	

    return 0;
}

