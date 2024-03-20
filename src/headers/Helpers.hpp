#pragma once

#include "Vector2f.hpp"

namespace gw
{

namespace helpers 
{

    //// Animation Builder Functions ////

	/// <summary>
	/// Builds a vector of subsprite coordinates for an animation across a single row.
	/// </summary>
	/// <param name="startX">The X coordinate of the first subsprite</param>
	/// <param name="y">The Y coordinate for all the subsprites</param>
	/// <param name="endX">The X coordinate of the last subsprite</param>
	/// <returns></returns>
	std::vector<gw::Vector2f> rowAnimation(int startX, int y, int endX) {
		std::vector<gw::Vector2f> animation;
		for (int x = startX; x <= endX; x++) {
			animation.emplace_back(x, y);
		}
		return animation;
	}

	/// <summary>
	/// Builds a vector of subsprite coordinates across multiple rows proceeding the first.
	/// </summary>
	/// <param name="startX">The X coordinate of the first subsprite</param>
	/// <param name="startY">The Y coordinate of the first subsprite</param>
	/// <param name="rowStops">The X coordinate of the last subsprite for each row</param>
	/// <returns></returns>
	std::vector<gw::Vector2f> multiRowAnimation(int startX, int startY, std::vector<int> rowStops) {
		std::vector<Vector2f> animation = rowAnimation(startX, startY, rowStops[0]);
		for (int rows = 1; rows < rowStops.size(); rows++) {
			std::vector<Vector2f> subanimation = rowAnimation(0, startY + rows, rowStops[rows]);
			animation.insert(animation.end(), subanimation.begin(), subanimation.end());
		}
		return animation;
	}


    //// Terrain Builder Functions ////
		// IDEA: these should return spriteCollection objects
		// Make it possible to merge sprite collections together so these builder functions can be continually used to build out a collection



} // namespace helpers

} // namespace gw