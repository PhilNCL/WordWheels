#pragma once
// Filename:	VectorDictionary.h
// Description: Functions for populating a vector of strings which hold current relevant subset of words
// Author:		Philip Jones
// Date:		12/03/18
// Notes:		

// Standard Includes
#include <string>    // std::string
#include <vector>    // std::vector

// Utility includes
#include "../Utility/CommonTypes.h" // StringVec

// Forward Declarations
class Dictionary;

// Populates argument target dictionary from the sourceDictionary based on the keys inferred 
// from sourceString and the minWordSize parameter
void GenerateDictionary(const std::string& sourceString, 
						const Dictionary& sourceDictionary, 
						std::vector <Wheels::StringVec>& targetDictionary, 
						std::size_t minWordSize);

// Modifies current dictionary from the sourceDictionary based on the keys inferred from sourceString, 
// the index of the last changed value in source  string and the minWordSize parameter
void UpdateDictionary(const std::string& sourceString, 
					  std::vector <Wheels::StringVec>& currentDictionary, 
					  const Dictionary& sourceDictionary, 
					  std::size_t index, 
					  std::size_t minWordSize);
