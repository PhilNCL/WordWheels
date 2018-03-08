// Case sensitive i.e. dinosaur and Dinosaur are considered distinct
#pragma once

#include <map>
#include <string>
#include <vector>

class Dictionary
{
	static const int DEFAULT_MIN_WORD_SIZE = 2;
	static const int DEFAULT_MAX_WORD_SIZE = 10;
public:
	Dictionary(int maxValidWordSize = DEFAULT_MAX_WORD_SIZE, int minValidWordSize = DEFAULT_MIN_WORD_SIZE);
	Dictionary(const std::string& filepath, int maxValidWordSize = DEFAULT_MAX_WORD_SIZE, int minValidWordSize = DEFAULT_MIN_WORD_SIZE);
	~Dictionary();

	// No test for duplication(?). Assumes minimum word length is 2 characters
	void AddWord(const std::string& word);

	bool GetWords(const std::string& firstLetters, std::size_t numLetters, std::vector<std::string>& wordList) const;
	bool GetWords(const std::string& firstLetters, std::vector<std::string>& wordList) const;
	void LoadWordsFromFile(const std::string& filepath);

	void SortAfterAdding(bool shouldSort);
protected:
	// Map from the first MIN_WORD_SIZE characters of the word to the word
	std::map<std::string, std::vector<std::vector<std::string>>> dictionary;

	const int MIN_WORD_SIZE;
	const int MAX_WORD_SIZE;

	//If true sorts words in alphabetical order. Set to true if dictionary files are not already sorted.
	bool  doWordSorting = false;
};

