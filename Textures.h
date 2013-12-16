#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

//Class that holds all the spritesheets so that each entity does not need to store a copy
//Entitie Sprites hold pointers to these spritesheets

//TODO:: different texture objects for different states?

//spritesheet type
//Add types of spritesheets to easily retrieve them by name
//example:
enum SPRITESHEETS { sBUTTONS, sPLAYER, sZOMBIE, sBATTERY, 
					sENGINE, sLASER, sBATTERYMETER, 
					sHEALTHMETER, sHOLOGRAMBORDER, sTITLEBACKGROUND, 
					sGAMEOVER, sPAUSED, sCOMPLETE, sWALL, 
					sTITLEROBOT, sTITLESPACESHIP, sHOLOGRAMTRIANGLE};
class Textures
{
private:
	//vetor that holds the textures
	std::vector<sf::Texture> mSheets;
public:
	Textures(void);
	virtual ~Textures(void);

	sf::Texture* getTexture(SPRITESHEETS pSheet);
};

