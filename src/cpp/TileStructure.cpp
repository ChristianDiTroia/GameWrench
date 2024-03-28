#include "TileStructure.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::TileStructure::TileStructure(std::string filePath, Vector2u cellSize) :
    TileStructure(filePath, cellSize.x, cellSize.y)
{}

gw::TileStructure::TileStructure(std::string filePath, int cellSizeX, int cellSizeY) :
    Sprite(filePath, cellSizeX, cellSizeY)
{}

// Copy constructor
gw::TileStructure::TileStructure(const TileStructure& other) :
    Sprite(other),
    tiles(other.tiles)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::TileStructure::asRow(int length) {
    tiles.clear();
    for (int tile = 1; tile <= length; tile++) { tiles.emplace_back(tile, 1); }
}

void gw::TileStructure::asColumn(int height) {
    tiles.clear();
    for (int tile = 1; tile <= height; tile++) { tiles.emplace_back(1, tile); }
}

void gw::TileStructure::asRectangle(int length, int height, bool fill) {
    tiles.clear();
    // loops start at 1 here since we need multiply to scale these numbers later when drawing //
    for (int tile = 1; tile <= length; tile++) { // length-wise
        tiles.emplace_back(tile, 1);        // top horizontal line
        tiles.emplace_back(tile, height);   // bottom horizontal line
    }
    // only loop 2...height-1 since corners already set in length-wise loop
    for (int tile = 2; tile < height; tile++) { // height-wise
        tiles.emplace_back(1, tile);        // left vertical line
        tiles.emplace_back(length, tile);   // right vertical line
    }
    if (fill) { // fill by creating a row inside the rectangle at each y-level
        // only loop 2...height-1 and length-1 since outline already exists
        for (int y = 2; y < height; y++) {
            for (int tile = 2; tile < length; tile++) {
                tiles.emplace_back(tile, y);
            }
        }
    }
}

void gw::TileStructure::asCircle(int radius, bool fill) {
    tiles.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of pure virtual function for SFML drawing
void gw::TileStructure::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isHidden()) {
        // size in pixels == size in cells * size of one cell * scale
        Vector2f tileSize = getSize() * getCellSize() * getScale();
        sf::Transformable tf;
        for (Vector2f tile : tiles) {
            tf.setPosition(tile.x * tileSize.x, tile.y * tileSize.y);
            states.transform = tf.getTransform(); // Transform sprite into each tile to draw
            target.draw(getSprite(), states);
        }
    }
}