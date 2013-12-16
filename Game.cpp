#include "Game.h"

//takes in pointer to class that hold spritesheets so entities can be created with certain spritesheet
Game::Game(Textures *pTextureHolder,  sf::View * pView) :
	mTextures(pTextureHolder),
	mPlayer(sf::Vector2f(50,50), sf::Vector2f(0,0), sf::Vector2i(32,32), (pTextureHolder->getTexture(sPLAYER))),
	mView(pView),
	mMap(pTextureHolder)
{
	//text example
	/*
	mFont.loadFromFile("Assets/galaxymonkey.ttf");
	mTextLives.setFont(mFont);
	mTextTown.setFont(mFont);
	mTextLives.setColor(sf::Color::White);
	mTextTown.setColor(sf::Color::White);
	mTextTown.setScale(0.6,0.6);
	mTextLives.setScale(0.6,0.6);
	mTextTown.setPosition(30, WindowHeight - 25);
	mTextLives.setPosition(WindowWidth - 100, WindowHeight - 25);
	*/

	mView->reset(sf::FloatRect(0,0,WindowWidth,WindowHeight));
	mView->zoom(0.5f);
	mView->setCenter(mPlayer.getPosition());
}

void Game::reset()
{
	quit();
	mPlayer.setPosition(50,50);
	mPlayer.setIsLeft(false);
	mPlayer.setIsRight(false);
	mPlayer.setIsUp(false);
	mPlayer.setIsDown(false);
	mPlayer.setIsAttacking(false);
}

Game::~Game(void)
{
}

//update method used during game state
//TODO: think of a way to make Game update not so beastly and hacky, maybe some kind of event system

//Everything from update can be taken out / very specific to your game
//left in as example
void Game::update()
{


	//move view to follow player unless view would expose past the room, then stop moving to player
	mView->setCenter(static_cast<int>(mPlayer.getOldPosition().x),static_cast<int>(mPlayer.getOldPosition().y));

	if(mView->getCenter().x < mView->getSize().x/2)
	{
		mView->setCenter(static_cast<int>(mView->getSize().x/2), static_cast<int>(mView->getCenter().y));
	}
	else if(mView->getCenter().x > mMap.getCurrentRoom()->getRoomWidth() * mMap.getCurrentRoom()->getTileSize().x - mView->getSize().x/2)
	{
		mView->setCenter(static_cast<int>(mMap.getCurrentRoom()->getRoomWidth() * mMap.getCurrentRoom()->getTileSize().x - mView->getSize().x/2), static_cast<int>(mView->getCenter().y));
	}
	if(mView->getCenter().y < mView->getSize().y/2)
	{
		mView->setCenter(static_cast<int>(mView->getCenter().x), static_cast<int>(mView->getSize().y/2));
	}
	else if(mView->getCenter().y > mMap.getCurrentRoom()->getRoomHeight() * mMap.getCurrentRoom()->getTileSize().y - mView->getSize().y/2)
	{
		mView->setCenter(static_cast<int>(mView->getCenter().x), static_cast<int>(mMap.getCurrentRoom()->getRoomHeight() * mMap.getCurrentRoom()->getTileSize().y - mView->getSize().y/2));
	}
	

	for(int i = 0; i < mMap.getCurrentRoom()->getEnemyAmount(); i++)
	{	

		//update enemy
		Enemy* tmpEnemyPtr = mMap.getCurrentRoom()->getEnemy(i);

		//collision detection with player
		if(tmpEnemyPtr->getBounds().intersects(mPlayer.getBounds()))
		{
			if(mPlayer.getIsAttacking())
			{
				tmpEnemyPtr->setIsActive(false);
				continue;
			}
		}
		//TODO ENEMIES COLLIDING
		
		for(int j = 0; j < mMap.getCurrentRoom()->getEnemyAmount(); j++)
		{
			if(j==i) continue;
			if(tmpEnemyPtr->getBounds().intersects(mMap.getCurrentRoom()->getEnemy(j)->getBounds()))
			{
				tmpEnemyPtr->revertPosition();
				tmpEnemyPtr->setVelocity(-tmpEnemyPtr->getVelocity().x,-tmpEnemyPtr->getVelocity().y);
				mMap.getCurrentRoom()->getEnemy(j)->revertPosition();
				//mMap.getCurrentRoom()->getEnemy(j)->setVelocity(0,0);
				mMap.getCurrentRoom()->getEnemy(j)->setVelocity(-mMap.getCurrentRoom()->getEnemy(j)->getVelocity().x,-mMap.getCurrentRoom()->getEnemy(j)->getVelocity().y);
			}
		}
		

		for(int i = 0; i < mMap.getCurrentRoom()->getWallAmount(); i++)
		{
			sf::Sprite* tmpWallPtr = mMap.getCurrentRoom()->getWall(i);

			if(tmpWallPtr->getGlobalBounds().intersects(tmpEnemyPtr->getBounds()))
			{
				tmpEnemyPtr->revertPosition();
			}
		}

		tmpEnemyPtr->update(mPlayer.getPosition());
	}

	for(int i = 0; i < mMap.getCurrentRoom()->getWallAmount(); i++)
	{
		sf::Sprite* tmpWallPtr = mMap.getCurrentRoom()->getWall(i);

		if(tmpWallPtr->getGlobalBounds().intersects(mPlayer.getBounds()))
		{
			mPlayer.revertPosition();
		}
	}

	mPlayer.update();


	//check for room switch
	if(mPlayer.getPosition().x < 0)
	{
		mMap.setCurrentRoom(LEFT);
		mPlayer.setPosition((mMap.getCurrentRoom()->getRoomWidth() * mMap.getCurrentRoom()->getTileSize().x) - mPlayer.getSize().x/2, mPlayer.getPosition().y);
	}
	else if (mPlayer.getPosition().y < 0)
	{
		mMap.setCurrentRoom(UP);
		mPlayer.setPosition(mPlayer.getPosition().x, (mMap.getCurrentRoom()->getRoomHeight() * mMap.getCurrentRoom()->getTileSize().y) - mPlayer.getSize().y/2);
	}
	else if (mPlayer.getPosition().x > (mMap.getCurrentRoom()->getRoomWidth() * mMap.getCurrentRoom()->getTileSize().x))
	{
		mMap.setCurrentRoom(RIGHT);
		mPlayer.setPosition(mPlayer.getSize().x/2, mPlayer.getPosition().y);
	}
	else if (mPlayer.getPosition().y > (mMap.getCurrentRoom()->getRoomHeight() * mMap.getCurrentRoom()->getTileSize().y))
	{
		mMap.setCurrentRoom(DOWN);
		mPlayer.setPosition(mPlayer.getPosition().x, mPlayer.getSize().y/2);
	}

}

//just call draw of all entities
//entities drawn first will be back layers
void Game::draw(sf::RenderWindow *window, float pInterpolation)
{
	window->setView(*mView);

	mMap.getCurrentRoom()->draw(window,pInterpolation);

	for(int i = 0; i < mMap.getCurrentRoom()->getEnemyAmount(); i++)
	{
		mMap.getCurrentRoom()->getEnemy(i)->draw(window, pInterpolation);
	}

	mPlayer.draw(window, pInterpolation);

}

//get passed the input events do stuff based on event type
void Game::input(sf::Event *pEvent)
{
	switch(pEvent->type)
	{
	//change state of player based on what key is pressed
	case(sf::Event::KeyPressed):
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mPlayer.setIsLeft(true);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mPlayer.setIsRight(true);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mPlayer.setIsDown(true);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mPlayer.setIsUp(true);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			mGameState = gPAUSED;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			mPlayer.setIsAttacking(true);
		}
		break;
	case(sf::Event::KeyReleased):
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mPlayer.setIsLeft(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mPlayer.setIsRight(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mPlayer.setIsDown(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			mPlayer.setIsUp(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			mPlayer.setIsAttacking(false);
		break;
	default:
		break;
	}
}

//handle memory leaks before quitting

void Game::quit()
{
	/*
	//we go down because when we remove from front, everything shifts down
	for(int i = mEnemies.size() - 1; i >= 0; i--)
	{
		removeEnemy(i);
	}
	*/
}

