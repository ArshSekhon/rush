#pragma once
#include "../Sprite.h"

class Enemy {


private:
	Sprite* enemySprite;
	int enemyH, enemyW; 
	int velX, velY;
	float x_on_map;
	float y_on_map;


public:

	Enemy(int w, int h, int posX, int posY, int fps);
	void renderEnemy(BITMAP* destination);
	Sprite* getSprite();
	~Enemy();
};