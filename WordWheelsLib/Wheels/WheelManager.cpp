#include "WheelManager.h"

// Standard Includes
#include <cassert>  // assert()
#include <fstream>	// std::ifstream
#include <sstream>

#include "../Utility/FileManager.h"
#include "../Utility/UtilityFunctions.h"

#include "Dictionary.h"

// Declarations
using std::ifstream;

WheelManager::WheelManager(int minWordSize) :
MIN_WORD_SIZE(minWordSize)
{
}

WheelManager::WheelManager(const std::string& filepath, int minWordSize) :
	WheelManager(minWordSize)
{
	LoadWheelsFromFile(filepath);
}

WheelManager::~WheelManager()
{
}

void WheelManager::LoadWheelsFromFile(const std::string& filepath)
{
	FileManager fileManager;
	std::stringstream wheelFile;

	if (fileManager.LoadFile(filepath, wheelFile))
	{
		int numWheels;
		int lettersPerWheel;

		ReadHeader(wheelFile, numWheels, lettersPerWheel);
		ReadWheels(wheelFile, numWheels, lettersPerWheel);
	}

}

void WheelManager::AddWheel(const std::string& wheel)
{
	wheels.push_back(wheel);
}

std::size_t WheelManager::GetNumWheels() const
{
	return wheels.size();
}

std::string WheelManager::GetWheel(std::size_t idx)
{
	if (idx < 0 || idx >= wheels.size())
	{
		return std::string();
	}
	else
	{
		return wheels[idx];
	}
}

void WheelManager::WheelWordsInList(const std::vector<std::string>& potentialWords, std::vector<std::string>& matchingWords)
{
	for (auto& wheel : wheels)
	{
		FindSubstringsFromList(wheel, potentialWords, matchingWords);
	}
	
}


void WheelManager::WheelWordsInDictionary(const Dictionary* dictionary, std::vector<std::string>& matchingWords)
{
	for (auto& wheel : wheels)
	{
		WordsInDictionary(wheel, dictionary, matchingWords);
	}
}

void  WheelManager::WordsInDictionary(const std::string& wheel, const Dictionary* dictionary, std::vector<std::string>& matchingWords)
{
	std::size_t endChar = wheel.length() - MIN_WORD_SIZE;

	for (std::size_t startChar = 0; startChar < endChar; ++startChar)
	{
		std::vector<std::string> potentialWords;
		dictionary->GetWordsFromKey(wheel.substr(startChar, MIN_WORD_SIZE), potentialWords);
		FindSubstringsFromList(wheel.substr(startChar), potentialWords, matchingWords);
	}
}

void WheelManager::ReadHeader(std::stringstream & wheelFile, int & numWheels, int & lettersPerWheel)
{
	wheelFile >> numWheels;
	wheelFile >> lettersPerWheel;
}

void  WheelManager::ReadWheels(std::stringstream& wheelFile, int numWheels, int lettersPerWheel)
{
	std::string wheel;
	while (wheelFile >> wheel)
	{
		wheels.push_back(wheel);
		assert(wheel.length() == lettersPerWheel);
	}
	assert(wheels.size() == numWheels);
}

