#pragma once

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