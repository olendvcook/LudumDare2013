#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(sf::Vector2f pPosition, sf::Vector2f pVelocity, float pAngle, float pAngularVelocity, int pTTL, float pSize, sf::Color pColor, DrawType pDrawType) :
	mPosition(pPosition),
	mVelocity(pVelocity),
	mAngle(pAngle),
	mAngularVelocity(pAngularVelocity),
	mTTL(pTTL),
	maxTTL(pTTL),
	mSize(pSize),
	mColor(pColor),
	mDrawType(pDrawType)
{
}

Particle::~Particle(void)
{
}

void Particle::Update()
{
	mColor.a = (255/maxTTL) * mTTL;
	mTTL--;
	mPosition += mVelocity;
	mAngle += mAngularVelocity;
}

void Particle::Draw(sf::RenderWindow* pWindow, float pInterpolation)
{
	if (mDrawType == eRANDOM) mDrawType = newDrawType();
		switch (mDrawType)
		{
		case(eRECTANGLE):
			DrawRectangles(pWindow, pInterpolation);
			break;
		case(eCIRCLE):
			DrawCircles(pWindow,  pInterpolation);
			break;		
		default:
			DrawCircles(pWindow,  pInterpolation, mDrawType);
			break;
		}
}

void Particle::DrawRectangles(sf::RenderWindow* pWindow, float pInterpolation)
{
	mRectangle.setPosition(mPosition + (mVelocity * pInterpolation));
	mRectangle.setSize(sf::Vector2f(mSize,mSize * 2));
	mRectangle.setFillColor(mColor);
	mRectangle.setRotation(mAngle);
	pWindow->draw(mRectangle);
}

void Particle::DrawCircles(sf::RenderWindow* pWindow, float pInterpolation, DrawType pDrawType)
{
	mCircle.setPosition(mPosition + (mVelocity * pInterpolation));
	mCircle.setRadius(mSize);
	mCircle.setPointCount(12);
	switch (pDrawType)
	{
		case(eTRIANGLE):
			mCircle.setPointCount(3);
			break;
		case(eSQUARE):
			mCircle.setPointCount(4);
			break;
		case(ePENTAGON):
			mCircle.setPointCount(5);
			break;
		case(eOCTAGON):
			mCircle.setPointCount(8);
			break;
		case(eCIRCLE):
			break;
		default:
			mCircle.setRadius(1);
	}
	mCircle.setFillColor(mColor);
	mCircle.setRotation(mAngle);
	pWindow->draw(mCircle);
}

void Particle::setPosition(sf::Vector2f pPosition)
{
	mPosition = pPosition;
}

sf::Vector2f Particle::getPosition()
{
	return mPosition;
}

void Particle::setVelocity(sf::Vector2f pVelocity)
{
	mVelocity = pVelocity;
}

void Particle::changeVelocity(sf::Vector2f pVelocity)
{
	mVelocity += pVelocity;
}

sf::Vector2f Particle::getVelocity()
{
	return mVelocity;
}

void Particle::setAngle( float pAngle)
{
	mAngle = pAngle;
}

float Particle::getAngle()
{
	return mAngle;
}

void Particle::setAnglularVelocity(float pAngVel)
{
	mAngularVelocity = pAngVel;
}

float Particle::getAngularVelocity()
{
	return mAngularVelocity;
}

void Particle::setColor(sf::Color pColor)
{
	mColor = pColor;
}

sf::Color Particle::getColor()
{
	return mColor;
}

void Particle::setSize(float pSize)
{
	mSize = pSize;
}

float Particle::getSize()
{
	return mSize;
}

void Particle::setTTL(int pTTL)
{
	mTTL = pTTL;
}

int Particle::getTTL()
{
	return mTTL;
}

void Particle::setDrawType(DrawType pDrawType)
{
	mDrawType = pDrawType;
}

DrawType Particle::getDrawType()
{
	return mDrawType;
}

float RandomFloat(float pA, float pB) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = pB - pA;
    float r = random * diff;
    return pA + r;
}

int RandomInt (int pA, int pB)
{
    return pA + (rand() % (int)(pB - pA + 1));
}

DrawType newDrawType()
{
	return (DrawType)RandomInt(0,7);	
}