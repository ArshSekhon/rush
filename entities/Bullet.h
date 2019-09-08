#pragma once
#include "../Sprite.h"
#include "../constants.h"

class Bullet
{
private:
	Sprite* bulletSprite;
	int exploded; 
	int damageVal = 10;
	 
public:
	Bullet(int w, int h, double speedY, int delayY, int posX, int posY, bool isEnemyBullet = false, int damageVal = 20);
	~Bullet();
	void renderBullet(BITMAP* buffer);
	bool isOffScreen();
	bool hasExploded();
	bool isEnemyBullet;
	Sprite* getSprite();
	int getDamageVal();
	void setDamageVal(int damageVal);
};

