// Case insensitive i.e. dinosaur and Dinosaur are considered distinct. All words capitalized
#pragma once

#include <map>
#include <string>
#include <vector>

#include "../Utility/CommonTypes.h"

class Dictionary
{
	static const std::size_t DEFAULT_MIN_WORD_SIZE = 2;
	static const std::size_t DEFAULT_MAX_WORD_SIZE = 10;
public:
	Dictionary(std::size_t maxValidWordSize = DEFAULT_MAX_WORD_SIZE, std::size_t minValidWordSize = DEFAULT_MIN_WORD_SIZE);
	Dictionary(const std::string& filepath, std::size_t maxValidWordSize = DEFAULT_MAX_WORD_SIZE, std::size_t minValidWordSize = DEFAULT_MIN_WORD_SIZE);
	~Dictionary();

	// No test for duplication(?). Words with length outside of the range MIN_WORD_SIZE/MAX_WORD_SIZE will not be added
	void AddWord(const std::string& word);
	// key must be equal to MIN_WORD_SIZE
	void GetWordsFromKey(const std::string& key, Wheels::StringVec& keyWords) const;

	void LoadWordsFromFile(const std::string& filepath);
protected:
	// Map from the first MIN_WORD_SIZE characters of the word to the word
	Wheels::DictionaryMap dictionary;

	const std::size_t MIN_WORD_SIZE;
	const std::size_t MAX_WORD_SIZE;

protected:
	bool isValidWord(const std::string& word) const;
	bool isValidKey(const std::string& key) const;

private:
	void LoadWords(std::stringstream& dicFile);
};

