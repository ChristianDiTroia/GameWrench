#pragma once

#include "AnimatedSprite.h"

namespace gw {

/// Create and store a single animated effect to play on screen
class Effect : public gw::AnimatedSprite
{
public:

	//////////////////////////////////////////////////////
	//////////////////// Constructors ////////////////////
	//////////////////////////////////////////////////////

	Effect(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

	//////////////////////////////////////////////////
	//////////////////// Mutators ////////////////////
	//////////////////////////////////////////////////

	void setAnimation(std::vector<Vector2f> animation);
	void playEffect(int animationCycles, float timePerFrame);
	void update(float deltaTime) override;

private:

	/////////////////////////////////////////////////////////
	//////////////////// Private Members ////////////////////
	/////////////////////////////////////////////////////////

	float timer;
	std::vector<Vector2f> animation;	// Subsprites in effect animation
	int curFrame;						// Current frame of animation
	int animationCycles;				// Number of animation cycles per effect
	float animationTime;				// Time to display one frame of the effect
};

} // namespace gw

