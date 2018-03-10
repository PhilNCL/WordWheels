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
	EXPECT_EQ(words.at(0), "MY");
	
	words.clear();
	dictionary.GetWords("Me", words);
	EXPECT_EQ(words.size(), 3);
	EXPECT_EQ(words.at(0), "MELODIC");
	EXPECT_EQ(words.at(1), "MERLIN");
	EXPECT_EQ(words.at(2), "MESSAGE");

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

TEST(Dictionary, CaseInsensitive)
{
	Dictionary dictionary;
	dictionary.AddWord("Koala");
	dictionary.AddWord("giraffe");
	dictionary.AddWord("tUrkey");
	dictionary.AddWord("aaRDVARK");
	dictionary.AddWord("pAnDa");

	std::vector<std::string> words;

	dictionary.GetWords("Ko", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("kO", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("ko", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("KO", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();

	dictionary.GetWords("Gi", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("gI", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("GI", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("gi", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();


	dictionary.GetWords("Tu", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("tU", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("TU", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("tu", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();

	dictionary.GetWords("Aa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("aA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("AA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("aa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();

	dictionary.GetWords("Pa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("pA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("PA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWords("pa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
}
