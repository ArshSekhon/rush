#pragma once 
#include "Constants.h"

/**
 * @brief Allows loading and saving config from and to a file, allowing it to persist when the game is closed and re-launched.
 * 
 */
class ConfigManager{
public: 
	/**
	 * @brief Loads configuration from the config file.
	 * 
	 * @param configFile Pointer to the name of the configuration file.
	 * @param gs Pointer to the GameState struct containing game's existing state.
	 */
	void load_config(const char* configFile, GameState* gs);
	/**
	 * @brief Saves the current game configuration to a configuration file.
	 * 
	 * @param configFile Pointer to the name of the configuration file where configuration has to be saved to
	 * @param gs Pointer to the GameState struct containing game's existing state.
	 */
	void save_config(const char* configFile, GameState* gs);
};