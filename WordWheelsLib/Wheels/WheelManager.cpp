#include "WheelManager.h"

// Standard Includes
#include <cassert>  // assert()
#include <fstream>	// std::ifstream
#include <sstream>

#include "../Utility/FileManager.h"



// Declarations
using std::ifstream;

WheelManager::WheelManager()
{
}

WheelManager::WheelManager(const std::string& filepath)
{
	LoadWheelsFromFile(filepath);
}

WheelManager::~WheelManager()
{
}

void WheelManager::LoadWheelsFromFile(const std::string& filepath)
{
	FileManager fileManager;
	std::stringstream wheelFile;

	if (fileManager.LoadFile(filepath, wheelFile))
	{
		int numWheels;
		int numLettersPerWheel;

		wheelFile >> numWheels;
		wheelFile >> numLettersPerWheel;

		std::string wheel;
		while (wheelFile >> wheel)
		{
			wheels.push_back(wheel);
			assert(wheel.length() == numLettersPerWheel);
		}
		assert(wheels.size() == numWheels);
	}

}

void WheelManager::AddWheel(const std::string& wheel)
{
	wheels.push_back(wheel);
}

std::size_t WheelManager::GetNumWheels() const
{
	return wheels.size();
}

std::string WheelManager::GetWheel(std::size_t idx)
{
	if (idx < 0 || idx >= wheels.size())
	{
		return std::string();
	}
	else
	{
		return wheels[idx];
	}
}

std::vector<std::string> WordsInWheels(const std::vector<std::string>& potentialWords)
{
	return std::vector<std::string>();
}