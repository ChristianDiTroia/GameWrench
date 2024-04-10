#include "Sprites/TileStructure.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::TileStructure::TileStructure(std::string filePath, Vector2u cellSize) :
    TileStructure(filePath, cellSize.x, cellSize.y)
{}

gw::TileStructure::TileStructure(std::string filePath, int cellSizeX, int cellSizeY) :
    Sprite(filePath, cellSizeX, cellSizeY),
    length(1),
    height(1)
{
    calculateBounds();
}

// Copy constructor
gw::TileStructure::TileStructure(const TileStructure& other) :
    Sprite(other),
    tiles(other.tiles),
    length(other.length),
    height(other.height)
{
    calculateBounds();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::TileStructure::asRow(int length) {
    tiles.clear();
    for (int tile = 1; tile <= length; tile++) { tiles.emplace_back(tile, 1); }
    this->length = length;
    height = 1;
}

void gw::TileStructure::asColumn(int height) {
    tiles.clear();
    for (int tile = 1; tile <= height; tile++) { tiles.emplace_back(1, tile); }
    length = 1;
    this->height = height;
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
    this->length = length;
    this->height = height;
}

void gw::TileStructure::positionRelativeTo(TileStructure other, HorizontalBound xBound, 
    VerticalBound yBound) 
{   
    calculateBounds();
    float x = other.resolveBound(xBound);
    float y = other.resolveBound(yBound);
    /* Since TileStructures' origin tile is the top-left-most tile, the coodinates must be offset
    *  by the structure's length or height when placing to the left or top of other.
    *  In the case of centers, must only offset half of the length or height.
    *  Also must offset by the local origin of the tile towards the opposite direction of other.
    */
    Vector2f pixels = getSizeInPixels();
    Vector2f origin = getOrigin();
    if (xBound == left) { x -= length * pixels.x - origin.x; }
    else if (xBound == xCenter) { x -= (length - 1) / 2.0f * pixels.x - origin.x; }
    else { x += pixels.x / 2; }
    if (yBound == top) {  y -= height * pixels.y - origin.y; }
    else if (yBound == yCenter) { y -= (height - 1) / 2.0f * pixels.y - origin.y; }
    else { y += origin.y; }
    setPosition(x, y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of pure virtual function for SFML drawing
void gw::TileStructure::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isHidden()) {
        Vector2f tileSize = getSizeInPixels();
        sf::Transformable tf;
        for (Vector2u tile : tiles) {
            tf.setPosition(tile.x * tileSize.x, tile.y * tileSize.y);
            states.transform = tf.getTransform(); // Transform sprite into each tile to draw
            target.draw(getSprite(), states);
        }
    }
}

void gw::TileStructure::calculateBounds() {
    Vector2f origin = getOrigin();
    Vector2f position = getPosition();
    Vector2f pixels = getSizeInPixels();
    leftBound = position.x - origin.x;
    rightBound = position.x - origin.x + pixels.x * length;
    topBound = position.y - origin.y;
    bottomBound = position.y - origin.y + pixels.y * height;
    centerX = position.x - origin.x + pixels.x * (length - 1) / 2.0f;
    centerY = position.y - origin.y + pixels.y * (height - 1) / 2.0f;
}

float gw::TileStructure::resolveBound(HorizontalBound h) const {
    switch (h) {
        case(left): return leftBound;
        case(right): return rightBound;
        case(xCenter): return centerX;
    }
}

float gw::TileStructure::resolveBound(VerticalBound v) const {
    switch (v) {
        case(top): return topBound;
        case(bottom): return bottomBound;
        case(yCenter): return centerY;
    }
}