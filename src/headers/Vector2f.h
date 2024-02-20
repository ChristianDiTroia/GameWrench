#pragma once

namespace gw
{

class Vector2f
{
public:

	//// Constructors /////

	Vector2f(float x = 0.0f, float y = 0.0f) { this->x = x; this->y = y; }

	///// Operators /////

	Vector2f operator+(float n) { return Vector2f(x + n, y + n); }
	Vector2f operator-(float n) { return Vector2f(x - n, y - n); }
	Vector2f operator*(float n) { return Vector2f(x * n, y * n); }
	Vector2f operator/(float n) { return Vector2f(x / n, y / n); }

	///// Instance Variables /////

	float x, y;

};

} // namespace gw

