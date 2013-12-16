#pragma once

#include "LightSystem.h"
#include "Light_Point.h"
#include "EmissiveLight.h"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

const int WindowWidth = 640;
const int WindowHeight = 480;

//because pretty much everyone manipulates or uses these states
//they are in a header file
enum GAMESTATE { gMENU, gGAME, gGAMEOVER, gCOMPLETE, gPAUSED };
enum MENUSTATE { mMAIN, mOPTIONS, mTUTORIAL, mCREDITS };

//extern keyword forces that these are initialized somewhere
extern GAMESTATE mGameState;
extern MENUSTATE mMenuState;