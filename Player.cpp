#include "Player.h"

static const float mSpeed = 3;

Player::Player(
		Textures* pTextureHolder,
		sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture,  
		float pAngle, 
		float pAngularVelocity) :
	AnimatedSprite(pPosition, pVelocity, pSize, pTexture, pAngle, pAngularVelocity),
		mHud(pTextureHolder),
		mBatteryLevel(5),
		mPlayerHealth(3)
{

	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	isHealthDisplay = false;
	isBatteryDisplay = false;
	
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
	mPLAYERSTATE = pUP;

}

Player::~Player(void)
{
}

void Player::reset()
{
	mPlayerHealth = 3;
	mBatteryLevel = 5;
	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
}

//all this to just move left and right with acceleration
void Player::update()
{
	//player movement example
	if(!isHealthDisplay && !isBatteryDisplay)
	{
		//move right
		if(isRight && !isLeft)
		{
			mVelocity.x = mSpeed;
			mCurrentAnimation = 1;
			mPLAYERSTATE = pRIGHT;
		}
		//move left
		else if(isLeft && !isRight)
		{
			mVelocity.x = -mSpeed;
			mCurrentAnimation = 3;
			mPLAYERSTATE = pLEFT;
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
			mPLAYERSTATE = pUP;
		}
		//move down
		else if(isDown && !isUp)
		{
			mVelocity.y = mSpeed;
			mCurrentAnimation = 2;
			mPLAYERSTATE = pDOWN;
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
	}
	else
	{
		mCurrentAnimation = 5;
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

void Player::draw(sf::RenderWindow *window, float pInterpolation)
{
	AnimatedSprite::draw(window, pInterpolation);

	if(isHealthDisplay)
		mHud.draw(window, mPosition.x + mSize.x/2 - mSize.x/3, mPosition.y - mSize.y/2 + mSize.y/3, hHEALTH, mPlayerHealth, mBatteryLevel);
	else if (isBatteryDisplay)
		mHud.draw(window, mPosition.x + mSize.x/2 - mSize.x/3, mPosition.y - mSize.y/2 + mSize.y/3, hBATTERY, mPlayerHealth, mBatteryLevel);
}