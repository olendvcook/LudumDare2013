#pragma once
#include "Tilemap.h"
#include "Enemy.h"
#include "Textures.h"

//Hold the information for each room like tilemap background, enemies and objects, etc
class Room
{
private:

	Textures *mTextureHolder;

	TileMap mBackground;
	std::vector<sf::Sprite*> mWalls;
	std::vector<Enemy*> mEnemies;
	//stuff on the ground like batteries, collectables
	//std::vector<Objects*> mObjects;

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
	//Objects* getObject(int pIndex) {return mObjects[pIndex];}
	//int getObjectAmount() {return mObjects.size()}

	void draw(sf::RenderWindow *window, float pInterpolation);
	void addEnemy(float pXpos, float pYpos);
	void removeEnemy(int pIndex);
	void addObject(float pXpos, float pYpos);
	void removeObject(int pIndex);
	void addWall(float pXpos, float pYpos);
	void removeWall(int pIndex);
};

