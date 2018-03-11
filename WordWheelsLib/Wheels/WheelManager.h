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
	// Create an empty WheelManager
	WheelManager(std::size_t minWordSize = 2);

	// Create a WheelManager and populate it with wheels from file at filepath
	WheelManager(const std::string& filepath, std::size_t minWordSize = 2);

	~WheelManager();

public: // Interface
	// Load wheels from file at filepath
	bool LoadWheelsFromFile(const std::string& filepath);
	
	std::size_t GetNumWheels() const;

	// Get the wheel at index idx. Performs sanity check on idx.
	std::string GetWheel(std::size_t idx) const;

	// Returns a list of all words found by wheel words
	inline const Wheels::StringVec& GetFoundWords() { return matchingWords; }

	// Generates a list of all wheel words in dictionary. Accessed via GetFoundWords()
	void FindWordsInDictionary(const Dictionary& dictionary);

	// Returns a vector with an element equal to the maximum valid index of each wheel in wheels
	std::vector<std::size_t> GetMaxWheelIndices() const;

	// Returns a string corresponding to the characters of the input wheel configuration
	std::string BuildString(std::vector<std::size_t> configuration) const;

protected: // Helper functions for LoadWheelsFromFile()
	// Wheel files expect format to be first line Number of Wheels and second line Number of letters per wheel
	void ReadHeader(std::stringstream& wheelFile, std::size_t& numWheels, std::size_t& lettersPerWheel) const;

	// Wheel files expect format to be the header followed by numWheels lines each line representing 
	// one wheel of lettersPerWheel characters
	void ReadWheels(std::stringstream& wheelFile, std::size_t numWheels, std::size_t lettersPerWheel);

	// Duplicate letters on a wheel have no effect on the number of outputs so are culled for efficiency
	void RemoveDuplicateLetters();

protected: 
	// Iterates through all permutations of the wheel recording any matching words
	void CheckWheelCombinations(std::size_t startCharIdx, const Dictionary& dictionary);

protected: // Members
	const int MIN_WORD_SIZE;

	// Each element of the vector stores one wheel represented as a std::string
	Wheels::StringVec wheels;

	// A list of wheels found by FindWordsInDictionary()
	Wheels::StringVec matchingWords;

	// Guards write access to matchingWords
	std::mutex matchingWordMutex;





	// Thread safe push back for found matching words
	void AddFoundWord(std::string newWord);


	void MatchingWordsInDictionary(std::vector <Wheels::StringVec>& currentDictionary, std::vector<Wheels::StringVec>& potentialWords);
	void WordsInDictionary(const std::string& string, std::size_t minWordSize, const Dictionary& dictionary);

	void CheckAllConfigurations(ConfigurationManager& configuration, const Dictionary& dictionary);









};

