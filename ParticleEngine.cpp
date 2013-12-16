#include "ParticleEngine.h"

ParticleEngine::ParticleEngine(sf::Vector2f pLocation, int pCount, sf::Color pColor) :
	mEmitterLocation(pLocation),
	mParticles(pCount),
	mColor(pColor)
{
	srand ((unsigned int) time(NULL));
	Refill(pCount);
}

ParticleEngine::~ParticleEngine(void)
{
}

void ParticleEngine::Refill(int pCount, PARTICLEDIRECTION pPARTICLEDIRECTION)
{
	mParticles.resize(pCount);
	for(int i = 0; i < mParticles.size(); i++)
	{
		//float xMin = -2, float xMax = 2, 
		//float yMin = -5, float yMax = -2, 
		switch (pPARTICLEDIRECTION)
		{
		case pdUP:
			mParticles[i] = GenerateNewParticle();
			break;
		case pdLEFT:
			mParticles[i] = GenerateNewParticle(-5, -2, -2, 2);
			break;
		case pdDOWN:
			mParticles[i] = GenerateNewParticle(-2,2,2,5);
			break;
		case pdRIGHT:
			mParticles[i] = GenerateNewParticle(2,5,-2,2);
			break;
		default:
			break;
		}
	}
}

void ParticleEngine::Clear()
{
	mParticles.clear();
}

Particle ParticleEngine::GenerateNewParticle(float xMin, float xMax, 
											 float yMin, float yMax, 
											 float TTLmin, float TTLmax, 
											 int sizeMin, int sizeMax, float pAngle,
											 float pAngularvelocity, DrawType pDrawType)
{
	sf::Vector2f position = mEmitterLocation;
	sf::Vector2f velocity(RandomFloat(xMin,xMax),RandomFloat(yMin,yMax));
	float angle = pAngle;
	float angularVelocity;
	if (pAngularvelocity = -99) angularVelocity = RandomFloat(-1,1);
	else angularVelocity = pAngularvelocity;
	sf::Color tmpColor;
	if(mColor == sf::Color::Black)
	{
		tmpColor = sf::Color(RandomInt(0,255),
								RandomInt(0,255),
								RandomInt(0,255));
	}
	else tmpColor = mColor;

	int size = RandomInt(sizeMin,sizeMax);
	int ttl = RandomInt(TTLmin,TTLmax);

	return Particle(position, velocity, angle, angularVelocity, ttl, size, tmpColor, pDrawType);
}

void ParticleEngine::Update(float gravity, bool kill)
{
	std::vector<Particle>::iterator it = mParticles.begin();

	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].Update();
		mParticles[i].changeVelocity(sf::Vector2f(0,gravity));
		if (mParticles[i].getTTL() <= 0)
		{
			if (kill) 
			{
				mParticles.erase(mParticles.begin() + i);
			}
			else
			{
				mParticles[i] = GenerateNewParticle();
			}
		}
	}
}

void ParticleEngine::Draw(sf::RenderWindow* window, float pInterpolation)
{ 
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].Draw(window, pInterpolation);
	}
}

void ParticleEngine::setColor(sf::Color pColor)
{
	mColor = pColor;
}

sf::Color ParticleEngine::getColor()
{
	return mColor;
}

void ParticleEngine::setEmitterLocation(sf::Vector2f pPosition)
{
	mEmitterLocation = pPosition;
}

sf::Vector2f ParticleEngine::getEmitterLocation()
{
	return mEmitterLocation;
}

void ParticleEngine::setPosition(sf::Vector2f pPosition)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setPosition(pPosition);
	}
}

void ParticleEngine::setVelocity(sf::Vector2f pVelocity)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setVelocity(pVelocity);
	}
}

void ParticleEngine::changeVelocity(sf::Vector2f pVelocity)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].changeVelocity(pVelocity);
	}
}

void ParticleEngine::setAngle( float pAngle)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setAngle(pAngle);
	}
}

void ParticleEngine::setAnglularVelocity(float pAngVel)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setAnglularVelocity(pAngVel);
	}
}

void ParticleEngine::setSize(float pSize)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setSize(pSize);
	}
}

void ParticleEngine::setTTL(int pTTL)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setTTL(pTTL);
	}
}

void ParticleEngine::setDrawType(DrawType pDrawType)
{
	for(int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i].setDrawType(pDrawType);
	}
}