// WordWheels.cpp : Defines the entry point for the console application.
#include <stdlib.h>
#include <iostream>
#include <Wheels\Dictionary.h>
#include <Wheels\WheelManager.h>
#include <Utility\FileConstants.h>
#include <Utility\CommonTypes.h>


int main(int argc, char* argv[])
{
	using namespace FileConstants;
	using namespace Wheels;

	std::cout << "Loading Dictionary.." << std::endl;
	Dictionary dictionary(DICTIONARY_PATH);

	std::cout << "Loading Wheels.." << std::endl;
	WheelManager wheelManager(WHEELS_PATH);

	std::cout << "Finding words.." << std::endl;
	StringVec foundWords;
	wheelManager.WheelWordsInDictionary(&dictionary, foundWords);
	
	std::cout << "Found words.." << std::endl;
	for (auto& word : foundWords)
	{
		std::cout << word << std::endl;
	}
	std::cout << "Num Words Found: " << foundWords.size() << std::endl;

	std::cout << argc << std::endl;
	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}
	system("pause");
    return 0;
}

