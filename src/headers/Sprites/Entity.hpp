#pragma once

#include "AnimatedSprite.hpp"

namespace gw {

/// Sprite that can store and play multiple animations with movement.
/// Specify animations as a list of subsprites in the order they are to be displayed.
class Entity : public gw::AnimatedSprite
{
public:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Entity(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

	Entity(std::string filePath, int cellSizeX = 1, int cellSizeY = 1);

	// Copy construcor
	Entity(const Entity& other);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Mutators 
///////////////////////////////////////////////////////////////////////////////////////////////////

	Entity& addAnimation(std::string name, std::vector<Vector2f> subsprites, 
		Vector2f subspriteSize = Vector2f(1, 1));
	bool animate(std::string animation, float timePerFrame, bool interruptible = true);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors 
///////////////////////////////////////////////////////////////////////////////////////////////////

	const std::vector<std::string>& getAnimationList() const;
	const std::string& getCurrentAnimation() const;

private:

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods 
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Implement pure virtual method from AnimatedSprite
	void updateAnimation(float deltaTime) override;

	int findAnimation(std::string animation);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Private Members 
///////////////////////////////////////////////////////////////////////////////////////////////////

	// Animation instructions //
	std::vector<std::vector<Vector2f>> animations;	// Subsprites for each animation
	std::vector<Vector2f> sizes;					// Size of the subsprite in each animation
	std::vector<std::string> names;					// Parallel array to ID animations by name

	int curAnimation;		// Current animation to play
	int prevAnimation;		// Animation played on latest update call
	int curFrame;			// Current frame in the animation
	float animationTime;	// Time to display one frame of an animation
	bool canInterrupt;		// Can current animation be interupted
	float timer;			// Keep track of overall time of an animation
};

} // namespace gw