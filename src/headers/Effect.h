#pragma once

#include "AnimatedSprite.h"

namespace gw {

class Effect : public gw::AnimatedSprite
{
public:

	///// Constructors /////

	Effect(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

	///// Mutators /////

	void setAnimation(std::vector<Vector2u> animation);

	void playEffect(int animationCycles, float timePerFrame);

	void update(float deltaTime) override;

private:

	float timer;
	std::vector<Vector2u> animation;	// Subsprites in effect animation
	int curFrame;						// Current frame of animation
	int animationCycles;				// Number of animation cycles per effect
	float animationTime;				// Time to display one frame of the effect

};

} // namespace gw

