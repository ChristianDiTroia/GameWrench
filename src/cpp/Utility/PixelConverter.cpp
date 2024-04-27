#include "Utility/PixelConverter.hpp"

using namespace gw::helpers;

gw::helpers::PixelConverter::PixelConverter(float pixelsPerUnit) :
    converter(pixelsPerUnit)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Conversions
////////////////////////////////////////////////////////////////////////////////////////////////////

float gw::helpers::PixelConverter::fromPixels(float pixels) const {
    return converter.unit1ToUnit2(pixels);
}

gw::Vector2f gw::helpers::PixelConverter::fromPixels(Vector2f pixels) const {
    return fromPixels(pixels.x, pixels.y);
}

gw::Vector2f gw::helpers::PixelConverter::fromPixels(float pixelsX, float pixelsY) const {
    return Vector2f(fromPixels(pixelsX), fromPixels(pixelsY));
}

float gw::helpers::PixelConverter::toPixels(float gameUnits) const {
    return converter.unit2ToUnit1(gameUnits);
}

gw::Vector2f gw::helpers::PixelConverter::toPixels(Vector2f gameUnits) const {
    return toPixels(gameUnits.x, gameUnits.y);
}

gw::Vector2f gw::helpers::PixelConverter::toPixels(float gameUnitsX, float gameUnitsY) const {
    return Vector2f(toPixels(gameUnitsX), toPixels(gameUnitsY));
}

float gw::helpers::PixelConverter::scalePixels(int pixels, float gameUnits) const {
    return converter.scaleFactor(pixels, gameUnits);
}

gw::Vector2f gw::helpers::PixelConverter::scalePixels(Vector2f pixels, Vector2f gameUnits) const {
    return Vector2f(scalePixels(pixels.x, gameUnits.x), scalePixels(pixels.y, gameUnits.y));
}

void gw::helpers::PixelConverter::scaleSprite(Sprite& sprite, float gameUnitsX,
    float gameUnitsY) const
{
    scaleSprite(sprite, Vector2f(gameUnitsX, gameUnitsY));
}

void gw::helpers::PixelConverter::scaleSprite(Sprite& sprite, Vector2f gameUnits) const {
    Vector2f sizeInPixels = sprite.getSizeInPixels();
    sprite.scale(scalePixels(sizeInPixels, gameUnits));
}