#pragma once

const int WindowWidth = 640;
const int WindowHeight = 480;


//because pretty much everyone manipulates or uses these states
//they are in a header file
enum GAMESTATE { gMENU, gGAME, gGAMEOVER, gCOMPLETE, gPAUSED };
enum MENUSTATE { mMAIN, mOPTIONS, mTUTORIAL, mCREDITS };

//extern keyword forces that these are initialized somewhere
extern GAMESTATE mGameState;
extern MENUSTATE mMenuState;