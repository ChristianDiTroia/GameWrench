#include "GameManagement/SpriteCollection.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::SpriteCollection::SpriteCollection(Sprite& initSprite) {
    addSprite(initSprite);
}

gw::SpriteCollection::SpriteCollection(AnimatedSprite& initSprite) {
    addSprite(initSprite);
}

// Copy constructor - initialize with sprites from another collection
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
    if (&(*this) != &collection) { // cannot add a collection to itself
        for (Sprite* sprite : collection.getSprites()) {
            sprites.push_back(sprite);
        }
        for (AnimatedSprite* sprite : collection.getAnimatedSprites()) {
            animatedSprites.push_back(sprite);
        }
    }
    return *this;
}

void gw::SpriteCollection::setAllPositions(Vector2f position) {
    setAllPositions(position.x, position.y);
}

void gw::SpriteCollection::setAllPositions(float x, float y) {
    for (Sprite* sprite : sprites) { sprite->setPosition(x, y); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->setPosition(x, y); }
}

void gw::SpriteCollection::moveAllPositions(Vector2f distance) {
    moveAllPositions(distance.x, distance.y);
}

void gw::SpriteCollection::moveAllPositions(float x, float y) {
    for (Sprite* sprite : sprites) { sprite->movePosition(x, y); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->movePosition(x, y); }
}

void gw::SpriteCollection::setAllScales(Vector2f scaleFactor) {
    setAllScales(scaleFactor.x, scaleFactor.y);
}

void gw::SpriteCollection::setAllScales(float xFactor, float yFactor) {
    for (Sprite* sprite : sprites) { sprite->setScale(xFactor, yFactor); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->setScale(xFactor, yFactor); }
}

void gw::SpriteCollection::scaleAll(Vector2f scaleFactor) {
    scaleAll(scaleFactor.x, scaleFactor.y);
}

void gw::SpriteCollection::scaleAll(float xFactor, float yFactor) {
    for (Sprite* sprite : sprites) { sprite->scale(xFactor, yFactor); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->scale(xFactor, yFactor); }
}

void gw::SpriteCollection::setAllRotations(float rotation) {
    for (Sprite* sprite : sprites) { sprite->setRotation(rotation); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->setRotation(rotation); }
}

void gw::SpriteCollection::rotateAll(float rotation) {
    for (Sprite* sprite : sprites) { sprite->rotate(rotation); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->rotate(rotation); }
}

void gw::SpriteCollection::mirrorAllX() {
    for (Sprite* sprite : sprites) { sprite->mirrorX(); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->mirrorX(); }
}

void gw::SpriteCollection::mirrorAllY() {
    for (Sprite* sprite : sprites) { sprite->mirrorY(); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->mirrorY(); }
}

void gw::SpriteCollection::hideAll() {
    for (Sprite* sprite : sprites) { sprite->hide(); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->hide(); }
}

void gw::SpriteCollection::showAll() {
    for (Sprite* sprite : sprites) { sprite->show(); }
    for (AnimatedSprite* sprite : animatedSprites) { sprite->show(); }
}