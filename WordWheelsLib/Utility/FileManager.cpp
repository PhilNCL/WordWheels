#include "FileManager.h"

#include <fstream>	// std::ifstream
#include <sstream> // std::stringstream

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
		return true;
	}
	else
	{
		return false;
	}
}