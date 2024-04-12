#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Utility/Vector2u.hpp"
#include "Utility/Vector2f.hpp"

namespace gw 
{

/// Sprite class for managing sprites and their sprite sheets.
/// Sprites are selected by specifying a (row, col) cell coordinate on the sprite sheet.
/// Recommended to set cell size to size of one sprite. Default is 1x1 pixels.
class Sprite : public sf::Drawable
{
public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

    Sprite(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

    Sprite(std::string filePath, int cellSizeX, int cellSizeY);

    // Copy constructor
    Sprite(const Sprite& other);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

    void setSubsprite(Vector2f spriteCoord, Vector2f spriteSize = Vector2f(1, 1));
    void setSubsprite(float row, float column, float sizeX = 1, float sizeY = 1); 
    void setPosition(Vector2f position);
    void setPosition(float x, float y);
    void movePosition(Vector2f distance);
    void movePosition(float x, float y);
    void setScale(Vector2f scaleFactor);
    void setScale(float xFactor, float yFactor);
    void scale(Vector2f scaleFactor);
    void scale(float xFactor, float yFactor);
    void setRotation(float rotation);
    void rotate(float rotation);
    void mirrorX();
    void mirrorY();
    void hide() { hidden = true; }
    void show() { hidden = false; }

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f getSubsprite() const { return subsprite; }
    Vector2f getPosition() const;
    Vector2f getOrigin() const;
    Vector2f getScale() const;
    float getRotation() const;
    /// Size of one cell in pixels
    Vector2u getCellSize() const { return cellSize; }
    /// Size of the current subsprite in cells
    Vector2f getSize() const { return size; }
    Vector2f getSizeInPixels() const;
    bool isMirroredX() const { return mirroredX; }
    bool isMirroredY() const { return mirroredY; }
    bool isHidden() const { return hidden; }

public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Protected Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Subclasses can safely access their SFML Sprite if needed
    const sf::Sprite& getSprite() const { return sprite; }

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Implementation of pure virtual function for SFML drawing
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Resource-heavy textures stored once on the heap as a shared resource
    std::shared_ptr<sf::Texture> spriteSheet;   // Image file containing sprites to be drawn

    sf::Sprite sprite;	    // SFML sprite object to be drawn
    Vector2u cellSize;	    // Size of one cell on the spriteSheet
    Vector2f subsprite;	    // Cell row, col coordinates of selected sprite from spriteSheet
    Vector2f size;          // Size in cells of the current subsprite
    bool mirroredX;
    bool mirroredY;
    bool hidden;
};

} // namespace gw