// Note : Uses sort() which stores strings in ACSII order. Requires more checks if expecting 
// words not in English e.g. diacritical marks
#include "Dictionary.h"

#include <algorithm> // find(), sort()
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

	auto& wordList = dictionary[word.substr(0, MIN_WORD_SIZE)];
	if (wordList.empty())
	{
		wordList = std::vector<std::vector<std::string>>(MAX_WORD_SIZE);
	}

	auto& wordListLength = wordList[word.length() - 1];
	if (std::find(wordListLength.cbegin(), wordListLength.cend(), word) == wordListLength.cend())
	{
		wordListLength.push_back(word);
		if (doWordSorting)
		{
			std::sort(wordListLength.begin(), wordListLength.end(), [](const std::string& lhs, const std::string& rhs) { return lhs.compare(rhs) < 0;});
		}
	}
	
}

bool Dictionary::GetWords(const std::string& firstLetters, std::vector<std::string>& wordList) const
{
	if (firstLetters.size() != MIN_WORD_SIZE)
	{
		return false;
	}

	auto potentialWordList = dictionary.find(firstLetters);
	if (potentialWordList == dictionary.end())
	{
		return false;
	}
	else
	{
		for (std::size_t wordSize = 0; wordSize < MAX_WORD_SIZE; ++wordSize)
		{
			auto& wordsOfSize = potentialWordList->second[wordSize];
			wordList.insert(wordList.end(), wordsOfSize.begin(), wordsOfSize.end());
		}
	
		return true;
	}
}

bool Dictionary::GetWords(const std::string& firstLetters, std::size_t numLetters, std::vector<std::string>& wordList) const
{
	if (firstLetters.size() != MIN_WORD_SIZE)
	{
		return false;
	}

	auto potentialWordList = dictionary.find(firstLetters);
	if (potentialWordList == dictionary.end())
	{
		return false;
	}
	else
	{
		wordList = potentialWordList->second[numLetters - 1];
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

