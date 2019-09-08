#pragma once
#include <vector>
#include "Bullet.h"
#include "../Sprite.h"
#include "../constants.h"
#include "../SoundManager.h"


class PlayerShip {

private:
	Sprite* shipSprite;
	int playerShipSize;
	std::vector<Bullet*>* bullets;
	bool keyUp;
	unsigned long lastBulletShootTime;
	int bulletShootDelay;
	bool wasSpaceUp = false; 
	bool dualBullets = false;
	bool isActive = true;
	SoundManager* soundManager;

public:
	PlayerShip(std::vector<Bullet*>* bullets, int bulletShootDelay, SoundManager* soundManager);
	~PlayerShip();
	void showShipAndHandleControls(BITMAP* buffer);
	Sprite* getSprite();
	void kill();
	bool isAlive();

};