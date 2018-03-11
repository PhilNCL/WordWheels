#pragma once

// Standard Includes
#include <string>    // std::string
#include <vector>    // std::vector

// Utility includes
#include "../Utility/CommonTypes.h" // StringVec

// Forward Declarations
class Dictionary;

// Non string utility functions**************
void GenerateDictionary(const std::string& sourceString, const Dictionary* sourceDictionary, std::vector <Wheels::StringVec>& targetDictionary, std::size_t minWordSize);
void UpdateDictionary(const std::string& sourceString, std::vector <Wheels::StringVec>& currentDictionary, const Dictionary* sourceDictionary, std::size_t index, std::size_t minWordSize);
