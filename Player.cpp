#include "Player.h"

static const float mSpeed = 1.3;
static const float mEnemySpeed = 5;

Player::Player(
		sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture,  
		float pAngle, 
		float pAngularVelocity) :
	AnimatedSprite(pPosition, pVelocity, pSize, pTexture, pAngle, pAngularVelocity)
{
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	isAttacking = false;
	
	//add animations idle/walk/jump
	//animation takes in Number of frames / animation speed / escalator or not
	mAnimations.insert(mAnimations.end(), Animation(8, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(8, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(8, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(8, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.1, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.1, false));

	//start playing idle animation
	AnimatedSprite::startAnimation();

}

Player::~Player(void)
{
}

//all this to just move left and right with acceleration
void Player::update()
{
	//player movement example
	
	//move right
	if(isRight && !isLeft)
	{
		mVelocity.x = mSpeed;
		mCurrentAnimation = 1;
	}
	//move left
	else if(isLeft && !isRight)
	{
		mVelocity.x = -mSpeed;
		mCurrentAnimation = 3;
	}
	//come to a stop
	else
	{
		mVelocity.x = 0;
	}

	//move up
	if(isUp && !isDown)
	{
		mVelocity.y = -mSpeed;
		mCurrentAnimation = 0;
	}
	//move down
	else if(isDown && !isUp)
	{
		mVelocity.y = mSpeed;
		mCurrentAnimation = 2;
	}
	//come to a stop
	else
	{
		mVelocity.y = 0;
	}

	if(mVelocity.x == 0 && mVelocity.y == 0)
	{
		if(mCurrentAnimation == 0)
			mCurrentAnimation = 4;
		else if(mCurrentAnimation == 1)
			mCurrentAnimation = 5;
		else if(mCurrentAnimation == 2)
			mCurrentAnimation = 6;
		else if(mCurrentAnimation == 3)
			mCurrentAnimation = 7;
	}

	if(isAttacking)
	{
		mVelocity.x = 0;
		mVelocity.y = 0;
	}
	
	/*
	//check bounds with right and left side of screen
	if(mPosition.x <= 32 + mSize.x/2)
	{
		mPosition.x = 32 + mSize.x/2;
		if(mVelocity.x < 0)
			mVelocity.x = 0;
	}
	else if(mPosition.x >= 32 * 32 - (mSize.x/2 + 32))
	{
		mPosition.x = 32 * 32 - (mSize.x/2 + 32);
		if(mVelocity.x > 0)
			mVelocity.x = 0;
	}

	//top and bottom
	if(mPosition.y <= 32 + mSize.y/2)
	{
		mPosition.y = 32 + mSize.y/2;
		if(mVelocity.y < 0)
			mVelocity.y = 0;
	}
	else if (mPosition.y >= 32 * 32 - (mSize.y/2 + 32))
	{
		mPosition.y = 32 * 32 - (mSize.y/2 + 32);
		if(mVelocity.y > 0)
			mVelocity.y = 0;
	}
	*/
	

	//call superclass update
	AnimatedSprite::update();
}