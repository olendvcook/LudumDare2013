#pragma once
#include "AnimatedSprite.h"

enum OBJECTTYPE { oBATTERY, oENGINE };

class Object :
	public AnimatedSprite
{
private:
	OBJECTTYPE mOBJECTTYPE;
public:
	Object(sf::Vector2f pPosition, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		OBJECTTYPE pOBJECTTYPE,
		sf::Vector2f pVelocity = sf::Vector2f(0,0),
		float pAngle = 0, 
		float pAngularVelocity = 0);
	virtual ~Object(void);

	OBJECTTYPE getObjectType() { return mOBJECTTYPE;}
};

