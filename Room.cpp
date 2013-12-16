#include "Room.h"


Room::Room(Textures *pTextureHolder,
		   const std::string& pTileset, 
		   sf::Vector2u pTileSize, 
		   int pBackground[], 
		   int pObjectLayer[], 
		   int pWidth, int pHeight):
	mTextureHolder(pTextureHolder),
	mRoomHeight(pHeight),
	mRoomWidth(pWidth),
	mTileSize(pTileSize)
{
	mBackground.load(pTileset,pTileSize,pBackground,pWidth,pHeight);
	generateObjects(pObjectLayer);
}


Room::~Room(void)
{
}

void Room::generateObjects(int pObjectLayer[])
{
	enum Objects {NONE, WALLS, ENEMY, BATTERY, ENGINE, ETC/*fill this out when we have all our objects*/};
	for(int i = 0; i < mRoomWidth; i++)
	{
		for(int j = 0; j < mRoomHeight; j++)
		{
			switch(pObjectLayer[mRoomWidth * j + i])
			{
			case(WALLS):
				//add da walls
				addWall(i * mTileSize.x + mTileSize.x/2, j * mTileSize.y + mTileSize.y/2);
				break;
			case(ENEMY):
				addEnemy(i * mTileSize.x + mTileSize.x/2, j * mTileSize.y + mTileSize.y/2);
				//add da enemy
				break;
			case(BATTERY):
				//add battery
				addObject(i * mTileSize.x + mTileSize.x/2, j * mTileSize.y + mTileSize.y/2, oBATTERY);
				break;
			case(ENGINE):
				addObject(i * mTileSize.x + mTileSize.x/2, j * mTileSize.y + mTileSize.y/2, oENGINE);
				break;
			case(NONE):
				//dont do anything
				break;
			}
		}
	}
}

void Room::draw(sf::RenderWindow *window, float pInterpolation)
{
	window->draw(mBackground);

	for(int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->draw(window, pInterpolation);
	}

	//TODO: foreach object draw object
}

void Room::addEnemy(float pXpos, float pYpos)
{
	//if no delete before removed u get memory leaks
	//if you ever call new you MUST call delete later
	mEnemies.insert(mEnemies.begin(), new Enemy(sf::Vector2f(pXpos, pYpos), sf::Vector2i(32,32), (mTextureHolder->getTexture(sZOMBIE))));
}

void Room::removeEnemy(int pIndex)
{
	//so delete :D
	delete(mEnemies.at(pIndex));
	mEnemies.erase((mEnemies.begin() + pIndex));
}

void Room::addWall(float pXpos, float pYpos)
{
	//create a wall then set its position
	mWalls.insert(mWalls.begin(), new sf::Sprite(*(mTextureHolder->getTexture(sWALL))));
	mWalls[0]->setOrigin(mTileSize.x/2,mTileSize.y/2);
	mWalls[0]->setPosition(pXpos,pYpos);
}

void Room::removeWall(int pIndex)
{
	delete(mWalls.at(pIndex));
	mWalls.erase((mWalls.begin() + pIndex));
}

//TODO: these methods when we have objects
void Room::addObject(float pXpos, float pYpos, OBJECTTYPE pOBJECTTYPE)
{
	switch(pOBJECTTYPE)
	{
		case oBATTERY:
			mObjects.insert(mObjects.begin(), new Object(sf::Vector2f(pXpos, pYpos), sf::Vector2i(32,32), (mTextureHolder->getTexture(sBATTERY)), oBATTERY));
			break;
		case oENGINE:
			mObjects.insert(mObjects.begin(), new Object(sf::Vector2f(pXpos, pYpos), sf::Vector2i(32,32), (mTextureHolder->getTexture(sENGINE)), oENGINE));
			break;
	}
}

void Room::removeObject(int pIndex)
{
	delete(mObjects.at(pIndex));
	mObjects.erase((mObjects.begin() + pIndex));
}
//---------------------------------------