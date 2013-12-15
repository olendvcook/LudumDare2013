#include "Map.h"


Map::Map(Textures *pTextureHolder):
	mMapWidth(20),
	mMapHeight(20),
	mTextureHolder(pTextureHolder)
{
	Room* tmpRoomHolder[20*20];
	mRoomHolder = *tmpRoomHolder;
	setCurrentRoom(0,5);

}


Map::~Map(void)
{
}

void Map::setCurrentRoom (eExitDirection pDirection)
{
	switch(pDirection)
	{
	case(UP):
		mCurrentRoom = &mRoomHolder[mMapWidth * --mCurrentRoomYpos + mCurrentRoomXpos ];
		break;
	case(DOWN):
		mCurrentRoom = &mRoomHolder[mMapWidth * ++mCurrentRoomYpos + mCurrentRoomXpos];
		break;
	case(LEFT):
		mCurrentRoom = &mRoomHolder[mMapWidth * mCurrentRoomYpos + --mCurrentRoomXpos];
		break;
	case(RIGHT):
		mCurrentRoom = &mRoomHolder[mMapWidth * mCurrentRoomYpos + ++mCurrentRoomXpos];
		break;
	}
}

void Map::setCurrentRoom (int pXIndex, int pYIndex)
{
	mCurrentRoom = &mRoomHolder[mMapWidth * pYIndex + pXIndex];
}

void Map::generateMap(void)
{
	//this is a doozy
	int map[100]=
	{
		2,2,2,2,2,2,2,2,2,2,
		2,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,2,1,1,2,
		2,1,1,1,1,1,2,1,1,2,
		2,1,1,1,1,1,2,1,1,2,
		2,1,1,1,1,1,2,1,1,2,
		2,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,2,
		2,2,2,2,2,2,2,2,2,2
	};

	//c++ 1D version
int objects[100]=
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1
	};
	mRoomHolder[mMapWidth * 5 + 0] = *new Room(mTextureHolder, "Assets/tileset.png", sf::Vector2u(32,32), map, objects, 32, 32);
}

