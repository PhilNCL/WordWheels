// Filename:	WheelManager.cpp
// Description: Methods for WheelManager.h
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		
#include "WheelManager.h"

// Standard Includes
#include <cassert>  // assert()
#include <fstream>	// std::ifstream
#include <sstream>  // std::stringstream
#include <thread>   // std::thread

// Utilities
#include "../Utility/FileManager.h"
#include "../Utility/UtilityFunctions.h"

// Other Includes
#include "Dictionary.h"
#include "ConfigurationManager.h"

// Namespace Declarations
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
	if (idx >= wheels.size())
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


void WheelManager::WheelWordsInDictionary(const Dictionary* dictionary, StringVec& matchingWords) const
{
	if (wheels.empty())
	{
		return;
	}
	std::vector<std::thread> threads;
	for (std::size_t startCharIdx = 0; startCharIdx < wheels[0].length(); ++startCharIdx)
	{
		//threads.push_back(std::thread(&WheelManager::CheckWheelCombinations, this, std::ref(startCharIdx), std::ref(dictionary), std::ref(matchingWords)));
		CheckWheelCombinations(startCharIdx, dictionary, matchingWords);
	}

	for (auto& thread : threads) 
	{
		thread.join();
	}
}


void WheelManager::CheckWheelCombinations(std::size_t startCharIdx, const Dictionary* dictionary, StringVec& matchingWords) const
{
	ConfigurationManager configuration(GetMaxWheelIndices(), startCharIdx);

	// Initial Pass
	std::string configString = BuildString(configuration.GetCurrentConfig());
	WordsInDictionary(configString, MIN_WORD_SIZE, dictionary, matchingWords);

	//  Run Algorithm
	CheckAllConfigurations(configuration, dictionary, matchingWords);
}

void WheelManager::CheckAllConfigurations(ConfigurationManager& configuration, const Dictionary* dictionary, StringVec& matchingWords) const
{
	std::vector<std::vector<std::string>> targetDictionary;
	std::string configString = BuildString(configuration.GetCurrentConfig());
	GenerateDictionary(configString, dictionary, targetDictionary, MIN_WORD_SIZE);
	while (!configuration.IsFinalConfiguration())
	{
		std::vector<StringVec> potentialWords(configString.size() - 1);

		configuration.NextConfiguration();
		configString = BuildString(configuration.GetCurrentConfig());


		// Words which are on consecutive wheels
		RefreshDictionary(configString, targetDictionary, dictionary, configuration.GetLastChangedIndex(), MIN_WORD_SIZE);
		BreakString(configString, configuration.GetLastChangedIndex(), configuration.GetLowestChangedIndex(), MIN_WORD_SIZE, potentialWords);

		MatchingWordsInDictionary(targetDictionary, potentialWords, matchingWords);

		// Non-consecutive wheels

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
	const int SECOND_WHEEL_IDX = FIRST_WHEEL_IDX + 1;

	for (std::size_t idx = SECOND_WHEEL_IDX; idx < wheels.size(); ++idx)
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

	for (std::size_t wheel = 0; wheel < wheels.size(); ++wheel)
	{
		wheelConfiguration.push_back(wheels[wheel][configuration[wheel]]);
	}
	return wheelConfiguration;
}

std::vector<std::size_t> WheelManager::GetMaxWheelIndices() const
{
	std::vector<std::size_t> maxIndices;
	for (std::size_t wheelIdx = FIRST_WHEEL_IDX; wheelIdx < wheels.size(); ++wheelIdx)
	{
		maxIndices.push_back(wheels[wheelIdx].length() - 1);
	}
	return maxIndices;
}
