#include "Effect.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Effect::Effect(std::string filePath, Vector2u cellSize) :
	Effect(filePath, cellSize.x, cellSize.y)
{}

gw::Effect::Effect(std::string filePath, int cellSizeX, int cellSizeY) :
	AnimatedSprite(filePath, cellSizeX, cellSizeY),
	timer(0),
	curFrame(-1),
	animationCycles(0),
	animationTime(0)
{
	hide();
}

// Copy constructor
gw::Effect::Effect(const Effect& other) :
	AnimatedSprite(other),
	animation(other.animation),
	timer(other.timer),
	curFrame(other.curFrame),
	animationCycles(other.animationCycles),
	animationTime(other.animationTime)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::Effect::setAnimation(std::vector<Vector2f> subsprites) { animation = subsprites; }

void gw::Effect::playEffect(int animationCycles, float timePerFrame, Vector2f velocity) {
	playEffect(animationCycles, timePerFrame, velocity.x, velocity.y);
}

void gw::Effect::playEffect(int animationCycles, float timePerFrame,
	float velocityX, float velocityY) 
{
	playEffect(animationCycles, timePerFrame);
	setVelocity(velocityX, velocityY);
}

void gw::Effect::playEffect(int animationCycles, float timePerFrame) {
	this->animationCycles = animationCycles * (animationCycles > 0); // force animationCycles >= 0
	animationTime = timePerFrame;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Override method from AnimatedSprite to prevent moving when effect isn't playing
void gw::Effect::updatePosition(float deltaTime) {
	if (isPlaying()) { movePosition(getVelocity() * deltaTime); }
}

// Implementation of pure virtual function from AnimatedSprite
void gw::Effect::updateAnimation(float deltaTime) {
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
		setSubsprite(animation[curFrame]);
	}
	else if (timer >= animationTime) { // ensure last frame displayed long enough
		// all effect animation cycles completed
		curFrame = -1;
		timer = 0;
		hide();
	}
}