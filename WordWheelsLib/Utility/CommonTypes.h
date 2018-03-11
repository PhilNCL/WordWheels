#pragma once
// Filename:	CommonTypes.h
// Description: A collection of useful typedefs
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		

// Standard Includes
#include <map>			// std::map
#include <set>			// std::set
#include <string>		// std::string
#include <vector>		// std::vector

namespace Wheels
{
	typedef std::vector<std::string> StringVec;
	typedef std::set<std::string> StringSet;
	typedef std::map< std::string, StringVec > DictionaryMap;
}