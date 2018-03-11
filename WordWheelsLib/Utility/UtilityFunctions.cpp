// Filename:	UtilityFunctions.cpp
// Description: Methods for UtilityFunctions.h
// Author:		Philip Jones
// Date:		11/03/18
// Notes:

// Standard Includes
#include <algorithm> // transform(), min(), max()
#include <cassert>	 // assert()
#include <set>		 //  std::set

// Utility Includes
#include "UtilityFunctions.h"

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

void BreakString(const std::string& string, std::size_t chopIndex, std::size_t lowestChangedIndex, std::size_t minWordSize, std::vector<std::vector<std::string>>& strings)
{
	assert(chopIndex > 0 && chopIndex < string.length());

	for (std::size_t startIdx = 0; startIdx <= lowestChangedIndex; ++startIdx)
	{
		for (std::size_t endIdx = chopIndex; endIdx < string.length(); ++endIdx)
		{
			std::size_t length = endIdx + 1 - startIdx;
			if (length >= minWordSize)
			{
				//TODO: If pass uninitialised strings startIdx will crash
				strings[startIdx].push_back(string.substr(startIdx, length));
			}

		}
	}
}



void GenerateDictionary(const std::string& sourceString, const Dictionary* sourceDictionary, std::vector<StringVec>& targetDictionary, std::size_t minWordSize)
{
	std::size_t endChar = sourceString.length() - minWordSize;

	for (std::size_t startChar = 0; startChar <= endChar; ++startChar)
	{
		StringVec potentialWords;
		sourceDictionary->GetWordsFromKey(sourceString.substr(startChar, minWordSize), potentialWords, sourceString.size() - startChar);
		targetDictionary.push_back(potentialWords);
	}
}

void RefreshDictionary(const std::string& sourceString, std::vector <StringVec>& currentDictionary, const Dictionary* sourceDictionary, std::size_t index, std::size_t minWordSize)
{
	const std::size_t zeroIdx = 0;
	std::size_t minIdx = (index > minWordSize) ? index - minWordSize + 1 : zeroIdx;
	std::size_t maxIdx = std::min(index + minWordSize - 1, currentDictionary.size());

	for (std::size_t startChar = minIdx; startChar < maxIdx; ++startChar)
	{
		sourceDictionary->GetWordsFromKey(sourceString.substr(startChar, minWordSize), currentDictionary[startChar], sourceString.size() - startChar);
	}

}
