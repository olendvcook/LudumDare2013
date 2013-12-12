#pragma once

#include <SFML\Graphics.hpp>

//Class used to control and store what animation frame the animation is on
class Animation
{
private:
	int mCurrentFrame;
	int mMaxFrames;
	bool isUpOrDown;
	//escalator is what im calling 1234321 instead of 12341234
	bool isEscalator;

	//control how fast to iterate to play animations faster/slower
	float mAnimateSpeed;
	sf::Clock mClock;

public:
	Animation(int pMaxFrames, float pAnimateSpeed = 0.3, bool pIsEscalator = false);
	virtual ~Animation(void);

	void animate();
	void resetAnimation();
	int getCurrentFrame() { return mCurrentFrame; }
};

