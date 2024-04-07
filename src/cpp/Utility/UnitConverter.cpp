#include "Utility/UnitConverter.hpp"

using namespace gw::helpers;

gw::helpers::UnitConverter::UnitConverter(float unit1, float unit2) :
    unit1(unit1),
    unit2(unit2)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Conversions / Accessors
////////////////////////////////////////////////////////////////////////////////////////////////////


float gw::helpers::UnitConverter::unit1ToUnit2(float valInUnit1) const {
    return valInUnit1 * (unit2 / unit1);
}

float gw::helpers::UnitConverter::unit2ToUnit1(float valInUnit2) const { 
    return valInUnit2 * (unit1 / unit2);
}

float gw::helpers::UnitConverter::scaleFactor(float valInUnit1, float valInUnit2) const {
    return valInUnit2 / unit1ToUnit2(valInUnit1);
}

float gw::helpers::UnitConverter::unit1ToUnit2Ratio() const { return unit1 / unit2; }

float gw::helpers::UnitConverter::unit2ToUnit1Ratio() const { return unit1 / unit2; }