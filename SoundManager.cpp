#include "SoundManager.h"

SoundManager::SoundManager(GameState* gameState) {
	this->gameState = gameState;
	this->sounds_datafile = load_datafile("assets/sounds.dat");

	//load music
	this->bgMusic = (MIDI*)sounds_datafile[LEGEND_MID].dat;;
	this->buzzer = (SAMPLE*)sounds_datafile[BUZZER_WAV].dat;
	this->clickSound = (SAMPLE*)sounds_datafile[CLICK_WAV].dat;
	this->boingSound = (SAMPLE*)sounds_datafile[JUMP_09_WAV].dat;


	if (!buzzer || !clickSound || !boingSound || !bgMusic) {		allegro_message("Error loading sounds.dat");	}

}

SoundManager::~SoundManager() {
	unload_datafile(sounds_datafile);
}

void SoundManager::playBgMusic(int loop) {
	
	if (this->gameState->bgMusicPlaying==1) {
		return;
	}

	if (play_midi(this->bgMusic, loop) == 0) {
		this->gameState->bgMusicPlaying = 1;
	}
	else {
		this->gameState->bgMusicPlaying = -1;
	}
}


void SoundManager::stopBgMusic(void)
{
	stop_midi();
	this->gameState->bgMusicPlaying = -1;
}

void SoundManager::playSound(int sfxId, int freq) {
	switch (sfxId) {
	case SOUND_CLICK:
		play_sample(clickSound, gameState->sound_volume * 12, 128, freq, 0);
		break;
	case SOUND_JUMP:
		play_sample(boingSound, gameState->sound_volume * 25.5, 128, freq, 0);
		break; 
	case SOUND_BUZZER:
		play_sample(buzzer, gameState->sound_volume * 25.5, 128, freq, 0);
		break;
	}
}
