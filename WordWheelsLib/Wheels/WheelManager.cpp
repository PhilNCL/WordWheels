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
using namespace Wheels;

WheelManager::WheelManager(std::size_t minWordSize) :
MIN_WORD_SIZE(minWordSize)
{
}

WheelManager::WheelManager(const std::string& filepath, std::size_t minWordSize) :
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
		std::size_t numWheels;
		std::size_t lettersPerWheel;

		ReadHeader(wheelFile, numWheels, lettersPerWheel);
		InitaliseWheels(numWheels, lettersPerWheel);
		ReadWheels(wheelFile, numWheels, lettersPerWheel);
		RemoveDuplicateLetters();
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

std::string WheelManager::GetWheel(std::size_t idx) const
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

void WheelManager::WheelWordsInList(const StringVec& potentialWords, StringVec& matchingWords) const
{
	for (auto& wheel : wheels)
	{
		FindSubstringsFromList(wheel, potentialWords, matchingWords);
	}
}

#include<iostream>

void WheelManager::WheelWordsInDictionary(const Dictionary* dictionary, StringVec& matchingWords) const
{

	// TODO: What if wheels is empty???
	for (std::size_t startCharIdx = 0; startCharIdx < wheels[0].length(); ++startCharIdx)
	{
		std::cout << startCharIdx + 1 << " out of " << wheels[0].length() << std::endl;
		CheckWheelCombinations(startCharIdx, dictionary, matchingWords);
	}
}

// Requires valid input
void WheelManager::CheckWheelCombinations(std::size_t startCharIdx, const Dictionary* dictionary, StringVec& matchingWords) const
{
	const int FIRST_WHEEL_IDX = 0;
	const int SECOND_WHEEL_IDX = FIRST_WHEEL_IDX + 1;

	// Create Maximum Indices
	std::vector<std::size_t> maximumIndices;
	for (std::size_t wheelIdx = FIRST_WHEEL_IDX; wheelIdx < wheels.size(); ++wheelIdx)
	{
		maximumIndices.push_back(wheels[wheelIdx].length() - 1);
	}

	std::vector<std::size_t> wheelConfiguration = maximumIndices;
	wheelConfiguration[0] = startCharIdx;
	
	std::vector<std::vector<std::string>> targetDictionary;

	// Fist pass
	std::string configString = BuildString(wheelConfiguration);
	GenerateDictionary(configString, dictionary, targetDictionary, MIN_WORD_SIZE);
	configString = BuildString(wheelConfiguration);
	WordsInDictionary(configString, MIN_WORD_SIZE, dictionary, matchingWords);
	// Refresh Pass
	std::size_t lowestChangedIndex = configString.size() - 1;
	while (!IsFinalConfiguration(wheelConfiguration))
	{
		std::size_t chopIndex;
		std::vector<StringVec> potentialWords(configString.size() - 1); //TODO: - 1 with MIN_WORDS?
		NextConfiguration(wheelConfiguration, maximumIndices, chopIndex);
		if (chopIndex < lowestChangedIndex)
		{
			lowestChangedIndex = chopIndex;
			std::cout << lowestChangedIndex <<std::endl;
		}
		configString = BuildString(wheelConfiguration);
		RefreshDictionary(configString, targetDictionary, dictionary, chopIndex, MIN_WORD_SIZE);
		BreakString(configString, chopIndex, lowestChangedIndex, MIN_WORD_SIZE, potentialWords);
		MatchingWordsInDictionary(targetDictionary, potentialWords, matchingWords);
	}
}


void WheelManager::ReadHeader(std::stringstream & wheelFile, std::size_t& numWheels, std::size_t& lettersPerWheel) const
{
	wheelFile >> lettersPerWheel;
	wheelFile >> numWheels;
}

void WheelManager::InitaliseWheels(std::size_t numWheels, std::size_t lettersPerWheel)
{
	wheels.resize(numWheels);
	for (auto& wheel : wheels)
	{
		wheel.resize(lettersPerWheel);
	}
}


void  WheelManager::ReadWheels(std::stringstream& wheelFile, std::size_t numWheels, std::size_t lettersPerWheel)
{
	std::string row;
	StringVec rows;
	while (wheelFile >> row)
	{
		rows.push_back(row);
		assert(row.length() == numWheels);
	}
	assert(rows.size() == lettersPerWheel);

	for (std::size_t charIdx = 0; charIdx < rows.size(); ++charIdx)
	{
		for (std::size_t wheelIdx = 0; wheelIdx < wheels.size(); ++wheelIdx)
		{
			wheels[wheelIdx][charIdx] = rows[charIdx][wheelIdx];
		}
	}
}

void WheelManager::RemoveDuplicateLetters()
{
	for (auto& wheel : wheels)
	{
		MakeStringUnique(wheel);
	}
}


bool WheelManager::IsFinalConfiguration(const std::vector<std::size_t>& configuration) const
{
	const int FIRST_WHEEL_IDX = 0;
	const int SECOND_WHEEL_IDX = FIRST_WHEEL_IDX + 1;

	for (int idx = SECOND_WHEEL_IDX; idx < wheels.size(); ++idx)
	{
		if (configuration[idx])
		{
			return false;
		}
	}
	return true;
}

std::string  WheelManager::BuildString(std::vector<std::size_t> configuration) const
{
	assert(configuration.size() == wheels.size());

	std::string wheelConfiguration;

	for (auto wheel = 0; wheel < wheels.size(); ++wheel)
	{
		wheelConfiguration.push_back(wheels[wheel][configuration[wheel]]);
	}
	return wheelConfiguration;
}

/*
ANRT
ELNOT
CHMTI
CEJOS
0444
*/