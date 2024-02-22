#include "Vector2u.h"
#include <stdlib.h>

using namespace gw;

//////////////////////////////////////////////////////
//////////////////// Constructors ////////////////////
//////////////////////////////////////////////////////

gw::Vector2u::Vector2u(int x, int y) {
	if (x < 0) { this->x = 0; }
	else { this->x = x; }

	if (y < 0) { this->y = 0; }
	else { this->y = y; }
}

///////////////////////////////////////////////////
//////////////////// Operators ////////////////////
//////////////////////////////////////////////////

Vector2u gw::Vector2u::operator+(int n) {
	if (n < 0) { return Vector2u::operator-(abs(n)); }
	else { return Vector2u::Vector2u(x + n, y + n); }
}

Vector2u gw::Vector2u::operator-(int n) {
	int magnitudeN = abs(n);
	int newX = 0; int newY = 0;
	if (magnitudeN < x) { newX = x - n; }
	if (magnitudeN < y) { newY = y - n; }
	return Vector2u::Vector2u(newX, newY);
}

Vector2u gw::Vector2u::operator*(int n) {
	int newX = 0; int newY = 0;
	if (n > 0) { newX = x * n; newY = y * n; }
	return Vector2u::Vector2u(newX, newY);
}

Vector2u gw::Vector2u::operator/(int n) {
	int newX = 0; int newY = 0;
	if (n > 0) { newX = x / n; newY = y / n; }
	return Vector2u::Vector2u(newX, newY);
}

Vector2u gw::Vector2u::operator%(int n) { 
	return (Vector2u::Vector2u(x % n, y % n));
}

Vector2u gw::Vector2u::operator+(Vector2u v) {
	return Vector2u::Vector2u(x + v.x, y + v.y);
}

Vector2u gw::Vector2u::operator-(Vector2u v) {
	int newX = 0; int newY = 0;
	if (v.x < this->x) { newX = x - v.x; }
	if (v.y < this->y) { newY = y - v.y; }
	return Vector2u::Vector2u(newX, newY);
}

Vector2u gw::Vector2u::operator*(Vector2u v) {
	return Vector2u::Vector2u(x * v.x, y * v.y);
}

Vector2u gw::Vector2u::operator/(Vector2u v) {
	return Vector2u::Vector2u(x / v.x, y / v.y);
}

Vector2u gw::Vector2u::operator%(Vector2u v) {
	return Vector2u::Vector2u(x % v.x, y % v.y);
}
