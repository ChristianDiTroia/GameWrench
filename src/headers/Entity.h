#pragma once

#include "AnimatedSprite.h"

namespace gw {

class Entity : public gw::AnimatedSprite
{
public:

	///// Constructors /////

	Entity(std::string filePath, Vector2u cellSize = Vector2u(1, 1));

	///// Mutators /////

	void addAnimation(std::string name, std::vector<Vector2u> subSprites);
	bool animate(std::string animation, float timePerFrame, bool interuptable = true);
	void setVelocity(float xVelocity, float yVelocity);
	void update(float deltaTime) override;

	///// Accessors /////

	std::vector<std::string> getAnimationList() const;
	std::string getCurrentAnimation() const;

private:

	///// Private Methods /////

	int findAnimation(std::string animation);

	///// Private Members /////

	std::vector<std::vector<Vector2u>> animations;  // SubSprites used for each animation
	std::vector<std::string> animationNames;		// Parallel array to ID animations by name

	int curAnimation;						// Current animation to play
	int prevAnimation;						// Animation played on latest update call
	int curFrame;							// Current frame in the animation
	float animationTime;					// Time to display one frame of an animation
	bool canInterupt;						// Can current animation be interupted
	Vector2f velocity;						// X, Y pixels per second
	float timer;
};

} // namespace gw