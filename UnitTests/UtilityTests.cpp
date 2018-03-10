//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\UtilityFunctions.h>

TEST(Utility, IsSubstringInString)
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

TEST(Utility, AllSubstringsInList)
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