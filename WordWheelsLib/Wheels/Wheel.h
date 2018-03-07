#pragma once

// Standard Includes
#include <string>

class Wheel
{
public:
	Wheel(const std::string& wheelLetters);
	~Wheel();

protected:
	std::string letters;

};

