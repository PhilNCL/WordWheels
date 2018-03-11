#include "UtilityFunctions.h"

#include <algorithm> // transform()
#include <cassert>
#include <set>

//TODO: Wronge place for this
#include "../Wheels/Dictionary.h"
#include <string>
using namespace Wheels;


bool ReverseStringCompare(const std::string& left, const std::string& right)
{
	assert(left.size() == right.size());
	return std::equal(left.rbegin(), left.rend(), right.rbegin());
}

void FindSubstringsFromList(const std::string& string, const StringVec& potentialWords, StringVec& matchingStrings)
{
	for (auto& subStr : potentialWords)
	{
		if (subStr.length() > string.length())
		{
			continue;
		}

		if (IsSubstringInString(string, subStr))
		{
			matchingStrings.push_back(subStr);
		}
	}
}

bool IsSubstringInString(const std::string& string, const std::string& substring)
{
	if (string.find(substring) != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MakeUpperCase(const std::string& originalString, std::string& upperCaseString)
{
	upperCaseString.resize(originalString.length());
	std::transform(originalString.begin(), originalString.end(), upperCaseString.begin(), ::toupper);
}

void MakeStringUnique(std::string& upperCaseString) 
{
	std::sort(upperCaseString.begin(), upperCaseString.end());
	auto lastChar = std::unique(upperCaseString.begin(), upperCaseString.end());
	upperCaseString.erase(lastChar, upperCaseString.end());
}

void BreakString(std::string originalString, std::size_t chopIndex, std::size_t minWordSize, std::vector<std::string>& strings)
{
	assert(chopIndex > 0 && chopIndex < originalString.length());

	for (std::size_t startIdx = 0; startIdx <= chopIndex; ++startIdx)
	{
		for (std::size_t endIdx = chopIndex; endIdx < originalString.length(); ++endIdx)
		{
			std::size_t length = endIdx + 1 - startIdx;
			if (length >= minWordSize)
			{
				strings.push_back(originalString.substr(startIdx, length));
			}

		}
	}
}

void  WordsInDictionary(const std::string& string, std::size_t minWordSize, const Dictionary* dictionary, StringVec& matchingWords)
{
	std::size_t endChar = string.length() - minWordSize;

	for (std::size_t startChar = 0; startChar <= endChar; ++startChar)
	{
		StringVec potentialWords;
		dictionary->GetWordsFromKey(string.substr(startChar, minWordSize), potentialWords);
		FindSubstringsFromList(string.substr(startChar), potentialWords, matchingWords);
	}
}


void NextConfiguration(std::vector<std::size_t>& currentConfiguration, const std::vector<std::size_t>& initialConfiguration)
{
	assert(currentConfiguration.size() == initialConfiguration.size());

	for (int index = currentConfiguration.size() - 1; index != 0; --index)
	{
		if (currentConfiguration[index])
		{
			--currentConfiguration[index];
			while (index != currentConfiguration.size() - 1)
			{
				++index;
				currentConfiguration[index] = initialConfiguration[index];
			}
			break;
		}
	}
}

void NextConfiguration(std::vector<std::size_t>& currentConfiguration, const std::vector<std::size_t>& initialConfiguration, int& indexChanged)
{
	assert(currentConfiguration.size() == initialConfiguration.size());

	for (int index = currentConfiguration.size() - 1; index != 0; --index)
	{
		if (currentConfiguration[index])
		{
			--currentConfiguration[index];
			indexChanged = index;
			while (index != currentConfiguration.size() - 1)
			{
				++index;
				currentConfiguration[index] = initialConfiguration[index];
			}
			break;
		}
	}
}

void GenerateDictionary(const std::string& sourceString, const Dictionary* sourceDictionary, std::vector<Wheels::StringVec>& targetDictionary, int minWordSize)
{
	std::size_t endChar = sourceString.length() - minWordSize;

	for (std::size_t startChar = 0; startChar <= endChar; ++startChar)
	{
		StringVec potentialWords;
		sourceDictionary->GetWordsFromKey(sourceString.substr(startChar, minWordSize), potentialWords);
		targetDictionary.push_back(potentialWords);
	}
}


