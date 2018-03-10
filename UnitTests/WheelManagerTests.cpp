//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\FileManager.h>
#include <Utility\FileConstants.h>

#include <Wheels\WheelManager.h>
#include <Wheels\Dictionary.h>

using namespace FileConstants;

#define REMOVE_DUPLICATES

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

// As told by output file
TEST(WheelManager, ParseWheelFile)
{
	const int NUM_WHEELS = 10;
	const int LETTERS_PER_WHEEL = 8;
	WheelManager wheelManager;
	wheelManager.LoadWheelsFromFile(WHEELS_PATH);

	EXPECT_EQ(wheelManager.GetNumWheels(), NUM_WHEELS);


	#ifdef REMOVE_DUPLICATES
			const std::string wheels[NUM_WHEELS] = {
				"EFHJQRSY",
				"ACGHQSTU",
				"FGKNVYZ",
				"FHILQR",
				"AIKQRTVX",
				"BFGIJKY",
				"BCDMNOW",
				"DEMPSUV",
				"ADLOQRX",
				"CEINPTWZ"
			};
	#else
			const std::string wheels[NUM_WHEELS] = {
				"YSHQFREJ",
				"GHCUSTQA",
				"VYFGKNZY",
				"LIQFRFHF",
				"AXIKVQTR",
				"IBJYJKFG",
				"NOBCNMDW",
				"SDPMUVUE",
				"QLRAQDOX",
				"CWEZTINP"
			};
		}
	#endif	

	for (int i = 0; i < NUM_WHEELS; ++i)
	{
		EXPECT_EQ(wheelManager.GetWheel(i), wheels[i]);
	}
}


TEST(WheelManager, FindDictionaryInWheels)
{
	WheelManager wheelManager(TEST_SMALL_WHEELS_PATH);
	Dictionary dictionary(TEST_DICTIONARY_PATH);

	std::vector<std::string> foundWords;
	wheelManager.WheelWordsInDictionary(&dictionary, foundWords);
	EXPECT_EQ(foundWords.size(), 4);

	auto iter = std::find(foundWords.begin(), foundWords.end(), "ALL");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "ABORT");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "BRIAN");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "AND");
	EXPECT_TRUE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "ASTEROID");
	EXPECT_FALSE(iter != foundWords.end());

	iter = std::find(foundWords.begin(), foundWords.end(), "AM");
	EXPECT_FALSE(iter != foundWords.end());
}

TEST(WheelManager, BuildString)
{
	WheelManager wheelManager(WHEELS_PATH);
	std::vector<std::size_t> config(10, 0);

	std::string testString = wheelManager.BuildString(config);
	EXPECT_EQ("EAFFABBDAC", testString);

	config[0] = 1;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FAFFABBDAC", testString);

	config[1] = 6;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTFFABBDAC", testString);

	config[2] = 2;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKFABBDAC", testString);

	config[3] = 4;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKQABBDAC", testString);


	config[4] = 7;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKQXBBDAC", testString);


	config[5] = 5;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKQXKBDAC", testString);


	config[6] = 1;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKQXKCDAC", testString);

	config[8] = 4;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKQXKCDQC", testString);

	config[9] = 7;
	testString = wheelManager.BuildString(config);
	EXPECT_EQ("FTKQXKCDQZ", testString);



}



// As told by instructions
//TEST(WheelManager, ParseWheelFile)
//{
//	const int NUM_WHEELS = 8;
//	const int LETTERS_PER_WHEEL = 10;
//	WheelManager wheelManager;
//	wheelManager.LoadWheelsFromFile(WHEELS_PATH);
//	
//	EXPECT_EQ(wheelManager.GetNumWheels(), NUM_WHEELS);
//
//	const std::string wheels[NUM_WHEELS] = { "YGVLAINSQC",
//											 "SHYIXBODLW",
//											 "HCFQIJBPRE",
//											 "QUGFKYCMAZ",
//											 "FSKRVJNUQT",
//											 "RTNFQKMVDI",
//											 "EQZHTFDUON",
//											 "JAYFRGWEXP" };
//
//	for (int i = 0; i < NUM_WHEELS; ++i)
//	{
//		EXPECT_EQ(wheelManager.GetWheel(i).length(), LETTERS_PER_WHEEL);
//		EXPECT_EQ(wheelManager.GetWheel(i), wheels[i]);
//	}
//}



//
//TEST(WheelManager, FindWordsInWheels)
//{
//	WheelManager wheelManager(TEST_WHEELS_PATH);
//
//	const std::vector<std::string> testDictionary = { "ALL", "ABORT", "BRIAN", "AND", "SNIPPER", "AARDVARK" };
//
//	std::vector<std::string> foundWords;
//	wheelManager.WheelWordsInList(testDictionary, foundWords);
//	EXPECT_EQ(foundWords.size(), 4);
//
//	auto iter = std::find(foundWords.begin(), foundWords.end(), "ALL");
//	EXPECT_TRUE(iter != foundWords.end());
//
//	iter = std::find(foundWords.begin(), foundWords.end(), "ABORT");
//	EXPECT_TRUE(iter != foundWords.end());
//
//	iter = std::find(foundWords.begin(), foundWords.end(), "BRIAN");
//	EXPECT_TRUE(iter != foundWords.end());
//
//	iter = std::find(foundWords.begin(), foundWords.end(), "AND");
//	EXPECT_TRUE(iter != foundWords.end());
//
//	iter = std::find(foundWords.begin(), foundWords.end(), "SNIPPER");
//	EXPECT_FALSE(iter != foundWords.end());
//
//	iter = std::find(foundWords.begin(), foundWords.end(), "AARDVARK");
//	EXPECT_FALSE(iter != foundWords.end());
//}
