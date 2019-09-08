#pragma once
#include <cstdlib>
#include <ctime>
#include "../Sprite.h" 


class MineBomb
{
public:
	MineBomb(int initPosX, int initPosY, int difficultyLevel);
	MineBomb(int initPosX, int initPosY, double velX, double velY, int delayX, int delayY, int difficultyLevel);
	~MineBomb();
	void update();
	void render(BITMAP* buffer);
	void setExploded();
	bool hasExploded();
	Sprite* getSprite();
	int getDamageVal();
	void setDamageVal(int damageVal);
	bool isOffScreen();


private:
	Sprite* bombSprite;
	double difficultyLevel;
	double velX = 3, velY = 3;
	int delayX = 1, delayY = 1; 
	int initX = 0;
	int swerveDistance;
	
	bool swervingLeft = false;

	bool exploded = false; 
	int size = 50*SCALING_FACTOR_RELATIVE_TO_1280;
	int damageVal = 30;



};

