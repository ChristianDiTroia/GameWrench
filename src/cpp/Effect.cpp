#include "Effect.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Effect::Effect(std::string filePath, Vector2u cellSize) :
	AnimatedSprite(filePath, cellSize),
	timer(0),
	curFrame(-1),
	animationCycles(0),
	animationTime(0)
{
	hide();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::Effect::setAnimation(std::vector<Vector2f> subSprites) { animation = subSprites; }

void gw::Effect::playEffect(int animationCycles, float timePerFrame) {
	this->animationCycles += animationCycles * (animationCycles > 0); // ensure animationCycles >= 0
	animationTime = timePerFrame;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of pure virtual function from AnimatedSprite
void gw::Effect::update(float deltaTime) {
	timer += deltaTime;
	if (animationCycles > 0) {
		if (curFrame == -1) { // start new effect animation
			timer = 0;
			curFrame = 0;
			show();
		}
		else if (timer >= animationTime) {
			curFrame = (curFrame + 1) % animation.size();
			timer -= animationTime; // keep extra time so next frame shown sooner
			if (curFrame == animation.size() - 1) { animationCycles--; } // one cycle completed
		}
		setSubSprite(animation[curFrame]);
	}
	else if (curFrame == -1 || timer >= animationTime) { // ensure last frame displayed long enough
		// all effect animation cycles completed
		curFrame = -1;
		timer = 0;
		hide();
	}
}