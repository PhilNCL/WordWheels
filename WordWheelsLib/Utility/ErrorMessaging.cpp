// Filename:	ErrorMessaging.h
// Description: Definitions for ErrorMessaging functions
// Author:		Philip Jones
// Date:		12/03/18
// Notes:	

#include "ErrorMessaging.h"

// Standard Includes
#include <iostream>		//std::cin

// Namespaces
using namespace Errors;

// Pauses program until user presses a key when it exits with error code
void Abort(Error  errorType)
{
	std::cin.get();
	exit(errorType);
}

// Prints error message to user based on errorType
void HandleError(Error  errorType, const std::string& extraInfo)
{
	switch (errorType)
	{
	case NO_ARGUMENTS:
		std::cout << "ERROR: Please provide dictionary and filepath arguments!" << std::endl;
		break;
	case FILE_LOAD_FAILED:
		std::cout << "ERROR: Failed to load file" <<  extraInfo << std::endl;
		Abort(errorType);
		break;
	case INVALID_FILE_HEADER:
		std::cout << "ERROR: File does not have a valid header!" << std::endl;
		Abort(errorType);
		break;
	case INVALID_FILE_FORMAT:
		std::cout << "ERROR: File format is invalid!" << std::endl;
		Abort(errorType);
		break;
	default:
		std::cout << "ERROR: An unclassified error has occured" << std::endl;
		Abort(errorType);
		break;
	}

}
