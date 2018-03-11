#include "ErrorMessaging.h"

#include <iostream>
using namespace Errors;

void PrintError(Errors::Error  errorType, const std::string& extraInfo)
{
	switch (errorType)
	{
	case NO_ARGUMENTS:
		std::cout << "ERROR: Please provide dictionary and filepath arguments!" << std::endl;
		break;
	case FILE_LOAD_FAILED:
		std::cout << "ERROR: Failed to load file" <<  extraInfo << std::endl;
		break;
	default:
		std::cout << "ERROR: An unclassified error has occured" << std::endl;
		break;
	}
}
