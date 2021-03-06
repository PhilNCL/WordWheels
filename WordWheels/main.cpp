// Filename:	WordWheels.cpp
// Description: A collection of useful functions for working with strings
// Author:		Philip Jones
// Date:		11/03/18
// Notes:

// Standard Includes
#include <iostream> // std::cout std::cin
#include <fstream>

// Utility Includes
#include <Utility\CommonTypes.h>	  // StringVec
#include <Utility\FileConstants.h>    // FileConstants::
#include <Utility\ErrorMessaging.h>   // PrintErrorToConsole()
#include <Utility\UtilityFunctions.h> // PrintStrings()

// Wheel Includes
#include <Wheels\Dictionary.h>		  // Dictionary
#include <Wheels\WheelManager.h>      // WheelManager

// Sets up filepaths from command line arguments. If no arguments passed sets up defaults
void ValidateCommandLineArgs(int argc, char* argv[], Wheels::StringVec& filepaths);

// Prints output to console and file
void PrintOutput(const Wheels::StringVec& foundWords);

int main(int argc, char* argv[])
{
	using namespace FileConstants;
	using namespace Wheels;

	std::vector<std::string> filepaths;
	ValidateCommandLineArgs(argc, argv, filepaths);

	std::cout << "Loading Wheels.." << std::endl;
	WheelManager wheelManager(filepaths[0]);

	std::cout << "Loading Dictionary.." << std::endl;
	Dictionary dictionary(filepaths[1]);

	std::cout << "Finding words.." << std::endl;
	std::cout << "(Warning: Large example file takes approx 2 minutes on my machine...)" << std::endl;
	wheelManager.FindWordsInDictionary(dictionary);
	
	std::cout << "Found words.." << std::endl;
	StringVec foundWords = wheelManager.GetFoundWords();
	PrintOutput(foundWords);

	std::cin.get();
    return 0;
}

void ValidateCommandLineArgs(int argc, char* argv[], Wheels::StringVec& filepaths)
{
	using namespace FileConstants;
	if (argc == 1)
	{
		HandleError(Errors::NO_ARGUMENTS);
		std::cout << "Trying default file paths..." << std::endl;
		filepaths.push_back(WHEELS_PATH);
		filepaths.push_back(DICTIONARY_PATH);
	}
	for (int i = 1; i < argc; ++i)
	{
		filepaths.push_back(argv[i]);
	}
}

// Prints output to console and file
void PrintOutput(const Wheels::StringVec& foundWords)
{
	using namespace FileConstants;

	PrintStrings(std::cout, foundWords);
	std::ofstream outFile(OUTPUT_PATH);
	if (outFile)
	{
		PrintStrings(outFile, foundWords);
	}

}