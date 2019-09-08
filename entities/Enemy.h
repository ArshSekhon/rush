#pragma once
#include "../Sprite.h"

class Enemy {


private:
	Sprite* enemySprite;
	int enemyH, enemyW; 
	int velX, velY;


public:

	Enemy(int w, int h, int posX, int posY, int fps);
	void renderEnemy(BITMAP* destination);
	~Enemy();
};