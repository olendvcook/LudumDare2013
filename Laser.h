#pragma once
#include "AnimatedSprite.h"

class Laser:
	public AnimatedSprite
{
protected:

public:
	Laser(sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		float pAngle = 0, 
		float pAngularVelocity = 0);
	virtual ~Laser(void);

};

