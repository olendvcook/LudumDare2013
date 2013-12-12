#include "Game.h"

//takes in pointer to class that hold spritesheets so entities can be created with certain spritesheet
Game::Game(Textures *pSpriteSheet,  sf::View * pView) :
	mTextures(pSpriteSheet),
	mPlayer(sf::Vector2f(WindowWidth/2,WindowHeight/2), sf::Vector2f(0,0), sf::Vector2i(16,16), (pSpriteSheet->getTexture(sPLAYER))),
	mNumofLives(3),
	mCurrentLevel(0),
	mMaxLevel(9),
	mView(pView)
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


	int level[] =
    {
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,447,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,447,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,447,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,447,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,447,1,1,1,1,1,1,1,1,2,
		2,1,1,443,443,1,1,1,1,447,1,1,1,1,1,1,1,447,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,447,447,1,1,1,2,
		2,1,1,1,1,1,1,1,1,443,1,1,1,1,1,1,1,1,447,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,443,1,1,1,1,1,1,1,447,1,1,1,443,1,1,1,1,1,443,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
    };

	tilemap.load("Assets/tileset.png", sf::Vector2u(32,32), level, 32, 32);
	
	addEnemy(320,100, 3, 3);
	addEnemy(440,100, 3, -3);
	addEnemy(200,100, 1, 5);
	addEnemy(80,100, -5, 1);
	addEnemy(560,100, 2, 4);
	addEnemy(320,200, 4, 2);
	addEnemy(440,200, -2, 6);
	addEnemy(200,200, 5, 3);
	addEnemy(80,200, 1, 3);
	addEnemy(560,200, -3, 1);
	addEnemy(320,300, -3, -3);
	addEnemy(440,300, -2, 2);
	addEnemy(200,300, 2, -2);
	addEnemy(80,300, 2, 5);
	addEnemy(560,300, 5, 2);
	
}

void Game::reset()
{
	mCurrentLevel = 0;
	mNumofLives = 3;
	quit();
	mPlayer.setPosition(WindowWidth/2,WindowHeight -40);
	mPlayer.setIsLeft(false);
	mPlayer.setIsRight(false);
	mPlayer.setIsUp(false);
	mPlayer.setIsDown(false);
	mPlayer.setIsAttacking(false);

	addEnemy(320,100, 3, 3);
	addEnemy(440,100, 3, -3);
	addEnemy(200,100, 1, 5);
	addEnemy(80,100, -5, 1);
	addEnemy(560,100, 2, 4);
	addEnemy(320,200, 4, 2);
	addEnemy(440,200, -2, 6);
	addEnemy(200,200, 5, 3);
	addEnemy(80,200, 1, 3);
	addEnemy(560,200, -3, 1);
	addEnemy(320,300, -3, -3);
	addEnemy(440,300, -2, 2);
	addEnemy(200,300, 2, -2);
	addEnemy(80,300, 2, 5);
	addEnemy(560,300, 5, 2);
}

Game::~Game(void)
{
}

//would have add and remove for each vector of entities
void Game::addEnemy(float pX, float pY, float xVel, float yVel)
{
	//if no delete before removed u get memory leaks
	//if you ever call new you MUST call delete later
	mEnemies.insert(mEnemies.begin(), new Enemy(sf::Vector2f(pX, pY), sf::Vector2f(xVel,yVel), sf::Vector2i(32,32), (mTextures->getTexture(sGHOST))));
}

void Game::removeEnemy(int pIndex)
{
	//so delete :D
	delete(mEnemies.at(pIndex));
	mEnemies.erase((mEnemies.begin() + pIndex));
}

//update method used during game state
//TODO: think of a way to make Game update not so beastly and hacky, maybe some kind of event system

//Everything from update can be taken out / very specific to your game
//left in as example
void Game::update()
{

	mPlayer.update();

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

	for(int i = 0; i < mEnemies.size(); i++)
	{	

		//update enemy
		mEnemies[i]->update();

		//collision detection with player
		if(mEnemies[i]->getBounds().intersects(mPlayer.getBounds()))
		{
			if(mPlayer.getIsAttacking())
			{
				removeEnemy(i);
				continue;
			}
		}
	}

	//if no more enemies
	
	if(mEnemies.size() <= 0)
	{
		mView->reset(sf::FloatRect(0,0,WindowWidth,WindowHeight));
		mGameState = gCOMPLETE;
	}
	
}

//just call draw of all entities
//entities drawn first will be back layers
void Game::draw(sf::RenderWindow *window, float pInterpolation)
{
	window->setView(*mView);

	window->draw(tilemap);
	window->draw(mTextLives);
	window->draw(mTextTown);

	mPlayer.draw(window, pInterpolation);

	for(int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->draw(window, pInterpolation);
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
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mPlayer.setIsLeft(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			mPlayer.setIsRight(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mPlayer.setIsDown(false);
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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
	//we go down because when we remove from front, everything shifts down
	for(int i = mEnemies.size() - 1; i >= 0; i--)
	{
		removeEnemy(i);
	}
}
