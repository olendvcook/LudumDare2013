#pragma once

#include "Animation.h"
#include <SFML\Graphics.hpp>
#include "Includes.h"

//A Entity that holds arrays of animation to display an animated sprite using a sprite sheet
//Has basic entity stuff like position, size, velocity
//Designed to be extended by more specific entities like Player/Enemy
class AnimatedSprite
{
protected:
	sf::Vector2f mPosition;
	sf::Vector2f mOldPosition;
	sf::Vector2f mVelocity;
	//for rotation
	float mAngle;
	float mAngularVelocity;
	//Sprite that hold and displays the texture
	sf::Sprite mSprite;
	//SpriteSize is used to determine size of the sprite on each spritesheet
	//size should be scaled with the sprite for collision stuff/ actual ingame size
	sf::Vector2i mSize;
	sf::Vector2i mSpriteSize;


	//store which array of animation is currently being used
	int mCurrentAnimation;
	
	bool mIsAnimating;


	//array of class Animation to store all the different Animations like Idle/Walk/Jump
	std::vector<Animation> mAnimations;

public:
	AnimatedSprite(
		sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		float pAngle = 0, 
		float pAngularVelocity = 0);

	virtual ~AnimatedSprite(void);

	virtual void startAnimation();
	virtual void endAnimation();
	virtual void update();
	virtual void draw(sf::RenderWindow *window, float pInterpolation);

	//getters and setters

	//change what the current animation is like idle/jump/walk
	virtual void setCurrentAnimation(int pRow) { mCurrentAnimation = pRow; }
	//get bounds in global space for use in collision detection
	virtual sf::FloatRect getBounds() { return mSprite.getGlobalBounds(); }

	virtual sf::Vector2f getPosition() { return mPosition; }
	virtual sf::Vector2i getSize() { return mSize; }
	virtual sf::Vector2f getVelocity() { return mVelocity; }
	virtual void setVelocity(float pX, float pY) { mVelocity = sf::Vector2f(pX,pY); };
	virtual void setVelocity(sf::Vector2f pVelocity) { mVelocity = pVelocity; };
	virtual void setPosition(float pX, float pY) { mPosition = sf::Vector2f(pX,pY); };
	virtual void setPosition(sf::Vector2f pPosition) { mPosition = pPosition; };
	virtual void revertPosition() { mPosition = mOldPosition; }
	virtual sf::Vector2f getOldPosition() { return mOldPosition; }
};
