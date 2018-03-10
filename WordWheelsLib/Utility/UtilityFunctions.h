#pragma once

#include <string>
#include <vector>

#include "CommonTypes.h"

// Compare two strings of equal size starting from the last character and moving backwards
bool ReverseStringCompare(const std::string& left, const std::string& right);

// Finds or all strings in potential words adds to matching words those which are substrings of word
void FindSubstringsFromList(const std::string& word, const Wheels::StringVec& potentialWords, Wheels::StringVec& matchingStrings);

// Returns true if substring is in string [case sensitive]
bool IsSubstringInString(const std::string& string, const std::string& substring);

void MakeUpperCase(const std::string& originalString, std::string& upperCaseString);