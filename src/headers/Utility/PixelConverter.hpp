#pragma once

#include "UnitConverter.hpp"
#include "Sprites/Sprite.hpp"

namespace gw::helpers {

class PixelConverter
{
public:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Creates a converter from pixels to a single in-game unit
    PixelConverter(float pixelsPerUnit);

    virtual ~PixelConverter() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Conversions
////////////////////////////////////////////////////////////////////////////////////////////////////

    float fromPixels(float pixels) const;
    Vector2f fromPixels(Vector2f pixels) const;
    Vector2f fromPixels(float pixelsX, float pixelsY) const;
    float toPixels(float gameUnits) const;
    Vector2f toPixels(Vector2f gameUnits) const;
    Vector2f toPixels(float gameUnitsX, float gameUnitsY) const;
    /// Returns the scale factor to convert the pixels to gameUnits
    float scalePixels(int pixels, float gameUnits) const;
    /// Scales the given sprite to the given number of gameUnits
    void scaleSprite(Sprite &sprite, Vector2f gameUnits) const;
    /// Scales the given sprite to the given number of gameUnits
    void scaleSprite(Sprite &sprite, float gameUnitsX, float gameUnitsY) const;

private:

    UnitConverter converter;
};

} // namespace gw::helpers