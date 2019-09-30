#include "Sprite.h"


Sprite::Sprite(
	BITMAP* src,
	int w, int h,
	int ssheetNumRows, int ssheetNumCols,
	int numOfFrames, int fps,
	double velX, double velY, int xDelay, int yDelay,
	int xPos, int yPos, bool loop) {
	// intialize vars
	this->bmp = src;

	this->spritesheetSpriteW = this->bmp->w / ssheetNumCols;
	this->spritesheetSpriteH = this->bmp->h / ssheetNumRows;

	this->spritesheetRows = ssheetNumRows;
	this->spritesheetCols = ssheetNumCols;

	this->totalFrames = numOfFrames;

	this->singleFrame_H = bmp->h / ssheetNumRows;
	this->singleFrame_W = bmp->w / ssheetNumCols;

	this->xPos = xPos;
	this->yPos = yPos;

	this->velX = velX;
	this->velY = velY;

	this->xDelay = xDelay;
	this->yDelay = yDelay;

	this->w = w;
	this->h = h;

	this->fps = fps;
	this->loop = loop;
}

void Sprite::draw(BITMAP* dest) {
	drawframe(dest, currentFrame);
	updateAnimation();
}

void Sprite::updateAnimation() {
	// update animation according to fps
	if (clock() - lastFrameSwitchTime > 1000 / this->fps) {
		lastFrameSwitchTime = clock();
		currentFrame++;

		if (currentFrame > totalFrames - 1) {
			if (loop)
				currentFrame = 0;
			else
				animationFinished = true;
		}

	}
}

void Sprite::drawframe(BITMAP* destination, int frameNumber) {

	int spriteSheetFrameStartX = (frameNumber % this->spritesheetCols) * this->spritesheetSpriteW;
	int spriteSheetFrameStartY = (frameNumber / this->spritesheetCols) * this->spritesheetSpriteH;

	masked_stretch_blit(this->bmp, destination, spriteSheetFrameStartX, spriteSheetFrameStartY, this->singleFrame_W, this->singleFrame_H, this->xPos, this->yPos, this->w, this->h);

}

int Sprite::inside(int x, int y, int left, int top, int right, int bottom)
{
	if (x > left && x < right && y > top && y < bottom)
		return 1;
	else
		return 0;
}

int Sprite::pointInside(int px, int py)
{
	return this->inside(px, py, (int)this->xPos, (int)this->yPos, (int)xPos + singleFrame_W, (int)yPos + singleFrame_H);
}

int Sprite::collided(Sprite* other, int shrink)
{
	int wa = (int)xPos + singleFrame_W;
	int ha = (int)yPos + singleFrame_H;
	int wb = (int)other->xPos + other->singleFrame_W;
	int hb = (int)other->yPos + other->singleFrame_H;

	if (inside((int)xPos, (int)yPos, (int)other->xPos + shrink, (int)other->yPos + shrink, wb - shrink, hb - shrink) ||
		inside((int)xPos, ha, (int)other->xPos + shrink, (int)other->yPos + shrink, wb - shrink, hb - shrink) ||
		inside(wa, (int)yPos, (int)other->xPos + shrink, (int)other->yPos + shrink, wb - shrink, hb - shrink) ||
		inside(wa, ha, (int)other->xPos + shrink, (int)other->yPos + shrink, wb - shrink, hb - shrink))
		return 1;
	else
		return 0;
}

int Sprite::collided(BITMAP* buffer, int shrinkWidth, int shrinkHeight, Sprite* other, int shrinkOtherWidth, int shrinkOtherHeight)
{
	int x1 = (int)xPos + shrinkWidth;
	int y1 = (int)yPos + shrinkHeight;

	int x2 = (int)xPos + this->w - shrinkWidth;
	int y2 = (int)yPos + this->h - shrinkHeight;

	int other_x1 = (int)other->xPos + shrinkOtherWidth;
	int other_y1 = (int)other->yPos + shrinkOtherHeight;

	int other_x2 = (int)other->xPos + other->w - shrinkOtherWidth;
	int other_y2 = (int)other->yPos + other->h - shrinkOtherHeight;

	rect(buffer, x1, y1, x2, y2, makecol(255, 0, 0));
	rect(buffer, other_x1, other_y1, other_x2, other_y2, makecol(0, 255, 0)); 

	if (inside(x1, y2, other_x1, other_y1, other_x2, other_y2) ||
		inside(x1, y2, other_x1, other_y1, other_x2, other_y2) ||
		inside(x2, y1, other_x1, other_y1, other_x2, other_y2) ||
		inside(x2, y2, other_x1, other_y1, other_x2, other_y2))

		return 1;
	else
		return 0;
	return 0;
}


Sprite::~Sprite() { 
}

void Sprite::move(int direction) {

	if (direction == SPRITE_MOVE_RIGHT) {

		if (clock() - this->xMillis > this->xDelay) {
			this->xMillis = clock();
			this->xPos += this->velX;
		}

	}
	else if (direction == SPRITE_MOVE_LEFT) {

		if (clock() - this->xMillis > this->xDelay) {
			this->xMillis = clock();
			this->xPos -= this->velX;
		}

	}
	else if (direction == SPRITE_MOVE_UP) {

		if (clock() - this->yMillis > this->yDelay) {
			this->yMillis = clock();
			this->yPos -= this->velY;
		}

	}
	else if (direction == SPRITE_MOVE_DOWN) {
		if (clock() - this->yMillis > this->yDelay) {
			this->yMillis = clock();
			this->yPos += this->velY;
		}
	}
}


int Sprite::getX() {
	return xPos;
}

int Sprite::getY() {
	return yPos;
}


int Sprite::getW() {
	return w;
}

int Sprite::getH() {
	return h;
}


int Sprite::getCenterX() {
	return xPos + w / 2;
}

int Sprite::getCenterY() {
	return yPos + h / 2;
}


bool Sprite::isFinishedAnimating() {
	return animationFinished;
}