#pragma once

#include "Vector2u.hpp"

namespace gw
{

/// Container for two floats.
class Vector2f
{
public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////
	
	Vector2f() { x = 0; y = 0; }

	Vector2f(float x, float y) { this->x = x; this->y = y; }

	virtual ~Vector2f() = default;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Operators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2f operator+(float n) { return Vector2f(x + n, y + n); }
	Vector2f operator-(float n) { return Vector2f(x - n, y - n); }
	Vector2f operator*(float n) { return Vector2f(x * n, y * n); }
	Vector2f operator/(float n) { return Vector2f(x / n, y / n); }

	Vector2f operator+(Vector2f v) { return Vector2f(x + v.x, y + v.y); }
	Vector2f operator-(Vector2f v) { return Vector2f(x - v.x, y - v.y); }
	Vector2f operator*(Vector2f v) { return Vector2f(x * v.x, y * v.y); }
	Vector2f operator/(Vector2f v) { return Vector2f(x / v.x, y / v.y); }

	bool operator==(Vector2f v) { return x == v.x && y == v.y; }
	bool operator>(Vector2f v) { return x > v.x && y > v.y; }
	bool operator>=(Vector2f v) { return x >= v.x && y >= v.y; }
	bool operator<(Vector2f v) { return x < v.x && y < v.y; }
	bool operator<=(Vector2f v) { return x <= v.x && y <= v.y; }

///////////////////////////////////////////////////////////////////////////////////////////////////
// Public Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

	float x, y;
};

} // namespace gw

