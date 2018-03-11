#pragma once

#include <string>
#include <vector>

#include "CommonTypes.h"

class Dictionary;

// Compare two strings of equal size starting from the last character and moving backwards
bool ReverseStringCompare(const std::string& left, const std::string& right);

// Finds or all strings in potential words adds to matching words those which are substrings of word
void FindSubstringsFromList(const std::string& word, const Wheels::StringVec& potentialWords, Wheels::StringVec& matchingStrings);

// Returns true if substring is in string [case sensitive]
bool IsSubstringInString(const std::string& string, const std::string& substring);

void MakeUpperCase(const std::string& originalString, std::string& upperCaseString);

// Alphabetical order, does no case check
void MakeStringUnique(std::string& sameCaseString);

void BreakString(const std::string& string, std::size_t index, std::size_t lowestChangedIndex, std::size_t minWordSize, std::vector<std::vector<std::string>>& strings);


// Non string utility functions***************
void NextConfiguration(std::vector<std::size_t>& currentConfiguration, const std::vector<std::size_t>& initialConfiguration);
void NextConfiguration(std::vector<std::size_t>& currentConfiguration, const std::vector<std::size_t>& initialConfiguration, std::size_t& indexChanged);


// Wheel Functions???
void  WordsInDictionary(const std::string& string, std::size_t minWordSize, const Dictionary* dictionary, Wheels::StringVec& matchingWords);

void GenerateDictionary(const std::string& sourceString, const Dictionary* sourceDictionary, std::vector <Wheels::StringVec>& targetDictionary, std::size_t minWordSize);
void RefreshDictionary(const std::string& sourceString, std::vector <Wheels::StringVec>& currentDictionary, const Dictionary* sourceDictionary, std::size_t index, std::size_t minWordSize);

void MatchingWordsInDictionary(std::vector <Wheels::StringVec>& currentDictionary, std::vector <Wheels::StringVec>& potentialWords, Wheels::StringVec& matchingWords);