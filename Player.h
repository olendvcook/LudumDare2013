#pragma once
#include "animatedsprite.h"
#include "Hud.h"
#include "Textures.h"

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
	bool isHealthDisplay;
	bool isBatteryDisplay;

	int mBatteryLevel;
	int mPlayerHealth;

	Hud mHud;

public:
	Player(void);
	Player(
		Textures* pTextureHolder,
		sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		float pAngle = 0, 
		float pAngularVelocity = 0);
	virtual ~Player(void);
	virtual void draw(sf::RenderWindow *window, float pInterpolation);
	void reset();
	void update();
	void setIsLeft(bool pParam) { isLeft = pParam; }
	void setIsRight(bool pParam) { isRight = pParam; }
	void setIsUp(bool pParam) { isUp = pParam; }
	void setIsDown(bool pParam) { isDown = pParam; }
	void setIsHealthDisplay(bool pParam) { isHealthDisplay = pParam; }
	void setIsBatteryDisplay(bool pParam) { isBatteryDisplay = pParam; }
	ePLAYERSTATE getPlayerState() { return mPLAYERSTATE; }
	int getBatterLevel() { return mBatteryLevel; }
	int getPlayerHealth() { return mPlayerHealth; }
	void setBatteryLevel(int pBatteryLevel) { mBatteryLevel = pBatteryLevel; }
	void setPlayerHealth(int pPlayerHealth) { mPlayerHealth = pPlayerHealth; }
};
