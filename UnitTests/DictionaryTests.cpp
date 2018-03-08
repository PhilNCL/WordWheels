//Description Unit Tests for Interpreter
#include <gtest\gtest.h>


#include <Wheels\Dictionary.h>
#include <Utility\FileConstants.h>

#include <vector>

using namespace FileConstants;

TEST(Dictionary, AddingWords)
{
	Dictionary dictionary;
	dictionary.SortAfterAdding(true);
	dictionary.AddWord("Message");
	dictionary.AddWord("Merlin");
	dictionary.AddWord("My");
	dictionary.AddWord("Most");
	dictionary.AddWord("Melodic");
	dictionary.AddWord("Asparagus");

	std::vector<std::string> words;
	dictionary.GetWords("My", words);
	EXPECT_EQ(words.size(), 1);
	EXPECT_EQ(words.at(0), "My");
	
	words.clear();
	dictionary.GetWords("Me", words);
	EXPECT_EQ(words.size(), 3);
	EXPECT_EQ(words.at(0), "Merlin");
	EXPECT_EQ(words.at(1), "Melodic");
	EXPECT_EQ(words.at(2), "Message");

	words.clear();
	dictionary.GetWords("As", words);
	EXPECT_EQ(words.size(), 1);
}

TEST(Dictionary, LoadingFromFile)
{
	Dictionary dictionary;
	dictionary.LoadWordsFromFile(TEST_DICTIONARY_PATH);

	std::vector<std::string> words;
	dictionary.GetWords("ab", words);
	EXPECT_EQ(words.size(), 4);

	words.clear();
	dictionary.GetWords("al", words);
	EXPECT_EQ(words.size(), 2);

	words.clear();
	dictionary.GetWords("br", words);
	EXPECT_EQ(words.size(), 1);

	words.clear();
	dictionary.GetWords("am", words);
	EXPECT_EQ(words.size(), 1);
}

TEST(Dictionary, GetWordsOfLength)
{
	Dictionary dictionary;
	dictionary.LoadWordsFromFile(TEST_DICTIONARY_PATH);

	std::vector<std::string> words;
	dictionary.GetWords("ab", 4, words);
	EXPECT_EQ(words.size(), 2);
	words.clear();
	dictionary.GetWords("ab", 6, words);
	EXPECT_EQ(words.size(), 1);
}