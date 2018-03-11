#pragma once
// Filename:	CommonTypes.h
// Description: A collection of useful typedefs
// Author:		Philip Jones
// Date:		11/03/18
// Notes:		

// Standard Includes
#include <map>
#include <set>
#include <string>
#include <vector>

namespace Wheels
{
	typedef std::vector<std::string> StringVec;
	typedef std::set<std::string> StringSet;
	typedef std::map< std::string, StringVec > DictionaryMap;
}