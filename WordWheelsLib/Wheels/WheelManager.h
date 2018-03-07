#pragma once

// Standard Includes
#include <string>
#include <vector>

class WheelManager
{
public:
	WheelManager();
	WheelManager(const std::string& filepath);
	~WheelManager();

	void AddWheel(const std::string& wheel);
	void LoadWheelsFromFile(const std::string& filepath);

	std::size_t GetNumWheels() const;
	std::string GetWheel(std::size_t idx);
protected:
	std::vector<std::string> wheels;


};

