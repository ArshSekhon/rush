#include "Enemy.h"

Enemy::Enemy(int w, int h, int posX, int posY, int fps)
{
	this->enemyH = h;
	this->enemyW = w;


	this->enemySprite = new Sprite(
		load_bitmap("assets/sprites/wizard-fly.bmp", NULL),
		enemyW, enemyH, // w, h
		1, 3,		// ssheetNumRows, ssheetNumCols
		3, 12,		// numOfFrames ,  fps
		7, 0, 1, 0,	// velX,  velY,  xDelay,  yDelay,
		posX, posY
		//(SCREEN_W) / 4, (SCREEN_H * (15.0/29)
	);

}


Enemy::~Enemy() 
{
	this->enemySprite->~Sprite();
}

void Enemy::renderEnemy(BITMAP* buffer)
{
	this->enemySprite->draw(buffer);
	this->enemySprite->move(SPRITE_MOVE_LEFT);
}