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
	sprites.addCollection(sprites);
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
	handleCollision(sprite, collidable, collision);
	if (pushOut && collision != Vector2f(0, 0)) {
		pushOutOfCollision(sprite, collidable, collision);
		/* Recursive call to check if sprite was pushed into another collision.
		*  Continue resolving until there are no collisions with this sprite */
		resolveCollisions(sprite); // *NOTE*: this is likely unecessary, but is a temp fix
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