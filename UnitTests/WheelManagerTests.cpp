//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\FileManager.h>
#include <Utility\FileConstants.h>

#include <Wheels\WheelManager.h>

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
	wheelManager.LoadWheelsFromFile(FileConstants::TEXT_DIRECTORY + std::string("wheels.txt"));
	
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



