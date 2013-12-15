#include "Room.h"


Room::Room(Textures *pTextureHolder,
		   const std::string& pTileset, 
		   sf::Vector2u pTileSize, 
		   int pBackground[], 
		   int pObjectLayer[], 
		   int pWidth, int pHeight):
	mTextureHolder(pTextureHolder),
	mRoomHeight(pHeight),
	mRoomWidth(pWidth)
{
	mBackground.load(pTileset,pTileSize,pBackground,pWidth,pHeight);
	generateObjects(pObjectLayer);
}


Room::~Room(void)
{
}

void Room::generateObjects(int pObjectLayer[])
{
}

void Room::update()
{
}

void Room::draw(sf::RenderWindow *window, float pInterpolation)
{
}

void Room::addEnemy(float pXpos, float pYpos)
{
	//if no delete before removed u get memory leaks
	//if you ever call new you MUST call delete later
	mEnemies.insert(mEnemies.begin(), new Enemy(sf::Vector2f(pXpos, pYpos), sf::Vector2i(32,32), (mTextureHolder->getTexture(sGHOST))));
}

void Room::removeEnemy(int pIndex)
{
}

void Room::removeObject(int pIndex)
{
}
