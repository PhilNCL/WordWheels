// Filename:	FileManager.cpp
// Description: Methods for FileManager class
// Author:		Philip Jones
// Date:		11/03/18
// Notes:	
#include "FileManager.h"

// Standard Includes
#include <fstream>	 // std::ifstream
#include <sstream>	 // std::stringstream

// Namespaces
using std::ifstream;
using std::stringstream;

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

bool FileManager::LoadFile(const std::string& filepath, std::stringstream& filebuffer)
{
	ifstream inFile(filepath);
	if (inFile)
	{
		filebuffer << inFile.rdbuf();
		inFile.close();
		return true;
	}
	else
	{
		return false;
	}
}