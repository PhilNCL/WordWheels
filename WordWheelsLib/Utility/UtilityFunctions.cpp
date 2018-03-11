// Filename:	UtilityFunctions.cpp
// Description: Methods for UtilityFunctions.h
// Author:		Philip Jones
// Date:		11/03/18
// Notes:

// Standard Includes
#include <algorithm> //  transform(), equal()
#include <cassert>	 //  assert()
#include <set>		 //  std::set
#include <string>    //  std::string

// Utility Includes
#include "UtilityFunctions.h"

// Namespaces
using namespace Wheels;


bool ReverseStringCompare(const std::string& left, const std::string& right)
{
	if (left.size() != right.size())
	{
		return false;
	}
	else
	{
		return std::equal(left.rbegin(), left.rend(), right.rbegin());
	}

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

std::string MakeUpperCase(const std::string& originalString)
{
	std::string upperCaseString;
	upperCaseString.resize(originalString.length());
	std::transform(originalString.begin(), originalString.end(), upperCaseString.begin(), ::toupper);
	return upperCaseString;
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