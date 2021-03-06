#include "SoundManager.h"

SoundManager::SoundManager(GameState* gameState) {
	this->gameState = gameState;
	//load music
	this->bgMusic = load_midi("assets/sounds/legend.mid"); 
	this->buzzer = load_wav("assets/sounds/buzzer.wav");
	this->clickSound = load_wav("assets/sounds/click.wav");
	this->boingSound = load_wav("assets/sounds/jump_09.wav");
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
