#pragma once
#include "constants.h"
#include <allegro.h>
// directions of sprite motion
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
	int currentFrame = 0, totalFrames, fps;
	long lastFrameSwitchTime = 0;
	int spritesheetCols, spritesheetRows;
	int spritesheetSpriteW, spritesheetSpriteH ;
	//vars to store information regarding the speed of the motion of sprite
	double velX, velY;
	int xDelay, yDelay;
	unsigned long xMillis, yMillis;
	// vars to hold info regarding animation
	bool loop = true;
	bool animationFinished = false;
	// pointer to the bitmap spritesheet
	BITMAP* bmp;
	// draws a given frame number to the destination
	void drawframe(BITMAP* destination, int frameNumber);
	// function to check if the point (x,y) is inside the box
	int inside(int x, int y, int left, int top, int right, int bottom);
	// checks if the point is inside the sprite
	int pointInside(int px, int py);


public:
	/**
	 * @brief Construct a new Sprite object
	 * 
	 * @param src Bitmap containing the spritesheet for the sprite
	 * @param w Width of a single frame of the spritesheet on rendering
	 * @param h Height of a single frame of the spritesheet on rendering
	 * @param ssheetNumRows Number of rows in the spritesheet
	 * @param ssheetNumCols Number of columns in the spritesheet
	 * @param numOfFrames Number of frames in the spriteshett
	 * @param fps Frames per second at which sprite should be animated
	 * @param velX The value by which the x-position of the sprite should be incremented after delayX milliseconds have passed
	 * @param velY The value by which the y-position of the sprite should be incremented after delayY milliseconds have passed 
	 * @param xDelay The time in milliseconds after which the x-position of the sprite should be updated
	 * @param yDelay The time in milliseconds after which the y-position of the sprite should be updated 
	 * @param xPos Initial X-Position of the sprite
	 * @param yPos Initial Y-Position of the sprite 
	 * @param loop Pass true if the animation has to be looped false if not
	 */
	Sprite(BITMAP* src, 
		int w, int h,
		int ssheetNumRows, int ssheetNumCols, int numOfFrames, 
		int fps, double velX = 0, double velY = 0, 
		int xDelay = 0, int yDelay = 0, 
		int xPos = 0, int yPos = 0, bool loop = 1);
	/**
	 * @brief Destroy the Sprite object
	 * 
	 */
	~Sprite();
	/**
	 * @brief Renders the current frame of the sprite to the destination bitmap
	 * 
	 * @param destination Bitmap on which the sprite should be rendered
	 */
	void draw(BITMAP* destination);
	/**
	 * @brief Updates the frame of the Sprite animation according to the fps value of the animation
	 * 
	 */
	void updateAnimation();
	/**
	 * @brief Set the Position of the sprite
	 * 
	 * @param x x-coordinate for the position
	 * @param y y-coordinate for the position
	 */
	void setPosition(int x, int y); 
	/**
	 * @brief Checks if this sprite has collidedn with another sprite
	 * 
	 * @param other Pointer to the other sprite which has to be check for collision with this sprite
	 * @param shrink Shrink value for collision detection box in pixels
	 * @return int 1 if there is a collision, 0 if these is none
	 */
	int collided(Sprite* other, int shrink);
	/**
	 * @brief Checks if this sprite has collidedn with another sprite
	 * 
	 * @param buffer Bitmap to draw collision boxes on (for debugging purposes only)
	 * @param shrinkHeight Shrink value for height in pixels for this sprite
	 * @param shrinkWidth  Shrink value for width in pixels for this sprite
	 * @param other Pointer to the other sprite which has to be check for collision with this sprite
	 * @param shrinkOtherWidth Shrink value for width in pixels for the other sprite
	 * @param shrinkOtherHeight Shrink value for height in pixels for the other sprite
	 * @return int 1 if there is a collision, 0 if these is none 
	 */
	int collided(BITMAP* buffer, int shrinkHeight, int shrinkWidth, Sprite* other, int shrinkOtherWidth, int shrinkOtherHeight);
	/**
	 * @brief Updates the position of the sprite in order to make it move
	 * 
	 * @param direction Direction in which the sprite should be moved
	 */
	void move(int direction);
	/**
	 * @brief Gets the X-coordinate of the top-left corner of the sprite
	 * 
	 * @return int x-coordinate
	 */
	int getX();
	/**
	 * @brief Gets the Y-coordinate of the top-left corner of the sprite
	 * 
	 * @return int y-coordinate
	 */
	int getY();
	/**
	 * @brief Gets the width of the sprite
	 * 
	 * @return int Width of the sprite
	 */
	int getW();
	/**
	 * @brief Gets the height of the sprite
	 * 
	 * @return int Height of the sprite
	 */
	int getH();
	/**
	 * @brief Gets the x-coordinate of the center
	 * 
	 * @return int x-coordinate of the center
	 */
	int getCenterX();
	/**
	 * @brief Gets the y-coordinate of the center
	 * 
	 * @return int y-coordinate of the center
	 */
	int getCenterY();
	/**
	 * @brief Checks if the animation of the non-looping sprite has ended
	 * 
	 * @return true If the animation has ended
	 * @return false If the animation is in progress
	 */
	bool isFinishedAnimating();

};