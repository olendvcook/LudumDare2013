#pragma once
#include "animatedsprite.h"

//Extended from AnimatedSprite, also contains player specific stuff for the player
//TODO: store Variable acceleration? should all sprites have acceleration?

enum ePLAYERSTATE { pUP, pDOWN, pLEFT, pRIGHT };


class Player :
	public AnimatedSprite
{
protected:
	ePLAYERSTATE mPLAYERSTATE;

	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isAttacking;

	int mBatteryLevel;
	int mPlayerHealth;

public:
	Player(void);
	Player(
		sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		float pAngle = 0, 
		float pAngularVelocity = 0);
	virtual ~Player(void);
	void reset();
	void update();
	void setIsLeft(bool pParam) { isLeft = pParam; }
	void setIsRight(bool pParam) { isRight = pParam; }
	void setIsUp(bool pParam) { isUp = pParam; }
	void setIsDown(bool pParam) { isDown = pParam; }
	void setIsAttacking(bool pParam) { isAttacking = pParam; }
	bool getIsAttacking() { return isAttacking; }
	ePLAYERSTATE getPlayerState() { return mPLAYERSTATE; }
	int getBatterLevel() { return mBatteryLevel; }
	int getPlayerHealth() { return mPlayerHealth; }
	void setBatteryLevel(int pBatteryLevel) { mBatteryLevel = pBatteryLevel; }
	void setPlayerHealth(int pPlayerHealth) { mPlayerHealth = pPlayerHealth; }
};
