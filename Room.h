#pragma once
#include "Tilemap.h"
#include "Enemy.h"
#include "Textures.h"
#include "Object.h"

//Hold the information for each room like tilemap background, enemies and objects, etc
class Room
{
private:

	Textures *mTextureHolder;

	TileMap mBackground;
	std::vector<sf::Sprite*> mWalls;
	std::vector<Enemy*> mEnemies;
	//stuff on the ground like batteries, collectables
	std::vector<Object*> mObjects;

	int mRoomWidth;
	int mRoomHeight;
	sf::Vector2u mTileSize;

	//populates the vectors based on object array
	void generateObjects(int pObjectLayer[]);

public:
	Room(Textures *pTextureHolder, const std::string& pTileset, sf::Vector2u pTileSize, int pBackground[], int pObjectLayer[], int pWidth, int pHeight);
	virtual ~Room(void);

	Enemy* getEnemy(int pIndex) {return mEnemies[pIndex];}
	int getEnemyAmount() {return mEnemies.size();}
	sf::Sprite* getWall(int pIndex) {return mWalls[pIndex];}
	int getWallAmount() {return mWalls.size();}
	Object* getObject(int pIndex) {return mObjects[pIndex];}
	int getObjectAmount() {return mObjects.size();}

	void draw(sf::RenderWindow *window, float pInterpolation);
	void addEnemy(float pXpos, float pYpos);
	void removeEnemy(int pIndex);
	void addObject(float pXpos, float pYpos, OBJECTTYPE pOBJECTTYPE);
	void removeObject(int pIndex);
	void addWall(float pXpos, float pYpos);
	void removeWall(int pIndex);
	int getRoomWidth() { return mRoomWidth; }
	int getRoomHeight() { return mRoomHeight; }
	sf::Vector2u getTileSize() { return mTileSize;}
};

