#include "UtilityFunctions.h"

#include <cassert>

bool ReverseStringCompare(const std::string& left, const std::string& right)
{
	assert(left.size() == right.size());
	return std::equal(left.rbegin(), left.rend(), right.rbegin());
}

void FindSubstringsFromList(const std::string& string, const std::vector<std::string>& potentialWords, std::vector<std::string>& matchingStrings)
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