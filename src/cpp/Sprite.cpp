#include "Sprite.hpp"

using namespace gw;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

gw::Sprite::Sprite(std::string filePath, Vector2u cellSize) :
    Sprite(filePath, cellSize.x, cellSize.y)
{}

gw::Sprite::Sprite(std::string filePath, int cellSizeX, int cellSizeY) :
    spriteSheet(std::make_shared<sf::Texture>()), // init new Texture on heap
    cellSize(Vector2u(cellSizeX, cellSizeY)),
    mirroredX(false),
    mirroredY(false),
    hidden(false)
{
    spriteSheet->loadFromFile(filePath); // make spriteSheet Texture from image file
    sprite.setTexture(*spriteSheet);
    setsubsprite(Vector2f(0, 0)); // default top-left corner of texture
}

// Copy constructor
gw::Sprite::Sprite(const Sprite& other) :
    spriteSheet(other.spriteSheet), // shared_ptr to existing spriteSheet on heap
    cellSize(other.cellSize),
    mirroredX(other.mirroredX),
    mirroredY(other.mirroredY),
    hidden(other.hidden)
{
    sprite.setTexture(*spriteSheet);
    // Copy current state of other Sprite
    sprite.setPosition(other.sprite.getPosition());
    sprite.setScale(other.sprite.getScale());
    sprite.setRotation(other.sprite.getRotation());
    setsubsprite(other.getsubsprite());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::Sprite::setsubsprite(Vector2f spriteCoord, Vector2f spriteSize) {
    setsubsprite(spriteCoord.x, spriteCoord.y, spriteSize.x, spriteSize.y);
}

void gw::Sprite::setsubsprite(float row, float column, float sizeX, float sizeY) {
    // Scale cell coords and sizes to actual pixels and convert from row, col to x, y
    float pixelCoordX = column * cellSize.x;    // find x coord from column
    float pixelCoordY = row * cellSize.y;       // find y coord from row
    float pixelSizeX = sizeX * cellSize.x;
    float pixelSizeY = sizeY * cellSize.y;
    sprite.setTextureRect(sf::IntRect(pixelCoordX, pixelCoordY,
                                        pixelSizeX, pixelSizeY));
    sprite.setOrigin(pixelSizeX / 2.0f, pixelSizeY / 2.0f); // center origin
}

void gw::Sprite::setPosition(Vector2f position) { setPosition(position.x, position.y); }

void gw::Sprite::setPosition(float x, float y) { sprite.setPosition(x, y); }

void gw::Sprite::movePosition(Vector2f distance) { movePosition(distance.x, distance.y); }

void gw::Sprite::movePosition(float x, float y) { sprite.move(x, y); }

void gw::Sprite::setScale(Vector2f scaleFactor) { setScale(scaleFactor.x, scaleFactor.y); }

void gw::Sprite::setScale(float xFactor, float yFactor) { sprite.setScale(xFactor, yFactor); }

void gw::Sprite::scale(Vector2f scaleFactor) { scale(scaleFactor.x, scaleFactor.y); }

void gw::Sprite::scale(float xFactor, float yFactor) { sprite.scale(xFactor, yFactor); }

void gw::Sprite::setRotation(float rotation) { sprite.setRotation(rotation); }

void gw::Sprite::rotate(float rotation) { sprite.rotate(rotation); }

void gw::Sprite::mirrorX() {
    sf::Vector2f scale = sprite.getScale();
    if (scale.x != 0) {	// cannot mirror if scale 0
        sprite.setScale(-scale.x, scale.y);
        mirroredX = !mirroredX;
    }
}

void gw::Sprite::mirrorY() {
    sf::Vector2f scale = sprite.getScale();
    if (scale.y != 0) { // cannot mirror if scale 0
        sprite.setScale(scale.x, -scale.y);
        mirroredY = !mirroredY;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

Vector2f gw::Sprite::getsubsprite() const { return subsprite; }

Vector2f gw::Sprite::getPosition() const {
    sf::Vector2f pos = sprite.getPosition();
    return Vector2f(pos.x, pos.y);
}

Vector2f gw::Sprite::getScale() const {
    sf::Vector2f scale = sprite.getScale();
    return Vector2f(scale.x, scale.y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Implement pure virtual sf::Drawable::draw() to make gw::Sprite drawable by SFML
void gw::Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!hidden) { target.draw(sprite, states); }
}