#include "Enemy.h"

static const float mEnemySpeed = 0.8;

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
	counter = 0;

	mAnimations.insert(mAnimations.begin(), Animation(8, 0.05, false));
	mAnimations.insert(mAnimations.begin(), Animation(8, 0.05, false));
	mAnimations.insert(mAnimations.begin(), Animation(8, 0.05, false));
	mAnimations.insert(mAnimations.begin(), Animation(8, 0.05, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.05, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.05, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.05, false));
	mAnimations.insert(mAnimations.end(), Animation(4, 0.05, false));
	//start idle animation
	AnimatedSprite::startAnimation();
}

Enemy::~Enemy(void)
{
}

//update based on what state we are in
void Enemy::update(sf::Vector2f pPlayerPosition)
{
	if(mIsActive)
	{
		float dx = pPlayerPosition.x - mPosition.x;
		float dy = pPlayerPosition.y - mPosition.y;
		float length = sqrtf(dx*dx + dy*dy);
		float angle = atan2f(dy,dx);

		if(angle >= -2.25 && angle <= -.75)
			if(mVelocity.x == 0 && mVelocity.y == 0)
				setCurrentAnimation(4);
			else
				setCurrentAnimation(0);
		else if (angle > -.75 && angle <= .75)
			if(mVelocity.x == 0 && mVelocity.y == 0)
				setCurrentAnimation(5);
			else
				setCurrentAnimation(1);
		else if (angle >.75 && angle <= 2.25)
			if(mVelocity.x == 0 && mVelocity.y == 0)
				setCurrentAnimation(6);
			else
				setCurrentAnimation(2);
		else
			if(mVelocity.x == 0 && mVelocity.y == 0)
				setCurrentAnimation(7);
			else
				setCurrentAnimation(3);

		if(length <= 100)
		{
			dx /= length;
			dy /= length;

			mVelocity.x = dx*mEnemySpeed;
			mVelocity.y = dy*mEnemySpeed;
			startAnimation();

		}
		else
		{
			mVelocity.x = 0;
			mVelocity.y = 0;
		}

		AnimatedSprite::update();
	}
	else
	{
		endAnimation();
		if(mClock.getElapsedTime().asSeconds() > 0.1)
		{
			switch (counter)
			{
			case 0:
				mCurrentAnimation = counter;
				mAnimations.at(mCurrentAnimation).setCurrentFrame(0);
				counter++;
				break;
			case 1:
				mCurrentAnimation = counter;
				mAnimations.at(mCurrentAnimation).setCurrentFrame(0);
				counter++;
				break;
			case 2:
				mCurrentAnimation = counter;
				mAnimations.at(mCurrentAnimation).setCurrentFrame(0);
				counter++;
				break;
			case 3:
				mCurrentAnimation = counter;
				mAnimations.at(mCurrentAnimation).setCurrentFrame(0);
				counter++;
				break;
			default:
				mCurrentAnimation = 7;
				mAnimations.at(mCurrentAnimation).setCurrentFrame(6);
				break;
			}
			mClock.restart();
		}
		
	}

	/*
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
	*/
	//call superclass update that handles changing pos by velocity and animates
}

