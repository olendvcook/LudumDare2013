#include "Player.h"

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
	mAnimations.insert(mAnimations.begin(), Animation(2, 0.2, false));
	mAnimations.insert(mAnimations.begin(), Animation(2, 0.2, false));
	mAnimations.insert(mAnimations.begin(), Animation(2, 0.2, false));
	mAnimations.insert(mAnimations.begin(), Animation(2, 0.2, false));

	mSprite.setScale(3,3);
	mSize.x *=3;
	mSize.y *=3;
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
		mCurrentAnimation = 2;
		mSprite.setScale(3,3);
	}
	//move left
	else if(isLeft && !isRight)
	{
		mVelocity.x = -mSpeed;
		mCurrentAnimation = 2;
		mSprite.setScale(-3,3);
	}
	//come to a stop
	else
	{
		mVelocity.x = 0;
		mCurrentAnimation = 0;
	}

	//move up
	if(isUp && !isDown)
	{
		mVelocity.y = -mSpeed;
		mCurrentAnimation = 2;
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
		mSprite.scale(1,1);
	}

	if(isAttacking)
	{
		mVelocity.x = 0;
		mVelocity.y = 0;
		mCurrentAnimation = 3;
	}
	
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
	

	//call superclass update
	AnimatedSprite::update();
}