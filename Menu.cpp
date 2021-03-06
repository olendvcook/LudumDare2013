#include "Menu.h"

//the Class whose implimentation is most scetchy

//pass in pointer to object that contains all the textures
Menu::Menu(Textures *pTextureHolder)
{
	//add the buttons/background
	//example:
	//TODO: Make Button Insertion Less Hardcoded
	
	mButtons.insert(mButtons.begin(), Button(sf::Vector2i(WindowWidth/2 - 96,300), sf::Vector2i(192, 64), pTextureHolder->getTexture(sBUTTONS), bSTART));
	mButtons.insert(mButtons.begin(), Button(sf::Vector2i(WindowWidth/2 - 96,360), sf::Vector2i(192, 64), pTextureHolder->getTexture(sBUTTONS), bCREDITS));
	mButtons.insert(mButtons.begin(), Button(sf::Vector2i(WindowWidth/2 - 96,360), sf::Vector2i(192, 64), pTextureHolder->getTexture(sBUTTONS), bBACK));

	mBackground.setTexture(*pTextureHolder->getTexture(sTITLEBACKGROUND));
}

Menu::~Menu(void)
{
}

void Menu::update()
{
	//mBackground.rotate(0.1);
}
//TODO: REWORK THIS METHOD ALSO, ITS KINDA BAD TOO
//draw all the members of the menu
void Menu::draw(sf::RenderWindow *window)
{
	//draw background
	window->draw(mBackground);

	//shouldn't be here got lazy at the end
	sf::Texture texture;
	sf::Sprite title;

	//-------------------------------------
	//for each button
	for(int i = 0; i < mButtons.size(); i++)
	{
		//draw for each menu state
		switch(mMenuState)
		{
		case(mMAIN):
			//draw only buttons of right type in that menu state
			switch(mButtons.at(i).getButtonType())
			{
			case(bSTART):
			case(bOPTIONS):
			case(bTUTORIAL):
			case(bCREDITS):
				mButtons.at(i).Draw(window);
				break;
			default:
				break;
			}
		case(mOPTIONS):
			break;
		case(mTUTORIAL):
			break;
		case(mCREDITS):
			switch(mButtons.at(i).getButtonType())
			{
			case(bSTART):
			case(bOPTIONS):
			case(bTUTORIAL):
			case(bCREDITS):
				break;
			case(bBACK):
				mButtons.at(i).Draw(window);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		//non buttons draw like backgrounds, titles
		switch (mMenuState)
		{
		case mMAIN:
			texture.loadFromFile("Assets/title.png");
			title.setTexture(texture);
			//title.setScale(0.7,0.7);
			//title.setPosition(WindowWidth/2 - title.getGlobalBounds().width/2, 50);
			window->draw(title);
			break;
		case mOPTIONS:
			break;
		case mTUTORIAL:
			break;
		case mCREDITS:
			texture.loadFromFile("Assets/credits.png");
			title.setTexture(texture);
			//title.setScale(0.7,0.7);
			//title.setPosition(WindowWidth/2 - title.getGlobalBounds().width/2, 50);
			window->draw(title);
			break;
		default:
			break;
		}
	}
}

//get input and do stuff based on that
void Menu::input(sf::Event *pEvent, sf::RenderWindow *pWindow)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*pWindow);
	for(int i=0; i < mButtons.size(); i++)
	{
		switch(pEvent->type)
		{
		case(sf::Event::MouseButtonPressed):
			if(pEvent->mouseButton.button == sf::Mouse::Left && mButtons.at(i).getBounds().contains(mousePos.x, mousePos.y))
			{
				mButtons.at(i).ButtonEvent();
			}
			break;
		case(sf::Event::MouseLeft):
			if(mButtons.at(i).isPressed())
			{
				mButtons.at(i).PressButton();
			}
			break;
		case(sf::Event::MouseButtonReleased):
			if(pEvent->mouseButton.button == sf::Mouse::Left && 
				mButtons.at(i).isPressed() && 
				mButtons.at(i).getBounds().contains(mousePos.x, mousePos.y))
			{
				//tell the button to do its stuff
				//we dont actually do anyhting on button press down, we wait till click release
				//to do stuff
				mButtons.at(i).ButtonEvent();
			}
			else if (pEvent->mouseButton.button == sf::Mouse::Left && mButtons.at(i).isPressed())
			{
				mButtons.at(i).PressButton();
			}
			break;
		}
	}
}


//not implimented yet
void Menu::reset()
{
	mMenuState = mMAIN;
}