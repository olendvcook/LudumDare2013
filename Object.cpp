#include "Object.h"


Object::Object(sf::Vector2f pPosition, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture, 
		OBJECTTYPE pOBJECTTYPE,
		sf::Vector2f pVelocity, 
		float pAngle, 
		float pAngularVelocity):
	AnimatedSprite(pPosition, pVelocity, pSize, pTexture, pAngle, pAngularVelocity),
		mOBJECTTYPE(pOBJECTTYPE)
{
	mAnimations.insert(mAnimations.end(), Animation(2, 0.1, false));
	startAnimation();
}


Object::~Object(void)
{
}
