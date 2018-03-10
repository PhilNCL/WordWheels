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



void WheelManager::WheelWordsInDictionary(const Dictionary* dictionary, StringVec& matchingWords) const
{

	// TODO: What if wheels is empty???
	for (std::size_t startCharIdx = 0; startCharIdx < wheels[0].length(); ++startCharIdx)
	{
		StringVec potentialWords;
		CheckWheelCombinations(startCharIdx);
	}
}

// Requires valid input
void WheelManager::CheckWheelCombinations(std::size_t startCharIdx) const
{
	const int FIRST_WHEEL_IDX = 0;
	const int SECOND_WHEEL_IDX = FIRST_WHEEL_IDX + 1;

	// Create Maximum Indices
	std::vector<std::size_t> maximumIndices;
	for (std::size_t wheelIdx = FIRST_WHEEL_IDX; wheelIdx < wheels.size(); ++wheelIdx)
	{
		maximumIndices.push_back(wheels[wheelIdx].length());
	}

	std::vector<std::size_t> indices = maximumIndices;
	std::vector<std::size_t> endIndices = maximumIndices;
	indices[0] = startCharIdx;

//	while (!isFinalConfiguration(indices))
	//{
		// Build String
	//	std::string wheelConfiguration;
		//BuildString(startCharIdx, maximumIndices, wheelConfiguration);

		// Increament Indicies

		//WordsInDictionary(wheelConfiguration, MIN_WORD_SIZE, dictionary, matchingWords);
//	}
}

void  WheelManager::WordsInDictionary(const std::string& wheel, const Dictionary* dictionary, StringVec& matchingWords) const
{

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