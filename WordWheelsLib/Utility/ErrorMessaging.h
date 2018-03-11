#pragma once

#include <string>

namespace Errors
{
	enum Error { NO_ARGUMENTS, 
				 FILE_LOAD_FAILED,
				 INVALID_FILE_HEADER,
				 INVALID_FILE_FORMAT,
			 };
}

void PrintError(Errors::Error  errorType, const std::string& extraInfo = "");