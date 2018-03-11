#pragma once
// Filename:	FileManager.h
// Description: A class to manage reading and writing to files
// Author:		Philip Jones
// Date:		11/03/18
// Notes:	


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

