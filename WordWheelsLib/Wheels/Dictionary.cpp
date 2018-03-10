// Note : Uses sort() which stores strings in ACSII order. Requires more checks if expecting 
// words not in English e.g. diacritical marks
#include "Dictionary.h"

#include <algorithm> // find(), sort(), transform()
#include <cassert>

#include "../Utility/FileManager.h"

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
	if (word.size() < MIN_WORD_SIZE || word.size() > MAX_WORD_SIZE)
	{
		return;
	}
	std::string keyWord = word.substr(0, MIN_WORD_SIZE);
	std::transform(keyWord.begin(), keyWord.end(), keyWord.begin(), ::tolower);
	
	auto& wordList = dictionary[keyWord];
	wordList.push_back(word);
	if (doWordSorting)
	{
		std::sort(wordList.begin(), wordList.end());
	}
}

bool Dictionary::GetWords(const std::string& firstLetters, std::vector<std::string>& wordList) const
{
	if (firstLetters.size() != MIN_WORD_SIZE)
	{
		return false;
	}

	std::string keyWord = firstLetters;
	std::transform(firstLetters.begin(), firstLetters.end(), keyWord.begin(), ::tolower);

	auto potentialWordList = dictionary.find(keyWord);
	if (potentialWordList == dictionary.end())
	{
		return false;
	}
	else
	{
		for (auto& word : potentialWordList->second)
		{
			std::string upperCase = word;
			std::transform(word.begin(), word.end(), upperCase.begin(), ::toupper);
			wordList.push_back(upperCase);
		}

		return true;
	}
}

void Dictionary::LoadWordsFromFile(const std::string& filepath)
{
	FileManager fileManager;
	std::stringstream dictionaryFile;

	if (fileManager.LoadFile(filepath, dictionaryFile))
	{
		std::string word;
		while (dictionaryFile >> word)
		{
			AddWord(word);
		}
	
	}

}

void Dictionary::SortAfterAdding(bool shouldSort)
{
	doWordSorting = shouldSort;
}

