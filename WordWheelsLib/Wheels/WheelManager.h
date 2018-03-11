#pragma once
// Filename:	WheelManager.h
// Description: Stores wheels and allows searching in a  
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		Employs simple threading, running one thread for each starting character on the first wheel

// Standard Includes
#include <mutex> // std::lockguard(), std::mutex
#include <string>
#include <vector>


// Utilities
#include "../Utility/CommonTypes.h" // StringVec

// Forward Declarations
class Dictionary;
class ConfigurationManager;

class WheelManager
{
	static const int FIRST_WHEEL_IDX = 0;
public: // Constructors
	WheelManager(std::size_t minWordSize = 2);
	WheelManager(const std::string& filepath, std::size_t minWordSize = 2);
	~WheelManager();




	void LoadWheelsFromFile(const std::string& filepath);
	
	std::size_t GetNumWheels() const;
	std::string GetWheel(std::size_t idx) const;

	// Brute force method
	//void WheelWordsInList(const Wheels::StringVec& potentialWords, Wheels::StringVec& matchingWords) const;
	void WheelWordsInDictionary(const Dictionary* dictionary);
	void CheckAllConfigurations(ConfigurationManager& configuration, const Dictionary* dictionary);

	inline const Wheels::StringVec& GetFoundWords() { return matchingWords; }
	// Thread safe push back for all matching words found
	
	std::string BuildString(std::vector<std::size_t> configuration) const;
protected:
	Wheels::StringVec wheels;
	
	const int MIN_WORD_SIZE;

private: 
	// Helper functions for LoadWheelsFromFile()
	void ReadHeader(std::stringstream& wheelFile, std::size_t& numWheels, std::size_t& lettersPerWheel) const;
	void ReadWheels(std::stringstream& wheelFile, std::size_t numWheels, std::size_t lettersPerWheel);

	void CheckWheelCombinations(std::size_t startCharIdx, const Dictionary* dictionary);
	// Duplicate letters on a wheel have no effect on the number of outputs
	void RemoveDuplicateLetters();

	bool IsFinalConfiguration(const std::vector<std::size_t>& configuration) const;

	// Returns a vector with an element equal to the maximum valid index of each wheel in wheels
	std::vector<std::size_t> GetMaxWheelIndices() const;

	std::mutex matchingWordMutex;
	void AddFoundWord(std::string newWord);
	Wheels::StringVec matchingWords;

	void MatchingWordsInDictionary(std::vector <Wheels::StringVec>& currentDictionary, std::vector<Wheels::StringVec>& potentialWords);
	void WordsInDictionary(const std::string& string, std::size_t minWordSize, const Dictionary* dictionary);
};

