#include "Hud.h"


Hud::Hud(Textures *pTextureHolder):
	mTextureHolder(pTextureHolder)
{
	mOverlaySprite.setTexture(*mTextureHolder->getTexture(sHOLOGRAMBORDER));
	mOverlaySprite.setOrigin(22,22);
	mTriangleSprite.setTexture(*mTextureHolder->getTexture(sHOLOGRAMTRIANGLE));
	mTriangleSprite.setOrigin(22,22);
	mHealthAmount.setTexture(*mTextureHolder->getTexture(sHEALTHMETER));
	mHealthAmount.setOrigin(16,16);
	mBatteryAmount.setTexture(*mTextureHolder->getTexture(sBATTERYMETER));
	mBatteryAmount.setOrigin(16,16);
}


Hud::~Hud(void)
{
}

void Hud::draw(sf::RenderWindow *window, int xPos, int yPos, HUDTYPE pHUDTYPE, int pHEALTHAMOUNT, int pBATTERYAMMOUNT)
{
	mOverlaySprite.setPosition(static_cast<int>(xPos)+ 67, static_cast<int>(yPos));
	window->draw(mOverlaySprite);

	mTriangleSprite.setPosition(static_cast<int>(xPos)+22, static_cast<int>(yPos));
	window->draw(mTriangleSprite);

	switch(pHUDTYPE)
	{
	case hBATTERY:
		mBatteryAmount.setPosition(static_cast<int>(xPos)+67, static_cast<int>(yPos));
		mBatteryAmount.setTextureRect(sf::IntRect(pBATTERYAMMOUNT * 32, 0, 32, 32));
		window->draw(mBatteryAmount);
		break;
	case hHEALTH:
		mHealthAmount.setPosition(static_cast<int>(xPos)+67, static_cast<int>(yPos));
		mHealthAmount.setTextureRect(sf::IntRect((pHEALTHAMOUNT-1) * 32, 0, 32, 32));
		window->draw(mHealthAmount);
		break;
	}
}
