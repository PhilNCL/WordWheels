#pragma once
// Filename:	Dictionary.h
// Description: Stores and manages groups of strings indexed by a key of their first MIN_WORD_SIZE characters
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		Dictionary is case insensitive e.g. dinosaur, Dinosaur and DINOsaur would all be considered equivalent. 

// Standard Includes
#include <string>

// Utilities
#include "../Utility/CommonTypes.h" // StringVec and DictionaryMap

class Dictionary
{
	static const std::size_t DEFAULT_MIN_WORD_SIZE = 2;
	static const std::size_t DEFAULT_MAX_WORD_SIZE = 10;
public: // Constructors
	// Constructs an empty dictionary
	Dictionary(std::size_t maxValidWordSize = DEFAULT_MAX_WORD_SIZE, std::size_t minValidWordSize = DEFAULT_MIN_WORD_SIZE);

	// Constructs a dictionary and loads words from filepath.
	Dictionary(const std::string& filepath, std::size_t maxValidWordSize = DEFAULT_MAX_WORD_SIZE, std::size_t minValidWordSize = DEFAULT_MIN_WORD_SIZE);

	~Dictionary();

public: // Interface
	// Adds a string to the dictionary without testing for duplication
	void AddWord(const std::string& word);

	// All strings associated with key are stored in the StringVec keyWords. keyWords will be empty 
	// after function call if no words are found. Note: The key is case insensitive and keyWords is not sorted.
	void GetWordsFromKey(const std::string& key, Wheels::StringVec& keyWords) const;

	// All strings with length less than wordSize associated with key are stored in the StringVec keyWords. keyWords will be empty 
	// after function call if no words are found.  Note: The key is case insensitive and keyWords is not sorted.
	void GetWordsFromKey(const std::string& key, Wheels::StringVec& keyWords, std::size_t wordSize) const;

	// Attempts to load a file at filepath and add all words without testing for duplication. Returns false if fails to open file.
	bool LoadWordsFromFile(const std::string& filepath);

protected: // Helper Functions
	// Words with length outside of the range MIN_WORD_SIZE / MAX_WORD_SIZE and will not be added to the dictionary
	bool isValidWord(const std::string& word) const;

	// Valid keys have a size equal to MIN_WORD_SIZE 
	bool isValidKey(const std::string& key) const;

	void LoadWords(std::stringstream& dicFile);


protected: // Members
	// Map from the first MIN_WORD_SIZE characters of the word to all words beginning with those characters
	Wheels::DictionaryMap dictionary;

	// Minimum number of characters required for a word to be valid
	const std::size_t MIN_WORD_SIZE;
	// Maximum number of characters required for a word to be valid
	const std::size_t MAX_WORD_SIZE;
};

