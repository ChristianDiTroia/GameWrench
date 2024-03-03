#pragma once

#include "Sprite.h"

namespace gw 
{

///	Abstract class that outlines a sprite which can be animated.
/// A subclass of AnimatedSprite can have its animation played by the Game class.
/// Update should determine what the next frame on screen should display.
class AnimatedSprite : public gw::Sprite
{
public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	//// Needed only to call sprite constructors

	AnimatedSprite(std::string filePath, Vector2u cellSize = Vector2u(1, 1)) :
		Sprite(filePath, cellSize) 
	{}

	AnimatedSprite(std::string filePath, int cellSizeX, int cellSizeY) :
		Sprite(filePath, cellSizeX, cellSizeY)
	{}

	// Copy constructor
	AnimatedSprite(const AnimatedSprite& other) :
		Sprite(other)
	{}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>Determines what the next frame on screen should display.</summary>
	/// <param name="deltaTime">Time the previous frame was displayed</param>
	virtual void update(float deltaTime) = 0;
};

} // namespace gw