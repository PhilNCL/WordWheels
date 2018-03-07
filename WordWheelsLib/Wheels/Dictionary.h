#pragma once

#include <map>
#include <string>
#include <vector>

class Dictionary
{
public:
	Dictionary(int minWordSize = 2);
	~Dictionary();

	// No test for duplication(?). Assumes minimum word length is 2 characters
	void AddWord(std::string word);

	bool GetWords(const std::string& firstLetters, std::vector<std::string>& wordList);
	
protected:
	// Map from the first two characters of the word to the word
	std::map<std::string, std::vector<std::string>> dictionary;

	const int MIN_WORD_SIZE;
};

