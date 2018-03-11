// Filename:	FileManagerTests.cpp
// Description: Unit Tests for FileManager Class
// Author:		Philip Jones
// Date:		11/03/18
// Notes:

// Google Test Includes
#include <gtest\gtest.h>

// Utility Includes
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