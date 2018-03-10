#include "UtilityFunctions.h"

#include <algorithm> // transform()
#include <cassert>

using namespace Wheels;


bool ReverseStringCompare(const std::string& left, const std::string& right)
{
	assert(left.size() == right.size());
	return std::equal(left.rbegin(), left.rend(), right.rbegin());
}

void FindSubstringsFromList(const std::string& string, const StringVec& potentialWords, StringVec& matchingStrings)
{
	for (auto& str : potentialWords)
	{
		if (IsSubstringInString(string, str))
		{
			matchingStrings.push_back(str);
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