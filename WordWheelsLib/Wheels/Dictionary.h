// Case insensitive i.e. dinosaur and Dinosaur are considered distinct. All words capitalized
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

	// No test for duplication(?). Words with length outside of the range MIN_WORD_SIZE/MAX_WORD_SIZE will not be added
	void AddWord(const std::string& word);
	// key must be equal to MIN_WORD_SIZE
	void GetWordsFromKey(const std::string& key, std::vector<std::string> & keyWords) const;

	void LoadWordsFromFile(const std::string& filepath);
protected:
	// Map from the first MIN_WORD_SIZE characters of the word to the word
	std::map< std::string, std::vector<std::string> > dictionary;

	const int MIN_WORD_SIZE;
	const int MAX_WORD_SIZE;

protected:
	bool isValidWord(const std::string& word) const;
	bool isValidKey(const std::string& key) const;

private:
	void LoadWords(std::stringstream& dicFile);
};

