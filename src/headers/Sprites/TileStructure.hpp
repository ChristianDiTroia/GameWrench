#pragma once

#include "Sprite.hpp"

namespace gw {

class TileStructure : public Sprite
{
public:

    enum HorizontalBound
    {
        left,
        right,
        xCenter
    };

    enum VerticalBound
    {
        top,
        bottom,
        yCenter
    };

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

    TileStructure(Sprite& tileSprite);

    TileStructure(std::string filePath, Vector2u cellSize = Vector2u(0, 0));

    TileStructure(std::string filePath, int cellSizeX = 1, int cellSizeY = 1);

    // Copy constructor
    TileStructure(const TileStructure& other);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

    void asRow(int length);
    void asColumn(int height);
    void asRectangle(int length, int height, bool fill);
    void positionRelativeTo(TileStructure& other, HorizontalBound xBound, VerticalBound yBound);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

    virtual std::vector<Vector2f> getAllPositions() const override;
    int getLengthInTiles() { return length; }
    int getHeightInTiles() { return height; }

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Implementation of pure virtual function for SFML drawing
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void calculateBounds();
    // Return the boundary coordinate associated with the given enum //
    float resolveBound(HorizontalBound h) const;
    float resolveBound(VerticalBound v) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Vector2u> tiles;    // The local coordinates of each tile in the structure
    int length;                     // Length of the structure in tiles
    int height;                     // Height of the structure in tiles

    // Boundaries pixel coords for relative positioning of other TileStructures //
    float leftBound;
    float rightBound;
    float topBound;
    float bottomBound;
    float centerX;
    float centerY;
};

} // namespace gw