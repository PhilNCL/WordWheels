#pragma once

// Standard Includes
#include <string>
#include <vector>

#include "../Utility/CommonTypes.h"

class Dictionary;

class WheelManager
{
public:
	WheelManager(std::size_t minWordSize = 2);
	WheelManager(const std::string& filepath, std::size_t minWordSize = 2);
	~WheelManager();

	void AddWheel(const std::string& wheel);
	void LoadWheelsFromFile(const std::string& filepath);
	
	std::size_t GetNumWheels() const;
	std::string GetWheel(std::size_t idx) const;

	// Brute force method
	void WheelWordsInList(const Wheels::StringVec& potentialWords, Wheels::StringVec& matchingWords) const;
	void WheelWordsInDictionary(const Dictionary* dictionary, Wheels::StringVec& matchingWords) const;

	std::string BuildString(std::vector<std::size_t> configuration) const;
protected:
	Wheels::StringVec wheels;
	
	const int MIN_WORD_SIZE;

private: 
	// Helper functions for LoadWheelsFromFile()
	void ReadHeader(std::stringstream& wheelFile, std::size_t& numWheels, std::size_t& lettersPerWheel) const;
	void InitaliseWheels(std::size_t numWheels, std::size_t lettersPerWheel);
	void ReadWheels(std::stringstream& wheelFile, std::size_t numWheels, std::size_t lettersPerWheel);

	void CheckWheelCombinations(std::size_t startCharIdx, const Dictionary* dictionary, Wheels::StringVec& matchingWords) const;
	// Duplicate letters on a wheel have no effect on the number of outputs
	void RemoveDuplicateLetters();

	bool IsFinalConfiguration(const std::vector<std::size_t>& configuration) const;
};

