#pragma once
#include "../Sprite.h"
#include "../SoundManager.h"

#define ANIMATION_RUNNING 0
#define ANIMATION_JUMPING 1
#define ANIMATION_DYING 2
#define ANIMATIONS_COUNT 3

#define MAX_JUMP_HEIGHT_RELATIVE_TO_SCREEN_H 0.2
#define MAX_JUMP_VELOCITY 10*SCALING_FACTOR_RELATIVE_TO_1280
#define JUMP_DELAY 1

class Player: public Sprite
{
private:
	// store position of player on screen
	int posX;
	int posY;
	//keep track of animation and player's current action/status
	int currentAnimation = ANIMATION_RUNNING;
	bool currently_jumping = false;
	bool currently_running = true;
	bool currently_alive = true;
	// used to keep track of player's progress in the world
	int xOnMap;
	// pointer to the sprite object for the player
	Sprite* playerSprite;

	void update();
	// array to store information regarding animation frames on the spritesheet
	int animationFrames[ANIMATIONS_COUNT][2];
	SoundManager* soundManager;

	// jumping related information
	float jumpHeight = 0;
	float jumpVelocity=0;
	bool isAscendingForJump = false;

public:

	/**
	 * @brief Construct a new Player object
	 * 
	 * @param soundManager Pointer to the sound manager object that is used to play sound effects
	 * @param initPosX Initial position (x-coordinate) of the player on the screen
	 * @param initPosY Initial position (y-coordinate) of the player on the screen 
	 * @param initXonMap Initial Position of the player in the world.
	 * @param w Width of the player on the screen
	 * @param h Height of the player on the screen
	 */
	Player(SoundManager* soundManager, int initPosX, int initPosY, int initXonMap, int w, int h);
	/**
	 * @brief Destroy the Player object
	 * 
	 */
	~Player();
	/**
	 * @brief Checks if the Player is alive or not
	 * 
	 * @return true If the player is alive
	 * @return false If the player is dead
	 */
	bool isAlive();
	/**
	 * @brief Sets the if the the player is alive or not
	 * 
	 * @param currently_alive If the player is alive or not (true/false)
	 */
	void alive(bool currently_alive);
	/**
	 * @brief Checks if the player is currently jumping or not
	 * 
	 * @return true If the player is still jumping
	 * @return false If the player is running or dead
	 */
	bool isJumping();
	/**
	 * @brief Set the current state of the player to jumping
	 * 
	 * @param currently_jumping Set true if the player status has to change to jumping else false
	 */
	void jumping(bool currently_jumping);
	/**
	 * @brief Checks if the player is currently running or not
	 * 
	 * @return true If the player is currently running
	 * @return false If the player is currently jumping or is dead
	 */
	bool isRunning();
	/**
	 * @brief  Set the current state of the player to jumping
	 * 
	 * @param currently_running Set true if the player status has to change to running else false
	 */
	void running(bool currently_running);
	/**
	 * @brief Get the Position (x-coordinate) on the screen for the player
	 * 
	 * @return int x-coordinate on the screen for the player
	 */
	int getPosX();
	/**
	 * @brief Set the Position (x-coordinate) on the screen for the player
	 * 
	 * @param posX new x-coordinate on the screen for the player
	 */
	void setPosX(int posX);
	/**
	 * @brief Get the Position (y-coordinate) on the screen for the player
	 * 
	 * @return int y-coordinate on the screen for the player
	 */
	int getPosY();
	/**
	 * @brief Set the Position (y-coordinate) on the screen for the player
	 * 
	 * @param posX new y-coordinate on the screen for the player
	 */
	void setPosY(int posY); 
	/**
	 * @brief Updates the animation for the player
	 * 
	 */
	void updateAnimation();
	
	/**
	 * @brief Renders the player to the destination bitmap
	 * 
	 * @param destination Bitmap where the player should be rendered
	 */
	void draw(BITMAP* destination);
	
	/**
	 * @brief Gets the position (x-coordinate) of the player in the game world. Note: This is not same as x-coordinate on the screen
	 * 
	 * @return int x-coordinate of the player in the game world.
	 */
	int get_x_on_map();
	/**
	 * @brief Set the position (x-coordinate) of the player in the game world. Note: This is not same as x-coordinate on the screen
	 * 
	 * @param x New x-coordinate of the player in the game world.
	 */
	void set_x_on_map(int x);

	/**
	 * @brief Makes the player jump
	 * 
	 */
	void jump();
	/**
	 * @brief Updates the position of the player
	 * 
	 */
	void updatePos();
	/**
	 * @brief Kills the player
	 * 
	 */
	void kill();

};