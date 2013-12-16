#pragma once
#include "animatedsprite.h"

//Example of extended Animated Sprite class to create simple enemies
//Should extend this for different types of enemies

//in this game ghost is implimented in enemy because ghost is so simple

//extends AnimatedSprite so it has all of AnimatedSprites vars and methods
class Enemy :
	public AnimatedSprite
{

protected:
	sf::Clock mClock;
	int counter;
	bool mIsActive;
public:
	Enemy(sf::Vector2f pPosition,  
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		sf::Vector2f pVelocity = sf::Vector2f(0,0),
		bool pIsActive = true,
		float pAngle = 0, 
		float pAngularVelocity = 0);
	virtual ~Enemy(void);

	//override animated sprite update method
	virtual void update(sf::Vector2f pPlayerPosition);

	virtual bool getIsActive() {return mIsActive;}
	virtual void setIsActive(bool pBool) { mIsActive = pBool; }

};

