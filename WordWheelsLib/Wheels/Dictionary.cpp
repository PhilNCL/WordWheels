// Note : Uses sort() which stores strings in ACSII order. Requires more checks if expecting 
// words not in English e.g. diacritical marks
#include "Dictionary.h"

#include <algorithm> // find(), sort()
#include <cassert>

Dictionary::Dictionary(int minValidWordSize) :
	MIN_WORD_SIZE(minValidWordSize)
{
	assert(minValidWordSize > 0);
}


Dictionary::~Dictionary()
{
}

void Dictionary::AddWord(std::string word) 
{
	if (word.size() < MIN_WORD_SIZE)
	{
		return;
	}

	auto& wordList = dictionary[word.substr(0, MIN_WORD_SIZE)];
	if (std::find(wordList.cbegin(), wordList.cend(), word) == wordList.cend())
	{
		wordList.push_back(word);
		std::sort(wordList.begin(), wordList.end(), [](const std::string& lhs, const std::string& rhs) { return lhs.compare(rhs) < 0;});
	}
	
}

bool Dictionary::GetWords(const std::string& firstLetters, std::vector<std::string>& wordList)
{	
	auto potentialWordList = dictionary.find(firstLetters);
	if (potentialWordList == dictionary.end())
	{
		return false;
	}
	else
	{
		wordList = potentialWordList->second;
		return true;
	}
}