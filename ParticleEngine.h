#pragma once

#include "Particle.h"

enum PARTICLEDIRECTION { pdUP, pdLEFT, pdDOWN, pdRIGHT};


class ParticleEngine
{
public:



	ParticleEngine(sf::Vector2f pLocation, int pCount, sf::Color pColor = sf::Color::Black);
	~ParticleEngine(void);
	void Update(float gravity = 0, bool kill = false);
	void Draw(sf::RenderWindow* window, float pInterpolation = 1.0);
	void Refill(int pCount, PARTICLEDIRECTION pPARTICLEDIRECTION = pdUP);
	void Clear();

	//getters/setters
	void setColor(sf::Color pColor);
	sf::Color getColor();
	void setEmitterLocation(sf::Vector2f pPosition);
	sf::Vector2f getEmitterLocation();

	//Particle setters
	void setPosition(sf::Vector2f pPosition);
	void setVelocity(sf::Vector2f pVelocity);
	void changeVelocity(sf::Vector2f pVelocity);
	void setAngle( float pAngle);
	void setAnglularVelocity(float pAngVel);
	void setSize(float pSize);
	void setTTL(int pTTL);
	void setDrawType(DrawType pDrawType);

private:

	sf::Color mColor;
	sf::Vector2f mEmitterLocation;
	std::vector<Particle> mParticles;

	Particle GenerateNewParticle(float xMin = -2, float xMax = 2, 
											 float yMin = -5, float yMax = -2, 
											 float TTLmin = 20, float TTLmax = 70, 
											 int sizeMin = 1, int sizeMax = 5, float pAngle = 0,
											 float pAngularvelocity = -99, DrawType pDrawType = ePOINT);
};

