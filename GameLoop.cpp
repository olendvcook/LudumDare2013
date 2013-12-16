#include "GameLoop.h"
#include <iostream>

//just call gameloop
GameLoop::GameLoop(void) :
	mTextureHolder()
{

	loop();
}


GameLoop::~GameLoop(void) 
{
}

void GameLoop::loop()
{
<<<<<<< HEAD
=======
	mWindow.setVerticalSyncEnabled(true);
	mMusic.openFromFile("Assets/song.wav");
	mMusic.setVolume(25);
	mMusic.setLoop(true);
	mMusic.play();

>>>>>>> origin/master
	mGameState = gMENU;
	//Initialize variables to regulate update speed
	sf::Clock clock;
	int nextGameTick = clock.getElapsedTime().asMilliseconds();
	int loops;
	float interpolation;
	//--------------------------------------------
	//create window
	mWindow.create(sf::VideoMode(WindowWidth, WindowHeight), "Rad Robot versus The Space Mutants - VW - 0.1");

	mView.reset(sf::FloatRect(0,0,WindowWidth,WindowHeight));

	ltbl::LightSystem ls(AABB(Vec2f(0.0f, 0.0f), Vec2f(static_cast<float>(WindowWidth), static_cast<float>(WindowHeight))), &mWindow, "data/lightFin.png", "data/shaders/lightAttenuationShader.frag");
	
	ltbl::Light_Point* dLight = new ltbl::Light_Point();
	dLight->m_radius = static_cast<float>(WindowWidth);
    dLight->m_size = 12.5f;
	dLight->m_intensity = 1.5f;
	dLight->m_spreadAngle = 2.0f * M_PI;
	dLight->m_bleed = 0.0f;
	dLight->m_linearizeFactor = 0.2f;

    dLight->CalculateAABB();

    ls.AddLight(dLight);

	ltbl::ConvexHull * testHull = new ltbl::ConvexHull();

	if(!testHull->LoadShape("data/testShape.txt"))
		abort();

	testHull->m_renderLightOverHull = false;

	testHull->CalculateNormals();
	testHull->CalculateAABB();

	testHull->SetWorldCenter(Vec2f(208.0f, WindowHeight - 160.0f));

	ls.AddConvexHull(testHull);

	ltbl::ConvexHull * testHull2 = new ltbl::ConvexHull();

	if(!testHull2->LoadShape("data/wallOne.txt"))
		abort();

	testHull2->m_renderLightOverHull = false;

	testHull2->CalculateNormals();
	testHull2->CalculateAABB();

	testHull2->SetWorldCenter(Vec2f(16.0f, WindowHeight - 160.0f));

	ls.AddConvexHull(testHull2);

	ltbl::ConvexHull * testHull3 = new ltbl::ConvexHull();

	if(!testHull3->LoadShape("data/wallTwo.txt"))
		abort();

	testHull3->m_renderLightOverHull = false;

	testHull3->CalculateNormals();
	testHull3->CalculateAABB();

	testHull3->SetWorldCenter(Vec2f(170.0f, WindowHeight - 16.0f));

	ls.AddConvexHull(testHull3);

	ltbl::ConvexHull * testHull4 = new ltbl::ConvexHull();

	if(!testHull4->LoadShape("data/wallThree.txt"))
		abort();

	testHull4->m_renderLightOverHull = false;

	testHull4->CalculateNormals();
	testHull4->CalculateAABB();

	testHull4->SetWorldCenter(Vec2f(304.0f, WindowHeight - 80.0f));

	ls.AddConvexHull(testHull4);

	ltbl::ConvexHull * testHull5 = new ltbl::ConvexHull();

	if(!testHull5->LoadShape("data/wallTwo.txt"))
		abort();

	testHull5->m_renderLightOverHull = false;

	testHull5->CalculateNormals();
	testHull5->CalculateAABB();

	testHull5->SetWorldCenter(Vec2f(170.0f, WindowHeight - 304.0f));

	ls.AddConvexHull(testHull5);

	ltbl::ConvexHull * testHull6 = new ltbl::ConvexHull();

	if(!testHull6->LoadShape("data/wallThree.txt"))
		abort();

	testHull6->m_renderLightOverHull = false;

	testHull6->CalculateNormals();
	testHull6->CalculateAABB();

	testHull6->SetWorldCenter(Vec2f(304.0f, WindowHeight - 240.0f));

	ls.AddConvexHull(testHull6);

	//create container classes
	Menu mMenu(&mTextureHolder);
	Game mGame(&mTextureHolder, &mView);

	gameOver.setScale(0.5,0.5);

	mWindow.setKeyRepeatEnabled(false);

	//game loop
	while (mWindow.isOpen())
	{
		loops = 0;
		mWindow.clear();

		sf::Event event;

		mWindow.setView(mView);
		
		dLight->TreeUpdate();

		mWindow.setView(mWindow.getDefaultView());
		ls.SetView(mWindow.getDefaultView());

		//controls update speed
		while (clock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			//updates Here
			switch(mGameState)
			{
			case(gMENU):
				mMenu.update();
				break;
			case(gGAME):
				mGame.update(&ls, dLight);
				ls.RenderLights();
				break;
			case(gGAMEOVER):
				break;
			case(gPAUSED):
			default:
				break;
			}

			nextGameTick += SKIP_TICKS;
			loops++;
		}
		

		//Input Here
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mGame.quit();
				mWindow.close();
			}
			if (event.type == sf::Event::LostFocus || event.type == sf::Event::MouseLeft)
			{
				if(mGameState == gGAME)
					mGameState = gPAUSED;
			}

			switch(mGameState)
			{
			case(gMENU):
				mMenu.input(&event, &mWindow);
				break;
			case(gGAME):
				mGame.input(&event);
				break;
			case(gCOMPLETE):
			case(gGAMEOVER):
				mGame.reset();
				if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					mGameState = gMENU;
				break;
			case(gPAUSED):
				if(event.type == sf::Event::KeyPressed)
					mGameState = gGAME;
				break;
			default:
				break;
			}
		}

		//calculate interpolation to (try to) smooth rendering between update
		interpolation = float(clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - nextGameTick)
			/ float(SKIP_TICKS);

		//mWindow.setView(mView);
		gameOver.setPosition(mView.getCenter().x - mView.getSize().x/2, mView.getCenter().y - mView.getSize().y/2);

		switch(mGameState)
		{
		case(gMENU):
			mWindow.setView(mWindow.getDefaultView());
			mMenu.draw(&mWindow);
			break;
		case(gGAME):
			mWindow.setView(mView);
			mGame.draw(&mWindow, interpolation, &ls);
			break;
		case(gGAMEOVER):
			gameOver.setTexture(*mTextureHolder.getTexture(sGAMEOVER));
			mWindow.draw(gameOver);
			break;
		case(gPAUSED):
			mGame.draw(&mWindow, interpolation, &ls);
			gameOver.setTexture(*mTextureHolder.getTexture(sPAUSED));
			ls.RenderLightTexture();
			mWindow.draw(gameOver);
			break;
		case(gCOMPLETE):
			gameOver.setTexture(*mTextureHolder.getTexture(sCOMPLETE));
			mWindow.draw(gameOver);
			break;
		default:
			break;
		}

		mWindow.display();
		
	}
}
