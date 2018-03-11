#include "StringPrinting.h"


void PrintStrings(std::ostream& os, const Wheels::StringVec& stringVec)
{
	for (auto& str : stringVec)
	{
		os << str << std::endl;
	}
	os << "Printed: " << stringVec.size() << " strings" << std::endl;
}
