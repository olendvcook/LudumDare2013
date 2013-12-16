#pragma once

#include <SFML/Graphics.hpp>

enum DrawType { ePOINT, eCIRCLE, eTRIANGLE, eSQUARE, eRECTANGLE, ePENTAGON, eOCTAGON, eRANDOM};

float RandomFloat(float pA, float pB);
int RandomInt (int pA, int pB);
DrawType newDrawType();

class Particle
{
private:

	sf::CircleShape mCircle;
	sf::RectangleShape mRectangle;

	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	float mAngle;
	float mAngularVelocity;
	sf::Color mColor;
	float mSize;
	//Time to Live
	int mTTL;
	int maxTTL;
	DrawType mDrawType;

	void DrawRectangles(sf::RenderWindow* pWindow,  float pInterpolation = 1.0);
	void DrawCircles(sf::RenderWindow* pWindow,  float pInterpolation = 1.0, DrawType pType = eCIRCLE);

public:

	Particle();
	Particle(sf::Vector2f pPosition, sf::Vector2f pVelocity, float pAngle, float pAngularVelocity, int pTTL, float pSize, sf::Color pColor = sf::Color::White, DrawType pDrawType = ePOINT);
	virtual ~Particle(void);
	void Update();
	void Draw(sf::RenderWindow* pWindow, float pInterpolation = 1.0);

	// getters/setters
	void setPosition(sf::Vector2f pPosition);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f pVelocity);
	void changeVelocity(sf::Vector2f pVelocity);
	sf::Vector2f getVelocity();
	void setAngle( float pAngle);
	float getAngle();
	void setAnglularVelocity(float pAngVel);
	float getAngularVelocity();
	void setColor(sf::Color pColor);
	sf::Color getColor();
	void setSize(float pSize);
	float getSize();
	void setTTL(int pTTL);
	int getTTL();
	void setDrawType(DrawType pDrawType);
	DrawType getDrawType();
};

