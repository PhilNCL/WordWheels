#pragma once

#include <string>

namespace Errors
{
	enum Error { NO_ARGUMENTS, 
				 FILE_LOAD_FAILED,
			 };
}

void PrintError(Errors::Error  errorType, const std::string& extraInfo = "");