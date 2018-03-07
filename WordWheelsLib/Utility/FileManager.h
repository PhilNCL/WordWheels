#pragma once

// Standard Includes
#include <string>   // std::string
#include <sstream>  // std::stringstream

class FileManager
{
public:
	FileManager();
	~FileManager();

	bool LoadFile(const std::string& filepath, std::stringstream& filebuffer);
protected:

};

