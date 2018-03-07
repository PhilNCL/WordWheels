//Description Unit Tests for Interpreter
#include <gtest\gtest.h>


#include <Wheels\Dictionary.h>

#include <vector>

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
	dictionary.GetWords("My", words);
	EXPECT_EQ(words.size(), 1);
	EXPECT_EQ(words.at(0), "My");
	
	words.clear();
	dictionary.GetWords("Me", words);
	EXPECT_EQ(words.size(), 3);
	EXPECT_EQ(words.at(0), "Melodic");
	EXPECT_EQ(words.at(1), "Merlin");
	EXPECT_EQ(words.at(2), "Message");

	words.clear();
	dictionary.GetWords("As", words);
	EXPECT_EQ(words.size(), 1);
}
