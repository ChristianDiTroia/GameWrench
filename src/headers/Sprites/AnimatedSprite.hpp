#pragma once

#include <functional>

#include "Sprite.hpp"

namespace gw 
{

///	Abstract class that outlines a sprite which can be animated.
/// A subclass of AnimatedSprite can have its animation played by the Game class.
/// updateAnimation should determine what the next frame on screen should display.
class AnimatedSprite : public gw::Sprite
{

	friend class Game; // Game class should be only caller of update()

public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	AnimatedSprite(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

	AnimatedSprite(std::string filePath, int cellSizeX, int cellSizeY);

	// Copy constructor
	AnimatedSprite(const AnimatedSprite& other);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	void setVelocity(Vector2f velocity);
	void setVelocity(float xVelocity, float yVelocity);
	void addVelocity(Vector2f velocity);
	void addVelocity(float xVelocity, float yVelocity);
	void applyGravity(Vector2f velocityPerSecond);
	void applyGravity(float xVelocityPerSecond, float yVelocityPerSecond);
	/// <summary>
	/// Define a behavior function that will execute before every frame to update this sprite
	/// </summary>
	/// <param name="behavior(self)">
	/// A custom behavior function where self is a reference to this sprite
	/// </param>
	void defineBehavior(std::function<void(AnimatedSprite& self)>behavior);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2f getVelocity() const { return velocity; }

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods
///////////////////////////////////////////////////////////////////////////////////////////////////

	/// Update is used by Game class to update all states of this AnimatedSprite.
	void update(float deltaTime);

	/// <summary>Determines and sets the position of the sprite</summary>
	/// <param name="deltaTime">Time the previous frame was displayed</param>
	virtual void updatePosition(float deltaTime);

	/// <summary>Determines and sets the subsprite to be displayed next frame.</summary>
	/// <param name="deltaTime">Time the previous frame was displayed</param>
	virtual void updateAnimation(float deltaTime) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members
///////////////////////////////////////////////////////////////////////////////////////////////////

	Vector2f velocity;									// X, Y pixels per second
	Vector2f gravity;									// Velocity to add per second
	std::function<void(AnimatedSprite& self)>behavior;	// User-defined behavior function
};

} // namespace gw