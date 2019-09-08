#include "Bullet.h"

Bullet::Bullet(int w, int h, double speedY, int delayY, int posX, int posY, bool isEnemyBullet, int damageVal) {
	this->exploded = false;
	if(!isEnemyBullet)
		this->bulletSprite = new Sprite(load_bitmap("assets/sprites/bullet.bmp",NULL), 
									w, h, 
									1, 1, 1, 
									60, 
									0, speedY, 
									0, delayY, 
									posX, posY);
	else
		this->bulletSprite = new Sprite(load_bitmap("assets/sprites/bullet_red.bmp", NULL),
			w, h,
			1, 1, 1,
			60,
			0, speedY,
			0, delayY,
			posX, posY);

	this->isEnemyBullet = isEnemyBullet;
	this->damageVal = damageVal;

}

Bullet::~Bullet() {
	this->bulletSprite->~Sprite();
}

void Bullet::renderBullet(BITMAP* buffer) {
	this->bulletSprite->draw(buffer);
	if(isEnemyBullet) 
		this->bulletSprite->move(SPRITE_MOVE_DOWN);
	else
		this->bulletSprite->move(SPRITE_MOVE_UP);

}

bool Bullet::isOffScreen() {
	int yCoord = this->bulletSprite->getY();
	return (yCoord > SCREEN_H || yCoord < 0);
}

bool Bullet::hasExploded() {
	return exploded;
}

Sprite* Bullet::getSprite() {
	return this->bulletSprite;
}

int Bullet::getDamageVal() 
{
	return damageVal;
}

void Bullet::setDamageVal(int damageVal)
{
	this->damageVal = damageVal;
}