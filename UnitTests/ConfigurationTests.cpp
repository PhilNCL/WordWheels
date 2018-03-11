//Description Unit Tests for Interpreter
#include <gtest\gtest.h>

#include <Wheels\ConfigurationManager.h>

TEST(Configuration, NextConfiguration)
{
	const std::vector<std::size_t> originalIndices = { 7, 8, 8, 4, 8, 8 };
	ConfigurationManager configuration(originalIndices);
	configuration.NextConfiguration();
	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 4);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 7);

	for (int i = 0; i < 7; ++i)
	{
		configuration.NextConfiguration();
	}

	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 4);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 0);

	configuration.NextConfiguration();
	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 4);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 8);

	for (int i = 0; i < 8; ++i)
	{
		configuration.NextConfiguration();
	}
	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 4);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 0);

	configuration.NextConfiguration();
	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 4);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 6);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 8);

	for (int i = 0; i < 9 * 6 + 8; ++i)
	{
		configuration.NextConfiguration();
	}
	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 4);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 0);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 0);

	configuration.NextConfiguration();
	EXPECT_EQ(configuration.GetCurrentConfig()[0], 7);
	EXPECT_EQ(configuration.GetCurrentConfig()[1], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[2], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[3], 3);
	EXPECT_EQ(configuration.GetCurrentConfig()[4], 8);
	EXPECT_EQ(configuration.GetCurrentConfig()[5], 8);
}