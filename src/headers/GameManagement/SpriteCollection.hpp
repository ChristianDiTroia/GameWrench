#pragma once

#include "Sprites/AnimatedSprite.hpp"

namespace gw
{

/// Container for a large group of related Sprites.
class SpriteCollection
{
public:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

    SpriteCollection() = default;

    SpriteCollection(Sprite& initSprite);

    SpriteCollection(AnimatedSprite& initSprite);

    // Copy constructor - initialize with sprites from another collection
    SpriteCollection(const SpriteCollection& other);

    virtual ~SpriteCollection() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators
////////////////////////////////////////////////////////////////////////////////////////////////////
    
    /// Add a sprite to this collection. Returns reference to this for chaining.
    SpriteCollection& addSprite(Sprite& sprite);
    /// Add a sprite to this collection. Returns reference to this for chaining.
    SpriteCollection& addSprite(AnimatedSprite& animatedSprite);
    /// Add a SpriteCollection to this collection. Returns reference to this for chaining.
    SpriteCollection& addCollection(SpriteCollection& collection);

    void setAllPositions(Vector2f position);
    void setAllPositions(float x, float y);
    void moveAllPositions(Vector2f distance);
    void moveAllPositions(float x, float y);
    void setAllScales(Vector2f scaleFactor);
    void setAllScales(float xFactor, float yFactor);
    void scaleAll(Vector2f scaleFactor);
    void scaleAll(float xFactor, float yFactor);
    void setAllRotations(float rotation);
    void rotateAll(float rotation);
    void mirrorAllX();
    void mirrorAllY();
    void hideAll();
    void showAll();

////////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::vector<Sprite*>& getSprites() const { return sprites; }
    const std::vector<AnimatedSprite*>& getAnimatedSprites() const { return animatedSprites; }
    int numSprites() const { return sprites.size(); }
    int numAnimatedSprites() const { return animatedSprites.size(); }
    int totalSprites() const { return sprites.size() + animatedSprites.size(); }

private:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members
////////////////////////////////////////////////////////////////////////////////////////////////////

    // References to all the sprites that exist in this collection //
    std::vector<Sprite*> sprites;
    std::vector<AnimatedSprite*> animatedSprites;
};

} // namespace gw