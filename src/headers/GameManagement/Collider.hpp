#pragma once

#include "SpriteCollection.hpp"
#include "Sprites/TileStructure.hpp"

namespace gw {

class Collider
{
friend class Game;

public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

    Collider(std::function<void(Sprite& sprite, Sprite& collidedWith, Vector2f collision)>
        handleCollision, bool pushOut = false);

	virtual ~Collider() = default;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

    Collider& applyCollision(Sprite& sprite);
    Collider& applyCollision(SpriteCollection& sprite);
    Collider& canCollideWith(Sprite& sprite);
    Collider& canCollideWith(SpriteCollection& sprite);

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Check for and resolve collisions using checkCollision and handleCollision
    void resolveAllCollisions();
    
    // Find and resolve any possible collisions with this sprite
    void resolveCollisions(Sprite& sprite);

    // Find and resolve any collision between the given sprites
    void resolveCollision(Sprite& sprite, Sprite& collidable);

    // Move a sprite out of a given collision
    void pushOutOfCollision(Sprite& sprite, Sprite& collidedWith, Vector2f collision);

    // Method of collision detection used by this Collider
    virtual gw::Vector2f checkCollision(gw::Sprite& sprite1, gw::Sprite& sprite2) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

    SpriteCollection sprites;       // Sprites to check for collision
    SpriteCollection collidables;   // Sprites to check if sprites are colliding with
    bool pushOut;                   // Should sprites be pushed out of collidables in a collision

	// What to do when two objects collide
    std::function<void(Sprite& sprite, Sprite& collidedWith, Vector2f collision)> handleCollision;
};

} // namespace gw