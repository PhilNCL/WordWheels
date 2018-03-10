//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\UtilityFunctions.h>
#include <Utility\FileConstants.h> \\TEST_DICTIONARY_PATH
#include <Wheels\Dictionary.h> \\TODO: Move
#include <vector>
using namespace FileConstants;

TEST(UtilityString, IsSubstringInString)
{
	const std::string SEARCH_STRING = "ANGELEYES";

	EXPECT_TRUE(IsSubstringInString(SEARCH_STRING, "ANGEL"));
	EXPECT_TRUE(IsSubstringInString(SEARCH_STRING, "EYES"));
	EXPECT_TRUE(IsSubstringInString(SEARCH_STRING, "GEL"));
	EXPECT_TRUE(IsSubstringInString(SEARCH_STRING, "ES"));
	EXPECT_TRUE(IsSubstringInString(SEARCH_STRING, "AN"));

	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "ANGELEYESSS"));

	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "BANANA"));
	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "LEMON"));

	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "LEG"));
	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "SEYE"));

	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "angel"));
	EXPECT_FALSE(IsSubstringInString(SEARCH_STRING, "eyes"));
}

TEST(UtilityString, AllSubstringsInList)
{
	const std::string SEARCH_STRING = "ANGELEYES";
	const std::vector<std::string> SEARCH_LIST = { "ANGEL", "EYES", "GEL", "ES", "AN", "ANGELEYESSS", "BANANA",  "LEG", "angel" };
	std::vector<std::string> matchingSubStrings;
	FindSubstringsFromList(SEARCH_STRING, SEARCH_LIST, matchingSubStrings);
	EXPECT_TRUE(matchingSubStrings.size() == 5);


	auto iter = std::find(matchingSubStrings.begin(), matchingSubStrings.end(), "ANGEL");
	EXPECT_TRUE(iter != matchingSubStrings.end());

	iter = std::find(matchingSubStrings.begin(), matchingSubStrings.end(), "EYES");
	EXPECT_TRUE(iter != matchingSubStrings.end());

	iter = std::find(matchingSubStrings.begin(), matchingSubStrings.end(), "EYES");
	EXPECT_TRUE(iter != matchingSubStrings.end());

	iter = std::find(matchingSubStrings.begin(), matchingSubStrings.end(), "ES");
	EXPECT_TRUE(iter != matchingSubStrings.end());

	iter = std::find(matchingSubStrings.begin(), matchingSubStrings.end(), "AN");
	EXPECT_TRUE(iter != matchingSubStrings.end());
}

TEST(UtilityString, MakeUpperCase)
{
	const std::string lowerCase = "verySmallLetters";
	std::string upperCase;

	MakeUpperCase(lowerCase, upperCase);
	EXPECT_EQ(upperCase, "VERYSMALLLETTERS");
}


TEST(UtilityString, MakeStringUnique)
{
	std::string testString = "VERYSMALLLETTERS";

	MakeStringUnique(testString);
	EXPECT_EQ(testString, "AELMRSTVY");
}


TEST(Utility, NextConfiguration)
{
	std::vector<std::size_t> indices = { 7, 8, 8, 4, 8, 8 };
	std::vector<std::size_t> originalIndices = indices;

	NextConfiguration(indices, originalIndices);
	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 4);
	EXPECT_EQ(indices[4], 8);
	EXPECT_EQ(indices[5], 7);

	for (int i = 0; i < 7; ++i)
	{
		NextConfiguration(indices, originalIndices);
	}

	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 4);
	EXPECT_EQ(indices[4], 8);
	EXPECT_EQ(indices[5], 0);

	NextConfiguration(indices, originalIndices);
	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 4);
	EXPECT_EQ(indices[4], 7);
	EXPECT_EQ(indices[5], 8);

	for (int i = 0; i < 8; ++i)
	{
		NextConfiguration(indices, originalIndices);
	}
	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 4);
	EXPECT_EQ(indices[4], 7);
	EXPECT_EQ(indices[5], 0);

	NextConfiguration(indices, originalIndices);
	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 4);
	EXPECT_EQ(indices[4], 6);
	EXPECT_EQ(indices[5], 8);

	for (int i = 0; i < 9 * 6 + 8; ++i)
	{
		NextConfiguration(indices, originalIndices);
	}
	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 4);
	EXPECT_EQ(indices[4], 0);
	EXPECT_EQ(indices[5], 0);

	NextConfiguration(indices, originalIndices);
	EXPECT_EQ(indices[0], 7);
	EXPECT_EQ(indices[1], 8);
	EXPECT_EQ(indices[2], 8);
	EXPECT_EQ(indices[3], 3);
	EXPECT_EQ(indices[4], 8);
	EXPECT_EQ(indices[5], 8);
}


TEST(Utility, GenerateDictionary)
{
	Dictionary dictionary(TEST_DICTIONARY_PATH);
	const std::string sourceString = "ANDOKBRIANABTIRED";
	std::vector<std::vector<std::string>> targetDictionary;

	GenerateDictionary(sourceString, &dictionary, targetDictionary, 2);
	
	const int EXPECTED_SIZES[] = { 1, 0 , 0 , 0, 0, 1, 0, 0 , 1, 0, 4, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < sourceString.size() - 2; ++i)
	{
		EXPECT_EQ(targetDictionary[i].size(), EXPECTED_SIZES[i]);
	}


	auto iter = std::find(targetDictionary[0].begin(), targetDictionary[0].end(), "AND");
	EXPECT_TRUE(iter != targetDictionary[0].end());

	iter = std::find(targetDictionary[10].begin(), targetDictionary[10].end(), "ABBA");
	EXPECT_TRUE(iter != targetDictionary[10].end());

	iter = std::find(targetDictionary[10].begin(), targetDictionary[10].end(), "ABORT");
	EXPECT_TRUE(iter != targetDictionary[10].end());

	iter = std::find(targetDictionary[10].begin(), targetDictionary[10].end(), "ABACUS");
	EXPECT_TRUE(iter != targetDictionary[10].end());

}