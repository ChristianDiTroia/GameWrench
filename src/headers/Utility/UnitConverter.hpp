#pragma once

namespace gw::helpers {

/// Utility class used to define and convert between two units. 
/// This should typically be between pixels and in-game meters.
class UnitConverter
{
public:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

    /// <summary>
    /// Create a UnitConverter by defining equivalent measurements for two different units
    /// </summary>
    /// <param name="unit1">Measure of unit1 equal to the magnitude of unit2</param>
    /// <param name="unit2">Measure of unit2 equal to the magnitude of unit1</param>
    UnitConverter(float unit1, float unit2 = 1.0f);

    virtual ~UnitConverter() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Conversions / Accessors
////////////////////////////////////////////////////////////////////////////////////////////////////

    // Conversions //

    float unit1ToUnit2(float valInUnit1) const;
    float unit2ToUnit1(float valInUnit2) const;
    /// Returns the scale factor to convert valInUnit1 to valInUnit2
    float scaleFactor(float valInUnit1, float valInUnit2) const;
    
    // Accessors //

    float unit1ToUnit2Ratio() const;
    float unit2ToUnit1Ratio() const;

private:

////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////

    float unit1;   // Value of unit 1 that makes magnitude(unit1) == magnitude(unit2)
    float unit2;   // Value of unit 2 that makes magnitude(unit2) == magnitude(unit1)
};

} // namespace gw::helpers