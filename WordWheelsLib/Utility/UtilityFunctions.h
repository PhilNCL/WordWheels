#pragma once
// Filename:	UtilityFunctions.h
// Description: A collection of useful functions for working with strings
// Author:		Philip Jones
// Date:		11/03/18
// Notes:

// Standard Includes
#include <string>
#include <vector>

// Utility includes
#include "CommonTypes.h" // StringVec

class Dictionary;

// Compare two strings of equal size starting from the last character and moving backwards
bool ReverseStringCompare(const std::string& left, const std::string& right);

// Finds or all strings in potential words adds to matching words those which are substrings of word
void FindSubstringsFromList(const std::string& word, const Wheels::StringVec& potentialWords, Wheels::StringVec& matchingStrings);

// Returns true if substring is in string [case sensitive]
bool IsSubstringInString(const std::string& string, const std::string& substring);

// Creates an upper case version of original string into upperCaseString
void MakeUpperCase(const std::string& originalString, std::string& upperCaseString);

// Removes duplicate characters from inputString. After a call to MakeStringUnique the characters of input string will be in alphabetical order. 
// Does no case checking
void MakeStringUnique(std::string& inputString);

// This function helps to maintain efficiency by not checking same substrings repeatedly.
void BreakString(const std::string& string, std::size_t index, std::size_t lowestChangedIndex, std::size_t minWordSize, std::vector<std::vector<std::string>>& strings);


// Non string utility functions**************

// Wheel Functions???
void  WordsInDictionary(const std::string& string, std::size_t minWordSize, const Dictionary* dictionary, Wheels::StringVec& matchingWords);

void GenerateDictionary(const std::string& sourceString, const Dictionary* sourceDictionary, std::vector <Wheels::StringVec>& targetDictionary, std::size_t minWordSize);
void RefreshDictionary(const std::string& sourceString, std::vector <Wheels::StringVec>& currentDictionary, const Dictionary* sourceDictionary, std::size_t index, std::size_t minWordSize);

void MatchingWordsInDictionary(std::vector <Wheels::StringVec>& currentDictionary, std::vector <Wheels::StringVec>& potentialWords, Wheels::StringVec& matchingWords);