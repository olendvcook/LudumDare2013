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
	
}

void Game::reset()
{
	quit();
	mPlayer.setPosition(WindowWidth/2,WindowHeight -40);
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

	mView->setCenter(mPlayer.getPosition());

	if(mView->getCenter().x < mView->getSize().x/2)
	{
		mView->setCenter(mView->getSize().x/2, mView->getCenter().y);
	}
	if(mView->getCenter().y < mView->getSize().y/2)
	{
		mView->setCenter(mView->getCenter().x, mView->getSize().y/2);
	}
	if(mView->getCenter().x > 32 * 32 - mView->getSize().x/2)
	{
		mView->setCenter(32 * 32 - mView->getSize().x/2, mView->getCenter().y);
	}
	if(mView->getCenter().y > 32 * 32 - mView->getSize().y/2)
	{
		mView->setCenter(mView->getCenter().x, 32 * 32 - mView->getSize().y/2);
	}

	for(int i = 0; i < mMap.getCurrentRoom()->getEnemyAmount(); i++)
	{	

		//update enemy
		Enemy* tmpEnemyPtr = mMap.getCurrentRoom()->getEnemy(i);
		tmpEnemyPtr->update();

		//collision detection with player
		if(tmpEnemyPtr->getBounds().intersects(mPlayer.getBounds()))
		{
			if(mPlayer.getIsAttacking())
			{
				tmpEnemyPtr->setIsActive(false);
				continue;
			}
		}
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
}

//just call draw of all entities
//entities drawn first will be back layers
void Game::draw(sf::RenderWindow *window, float pInterpolation)
{
	window->setView(*mView);

	mMap.getCurrentRoom()->draw(window,pInterpolation);

	mPlayer.draw(window, pInterpolation);

	for(int i = 0; i < mMap.getCurrentRoom()->getEnemyAmount(); i++)
	{
		mMap.getCurrentRoom()->getEnemy(i)->draw(window, pInterpolation);
	}

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

