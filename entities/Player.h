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

	int posX;
	int posY;
	int currentAnimation = ANIMATION_RUNNING;
	bool jumping = false;
	bool running = true;
	bool alive = true;
	int xOnMap;
	Sprite* playerSprite;

	bool isAscendingForJump = false;

	SoundManager* soundManager;
	float jumpHeight = 0;
	void update();
	int animationFrames[ANIMATIONS_COUNT][2];
	float jumpVelocity=0;

public:

	Player(int initPosX, int initPosY, int initXonMap, int w, int h);
	~Player();
	
	bool isAlive();
	void isAlive(bool alive);

	bool isJumping();
	void isJumping(bool alive);

	bool isRunning();
	void isRunning(bool alive);

	int getPosX();
	void setPosX(int posX);

	int getPosY();
	void setPosY(int posY);

	void render(BITMAP* buffer);

	void updateAnimation();

	void draw(BITMAP* dest);
	
	int get_x_on_map();
	void set_x_on_map(int x);

	void jump();
	void updatePos();


};