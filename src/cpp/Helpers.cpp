#include "Helpers.hpp"

using namespace gw::helpers;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Animation Builders
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<gw::Vector2f> gw::helpers::rowAnimation(int row, int column, int endColumn) {
	std::vector<gw::Vector2f> animation;
	for (int col = column; col <= endColumn; col++) {
		animation.emplace_back(row, col);
	}
	return animation;
}

std::vector<gw::Vector2f> gw::helpers::multiRowAnimation(int startRow, int startColumn, 
	std::vector<int> rowStops) 
{
	std::vector<Vector2f> animation = rowAnimation(startRow, startColumn, rowStops[0]);
	for (int row = startRow + 1; row < rowStops.size(); row++) {
		// create a subanimation at each row and append it to animation
		std::vector<Vector2f> subanimation = rowAnimation(row, 0, rowStops[row]);
		animation.insert(animation.end(), subanimation.begin(), subanimation.end());
	}
	return animation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Terrain Builders
////////////////////////////////////////////////////////////////////////////////////////////////////
