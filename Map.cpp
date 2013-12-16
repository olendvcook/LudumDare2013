#include "Map.h"


Map::Map(Textures *pTextureHolder):
	mMapWidth(20),
	mMapHeight(20),
	mTextureHolder(pTextureHolder)
{
	generateMap();
	setCurrentRoom(0,5);
	mCurrentRoomXpos = 0;
	mCurrentRoomYpos = 5;

}


Map::~Map(void)
{
}

void Map::setCurrentRoom (eExitDirection pDirection)
{
	switch(pDirection)
	{
	case(UP):
		mCurrentRoom = mRoomHolder[mMapWidth * --mCurrentRoomYpos + mCurrentRoomXpos ];
		break;
	case(DOWN):
		mCurrentRoom = mRoomHolder[mMapWidth * ++mCurrentRoomYpos + mCurrentRoomXpos];
		break;
	case(LEFT):
		mCurrentRoom = mRoomHolder[mMapWidth * mCurrentRoomYpos + --mCurrentRoomXpos];
		break;
	case(RIGHT):
		mCurrentRoom = mRoomHolder[mMapWidth * mCurrentRoomYpos + ++mCurrentRoomXpos];
		break;
	}
}

void Map::setCurrentRoom (int pXIndex, int pYIndex)
{
	mCurrentRoom = mRoomHolder[mMapWidth * pYIndex + pXIndex];
}

void Map::generateMap(void)
{
	//c++ 1D version
	int map[100]=
	{2,2,2,2,2,2,2,2,2,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,2,1,1,2,
	2,1,1,1,1,1,2,1,1,1,
	2,1,1,1,1,1,2,1,1,1,
	2,1,1,1,1,1,2,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,2,2,2,2,2,2,2,2,2
	};

	//c++ 1D version
	int objects[100]=
	{1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,2,0,0,1,0,0,1,
	1,0,0,0,0,0,1,0,0,0,
	1,0,0,0,0,0,1,0,0,0,
	1,0,0,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1
	};

	//Width * Y + X
	mRoomHolder[mMapWidth * 5 + 0] = new Room(mTextureHolder, "Assets/tileset.png", sf::Vector2u(32,32), map, objects, 10, 10);

	//c++ 1D version
	int map1[100]=
	{2,2,2,2,1,1,2,2,2,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,2,2,2,1,1,2,2,2,2
	};

	//c++ 1D version
	int objects1[100]=
	{1,1,1,1,0,0,1,1,1,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,1,1,1,1
	};

	mRoomHolder[mMapWidth * 5 + 1] = new Room(mTextureHolder, "Assets/tileset.png", sf::Vector2u(32,32), map1, objects1, 10, 10);

	//c++ 1D version
	int map2[100]=
	{2,2,2,2,2,2,2,2,2,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	1,1,1,1,1,1,1,1,1,2,
	1,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,2,2,2,2,2,2,2,2,2
	};

	//c++ 1D version
	int objects2[100]=
	{1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1
	};

	mRoomHolder[mMapWidth * 5 + 2] = new Room(mTextureHolder, "Assets/tileset.png", sf::Vector2u(32,32), map2, objects2, 10, 10);

	//c++ 1D version
	int map3[100]=
	{2,2,2,2,1,1,2,2,2,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,2,2,2,2,2,2,2,2,2
	};

	//c++ 1D version
	int objects3[100]=
	{1,1,1,1,0,0,1,1,1,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1
	};

	mRoomHolder[mMapWidth * 6 + 1] = new Room(mTextureHolder, "Assets/tileset.png", sf::Vector2u(32,32), map3, objects3, 10, 10);

	//c++ 1D version
	int map4[100]=
	{2,2,2,2,2,2,2,2,2,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,1,1,1,1,1,1,1,1,2,
	2,2,2,2,1,1,2,2,2,2
	};

	//c++ 1D version
	int objects4[100]=
	{1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,1,1,1,1
	};

	mRoomHolder[mMapWidth * 4 + 1] = new Room(mTextureHolder, "Assets/tileset.png", sf::Vector2u(32,32), map4, objects4, 10, 10);
}

