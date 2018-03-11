#pragma once
// Filename:	UtilityFunctions.h
// Description: A collection of useful functions for working with strings
// Author:		Philip Jones
// Date:		11/03/18
// Notes:

// Standard Includes
#include <ostream>		// std::ostream
#include <string>		// std::string
#include <vector>		// std::vector

// Utility includes
#include "CommonTypes.h" // StringVec

class Dictionary;

// Compare two strings of equal size starting from the last character and moving backwards
bool ReverseStringCompare(const std::string& left, const std::string& right);

// Finds or all strings in potential words adds to matching words those which are substrings of word
void FindSubstringsFromList(const std::string& word, 
							const Wheels::StringVec& potentialWords, 
							Wheels::StringVec& matchingStrings);

// Returns true if substring is in string [case sensitive]
bool IsSubstringInString(const std::string& string, const std::string& substring);

// Creates an upper case version of original string into upperCaseString
std::string MakeUpperCase(const std::string& originalString);

// Removes duplicate characters from inputString. 
// After a call to MakeStringUnique the characters of input string will be in alphabetical order. 
// Does no case checking
void MakeStringUnique(std::string& inputString);

// Stores in strings those substrings which have not previously been present in the input string argument
// based on the last changed index, lowestChangedIndex and minWordSize arguments
void GenerateNewSubstrings(const std::string& string, std::size_t index, 
				 std::size_t lowestChangedIndex, std::size_t minWordSize, 
				std::vector<std::vector<std::string>>& strings);

// Prints all strings in stringVec via the outputstream os
void PrintStrings(std::ostream& os, const Wheels::StringVec& stringVec);