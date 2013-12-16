#pragma once
#include <SFML\Graphics.hpp>
#include "Includes.h"
#include "Textures.h"

enum HUDTYPE {hBATTERY, hHEALTH };
class Hud
{
private:
	Textures* mTextureHolder;
	sf::Sprite mOverlaySprite;
	sf::Sprite mHealthAmount;
	sf::Sprite mBatteryAmount;
	sf::Sprite mTriangleSprite;
public:
	Hud(Textures *pTextureHolder);
	virtual ~Hud(void);

	virtual void draw(sf::RenderWindow *window, int xPos, int yPos, HUDTYPE pHUDTYPE, int pHEALTHAMOUNT, int pBATTERYAMMOUNT);
};

