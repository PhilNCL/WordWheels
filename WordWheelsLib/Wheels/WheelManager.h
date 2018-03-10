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
protected:
	void WordsInDictionary(const std::string& wheel, const Dictionary* dictionary, Wheels::StringVec& matchingWords) const;
	Wheels::StringVec wheels;
	
	const int MIN_WORD_SIZE;

private: 
	// Helper functions for LoadWheelsFromFile()
	void ReadHeader(std::stringstream& wheelFile, std::size_t& numWheels, std::size_t& lettersPerWheel) const;
	void ReadWheels(std::stringstream& wheelFile, std::size_t numWheels, std::size_t lettersPerWheel);
	
};

