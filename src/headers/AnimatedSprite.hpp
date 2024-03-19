#pragma once

#include "Sprite.hpp"

namespace gw 
{

///	Abstract class that outlines a sprite which can be animated.
/// A subclass of AnimatedSprite can have its animation played by the Game class.
/// Update should determine what the next frame on screen should display.
class AnimatedSprite : public gw::Sprite
{
friend class Game; // Game class should be only caller of update()

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

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Pure Virtual Method
///////////////////////////////////////////////////////////////////////////////////////////////////
	
	/// <summary>Determines what the next frame on screen should display.</summary>
	/// <param name="deltaTime">Time the previous frame was displayed</param>
	virtual void update(float deltaTime) = 0;
};

} // namespace gw