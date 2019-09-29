#pragma once
#include <cstdlib>
#include <ctime>
#include "../Sprite.h"

class Enemy {


private:
	//pointer to the sprite object for the enemy
	Sprite* enemySprite;
	// height and width of the enemy
	int enemyH, enemyW; 
	// velocity in x and y direction for the enemy
	int velX, velY;
	// x and y coordinate on the game world. This is used to keep track of enemy's position in the world
	float x_on_map;
	float y_on_map;

	// type of enemy
	int enemyType;


public:
	/**
	 * @brief Construct a new Enemy object
	 * 
	 * @param posX intial x-position of the enemy (can be greater than screen width)
	 * @param posY intial y-position of the enemy
	 * @param fps frame per second for the animation of the enemy sprite
	 */
	Enemy(  int posX, int posY, int fps);
	/**
	 * @brief Renders the enemy to the destination bitmap
	 * 
	 * @param destination Bitmap on which the enemy should be rendered on
	 */
	void renderEnemy(BITMAP* destination);
	/**
	 * @brief Get pointer to the sprite object for the enemy
	 * 
	 * @return Sprite* Pointer to the sprite object for enemy
	 */
	Sprite* getSprite();
	/**
	 * @brief Destroy the Enemy object
	 * 
	 */
	~Enemy();
};