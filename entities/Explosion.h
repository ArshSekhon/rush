#pragma once
#include "../Sprite.h"
#include "../constants.h"
//https://www.deviantart.com/fralexion/art/Ashey-Explosion-Sprite-Sheet-440151065
 

#define SMALL_EXPLOSION 0
#define MEDIUM_EXPLOSION 1
#define BIG_EXPLOSION 2

class Explosion
{

private:
	Sprite* explosionSprite;
	
public:
	Explosion( int w, int h, int posX, int posY, int fps);
	Explosion( int size, int posX, int posY, int fps);
	void renderExplosion(BITMAP* destination);
	bool hasEnded();
	~Explosion();


};

