#include "Explosion.h"


Explosion::Explosion( int w, int h, int posX, int posY, int fps)
{
	 
	this->explosionSprite = new Sprite(load_bitmap("assets/sprites/explosion.bmp", NULL),
		w, h,
		1, 14, 14,
		fps, 0, 0,
		0, 0,
		posX - w/2, posY - h/2,0);
}

Explosion::Explosion( int size, int posX, int posY, int fps)
{
	int sizeInPx = 0;	

	switch (size) {
		case SMALL_EXPLOSION:
			sizeInPx = 50 * SCALING_FACTOR_RELATIVE_TO_1280;
			break;
		case MEDIUM_EXPLOSION:
			sizeInPx = 120 * SCALING_FACTOR_RELATIVE_TO_1280;
			break;
		case BIG_EXPLOSION: 
			sizeInPx = 240 * SCALING_FACTOR_RELATIVE_TO_1280;
			break;
		default : 
			break;
	}


	this->explosionSprite = new Sprite(load_bitmap("assets/sprites/explosion.bmp", NULL),
		sizeInPx, sizeInPx,
		1, 14, 14,
		60, 0, 0,
		0, 0,
		posX- sizeInPx/2, posY - sizeInPx / 2, 0);
} 

void Explosion::renderExplosion(BITMAP* destination)
{ 
	this->explosionSprite->draw(destination);
}


bool Explosion::hasEnded()
{
	return this->explosionSprite->isFinishedAnimating();
}


Explosion::~Explosion() 
{
	this->explosionSprite ->~Sprite();
}