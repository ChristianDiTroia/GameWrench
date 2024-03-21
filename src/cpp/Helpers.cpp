#include "Helpers.hpp"

using namespace gw::helpers;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Animation Builders
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<gw::Vector2f> gw::helpers::rowAnimation(int startX, int y, int endX) {
	std::vector<gw::Vector2f> animation;
	for (int x = startX; x <= endX; x++) {
		animation.emplace_back(x, y);
	}
	return animation;
}

std::vector<gw::Vector2f> gw::helpers::multiRowAnimation(int startX, int startY, 
	std::vector<int> rowStops) 
{
	std::vector<Vector2f> animation = rowAnimation(startX, startY, rowStops[0]);
	for (int rows = 1; rows < rowStops.size(); rows++) {
		// create a subanimation at each row and append it to animation
		std::vector<Vector2f> subanimation = rowAnimation(0, startY + rows, rowStops[rows]);
		animation.insert(animation.end(), subanimation.begin(), subanimation.end());
	}
	return animation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Terrain Builders
////////////////////////////////////////////////////////////////////////////////////////////////////
