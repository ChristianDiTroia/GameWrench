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
	animations(std::make_shared<std::vector<std::vector<Vector2f>>>()), // init anim list on heap
	sizes(std::make_shared<std::vector<Vector2f>>()), // init anim size list on heap
	names(std::make_shared<std::vector<std::string>>()), // init anim name list on heap
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
	animations(other.animations), // shared_ptr to existing animations
	sizes(other.sizes), // shared_ptr to existing size list
	names(other.names), // shared_ptr to existing name list
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

/// Store an animation specified by a sequence of subSprites from the sprite sheet.
/// Returns a reference to this so calls can be chained.
Entity& gw::Entity::addAnimation(std::string name, std::vector<Vector2f> subSprites, 
	Vector2f subSpriteSize) 
{
	if (int exists = findAnimation(name) > 0) { // overwrite if exists
		(*animations)[exists] = subSprites;
		(*sizes)[exists] = subSpriteSize;
	}
	else {
		animations->push_back(subSprites);
		sizes->push_back(subSpriteSize);
		names->push_back(name);
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

void gw::Entity::setVelocity(Vector2f velocity) { setVelocity(velocity.x, velocity.y); }

void gw::Entity::setVelocity(float xVelocity, float yVelocity) {
	velocity.x = xVelocity;
	velocity.y = yVelocity;
}

void gw::Entity::addVelocity(Vector2f velocity) { addVelocity(velocity.x, velocity.y); }

void gw::Entity::addVelocity(float xVelocity, float yVelocity) {
	velocity.x += xVelocity;
	velocity.y += yVelocity;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<std::string>& gw::Entity::getAnimationList() const { return *names; }

const std::string& gw::Entity::getCurrentAnimation() const { return (*names)[curAnimation]; }

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of pure virtual method of AnimatedSprite
void gw::Entity::update(float deltaTime) {
	// Update animation //
	if (curAnimation > -1) { // Ensure an animation is selected and exists
		timer += deltaTime;
		if (curAnimation != prevAnimation) { // start new animation
			curFrame = 0;
			timer = 0.0f;
			prevAnimation = curAnimation;
		}
		else if (timer >= animationTime) { // display next animation frame
			curFrame = (curFrame + 1) % (*animations)[curAnimation].size();
			timer -= animationTime;
			if (curFrame == 0) { canInterrupt = true; } // curFrame inc to 0, animation completed
		}
		setSubSprite((*animations)[curAnimation][curFrame], (*sizes)[curAnimation]);
	}

	// Update movement //
	movePosition(velocity.x * deltaTime, velocity.y * deltaTime);
}

// Find a given animation and return its index or -1 if not found
int gw::Entity::findAnimation(std::string animation) {
	int found = -1;
	for (int i = 0; i < names->size(); i++) {
		if ((*names)[i] == animation) {
			found = i;
			break;
		}
	}
	return found;
}