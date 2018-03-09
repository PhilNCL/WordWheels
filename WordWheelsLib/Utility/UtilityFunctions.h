#pragma once

#include <string>
#include <vector>

// Compare two strings of equal size starting from the last character and moving backwards
bool ReverseStringCompare(const std::string& left, const std::string& right);

// Finds or all strings in potential words adds to matching words those which are substrings of word
void FindSubstringsFromList(const std::string& word, const std::vector<std::string>& potentialWords, std::vector<std::string>& matchingStrings);
