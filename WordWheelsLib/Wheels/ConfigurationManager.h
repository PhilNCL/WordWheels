#pragma once
// Filename:	ConfigurationManager.h
// Description: Stores and loops through different possible configurations
// Author:		Philip Jones
// Date:		12/03/18
// Notes:		Loops through the different permutations in reverse order.
//				Example: Consider 4 'wheels' with 2 possible states (0 and 1) 
//				Permutation 0: 1 / 1 / 1 / 1  
//			    Permutation 1: 1 / 1 / 1 / 0
//				Permutation 2: 1 / 1 / 0 / 1
//				Permutation 3: 1 / 1 / 0 / 0
//				Permutation 4: 1 / 0 / 1 / 1
//				etc....

// Standard Includes
#include <vector> // std::vector

class ConfigurationManager
{
public: // Constructor
	// Creates a ConfigurationManager with initial state equal to initialConfig
	ConfigurationManager(const std::vector<std::size_t>& initialConfig);

	// Creates a ConfigurationManager with the index of the first 'wheel' locked and otherwise with initial state equal to initialConfig 
	ConfigurationManager(const std::vector<std::size_t>& initialConfig, std::size_t firstIndex);

	~ConfigurationManager();

public: // Interface
	inline const std::vector<std::size_t>& GetCurrentConfig() const  { return currentConfiguration; }
	inline std::size_t					   GetLastChangedIndex() const { return lastChangedIndex; }
	inline std::size_t					   GetLowestChangedIndex() const { return lowestChangedIndex; }

	// Returns true if further calls to NextConfiguration() will have no effect
	bool   IsFinalConfiguration() const;

	// Moves currentConfiguration to the next permutation
	void NextConfiguration();

protected: // Helper functions
	// Keeps track of lowest 'wheel' in the configuration that has been altered from the original 
	void UpdateLowestChangedIndex();

protected: // Members
	std::vector<std::size_t> currentConfiguration;
	const std::vector<std::size_t> initialConfiguration;

	// Lowest index that has been changed in the current configuration
	std::size_t lowestChangedIndex;
	// Last index to be changed in the current configuration
	std::size_t lastChangedIndex;
};

