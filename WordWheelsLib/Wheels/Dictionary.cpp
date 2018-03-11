// Filename:	Dictionary.cpp
// Description: Defines methods for Dictionary class
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		
#include "Dictionary.h"

// Standard Includes
#include <algorithm> // find(), sort(), copy_if(), distance()
#include <cassert>	 // assert()

// Utilities
#include "../Utility/FileManager.h"
#include "../Utility/UtilityFunctions.h"

using namespace Wheels;

Dictionary::Dictionary(std::size_t maxValidWordSize, std::size_t minValidWordSize) :
	MIN_WORD_SIZE(minValidWordSize), MAX_WORD_SIZE(maxValidWordSize)
{
	assert(minValidWordSize > 0);
	assert(maxValidWordSize > 0);
}

Dictionary::Dictionary(const std::string& filepath, std::size_t maxValidWordSize, std::size_t minValidWordSize) :
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

bool Dictionary::LoadWordsFromFile(const std::string& filepath)
{
	FileManager fileManager;
	std::stringstream dictionaryFile;

	if (fileManager.LoadFile(filepath, dictionaryFile))
	{
		LoadWords(dictionaryFile);
		return true;
	}
	else
	{
		return false;
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

void Dictionary::GetWordsFromKey(const std::string& key, StringVec& keyWords) const
{
	if (!isValidKey(key))
	{
		return;
	}

	std::string keyWord;
	MakeUpperCase(key, keyWord);

	auto keyIter = dictionary.find(keyWord);
	if (keyIter != dictionary.end())
	{
		keyWords = keyIter->second;
	}
	else
	{
		keyWords = StringVec();
	}
}

void Dictionary::GetWordsFromKey(const std::string& key, StringVec& keyWords, std::size_t wordSize) const
{
	if (!isValidKey(key))
	{
		return;
	}
	std::string keyWord;
	MakeUpperCase(key, keyWord);

	auto keyIter = dictionary.find(keyWord);
	if (keyIter != dictionary.end())
	{
		keyWords.resize(keyIter->second.size());
		auto it = std::copy_if(keyIter->second.begin(), keyIter->second.end(), keyWords.begin(), [&wordSize](const std::string& s) {return (s.size()<= wordSize); });
		keyWords.resize(std::distance(keyWords.begin(), it));
	}
	else
	{
		keyWords = StringVec();
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