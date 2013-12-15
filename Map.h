#pragma once
#include "Room.h"
#include "Textures.h"

enum eExitDirection { UP, DOWN, LEFT, RIGHT};

class Map
{
private:
	Textures *mTextureHolder;
	//array of rooms
	Room* mRoomHolder;
	//pointer to current room
	Room* mCurrentRoom;
	int mCurrentRoomXpos;
	int mCurrentRoomYpos;

	const int mMapWidth;
	const int mMapHeight;
public:
	Map (Textures *pTextureHolder);
	virtual ~Map (void);

	Room * getCurrentRoom (void) {return mCurrentRoom;}

	void setCurrentRoom (eExitDirection pDirection);
	void setCurrentRoom (int pXIndex, int pYIndex);

	void draw(sf::RenderWindow *window, float pInterpolation);

	void generateMap(void);

};

