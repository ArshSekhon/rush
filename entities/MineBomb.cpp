#include "./MineBomb.h" 

MineBomb::MineBomb( int initPosX, int initPosY, int difficultyLevel)
{
	this->difficultyLevel = difficultyLevel;
	this->velY = this->velX = 30 * ((difficultyLevel * 1.0) / 10.0);
	
	this->bombSprite = new Sprite(load_bitmap("assets/sprites/mines.bmp", NULL), this->size, this->size, 1, 2, 2, 2, this->velX, this->velY, this->delayX, this->delayY, initPosX, initPosY, 1);
	srand(time(NULL)); 
	this->swerveDistance = std::rand()%(SCREEN_W/4);

	this->swervingLeft = std::rand() % (2);

	this->initX = initPosX;
	
}

MineBomb::MineBomb( int initPosX, int initPosY, double velX, double velY, int delayX, int delayY, int difficultyLevel) 
{
	
	this->velX = velX;
	this->velY = velY;
	this->delayX = delayX;
	this->delayY = delayY;

	this->bombSprite = new Sprite(load_bitmap("assets/sprites/mines.bmp", NULL), this->size, this->size, 1, 2, 2, 2, this->velX, this->velY, this->delayX, this->delayY, initPosX, initPosY, 1);
	
}

MineBomb::~MineBomb() {
	this->bombSprite->~Sprite();

}

void MineBomb::update() { 
	this->bombSprite->move(SPRITE_MOVE_DOWN);



	if (swervingLeft) {
		if (this->bombSprite->getCenterX() > initX - this->swerveDistance && this->bombSprite->getX() > 0)
			this->bombSprite->move(SPRITE_MOVE_LEFT);
		else 
		{
			swervingLeft = false;
		}
	}
	else {
		if (this->bombSprite->getCenterX() < initX + this->swerveDistance && this->bombSprite->getX() + this->bombSprite->getW() < PLAY_REGION_W)
			this->bombSprite->move(SPRITE_MOVE_RIGHT);
		else 
		{
			swervingLeft = true;
		}
	}


}

void MineBomb::render(BITMAP* buffer) {
	this->update();
	this->bombSprite->draw(buffer);
}

void MineBomb::setExploded() {
	this->exploded = true;
}

bool MineBomb::hasExploded() {
	return this->exploded;
}

Sprite* MineBomb::getSprite() {
	return this->bombSprite;
}
 
int MineBomb::getDamageVal()
{
	return damageVal;
}

void MineBomb::setDamageVal(int damageVal)
{
	this->damageVal = damageVal;
}

bool MineBomb::isOffScreen()
{
	return (this->bombSprite->getY() > SCREEN_H);
}