//Description Unit Tests for Interpreter
#include <gtest\gtest.h>


#include <Wheels\Dictionary.h>
#include <Utility\FileConstants.h>

#include <vector>

using namespace FileConstants;

TEST(Dictionary, AddingWords)
{
	Dictionary dictionary;
	dictionary.AddWord("Message");
	dictionary.AddWord("Merlin");
	dictionary.AddWord("My");
	dictionary.AddWord("Most");
	dictionary.AddWord("Melodic");
	dictionary.AddWord("Asparagus");

	std::vector<std::string> words;
	dictionary.GetWordsFromKey("My", words);
	EXPECT_EQ(words.size(), 1);
	EXPECT_EQ(words.at(0), "MY");
	
	words.clear();
	dictionary.GetWordsFromKey("Me", words);
	EXPECT_EQ(words.size(), 3);
	EXPECT_EQ(words.at(0), "MESSAGE"); 
	EXPECT_EQ(words.at(1), "MERLIN");
	EXPECT_EQ(words.at(2), "MELODIC");

	words.clear();
	dictionary.GetWordsFromKey("As", words);
	EXPECT_EQ(words.size(), 1);
}

TEST(Dictionary, LoadingFromFile)
{
	Dictionary dictionary;
	dictionary.LoadWordsFromFile(TEST_DICTIONARY_PATH);

	std::vector<std::string> words;
	dictionary.GetWordsFromKey("ab", words);
	EXPECT_EQ(words.size(), 4);

	words.clear();
	dictionary.GetWordsFromKey("al", words);
	EXPECT_EQ(words.size(), 2);

	words.clear();
	dictionary.GetWordsFromKey("br", words);
	EXPECT_EQ(words.size(), 1);

	words.clear();
	dictionary.GetWordsFromKey("am", words);
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

	dictionary.GetWordsFromKey("Ko", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("kO", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("ko", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("KO", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();

	dictionary.GetWordsFromKey("Gi", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("gI", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("GI", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("gi", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();


	dictionary.GetWordsFromKey("Tu", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("tU", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("TU", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("tu", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();

	dictionary.GetWordsFromKey("Aa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("aA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("AA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("aa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();

	dictionary.GetWordsFromKey("Pa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("pA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("PA", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
	dictionary.GetWordsFromKey("pa", words);
	EXPECT_EQ(words.size(), 1);
	words.clear();
}

TEST(Dictionary, GetWordsBelowSize)
{
	Dictionary dictionary;
	dictionary.LoadWordsFromFile(TEST_DICTIONARY_PATH);

	std::vector<std::string> words;
	dictionary.GetWordsFromKey("ab", words, 4);
	EXPECT_EQ(words.size(), 2);

	words.clear();
	dictionary.GetWordsFromKey("al", words, 4);
	EXPECT_EQ(words.size(), 1);

	words.clear();
	dictionary.GetWordsFromKey("br", words, 8);
	EXPECT_EQ(words.size(), 1);

	words.clear();
	dictionary.GetWordsFromKey("am", words, 1);
	EXPECT_EQ(words.size(), 0);
}
