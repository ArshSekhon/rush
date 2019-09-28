#pragma once
#include <cstdlib>
#include <ctime>
#include "../Sprite.h"

class Enemy {


private:
	Sprite* enemySprite;
	int enemyH, enemyW; 
	int velX, velY;
	float x_on_map;
	float y_on_map;
	int enemyType;


public:

	Enemy(  int posX, int posY, int fps);
	void renderEnemy(BITMAP* destination);
	Sprite* getSprite();
	~Enemy();
};