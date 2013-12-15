#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Includes.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "Textures.h"
#include "Enemy.h"
#include "Tilemap.h"
#include "Map.h"

//Handles the gameplay state, holds its entities like enemies and player would hold score etc...
//Handles interaction between entities


//TODO: Gameplay states for easy seperate levels possibly, think about it more
class Game
{
private:
	//store entities
	Player mPlayer;
	Map mMap;

	//drawing stuff
	Textures *mTextures;
	sf::Sprite mBackground;
	sf::Font mFont;


	sf::View* mView;


	

public:

	Game(Textures *pTextureHolder, sf::View * pView);
	virtual ~Game(void);

	void update();
	void draw(sf::RenderWindow *window, float pInterpolation);
	void input(sf::Event *pEvent);

	//add and delete for each vector
	void addEnemy(float pX, float pY, float xVel, float yVel);
	void removeEnemy(int pIndex);
	void addGrave(float pX, float pY, float pReleaseTimeMin, float pReleaseTimeMax);
	void removeGrave(int pIndex);

	void nextlevel();
	void reset();
	void quit();

	//TODO: should probably have an init
	void init();
};

