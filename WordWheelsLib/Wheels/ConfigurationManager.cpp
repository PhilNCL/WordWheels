// Filename:	ConfigurationManager.cpp
// Description: Methods for ConfigurationManager class
// Author:		Philip Jones
// Date:		12/03/18
// Notes:		
#include "ConfigurationManager.h"


ConfigurationManager::ConfigurationManager(const std::vector<std::size_t>& initialConfig, std::size_t firstIndex) :
	currentConfiguration(initialConfig), initialConfiguration(initialConfig)
{
	currentConfiguration[0] = firstIndex;
	lowestChangedIndex = lastChangedIndex = initialConfig.size() - 1;
}

ConfigurationManager::ConfigurationManager(const std::vector<std::size_t>& initialConfig) :
	currentConfiguration(initialConfig), initialConfiguration(initialConfig)
{
	lowestChangedIndex = lastChangedIndex = initialConfig.size() - 1;
}

ConfigurationManager::~ConfigurationManager()
{
}


// In the final configuration all indices are zero (except the first wheel which is fixed for threading)
bool   ConfigurationManager::IsFinalConfiguration() const
{
	const std::size_t FIRST_WHEEL_IDX = 0;
	const std::size_t SECOND_WHEEL_IDX = FIRST_WHEEL_IDX + 1;

	for (std::size_t idx = SECOND_WHEEL_IDX; idx < currentConfiguration.size(); ++idx)
	{
		if (currentConfiguration[idx])
		{
			return false;
		}
	}
	return true;
}


void ConfigurationManager::NextConfiguration()
{
	for (std::size_t index = currentConfiguration.size() - 1; index != 0; --index)
	{
		if (currentConfiguration[index])
		{
			--currentConfiguration[index];
			lastChangedIndex = index;
			while (index != currentConfiguration.size() - 1)
			{
				++index;
				currentConfiguration[index] = initialConfiguration[index];
			}
			break;
		}
	}

	UpdateLowestChangedIndex();
}


void ConfigurationManager::UpdateLowestChangedIndex()
{
	if (lastChangedIndex < lowestChangedIndex)
	{
		lowestChangedIndex = lastChangedIndex;
	}
}