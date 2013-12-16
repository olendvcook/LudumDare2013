#include "Game.h"

//takes in pointer to class that hold spritesheets so entities can be created with certain spritesheet
Game::Game(Textures *pTextureHolder,  sf::View * pView) :
	mTextureHolder(pTextureHolder),
	mPlayer(pTextureHolder, sf::Vector2f(50,50), sf::Vector2f(0,0), sf::Vector2i(32,32), (pTextureHolder->getTexture(sPLAYER))),
	mView(pView),
	mMap(pTextureHolder),
	particleEngine(sf::Vector2f(-300,300),500, sf::Color::Red)
{

	mLaserSoundBuffer.loadFromFile("Assets/Laser_Shoot.wav");
	mLaserSound.setBuffer(mLaserSoundBuffer);

	particleEngine.setSize(10);
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
	mPlayer.reset();
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

	particleEngine.Update(0, true);

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
	

	for(int i = 0; i < mLasers.size(); i++)
	{
		mLasers.at(i)->update();

		if(mLasers.at(i)->getPosition().x < 0)
		{
			removeLaser(i);
			continue;
		}
		else if(mLasers.at(i)->getPosition().y < 0)
		{
			removeLaser(i);
			continue;
		}
		else if(mLasers.at(i)->getPosition().y > mMap.getCurrentRoom()->getRoomHeight() * mMap.getCurrentRoom()->getTileSize().y)
		{
			removeLaser(i);
			continue;
		}
		else if(mLasers.at(i)->getPosition().y > mMap.getCurrentRoom()->getRoomWidth() * mMap.getCurrentRoom()->getTileSize().x)
		{
			removeLaser(i);
			continue;
		}

		for(int j = 0; j < mMap.getCurrentRoom()->getWallAmount(); j++)
		{
			if(mLasers.at(i)->getBounds().intersects(mMap.getCurrentRoom()->getWall(j)->getGlobalBounds()))
			{
				particleEngine.setEmitterLocation(mLasers.at(i)->getPosition());
				if(mLasers.at(i)->getVelocity().x > 0)
					particleEngine.Refill(30,pdLEFT);
				else if(mLasers.at(i)->getVelocity().x < 0)
					particleEngine.Refill(30,pdRIGHT);
				else if(mLasers.at(i)->getVelocity().y < 0)
					particleEngine.Refill(30,pdDOWN);
				else
					particleEngine.Refill(30);
				//TODO: particles
				removeLaser(i);
				break;
			}
		}

		for(int j = 0; j < mMap.getCurrentRoom()->getEnemyAmount(); j++)
		{
			if(mLasers.at(i)->getBounds().intersects(mMap.getCurrentRoom()->getEnemy(j)->getBounds()))
			{
				particleEngine.setEmitterLocation(mLasers.at(i)->getPosition());
				if(mLasers.at(i)->getVelocity().x > 0)
					particleEngine.Refill(30,pdLEFT);
				else if(mLasers.at(i)->getVelocity().x < 0)
					particleEngine.Refill(30,pdRIGHT);
				else if(mLasers.at(i)->getVelocity().y < 0)
					particleEngine.Refill(30,pdDOWN);
				else
					particleEngine.Refill(30);
				mMap.getCurrentRoom()->getEnemy(j)->setIsActive(false);
				//TODO: particles
				removeLaser(i);
				break;
			}
		}

	}



	for(int i = 0; i < mMap.getCurrentRoom()->getEnemyAmount(); i++)
	{	

		//update enemy
		Enemy* tmpEnemyPtr = mMap.getCurrentRoom()->getEnemy(i);

		if(tmpEnemyPtr->getIsActive())
		{
			//collision detection with player
			if(tmpEnemyPtr->getBounds().intersects(mPlayer.getBounds()))
			{
				mPlayer.setPlayerHealth(mPlayer.getPlayerHealth() - 1);
				tmpEnemyPtr->setIsActive(false);
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

	if(mPlayer.getPlayerHealth() <= 0)
	{
		mGameState = gGAMEOVER;
	}

	for(int i = 0; i < mMap.getCurrentRoom()->getObjectAmount(); i++)
	{
		Object* tmpObjectPtr = mMap.getCurrentRoom()->getObject(i);

		tmpObjectPtr->update();

		if(tmpObjectPtr->getBounds().intersects(mPlayer.getBounds()))
		{
			switch (tmpObjectPtr->getObjectType())
			{
			case oBATTERY:
				mPlayer.setBatteryLevel(mPlayer.getBatterLevel() + 2);
				if(mPlayer.getBatterLevel() > 5)
					mPlayer.setBatteryLevel(5);
				mMap.getCurrentRoom()->removeObject(i);
				break;
			case oENGINE:
				mGameState = gCOMPLETE;
				break;
			}
		}
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

	for(int i = 0; i < mMap.getCurrentRoom()->getObjectAmount(); i++)
	{
		mMap.getCurrentRoom()->getObject(i)->draw(window, pInterpolation);
	}

	mPlayer.draw(window, pInterpolation);

	for(int i = 0; i < mLasers.size(); i++)
	{
		mLasers.at(i)->draw(window, pInterpolation);
	}

	particleEngine.Draw(window,pInterpolation);


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
			//TODO: take out is attacking
			//TODO: player battery charge variable and deplete it
			if(mPlayer.getBatterLevel() > 0)
			{
			if(mPlayer.getPlayerState() == pUP)
				addLaser(mPlayer.getPosition().x,mPlayer.getPosition().y - mPlayer.getSize().y/2,0,-4);
			else if(mPlayer.getPlayerState() == pDOWN)
				addLaser(mPlayer.getPosition().x,mPlayer.getPosition().y + mPlayer.getSize().y/2,0,4);
			else if(mPlayer.getPlayerState() == pLEFT)
				addLaser(mPlayer.getPosition().x - mPlayer.getSize().x/2,mPlayer.getPosition().y,-4,0);
			else
				addLaser(mPlayer.getPosition().x + mPlayer.getSize().x/2,mPlayer.getPosition().y,4,0);
			mPlayer.setBatteryLevel(mPlayer.getBatterLevel() -1);
			mLaserSound.play();
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			mPlayer.setIsHealthDisplay(true);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			mPlayer.setIsBatteryDisplay(true);
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
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			mPlayer.setIsHealthDisplay(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			mPlayer.setIsBatteryDisplay(false);
		break;
	default:
		break;
	}
}

void Game::addLaser(float pX, float pY, float xVel, float yVel)
{
	mLasers.insert(mLasers.begin(), new Laser(sf::Vector2f(pX, pY), sf::Vector2f(xVel,yVel), sf::Vector2i(16,16), (mTextureHolder->getTexture(sLASER))));
}

void Game::removeLaser(int pIndex)
{
	delete(mLasers.at(pIndex));
	mLasers.erase((mLasers.begin() + pIndex));
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

