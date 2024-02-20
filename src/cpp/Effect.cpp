#include "Effect.h"

using namespace gw;

gw::Effect::Effect(std::string filePath, Vector2u cellSize) :
	AnimatedSprite(filePath, cellSize),
	timer(0),
	curFrame(-1),
	animationCycles(0),
	animationTime(0)
{
	hide();
}

void gw::Effect::setAnimation(std::vector<Vector2u> subSprites) { animation = subSprites; }

void gw::Effect::playEffect(int animationCycles, float timePerFrame) {
	this->animationCycles += animationCycles * (animationCycles > 0); // ensure animationCycles >= 0
	animationTime = timePerFrame;
}

void gw::Effect::update(float deltaTime) {
	if (animationCycles > 0) {
		timer += deltaTime;
		if (curFrame == -1) { // start new effect animation
			timer = 0;
			curFrame = 0;
			show();
		}
		else if (timer >= animationTime) {
			curFrame = (curFrame + 1) % animation.size();
			timer -= animationTime;
			if (curFrame == animation.size() - 1) { animationCycles--; }
		}
		setSubSprite(animation[curFrame]);
	}
	else { 
		curFrame = -1; 
		timer = 0;
		hide();
	}
}