#pragma once

namespace gw 
{

/// Container for two unsigned ints.
/// Operations with negative results default members to zero.
class Vector2u
{
public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2u() { x = 0; y = 0; }

	Vector2u(int x, int y);
	
///////////////////////////////////////////////////////////////////////////////////////////////////
// Operators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2u operator+(int n);
	Vector2u operator-(int n);
	Vector2u operator*(int n);
	Vector2u operator/(int n);
	Vector2u operator%(int n);

	Vector2u operator+(Vector2u v);
	Vector2u operator-(Vector2u v);
	Vector2u operator*(Vector2u v);
	Vector2u operator/(Vector2u v);
	Vector2u operator%(Vector2u v);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Public Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned int x, y;
};

}