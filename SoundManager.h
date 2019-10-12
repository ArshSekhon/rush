#pragma once
#include "Constants.h"
#include "assets/sounds_define.h"
#include <allegro.h>

//SOUND EFFECTS
#define SOUND_CLICK 0 
#define SOUND_BUZZER 2
#define SOUND_JUMP 3

/**
 * @brief Manages sound and music for the game. Also Provides methods to play different sound effects.
 * 
 */
class SoundManager
{
private:
	MIDI* bgMusic;
	SAMPLE* buzzer;
	SAMPLE* clickSound; 
	SAMPLE* boingSound;
	GameState* gameState;
	DATAFILE* sounds_datafile;

public:
	/**
	 * @brief Construct a new Sound Manager object
	 * 
	 * @param gameState Pointer to the struct that represents game's state
	 */
	SoundManager(GameState* gameState);
	~SoundManager();
	/**
	 * @brief Starts playing background game music.
	 * 
	 * @param loop Should the music loop? If yes pass 1 else 0.
	 */
	void playBgMusic(int loop);
	/**
	 * @brief Stops the background game music.
	 * 
	 */
	void stopBgMusic(void);
	/**
	 * @brief Play a particular sound effect
	 * 
	 * @param sfxId ID of sound effect that has to played
	 * @param freq Frequency of the sound
	 */
	void playSound(int sfxId, int freq);
};