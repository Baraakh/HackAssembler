#include <iostream>
#include <fstream>
#include <string>
#include "clsHackParser.h";
#include "clsInstructionsTranslator.h";
using namespace std;


int main(int argc, char* argv[])
{
	clsInstructionsTranslator translator;

    string inputFileLocation = "";
    string outputFileLocation = "Output.hack";

    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " -i input_filename -n output_filename\n";
        return 1;
    }

    // Process command-line arguments
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-i" || arg == "-I") {
            if (i + 1 < argc) {
                inputFileLocation = argv[i + 1];
                cout << "Input filename: " << inputFileLocation << endl;
                ++i; // Skip the next argument (filename)
            }
            else {
                cerr << "Error: Missing filename after -i flag\n";
                return 1;
            }
        }
        else if (arg == "-n" || arg == "-N") {
            if (i + 1 < argc) {
                outputFileLocation = argv[i + 1];
                cout << "Output filename: " << outputFileLocation << endl;
                ++i; // Skip the next argument (filename)
            }
            else {
                cerr << "Error: Missing filename after -n flag\n";
                return 1;
            }
        }
    }
    
	fstream assemblyFile;
	assemblyFile.open(inputFileLocation, ios::in);//read Mode

    fstream BinaryOutputFile;
    BinaryOutputFile.open(outputFileLocation, ios::out);//overwrite

    if (assemblyFile.is_open())
    {

        string Line;

        while (getline(assemblyFile, Line))
        {

            clsInstruction* instruction = clsHackParser::parseInstruction(Line);

            if (instruction != nullptr)
            {
                BinaryOutputFile << translator.ConvertInstructionToBinary(instruction) << "\n";
            }
        }

        assemblyFile.close();
        BinaryOutputFile.close();

    }

    return 0;
}

