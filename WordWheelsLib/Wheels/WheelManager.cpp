// Filename:	WheelManager.cpp
// Description: Methods for WheelManager.h
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		Duplicate letters in the same wheel do not give any additional
//				words therefore wheel size is capped to 24 (for the Roman 
//				alphabet). 
//				Consider 10 wheels in following configuration
//				| A | C | T | I | V | I | S | I | O | N |
//				if in the next configuration only the letter V changes
//				| A | C | T | I | Q | I | S | I | O | N |
//				then to increase efficiency the unchanged substrings (AC, ACT, ACTI, CTI, SIO, 
//				SION, ION,...) are not searched again. Furthermore a new dictionary is not 
//				generated. Instead words beginning with IV and VI are replaced with those beginning 
//				IQ and QI (assuming a word size of 2). Potential dictionary words are also
//				culled by the amount of remaining characters. In this example SING and SIT would
//				be in the potential word list but SITUATION is not considered (as there is no wrapping)

#include "WheelManager.h"

// Standard Includes
#include <cassert>  // assert()
#include <fstream>	// std::ifstream
#include <sstream>  // std::stringstream
#include <thread>   // std::thread

// Utility Includes
#include "../Utility/FileManager.h"			// FileManager
#include "../Utility/UtilityFunctions.h"    // MakeStringUnique(), FindSubstringsFromList()
#include "../Utility/ErrorMessaging.h"		// HandleError()


// Wheel Includes
#include "Dictionary.h"				// Dictionary
#include "ConfigurationManager.h"   // ConfigurationManager
#include "VectorDictionary.h"       // GenerateDictionary(), UpdateDictionary()

// Namespace Declarations
using std::ifstream;
using namespace Wheels;

WheelManager::WheelManager(std::size_t minWordSize) :
	MIN_WORD_SIZE(minWordSize)
{}

WheelManager::WheelManager(const std::string& filepath, std::size_t minWordSize) :
	WheelManager(minWordSize)
{
	LoadWheelsFromFile(filepath);
}

WheelManager::~WheelManager()
{}


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

void WheelManager::FindWordsInDictionary(const Dictionary& dictionary) 
{
	if (wheels.empty())
	{
		return;
	}
	matchingWords.clear();

	std::vector<std::thread> threads;
	for (std::size_t startCharIdx = 0; startCharIdx < wheels[FIRST_WHEEL_IDX].length(); ++startCharIdx)
	{
		threads.push_back(std::thread(&WheelManager::CheckWheelCombinations, this, std::ref(startCharIdx), std::ref(dictionary)));
	}

	for (auto& thread : threads) 
	{
		thread.join();
	}
}


void WheelManager::CheckWheelCombinations(std::size_t startCharIdx, 
										 const Dictionary& dictionary)
{
	ConfigurationManager configuration(GetMaxWheelIndices(), startCharIdx);

	// Initial Pass
	std::string configString = BuildString(configuration.GetCurrentConfig());
	AddSubstringsInDictionary(configString, MIN_WORD_SIZE, dictionary);

	//  Run Algorithm
	CheckAllConfigurations(configuration, dictionary);
}

void WheelManager::CheckAllConfigurations(ConfigurationManager& configuration, 
										  const Dictionary& dictionary) 
{
	std::vector<std::vector<std::string>> targetDictionary;
	std::string configString = BuildString(configuration.GetCurrentConfig());
	GenerateDictionary(configString, dictionary, targetDictionary, MIN_WORD_SIZE);
	while (!configuration.IsFinalConfiguration())
	{
		std::vector<StringVec> potentialWords(configString.size() - 1);

		configuration.NextConfiguration();
		configString = BuildString(configuration.GetCurrentConfig());

		UpdateDictionary(configString, targetDictionary, dictionary, configuration.GetLastChangedIndex(), MIN_WORD_SIZE);
		GenerateNewSubstrings(configString, configuration.GetLastChangedIndex(), configuration.GetLowestChangedIndex(), MIN_WORD_SIZE, potentialWords);

		AddWordsFromVectorDictionary(targetDictionary, potentialWords);
	}
}

void WheelManager::ReadHeader(std::stringstream & wheelFile, 
							  std::size_t& numWheels, 
							  std::size_t& lettersPerWheel) const
{
	wheelFile >> numWheels;
	wheelFile >> lettersPerWheel;
	if (numWheels < MIN_WORD_SIZE || lettersPerWheel <= 0)
	{
		HandleError(Errors::INVALID_FILE_HEADER);
	}

}

void WheelManager::RemoveDuplicateLetters()
{
	for (auto& wheel : wheels)
	{
		MakeStringUnique(wheel);
	}
}


void  WheelManager::ReadWheels(std::stringstream& wheelFile, 
							   std::size_t numWheels, 
							   std::size_t lettersPerWheel)
{
	std::string wheel;
	while (wheelFile >> wheel)
	{
		wheels.push_back(wheel);
		if (wheel.length() != lettersPerWheel)
		{
			if (numWheels < MIN_WORD_SIZE || lettersPerWheel <= 0)
			{
				HandleError(Errors::INVALID_FILE_FORMAT);
			}
		}
	
	}
	if (wheels.size() != numWheels)
	{
		HandleError(Errors::INVALID_FILE_FORMAT);
	};
}

bool WheelManager::LoadWheelsFromFile(const std::string& filepath)
{
	FileManager fileManager;
	std::stringstream wheelFile;

	if (fileManager.LoadFile(filepath, wheelFile))
	{
		std::size_t numWheels;
		std::size_t lettersPerWheel;

		ReadHeader(wheelFile, numWheels, lettersPerWheel);
		ReadWheels(wheelFile, numWheels, lettersPerWheel);

		RemoveDuplicateLetters();

		return true;
	}
	else
	{
		HandleError(Errors::FILE_LOAD_FAILED, filepath);
		return false;
	}

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



void  WheelManager::AddWordsFromVectorDictionary(std::vector <StringVec>& currentDictionary, 
												 std::vector <StringVec>& potentialWords)
{
	assert(currentDictionary.size() == potentialWords.size());

	for (std::size_t idx = 0; idx < currentDictionary.size(); ++idx)
	{
		for (auto& word : potentialWords[idx])
		{
			if (std::find(currentDictionary[idx].begin(), currentDictionary[idx].end(), word) != currentDictionary[idx].end())
			{
				AddFoundWord(word);
			}
		}
	}
}

void  WheelManager::AddSubstringsInDictionary(const std::string& string, 
											  std::size_t minWordSize, 
											  const Dictionary& dictionary)
{
	std::size_t endChar = string.length() - minWordSize;
	StringVec foundWords;
	for (std::size_t startChar = 0; startChar <= endChar; ++startChar)
	{
		StringVec potentialWords;
		dictionary.GetWordsFromKey(string.substr(startChar, minWordSize), potentialWords);
		FindSubstringsFromList(string.substr(startChar), potentialWords, foundWords);
	}

	for (auto& word : foundWords)
	{
		AddFoundWord(word);
	}
}


void WheelManager::AddFoundWord(std::string newWord)
{
	std::lock_guard<std::mutex> guard(matchingWordMutex);
	matchingWords.push_back(newWord);
}
