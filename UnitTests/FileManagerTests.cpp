//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\FileManager.h>
#include <Utility\FileConstants.h>

TEST(FileManager, OpeningFiles)
{
	FileManager manager;

	std::string validFilePath = FileConstants::TEXT_DIRECTORY + "TestFile.txt";
	std::string invalidFilePath = "InvalidFilePath";
	std::stringstream dummyStream;

	EXPECT_TRUE(manager.LoadFile(validFilePath, dummyStream));
	EXPECT_FALSE(manager.LoadFile(invalidFilePath, dummyStream));
}

TEST(FileManager, ReadingFiles)
{
	FileManager manager;

	std::string			validFilePath = FileConstants::TEXT_DIRECTORY + "TestFile.txt";
	std::stringstream   sstream;
	if (manager.LoadFile(validFilePath, sstream))
	{
		EXPECT_EQ(sstream.str(),"testing");
	}
}