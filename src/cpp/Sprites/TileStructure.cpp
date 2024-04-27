#include "Sprites/TileStructure.hpp"

using namespace gw;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

gw::TileStructure::TileStructure(Sprite& tileSprite) :
    Sprite(tileSprite),
    length(0),
    height(0)
{
    calculateBounds();
}

gw::TileStructure::TileStructure(std::string filePath, Vector2u cellSize) :
    TileStructure(filePath, cellSize.x, cellSize.y)
{}

gw::TileStructure::TileStructure(std::string filePath, int cellSizeX, int cellSizeY) :
    Sprite(filePath, cellSizeX, cellSizeY),
    length(0),
    height(0)
{
    calculateBounds();
}

// Copy constructor
gw::TileStructure::TileStructure(const TileStructure& other) :
    Sprite(other),
    tiles(other.tiles),
    length(other.length),
    height(other.height),
    leftBound(other.leftBound),
    rightBound(other.rightBound),
    topBound(other.topBound),
    bottomBound(other.bottomBound),
    centerX(other.centerX),
    centerY(other.centerY)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

void gw::TileStructure::asRow(int length) {
    tiles.clear();
    for (int tile = 0; tile < length; tile++) { tiles.emplace_back(tile, 0); }
    this->length = length;
    height = 1;
}

void gw::TileStructure::asColumn(int height) {
    tiles.clear();
    for (int tile = 0; tile < height; tile++) { tiles.emplace_back(0, tile); }
    length = 1;
    this->height = height;
}

void gw::TileStructure::asRectangle(int length, int height, bool fill) {
    tiles.clear();
    for (int tile = 0; tile < length; tile++) { // length-wise
        tiles.emplace_back(tile, 0);            // top horizontal line
        tiles.emplace_back(tile, height - 1);   // bottom horizontal line
    }
    // only loop 1...height-1 since corners already set in length-wise loop
    for (int tile = 1; tile < height; tile++) { // height-wise
        tiles.emplace_back(0, tile);            // left vertical line
        tiles.emplace_back(length - 1, tile);   // right vertical line
    }
    if (fill) { // fill by creating a row inside the rectangle at each y-level
        // only loop 1...height-1 and length-1 since outline already exists
        for (int y = 1; y < height - 1; y++) {
            for (int tile = 1; tile < length - 1; tile++) {
                tiles.emplace_back(tile, y);
            }
        }
    }
    this->length = length;
    this->height = height;
}

void gw::TileStructure::positionRelativeTo(TileStructure& other, HorizontalBound xBound, 
    VerticalBound yBound) 
{   
    other.calculateBounds();
    float x = other.resolveBound(xBound);
    float y = other.resolveBound(yBound);
    /* Since TileStructures' origin tile is the top-left-most tile, the coodinates must be
    *  offset by the structure's length or height when placing to the left or top of other.
    *  The centers must always be offset half of the length or height.
    */
    Vector2f pixels = getSizeInPixels();
    Vector2f combinedRadius = getOrigin() + other.getOrigin();
    // X-axis positioning
    if (xBound == left) { x -= pixels.x * (length - 1) + combinedRadius.x; }
    else if (xBound == xCenter) { x -= pixels.x * (length - 1) / 2.0f; }
    else { x += combinedRadius.x; } // rightBound
    // Y-axis positioning
    if (yBound == top) { y -= pixels.y * (height - 1) + combinedRadius.y; }
    else if (yBound == yCenter) { y -= pixels.y * (height - 1) / 2.0f; }
    else { y += combinedRadius.y; } // leftBound
    setPosition(x, y);
}

std::vector<Vector2f> gw::TileStructure::getAllPositions() const {
    std::vector<Vector2f> globalCoords;
    for (Vector2u localCoord : tiles) {
        globalCoords.push_back(
            getPosition() + Vector2f(localCoord.x, localCoord.y) * getSizeInPixels()
        );
    }
    return globalCoords;
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
            // Apply a transform to translate each sprite to the correct global position
            tf.setPosition(tile.x * tileSize.x, tile.y * tileSize.y);
            states.transform = tf.getTransform();
            target.draw(getSprite(), states);
        }
    }
}

void gw::TileStructure::calculateBounds() {
    Vector2f position = getPosition();
    Vector2f pixels = getSizeInPixels();
    leftBound = position.x;
    rightBound = position.x + pixels.x * (length - 1);
    topBound = position.y;
    bottomBound = position.y + pixels.y * (height - 1);
    centerX = (leftBound + rightBound) / 2;
    centerY = (topBound + bottomBound) / 2;
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