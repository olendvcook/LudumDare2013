#include "AnimatedSprite.h"

//Animated Entity with a sprite, designed to be extended for any Entity with animation 
//see header file for more description
AnimatedSprite::AnimatedSprite(
	sf::Vector2f pPosition, 
	sf::Vector2f pVelocity, 
	sf::Vector2i pSize, 
	sf::Texture *pTexture, 
	float pAngle, 
	float pAngularVelocity) :
	//initialization list
		mSprite(*pTexture),
		mPosition(pPosition),
		mVelocity(pVelocity),
		mSpriteSize(pSize),
		mSize(pSize),
		mAngle(pAngle),
		mAngularVelocity(pAngularVelocity),
		mCurrentAnimation(0),
		mIsAnimating(false)
{
	//set origin of sprite in center for easy transformations like scale/rotate
	mSprite.setOrigin(pSize.x/2, pSize.y/2);
}

AnimatedSprite::~AnimatedSprite(void)
{
}

//basic update method that extended classes should call if overriding
//because this will handle animation update
void AnimatedSprite::update()
{
	//move through Animation array if animating
	if(mIsAnimating)
	{
		mAnimations.at(mCurrentAnimation).animate();
	}
	//else set sprite to first in animation
	else
	{
		mAnimations.at(mCurrentAnimation).resetAnimation();
	}

	//move sprite by velocity
	mPosition += mVelocity;
	
}

//draw to window, don't see a point of overriding it
//takes in pointer to window and pInterpolation (which is a variable to guess where the sprite should be between updates)
void AnimatedSprite::draw(sf::RenderWindow *window, float pInterpolation)
{
	//set sprite position to position of the actual entity + interpolation
	//mSprite.setPosition(mPosition.x + (mVelocity.x * pInterpolation), mPosition.y + (mVelocity.y * pInterpolation)); 
	mSprite.setPosition(mPosition.x, mPosition.y);

	//only draw the certain sprite needed from the sprite sheet
	mSprite.setTextureRect(sf::IntRect(mAnimations[mCurrentAnimation].getCurrentFrame() * mSpriteSize.x, 
		mCurrentAnimation * mSpriteSize.y, 
		mSpriteSize.x, mSpriteSize.y));
	window->draw(mSprite);
}

//switch between animating and not animating
//this could've been one method but it would've been harder to tell if starting or stopping when using the object
void AnimatedSprite::startAnimation()
{
	mIsAnimating = true;
}

void AnimatedSprite::endAnimation()
{
	mIsAnimating = false;
}
