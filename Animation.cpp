#include "Animation.h"

//Class thats a fancy counter to iterate through a list
//see header for more detail

Animation::Animation(int pMaxFrames, float pAnimateSpeed, bool pIsEscalator) :
	mMaxFrames(pMaxFrames),
	mAnimateSpeed(pAnimateSpeed),
	isEscalator(pIsEscalator)
{
	mCurrentFrame = 0;
	isUpOrDown = true;
}

Animation::~Animation(void)
{
}

//iterate through array to change current frame
void Animation::animate()
{
	//if its time to iterate based on animation speed
	if(mClock.getElapsedTime().asSeconds() > mAnimateSpeed){
		//escalator is what im calling 1234321 instead of 12341234
		if(isEscalator)
		{
			if(isUpOrDown)
			{
				mCurrentFrame++;
				if(mCurrentFrame == mMaxFrames -1)
					isUpOrDown = false;
			}
			else
			{
				mCurrentFrame--;
				if(mCurrentFrame == 0)
					isUpOrDown = true;
			}
		}
		else
		{
		mCurrentFrame++;
		mCurrentFrame %= mMaxFrames;
		}
	
		mClock.restart();
	}
}

//go back to first frame
void Animation::resetAnimation()
{
	mCurrentFrame = 0;
}
