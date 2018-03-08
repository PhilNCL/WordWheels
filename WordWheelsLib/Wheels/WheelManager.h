#pragma once

// Standard Includes
#include <string>
#include <vector>

class Dictionary;

class WheelManager
{
public:
	WheelManager(int minWordSize = 2);
	WheelManager(const std::string& filepath, int minWordSize = 2);
	~WheelManager();

	void AddWheel(const std::string& wheel);
	void LoadWheelsFromFile(const std::string& filepath);
	
	std::size_t GetNumWheels() const;
	std::string GetWheel(std::size_t idx);

	// Brute force method
	void WheelWordsInList(const std::vector<std::string>& potentialWords, std::vector<std::string>& matchingWords);
	void WheelWordsInDictionary(const Dictionary* dictionary, std::vector<std::string>& matchingWords);
protected:
	std::vector<std::string> wheels;
	
	const int MIN_WORD_SIZE;
	
};

