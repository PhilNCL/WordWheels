#pragma once
// Filename:	ErrorMessaging.h
// Description: Interface for printing  error messages and reacting to errors
// Author:		Philip Jones
// Date:		12/03/18
// Notes:	

#include <string> // std::string

namespace Errors
{
	enum Error { NO_ARGUMENTS, 
				 FILE_LOAD_FAILED,
				 INVALID_FILE_HEADER,
				 INVALID_FILE_FORMAT,
			 };
}

void HandleError(Errors::Error  errorType, const std::string& extraInfo = "");