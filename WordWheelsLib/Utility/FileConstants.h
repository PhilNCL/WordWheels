#pragma once
// Filename:	FileConstants.h
// Description: A collection of constants related to File I/O in WordWheels
// Author:		Philip Jones
// Date:		11/03/18
// Notes:	

// Standard Includes
#include <string>	// std::string

namespace FileConstants
{
	const std::string TEXT_DIRECTORY = "../Data/Text/";

	const std::string DICTIONARY_PATH = TEXT_DIRECTORY + "dictionary.txt";
	const std::string WHEELS_PATH = TEXT_DIRECTORY + "wheels.txt";

	const std::string OUTPUT_PATH = "myOutput.txt";

	const std::string TEST_PATH = TEXT_DIRECTORY + "TextFile.txt";
	const std::string TEST_DICTIONARY_PATH = TEXT_DIRECTORY + "TestDictionary.txt";
	const std::string TEST_WHEELS_PATH = TEXT_DIRECTORY + "TestWheels.txt";
	const std::string TEST_SMALL_WHEELS_PATH = TEXT_DIRECTORY + "TestSmallWheels.txt";
}

