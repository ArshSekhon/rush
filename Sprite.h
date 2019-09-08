#pragma once
#include "constants.h"
#include <allegro.h>

#define SPRITE_MOVE_RIGHT 0
#define SPRITE_MOVE_LEFT 1
#define SPRITE_MOVE_UP 2
#define SPRITE_MOVE_DOWN 3


class Sprite {


protected:
	bool displayOnScreen;
	int direction;
	double xPos, yPos;
	int w, h;
	int singleFrame_W, singleFrame_H;
	int totalFrames, fps;
	long lastFrameSwitchTime = 0;
	int spritesheetCols, spritesheetRows;
	int spritesheetSpriteW, spritesheetSpriteH ;

	double velX, velY;
	int xDelay, yDelay;
	unsigned long xMillis, yMillis;
	bool loop = true;
	bool animationFinished = false;

	BITMAP* bmp;

	void drawframe(BITMAP* destination, int frameNumber);
	int inside(int x, int y, int left, int top, int right, int bottom);
	int pointInside(int px, int py);

	int currentFrame = 0;

public:
	Sprite(BITMAP* src, 
		int w, int h,
		int ssheetNumRows, int ssheetNumCols, int numOfFrames, 
		int fps, double velX = 0, double velY = 0, 
		int xDelay = 0, int yDelay = 0, 
		int xPos = 0, int yPos = 0, bool loop = 1);
	~Sprite();
	void draw(BITMAP* destination);
	void updateAnimation();
	void setPosition(int x, int y); 
	int collided(Sprite* other, int shrink);
	int collided(BITMAP* buffer, int shrinkHeight, int shrinkWidth, Sprite* other, int shrinkOtherWidth, int shrinkOtherHeight);
	void move(int direction);
	int getX();
	int getY();
	int getW();
	int getH();
	int getCenterX();
	int getCenterY();
	bool isFinishedAnimating();

};