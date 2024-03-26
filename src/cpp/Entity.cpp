#include "Entity.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Entity::Entity(std::string filePath, Vector2u cellSize) :
	Entity(filePath, cellSize.x, cellSize.y)
{}

gw::Entity::Entity(std::string filePath, int cellSizeX, int cellSizeY) :
	AnimatedSprite(filePath, cellSizeX, cellSizeY),
	curAnimation(-1),
	prevAnimation(-1),
	curFrame(-1),
	animationTime(0.0f),
	canInterrupt(true),
	timer(0.0f)
{}

// Copy constructor
gw::Entity::Entity(const Entity& other) :
	AnimatedSprite(other), // call base class copy constructor
	animations(other.animations),
	sizes(other.sizes),
	names(other.names),
	curAnimation(other.curAnimation),
	prevAnimation(other.prevAnimation),
	curFrame(other.curFrame),
	animationTime(other.animationTime),
	canInterrupt(other.canInterrupt),
	timer(other.timer)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

/// Store an animation specified by a sequence of subsprites from the sprite sheet.
/// Returns a reference to this so calls can be chained.
Entity& gw::Entity::addAnimation(std::string name, std::vector<Vector2f> subsprites, 
	Vector2f subspriteSize) 
{
	if (int exists = findAnimation(name) > 0) { // overwrite if exists
		animations[exists] = subsprites;
		sizes[exists] = subspriteSize;
	}
	else {
		animations.push_back(subsprites);
		sizes.push_back(subspriteSize);
		names.push_back(name);
	}
	return *this;
}

bool gw::Entity::animate(std::string animation, float timePerFrame, bool interruptible) {
	int requestedAnim = findAnimation(animation);
	bool animationExists = requestedAnim >= 0;
	if (animationExists && requestedAnim != curAnimation && canInterrupt) {
		// Found different stored animation and current animation is interruptible
		curAnimation = requestedAnim;
		animationTime = timePerFrame;
		canInterrupt = interruptible;
	}
	return animationExists;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<std::string>& gw::Entity::getAnimationList() const { return names; }

const std::string& gw::Entity::getCurrentAnimation() const { return names[curAnimation]; }

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of pure virtual method of AnimatedSprite
void gw::Entity::updateAnimation(float deltaTime) {
	if (curAnimation > -1) { // Ensure an animation is selected and exists
		timer += deltaTime;
		if (curAnimation != prevAnimation) { // start new animation
			curFrame = 0;
			timer = 0.0f;
			prevAnimation = curAnimation;
		}
		else if (timer >= animationTime) { // display next animation frame
			curFrame = (curFrame + 1) % animations[curAnimation].size();
			timer -= animationTime;
			if (curFrame == 0) { canInterrupt = true; } // curFrame inc to 0, animation completed
		}
		setSubsprite(animations[curAnimation][curFrame], sizes[curAnimation]);
	}
}

// Find a given animation and return its index or -1 if not found
int gw::Entity::findAnimation(std::string animation) {
	int found = -1;
	for (int i = 0; i < names.size(); i++) {
		if (names[i] == animation) {
			found = i;
			break;
		}
	}
	return found;
}