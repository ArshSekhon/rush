#include "EnemyShip.h"

EnemyShip::EnemyShip(int shipType, std::vector<Bullet*>* bullets, int initPosX, int initPosY, double skillLevel) {
	this->shipType = shipType;
	this->bullets = bullets;

	this->velY = this->velX = 30 * ((skillLevel * 1.0) / 10.0);

	this->swervingLeft = std::rand() % (2);


	if (this->shipType == ENEMY_SHIP_BIG)
		this->shipSprite = new Sprite(load_bitmap("assets/sprites/redbig.bmp", NULL),
			bigEnemyShipWidth, bigEnemyShipHeight,
			1, 8, 8, 10,
			velX, velY, 1, 1, 
			initPosX, initPosY, 1
		);
	else
		this->shipSprite = new Sprite(load_bitmap("assets/sprites/redsmallship.bmp", NULL),
			smallEnemyShipWidth, smallEnemyShipHeight,
			1, 5, 5, 10,
			velX, velY, 1, 1, 
			initPosX, initPosY, 1
		);

	if (skillLevel > 10)
		skillLevel = 10;

	this->skillLevel = skillLevel;
}


EnemyShip::~EnemyShip() 
{
	this->shipSprite->~Sprite();
}

void EnemyShip::render(BITMAP* buffer)
{
	this->update(); 
	this->shipSprite->draw(buffer);
	this->showHealthBar(buffer);
}

void EnemyShip::update()
{ 
	if (shipType == ENEMY_SHIP_SMALL) 
	{
		this->shipSprite->move(SPRITE_MOVE_DOWN);
	}
	else
	{

		if (clock() - lastBulletShot > enemyShootDelay) {
			lastBulletShot = clock();
			this->bullets->push_back(new Bullet(15 * SCALING_FACTOR_RELATIVE_TO_960, 35 * SCALING_FACTOR_RELATIVE_TO_960, 10 * SCALING_FACTOR_RELATIVE_TO_960, 8, this->shipSprite->getCenterX(), this->shipSprite->getY() + this->shipSprite->getH(), true, 20));

			this->enemyShootDelay = std::rand() % (5000) + 500;

		}

		this->shipSprite->move(SPRITE_MOVE_DOWN);

		if (this->swervingLeft) 
		{ 
			if (this->shipSprite->getX() < 10)
				swervingLeft = false;

			this->shipSprite->move(SPRITE_MOVE_LEFT);
		}
		else
		{
			if(this->shipSprite->getX() + this->shipSprite->getW() > PLAY_REGION_W*0.95)
			{
				
				swervingLeft = true;
			}

			this->shipSprite->move(SPRITE_MOVE_RIGHT);
		}

	}

}

int EnemyShip::getCollisionDamage()
{
	return (shipType == ENEMY_SHIP_BIG) ? bigShipCollisionDamage : smallShipCollisionDamage;
}

int EnemyShip::getW()
{
	return (shipType == ENEMY_SHIP_BIG) ? bigEnemyShipWidth : smallEnemyShipWidth;
}

int EnemyShip::getH()
{
	return (shipType == ENEMY_SHIP_BIG) ? bigEnemyShipHeight : smallEnemyShipHeight;
}

int EnemyShip::getX()
{
	return this->shipSprite->getX();
}

int EnemyShip::getY()
{
	return this->shipSprite->getY();
}

Sprite* EnemyShip::getSprite()
{
	return this->shipSprite;
}
	
int EnemyShip::getCenterX()
{
	return this->getX() + this->getW() / 2;
}

int  EnemyShip::getCenterY()
{
	return this->getY() + this->getH() / 2;
}

int EnemyShip::getShipType()
{
	return shipType;
}

void EnemyShip::showHealthBar(BITMAP* buffer) {
	int healthBarW = 70 * SCALING_FACTOR_RELATIVE_TO_1280,
		healthBarH = 7 * SCALING_FACTOR_RELATIVE_TO_1280;


	int healthBarX1 = this->shipSprite->getX(),
		healthBarY1 = this->shipSprite->getY(),
		healthBarX2 = healthBarX1 + healthBarW * (1.0*health / 100.0),
		healthBarX2Full = healthBarX1 + healthBarW,
		healthBarY2 = healthBarY1 + healthBarH;


	rectfill(buffer, healthBarX1, healthBarY1, healthBarX2Full, healthBarY2, makecol(0, 0, 0));
	rectfill(buffer, healthBarX1, healthBarY1, healthBarX2, healthBarY2 , makecol(255, 0, 0));

}

int EnemyShip::makeBulletImpact(int impact)
{
	
	if(this->shipType == ENEMY_SHIP_BIG) 
		this->health -= (10.0 - 1.0 * this->skillLevel) / 20.0 * impact;
	else
		this->health -= (10.0 - 1.0 * this->skillLevel) / 10.0 * impact;



	if (this->health < 0)
		this->health = 0;

	return this->health;
}

bool EnemyShip::isOffScreen()
{
	return (this->shipSprite->getY() > SCREEN_H);

}