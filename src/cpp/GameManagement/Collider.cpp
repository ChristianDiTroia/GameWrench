#include "GameManagement/Collider.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Collider::Collider(std::function<void(Sprite& sprite, Sprite& collidedWith, 
	Vector2f collision)> handleCollision, bool pushOut) :
	handleCollision(handleCollision),
	pushOut(pushOut)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

Collider& gw::Collider::applyCollision(Sprite& sprite) {
	sprites.addSprite(sprite);
	return *this;
}

Collider& gw::Collider::applyCollision(SpriteCollection& sprites) {
	this->sprites.addCollection(sprites);
 	return *this;
}

Collider& gw::Collider::canCollideWith(Sprite& sprite) {
	collidables.addSprite(sprite);
	return *this;
}

Collider& gw::Collider::canCollideWith(SpriteCollection& sprites) {
	collidables.addCollection(sprites);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::Collider::resolveAllCollisions() {
	for (Sprite* sprite : sprites.getSprites()) { resolveCollisions(*sprite); }
	for (AnimatedSprite* sprite : sprites.getAnimatedSprites()) { resolveCollisions(*sprite); }
}

void gw::Collider::resolveCollisions(Sprite& sprite) {
	// check against the sprites
	for (Sprite* collidable : collidables.getSprites()) {
		resolveCollision(sprite, *collidable);
	}
	// check against the animated sprites
	for (Sprite* collidable : collidables.getAnimatedSprites()) {
		resolveCollision(sprite, *collidable);
	}
}

void gw::Collider::resolveCollision(Sprite& sprite, Sprite& collidable) {
	Vector2f collision = checkCollision(sprite, collidable);
	if (collision != Vector2f(0, 0)) {
		handleCollision(sprite, collidable, collision);
		if (pushOut) pushOutOfCollision(sprite, collidable, collision);
		/* NOTE: it is possible for pushOutOfCollision to be push sprite into another collision.
		*  New collisions must be fixed in the next frame to avoid recusrively checking collision. */
	}
}

void gw::Collider::pushOutOfCollision(Sprite& sprite, Sprite& collidable, Vector2f collision) {
	// Find and keep the axis on which the collision occurred
	collision.x = collision.x * (collision.x > collision.y);
	collision.y = collision.y * (collision.y > collision.x);
	// Find the direction the sprite needs to be moved
	if (sprite.getPosition().x < collidable.getPosition().x) { collision.x *= -1; }
	if (sprite.getPosition().y < collidable.getPosition().y) { collision.y *= -1; }
	sprite.movePosition(collision);
}