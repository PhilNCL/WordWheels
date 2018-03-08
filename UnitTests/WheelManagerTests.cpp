//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\FileManager.h>
#include <Utility\FileConstants.h>

#include <Wheels\WheelManager.h>
#include <Wheels\Dictionary.h>

using namespace FileConstants;

TEST(WheelManager, AddingWheels)
{
	WheelManager wheelManager;
	std::string wheel = "WheelOfFortune";
	wheelManager.AddWheel(wheel);

	EXPECT_EQ(wheelManager.GetNumWheels(), 1);
	EXPECT_EQ(wheelManager.GetWheel(0), "WheelOfFortune");

	wheel = "WheelOfDestiny";
	wheelManager.AddWheel(wheel);
	EXPECT_EQ(wheelManager.GetNumWheels(), 2);
	EXPECT_EQ(wheelManager.GetWheel(0), "WheelOfFortune");
	EXPECT_EQ(wheelManager.GetWheel(1), "WheelOfDestiny");
}

TEST(WheelManager, GetOutOfBoundsIndex)
{
	WheelManager wheelManager;
	std::string wheel = "WheelOfFortune";
	wheelManager.AddWheel(wheel);

	std::string test = wheelManager.GetWheel(1);
	
	EXPECT_EQ(wheelManager.GetWheel(1).length(), 0);
	EXPECT_EQ(wheelManager.GetWheel(-1).length(), 0);
}

TEST(WheelManager, ParseWheelFile)
{
	const int NUM_WHEELS = 8;
	const int LETTERS_PER_WHEEL = 10;
	WheelManager wheelManager;
	wheelManager.LoadWheelsFromFile(WHEELS_PATH);
	
	EXPECT_EQ(wheelManager.GetNumWheels(), NUM_WHEELS);

	const std::string wheels[NUM_WHEELS] = { "YGVLAINSQC",
											 "SHYIXBODLW",
											 "HCFQIJBPRE",
											 "QUGFKYCMAZ",
											 "FSKRVJNUQT",
											 "RTNFQKMVDI",
											 "EQZHTFDUON",
											 "JAYFRGWEXP" };

	for (int i = 0; i < NUM_WHEELS; ++i)
	{
		EXPECT_EQ(wheelManager.GetWheel(i).length(), LETTERS_PER_WHEEL);
		EXPECT_EQ(wheelManager.GetWheel(i), wheels[i]);
	}
}




TEST(WheelManager, FindWordsInWheels)
{
	WheelManager wheelManager(TEST_WHEELS_PATH);

	const std::vector<std::string> testDictionary = { "ALL", "ABORT", "BRIAN", "AND", "SNIPPER", "AARDVARK" };

	std::vector<std::string> foundWords;
	wheelManager.WheelWordsInList(testDictionary, foundWords);
	EXPECT_EQ(foundWords.size(), 4);

	auto iter = std::find(foundWords.begin(), foundWords.end(), "ALL");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "ABORT");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "BRIAN");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "AND");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "SNIPPER");
	EXPECT_FALSE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "AARDVARK");
	EXPECT_FALSE(iter != foundWords.end());
}

TEST(WheelManager, FindDictionaryInWheels)
{
	WheelManager wheelManager(TEST_WHEELS_PATH);
	Dictionary dictionary(TEST_DICTIONARY_PATH);

	std::vector<std::string> foundWords;
	wheelManager.WheelWordsInDictionary(&dictionary, foundWords);
	EXPECT_EQ(foundWords.size(), 4);

	auto iter = std::find(foundWords.begin(), foundWords.end(), "all");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "abort");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "brian");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "and");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "asteroid");
	EXPECT_FALSE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "am");
	EXPECT_FALSE(iter != foundWords.end());
}

