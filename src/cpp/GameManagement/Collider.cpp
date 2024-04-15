#include "GameManagement/Collider.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Collider::Collider(std::function<void(Sprite& sprite, Sprite& collidedWith, 
	Vector2f collision)> handleCollision) :
	handleCollision(handleCollision)
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

void gw::Collider::resolveCollisions() {
	// Check sprites for collision
	for (Sprite* sprite : sprites.getSprites()) {
		// against sprites
		for (Sprite* collidable : collidables.getSprites()) {
			Vector2f collision = checkCollision(*sprite, *collidable);
			handleCollision(*sprite, *collidable, collision);
		}
		// against animated sprites
		for (Sprite* collidable : collidables.getAnimatedSprites()) {
			Vector2f collision = checkCollision(*sprite, *collidable);
			handleCollision(*sprite, *collidable, collision);
		}
	}
	// Check animated sprites for collision
	for (Sprite* sprite : sprites.getAnimatedSprites()) {
		// against sprites
		for (Sprite* collidable : collidables.getSprites()) {
			Vector2f collision = checkCollision(*sprite, *collidable);
			handleCollision(*sprite, *collidable, collision);
		}
		// against animated sprites
		for (Sprite* collidable : collidables.getAnimatedSprites()) {
			Vector2f collision = checkCollision(*sprite, *collidable);
			handleCollision(*sprite, *collidable, collision);
		}
	}
}