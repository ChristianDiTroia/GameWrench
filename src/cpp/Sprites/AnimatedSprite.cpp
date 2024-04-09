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
	behavior([](AnimatedSprite&){}) // init empty behavior func until user provides an impl
{}

gw::AnimatedSprite::AnimatedSprite(const AnimatedSprite& other) :
	Sprite(other),
	velocity(other.velocity),
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

void gw::AnimatedSprite::defineBehavior(std::function<void(AnimatedSprite& self)> behavior) {
	this->behavior = behavior;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Virtual Methods
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::AnimatedSprite::update(float deltaTime) {
	behavior(*this);
	updateAnimation(deltaTime);
	updatePosition(deltaTime);
}

void gw::AnimatedSprite::updatePosition(float deltaTime) {
	movePosition(velocity.x * deltaTime, velocity.y * deltaTime);
}