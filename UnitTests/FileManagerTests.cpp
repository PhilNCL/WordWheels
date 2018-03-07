//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Utility\FileManager.h>
#include <Utility\FileConstants.h>

TEST(FileManager, OpeningFiles)
{
	FileManager manager;

	std::string validFilePath = FileConstants::TEXT_DIRECTORY + "TestFile.txt";
	std::string invalidFilePath = "InvalidFilePath";

	EXPECT_TRUE(manager.LoadFile(validFilePath, std::stringstream()));
	EXPECT_FALSE(manager.LoadFile(invalidFilePath, std::stringstream()));
}

