// WordWheels.cpp : Defines the entry point for the console application.
#include <stdlib.h>
#include <iostream>
#include <Utility\FileManager.h>
int main(int argc, char* argv[])
{
	FileManager manager;
	std::cout << argc << std::endl;
	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}
	system("pause");
    return 0;
}

