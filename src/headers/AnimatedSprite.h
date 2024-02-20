#pragma once

#include "Sprite.h"

namespace gw 
{

/// <summary>
///	Abstract class that outlines a sprite which can be animated.
///	A subclass of AnimatedSprite can have its animation played by the Game class.
///	Update should determine what the next frame on screen should display.
/// </summary>
class AnimatedSprite : public gw::Sprite
{
public:

	AnimatedSprite(std::string filePath, Vector2u cellSize = Vector2u(1, 1)) :
		Sprite(filePath, cellSize) 
	{}

	virtual void update(float deltaTime) = 0;

};

} // namespace gw