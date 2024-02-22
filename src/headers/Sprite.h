#pragma once

#include "Vector2u.h"
#include "Vector2f.h"
#include <string.h>
#include <SFML/Graphics.hpp>


namespace gw 
{

/// Sprite class for managing sprites and their sprite sheets.
/// Sprites are selected by specifying a cell coordinate on the sprite sheet.
/// Recommended to set cell size to size of one sprite. Default is 1x1 pixels.
class Sprite : public sf::Drawable
{
public:

    //////////////////////////////////////////////////////
    //////////////////// Constructors ////////////////////
    //////////////////////////////////////////////////////

    Sprite(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

    //////////////////////////////////////////////////
    //////////////////// Mutators ////////////////////
    //////////////////////////////////////////////////

    void setSpriteSheet(std::string filePath, Vector2u cellSize = Vector2u(1, 1));
    void setCellSize(Vector2u cellSize);
    void setSubSprite(Vector2u spriteCoord, Vector2u spriteSize = Vector2u(1, 1));
    void setPosition(float x, float y);
    void movePosition(float x, float y);
    void setScale(float xFactor, float yFactor);
    void mirrorX();
    void mirrorY();
    void hide() { hidden = true; }
    void show() { hidden = false; }

    ///////////////////////////////////////////////////
    //////////////////// Accessors ////////////////////
    ///////////////////////////////////////////////////

    Vector2u getSubSprite() const;
    Vector2f getPosition() const;
    Vector2f getScale() const;
    bool isMirroredX() const { return mirroredX; }
    bool isMirroredY() const { return mirroredY; }
    bool isHidden() const { return hidden; }

private:

    /////////////////////////////////////////////////////////
    //////////////////// Private Methods ////////////////////
    /////////////////////////////////////////////////////////

    // Implementation of pure virtual function for SFML drawing
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /////////////////////////////////////////////////////////
    //////////////////// Private Members ////////////////////
    /////////////////////////////////////////////////////////

    sf::Texture spriteSheet;	// Image file containing sprites to
    sf::Sprite sprite;		    // SFML sprite object to be drawn
    Vector2u cellSize;		    // Size of one cell on the spriteSheet
    Vector2u subSprite;		    // Cell coordinates of selected sprite from spriteSheet
    Vector2u spriteSize;		// Size of sprite in cells
    bool mirroredX;
    bool mirroredY;
    bool hidden;
};

} // namespace gw