#pragma once

// Standard Includes
#include <string>
#include <vector>

// Forward Declarations
class Wheel;

class WheelManager
{
public:
	WheelManager();
	WheelManager(const std::string& filepath);
	~WheelManager();

	void LoadWheelsFromFile(const std::string& filepath);
protected:
	
	std::vector<Wheel*> wheels;
};

