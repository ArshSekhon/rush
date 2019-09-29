#include "Enemy.h"

Enemy::Enemy( int posX, int posY, int fps)
{	
	// randomly generate enemy type
	this->enemyType = std::rand() % (3);
	// if enemy type is a flame like thing
	if (this->enemyType > 1) {
		// set height and width of the enemy
		this->enemyH = 48 * SCALING_FACTOR_RELATIVE_TO_1280;
		this->enemyW = 96 * SCALING_FACTOR_RELATIVE_TO_1280;

		posY *= 1.03;
		// create a sprite object
		this->enemySprite = new Sprite(
			load_bitmap("assets/sprites/flame.bmp", NULL),
			enemyW, enemyH, // w, h
			1, 4,		// ssheetNumRows, ssheetNumCols
			4, 12,		// numOfFrames ,  fps
			7*SCALING_FACTOR_RELATIVE_TO_1280, 0, 1, 0,	// velX,  velY,  xDelay,  yDelay,
			posX, posY
			//(SCREEN_W) / 4, (SCREEN_H * (15.0/29)
		);
	
	}
	else {

		// set height and width of the enemy
		this->enemyH = 99 * SCALING_FACTOR_RELATIVE_TO_1280;
		this->enemyW = 66 * SCALING_FACTOR_RELATIVE_TO_1280; 
		// create a sprite object
		this->enemySprite = new Sprite(
			load_bitmap("assets/sprites/wizard-fly.bmp", NULL),
			enemyW, enemyH, // w, h
			1, 3,		// ssheetNumRows, ssheetNumCols
			3, 12,		// numOfFrames ,  fps
			7 * SCALING_FACTOR_RELATIVE_TO_1280, 0, 1, 0,	// velX,  velY,  xDelay,  yDelay,
			posX, posY
			//(SCREEN_W) / 4, (SCREEN_H * (15.0/29)
		);

	}
}


Enemy::~Enemy() 
{	
	this->enemySprite->~Sprite();
}

void Enemy::renderEnemy(BITMAP* buffer)
{	
	// render and update position of the enemy
	this->enemySprite->draw(buffer);
	this->enemySprite->move(SPRITE_MOVE_LEFT);
}

Sprite* Enemy::getSprite()
{
	return enemySprite;
}