#include "Sprite.h"

using namespace gw;

gw::Sprite::Sprite(std::string filePath, Vector2u cellSize) :
	mirroredX(false),
	mirroredY(false),
	hidden(false)
{
	setSpriteSheet(filePath, cellSize);
}

void gw::Sprite::setSpriteSheet(std::string filePath, Vector2u cellSize) {
	spriteSheet.loadFromFile(filePath);
	sprite.setTexture(spriteSheet);
	this->cellSize = cellSize;
	setSubSprite(Vector2u(0, 0));
}

void gw::Sprite::setCellSize(Vector2u cellSize) { this->cellSize = cellSize; }

void gw::Sprite::setSubSprite(Vector2u spriteCoord, Vector2u spriteSize) {
	Vector2u pixelCoords = spriteCoord * cellSize;
	Vector2u pixelSize = spriteSize * cellSize;
	sprite.setTextureRect(sf::IntRect(pixelCoords.x, pixelCoords.y, 
										pixelSize.x, pixelSize.y));
	sprite.setOrigin(pixelSize.x / 2.0f, pixelSize.y / 2.0f);
	subSprite = spriteCoord;
}

void gw::Sprite::setPosition(float x, float y) { sprite.setPosition(x, y); }

void gw::Sprite::movePosition(float x, float y) { sprite.move(x, y); }

void gw::Sprite::setScale(float xFactor, float yFactor) {
	sprite.setScale(xFactor, yFactor);
}

void gw::Sprite::mirrorX() {
	sf::Vector2f scale = sprite.getScale();
	if (scale.x != 0 && scale.y != 0) {
		sprite.setScale(-scale.x, scale.y);
		mirroredX = !mirroredX;
	}
}

void gw::Sprite::mirrorY() {
	sf::Vector2f scale = sprite.getScale();
	if (scale.x != 0 && scale.y != 0) {
		sprite.setScale(scale.x, -scale.y);
		mirroredY = !mirroredY;
	}
}

Vector2u gw::Sprite::getSubSprite() const { return subSprite; }

Vector2f gw::Sprite::getPosition() const {
	sf::Vector2f pos = sprite.getPosition();
	return Vector2f(pos.x, pos.y);
}

Vector2f gw::Sprite::getScale() const {
	sf::Vector2f scale = sprite.getScale();
	return Vector2f(scale.x, scale.y);
}

void gw::Sprite::draw(sf::RenderTarget& target, 
						sf::RenderStates states) const {
	if (!hidden) { target.draw(sprite, states); }
}
