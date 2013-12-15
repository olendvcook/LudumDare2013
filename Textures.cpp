#include "Textures.h"

//load all texture and insert into a vector
Textures::Textures(void)
{
	//TODO: not hardcode how texture is loaded
	sf::Texture texture1;

	//load textures here in order of the enums
	//example:
	/*
	texture1.loadFromFile("Assets/buttonSheet.png");
	mSheets.insert(mSheets.end(), texture1);
	*/

	texture1.loadFromFile("Assets/buttonSheet.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/playerSheet.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/background.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/gameover.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/ghostsheet.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/gametile.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/paused.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/complete.png");
	mSheets.insert(mSheets.end(), texture1);

	texture1.loadFromFile("Assets/wall.png");
	mSheets.insert(mSheets.end(), texture1);
	
}

Textures::~Textures(void)
{
}

sf::Texture* Textures::getTexture(SPRITESHEETS pSheet)
{
	return &(mSheets.at(pSheet));
}