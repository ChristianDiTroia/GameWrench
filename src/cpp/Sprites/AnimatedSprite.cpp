#include "Sprites/AnimatedSprite.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::AnimatedSprite::AnimatedSprite(std::string filePath, Vector2u cellSize) :
	AnimatedSprite(filePath, cellSize.x, cellSize.y)
{}

gw::AnimatedSprite::AnimatedSprite(std::string filePath, int cellSizeX, int cellSizeY) :
	Sprite(filePath, cellSizeX, cellSizeY),
	velocity(0, 0),
	gravity(0, 0),
	behavior([](AnimatedSprite&){}) // init empty behavior func until user provides an impl
{}

gw::AnimatedSprite::AnimatedSprite(const AnimatedSprite& other) :
	Sprite(other),
	velocity(other.velocity),
	gravity(other.gravity),
	behavior(other.behavior)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::AnimatedSprite::setVelocity(Vector2f velocity) { setVelocity(velocity.x, velocity.y); }

void gw::AnimatedSprite::setVelocity(float xVelocity, float yVelocity) {
	velocity.x = xVelocity;
	velocity.y = yVelocity;
}

void gw::AnimatedSprite::addVelocity(Vector2f velocity) { addVelocity(velocity.x, velocity.y); }

void gw::AnimatedSprite::addVelocity(float xVelocity, float yVelocity) {
	velocity.x += xVelocity;
	velocity.y += yVelocity;
}

void gw::AnimatedSprite::applyGravity(Vector2f velocityPerSecond) { 
	applyGravity(velocityPerSecond.x, velocityPerSecond.y); 
}

void gw::AnimatedSprite::applyGravity(float xVelocityPerSecond, float yVelocityPerSecond) {
	gravity.x = xVelocityPerSecond;
	gravity.y = yVelocityPerSecond;
}

void gw::AnimatedSprite::defineBehavior(std::function<void(AnimatedSprite& self)> behavior) {
	this->behavior = behavior;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Virtual Methods
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::AnimatedSprite::update(float deltaTime) {
	behavior(*this);
	updatePosition(deltaTime);
	updateAnimation(deltaTime);
}

void gw::AnimatedSprite::updatePosition(float deltaTime) {
	addVelocity(gravity * deltaTime);
	movePosition(velocity.x * deltaTime, velocity.y * deltaTime);
}