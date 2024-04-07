#include "Utility/PixelConverter.hpp"

using namespace gw::helpers;

gw::helpers::PixelConverter::PixelConverter(float pixelsPerUnit) :
    converter(pixelsPerUnit)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Conversions
////////////////////////////////////////////////////////////////////////////////////////////////////

void gw::helpers::PixelConverter::scaleSprite(Sprite &sprite, Vector2f gameUnits) const {
    scaleSprite(sprite, gameUnits.x, gameUnits.y);
}

void gw::helpers::PixelConverter::scaleSprite(Sprite &sprite, float gameUnitsX, 
    float gameUnitsY) const 
{
    Vector2f sizeInPixels = sprite.getSizeInPixels();
    float scaleX = scalePixels(sizeInPixels.x, gameUnitsX);
    float scaleY = scalePixels(sizeInPixels.y, gameUnitsY);
    sprite.scale(scaleX, scaleY);
}

float gw::helpers::PixelConverter::fromPixels(float pixels) const {
    return converter.unit1ToUnit2(pixels);
}

float gw::helpers::PixelConverter::toPixels(float gameUnits) const {
    return converter.unit2ToUnit1(gameUnits);
}

float gw::helpers::PixelConverter::scalePixels(int pixels, float gameUnits) const {
    return converter.scaleFactor(pixels, gameUnits);
}
