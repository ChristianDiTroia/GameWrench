#include "AnimatedSprite.hpp"

using namespace gw;

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

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Virtual Methods
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::AnimatedSprite::update(float deltaTime) {
	updateAnimation(deltaTime);
	updatePosition(deltaTime);
}

void gw::AnimatedSprite::updatePosition(float deltaTime) {
	movePosition(velocity.x * deltaTime, velocity.y * deltaTime);
}