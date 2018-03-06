#include "WheelManager.h"

// Standard Includes
#include <fstream>	//std::ifstream
#include <sstream>

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
	int numWheels;
	int numLettersPerWheel;

}