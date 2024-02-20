#pragma once

namespace gw 
{

class Vector2u
{
public:

	//// Constructors /////

	Vector2u(int x = 0, int y = 0);
	
	///// Operators /////

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

	///// Instance Variables /////

	unsigned int x, y;

};

}