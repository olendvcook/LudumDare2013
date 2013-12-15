#include "Enemy.h"


Enemy::Enemy(sf::Vector2f pPosition,  
		sf::Vector2i pSize, 
		sf::Texture *pTexture,
		sf::Vector2f pVelocity,
		bool pIsActive,
		float pAngle, 
		float pAngularVelocity) :
	//call superclass constructor
	AnimatedSprite(pPosition, pVelocity, pSize, pTexture, pAngle, pAngularVelocity),
	mIsActive(pIsActive)
{
	//insert animations based on Enemy spriteSheet
	mAnimations.insert(mAnimations.begin(), Animation(4, 0.2, false));
	//start idle animation
	AnimatedSprite::startAnimation();
}

Enemy::~Enemy(void)
{
}

//update based on what state we are in
void Enemy::update()
{

	//check bounds with right and left side of screen
	if(mPosition.x <= 32 + mSize.x/2)
	{
		mPosition.x = 32 + mSize.x/2;
		mVelocity.x = -mVelocity.x;
	}
	else if(mPosition.x >= 32 * 32 - (mSize.x/2 + 32))
	{
		mPosition.x = 32 * 32 - (mSize.x/2 + 32);
		mVelocity.x = -mVelocity.x;
	}

	//top and bottom
	if(mPosition.y <= 32 + mSize.y/2)
	{
		mPosition.y = 32 + mSize.y/2;
		mVelocity.y = -mVelocity.y;
	}
	else if (mPosition.y >= 32 * 32 - (mSize.y/2 + 32))
	{
		mPosition.y = 32 * 32 - (mSize.y/2 + 32);
		mVelocity.y = -mVelocity.y;
	}

	//call superclass update that handles changing pos by velocity and animates
	AnimatedSprite::update();
}

