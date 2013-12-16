#include "Laser.h"


Laser::Laser(sf::Vector2f pPosition, 
		sf::Vector2f pVelocity, 
		sf::Vector2i pSize, 
		sf::Texture *pTexture,  
		float pAngle, 
		float pAngularVelocity) :
	AnimatedSprite(pPosition, pVelocity, pSize, pTexture, pAngle, pAngularVelocity)
{
	mAnimations.insert(mAnimations.end(), Animation(2, 0.1, false));
	startAnimation();

	if(mVelocity.x != 0)
		mSprite.rotate(90);
}


Laser::~Laser(void)
{
}
