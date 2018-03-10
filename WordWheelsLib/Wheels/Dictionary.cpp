// Note : Uses sort() which stores strings in ACSII order. Requires more checks if expecting 
// words not in English e.g. diacritical marks
#include "Dictionary.h"

#include <algorithm> // find(), sort()
#include <cassert>

#include "../Utility/FileManager.h"
#include "../Utility/UtilityFunctions.h"

Dictionary::Dictionary(int maxValidWordSize, int minValidWordSize) :
	MIN_WORD_SIZE(minValidWordSize), MAX_WORD_SIZE(maxValidWordSize)
{
	assert(minValidWordSize > 0);
	assert(maxValidWordSize > 0);
}

Dictionary::Dictionary(const std::string& filepath, int maxValidWordSize, int minValidWordSize) :
	Dictionary(maxValidWordSize, minValidWordSize)
{
	LoadWordsFromFile(filepath);
}

Dictionary::~Dictionary()
{
}



void Dictionary::AddWord(const std::string& word)
{
	if (!isValidWord(word))
	{
		return;
	}

	std::string upperCase;
	MakeUpperCase(word, upperCase);
	std::string keyWord = upperCase.substr(0, MIN_WORD_SIZE);
	
	auto& wordList = dictionary[keyWord];
	wordList.push_back(upperCase);
}

void Dictionary::LoadWordsFromFile(const std::string& filepath)
{
	FileManager fileManager;
	std::stringstream dictionaryFile;

	if (fileManager.LoadFile(filepath, dictionaryFile))
	{
		LoadWords(dictionaryFile);
	}

}

void Dictionary::LoadWords(std::stringstream& dicFile)
{
	std::string word;
	while (dicFile >> word)
	{
		AddWord(word);
	}
}

void Dictionary::GetWordsFromKey(const std::string& key, std::vector<std::string> & keyWords) const
{
	if (!isValidKey(key))
	{
		return;
	}

	std::string keyWord = key;
	std::transform(key.begin(), key.end(), keyWord.begin(), ::toupper);

	auto keyIter = dictionary.find(keyWord);
	if (keyIter != dictionary.end())
	{
		keyWords = keyIter->second;
	}
}

bool Dictionary::isValidWord(const std::string& word) const
{
	if (word.size() < MIN_WORD_SIZE || word.size() > MAX_WORD_SIZE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Dictionary::isValidKey(const std::string& key) const
{
	if (key.size() != MIN_WORD_SIZE)
	{
		return false;
	}
	else
	{
		return true;
	}
}