#pragma once
#include <vector>
#include "Bullet.h"
#include "../Sprite.h"
#include "../constants.h"

#include <cstdlib>
#include <ctime>

#define ENEMY_SHIP_SMALL 0
#define ENEMY_SHIP_BIG 1


class EnemyShip {
public:
	EnemyShip(int shipType, std::vector<Bullet*>* bullets, int initPosX, int initPosY, double skillLevel=0);
	~EnemyShip();
	Sprite* getSprite();
	void render(BITMAP* buffer);

	int getCollisionDamage();

	int getW();
	int getH();
	int getX();
	int getY();

	int getCenterX();
	int getCenterY();

	int makeBulletImpact(int impactLevel);

	int getShipType();
	bool isOffScreen();
	 

private:
	int shipType;
	Sprite* shipSprite;
	double skillLevel ;
	void update();	
	int health = 100;  

	int enemyShootDelay = 0;
	unsigned long lastBulletShot = 0;


	std::vector<Bullet*>* bullets;
	const int smallEnemyShipWidth = 120 * SCALING_FACTOR_RELATIVE_TO_1280, 
			  smallEnemyShipHeight =  120 * SCALING_FACTOR_RELATIVE_TO_1280;
	const int bigEnemyShipWidth = 175 * SCALING_FACTOR_RELATIVE_TO_1280, 
			  bigEnemyShipHeight = 175 * SCALING_FACTOR_RELATIVE_TO_1280;

	int bigShipCollisionDamage = 50;
	int smallShipCollisionDamage = 20;

	bool swervingLeft = false;


	double velX = 3, velY = 3;
	int delayX = 1, delayY = 1;

	void showHealthBar(BITMAP* buffer);
};