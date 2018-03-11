// Filename:	main.cpp
// Description: Runs all unit tests
// Author:		Philip Jones
// Date:		11/03/18
// Notes:


#include <gtest\gtest.h>


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::cin.get();
	return 0;
}