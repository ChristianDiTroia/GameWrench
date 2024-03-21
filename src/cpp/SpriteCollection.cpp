#include "SpriteCollection.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::SpriteCollection::SpriteCollection(SpriteCollection& other) {
    addCollection(other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators
////////////////////////////////////////////////////////////////////////////////////////////////////

SpriteCollection& gw::SpriteCollection::addSprite(Sprite& sprite) {
    sprites.push_back(&sprite);
    return *this;
}

SpriteCollection& gw::SpriteCollection::addSprite(AnimatedSprite& animatedSprite) {
    animatedSprites.push_back(&animatedSprite);
    return *this;
}

SpriteCollection& gw::SpriteCollection::addCollection(SpriteCollection& collection) {
    for (Sprite* sprite : collection.getSprites()) { 
        sprites.push_back(sprite); 
    }
    for (AnimatedSprite* sprite : collection.getAnimatedSprites()) { 
        animatedSprites.push_back(sprite); 
    }
    return *this;
}