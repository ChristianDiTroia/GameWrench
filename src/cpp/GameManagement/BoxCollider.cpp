#include "GameManagement/BoxCollider.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::BoxCollider::BoxCollider(std::function<void(Sprite& sprite, Sprite& collidedWith,
	Vector2f collision)> handleCollision) :
    Collider(handleCollision)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Collision Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Vector2f gw::BoxCollider::axisAlignedBoxCollision(gw::Sprite& sprite1, gw::Sprite& sprite2) {
	// Find radius of each box //
	Vector2f radius1 = sprite1.getSizeInPixels() / 2;
	Vector2f radius2 = sprite2.getSizeInPixels() / 2;
	// Sum of radii is the min distance between the boxes without a collision //
	float minDistX = radius1.x + radius2.x;
	float mindDistY = radius1.y + radius2.y;
	// Loop through and check all positions in which sprites are drawn //
	Vector2f collision(0, 0);
	for (Vector2f position1 : sprite1.getAllPositions()) {
		for (Vector2f position2 : sprite2.getAllPositions()) {
			// Find displacement on each axis //
			Vector2f displacement = position1 - position2;
			float dx = abs(displacement.x);
			float dy = abs(displacement.y);
			// Check if there is a collision
			if (dx <= minDistX && dy <= mindDistY) { // is colliding
				// Calculate collision //
				float collisionX = abs(dx - minDistX);
				float collisionY = abs(dy - mindDistY);
				/* Determine on which axis the collision occurred and keep that value only
				   if it is greater than the collision already found */
				float ratioX = dx / minDistX;
				float ratioY = dy / mindDistY;
				collisionX = collisionX * (ratioX > ratioY);
				collisionY = collisionY * (ratioY > ratioX);
				if (collisionX > collision.x) { collision.x = collisionX; }
				if (collisionY > collision.y) { collision.y = collisionY; }
			}
		}
	}
	return collision;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Vector2f gw::BoxCollider::checkCollision(gw::Sprite& sprite1, gw::Sprite& sprite2) {
    return axisAlignedBoxCollision(sprite1, sprite2);
}