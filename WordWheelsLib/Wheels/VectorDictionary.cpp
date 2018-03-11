#include "VectorDictionary.h"

#include <algorithm>  // std::min(), std::max()

// Wheel includes
#include "Dictionary.h"

// Namespace 
using namespace Wheels;

void GenerateDictionary(const std::string& sourceString, const Dictionary* sourceDictionary, std::vector<StringVec>& targetDictionary, std::size_t minWordSize)
{
	std::size_t endChar = sourceString.length() - minWordSize;

	for (std::size_t startChar = 0; startChar <= endChar; ++startChar)
	{
		StringVec potentialWords;
		sourceDictionary->GetWordsFromKey(sourceString.substr(startChar, minWordSize), potentialWords, sourceString.size() - startChar);
		targetDictionary.push_back(potentialWords);
	}
}

void UpdateDictionary(const std::string& sourceString, std::vector <StringVec>& currentDictionary, const Dictionary* sourceDictionary, std::size_t index, std::size_t minWordSize)
{
	const std::size_t zeroIdx = 0;
	std::size_t minIdx = (index > minWordSize) ? index - minWordSize + 1 : zeroIdx;
	std::size_t maxIdx = std::min(index + minWordSize - 1, currentDictionary.size());

	for (std::size_t startChar = minIdx; startChar < maxIdx; ++startChar)
	{
		sourceDictionary->GetWordsFromKey(sourceString.substr(startChar, minWordSize), currentDictionary[startChar], sourceString.size() - startChar);
	}

}
