#pragma once

#include <vector>

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
	std::vector<gw::Vector2f> rowAnimation(int startX, int y, int endX);

	/// <summary>
	/// Builds a vector of subsprite coordinates across multiple rows proceeding the first.
	/// </summary>
	/// <param name="startX">The X coordinate of the first subsprite</param>
	/// <param name="startY">The Y coordinate of the first subsprite</param>
	/// <param name="rowStops">The X coordinate of the last subsprite for each row</param>
	/// <returns></returns>
	std::vector<gw::Vector2f> multiRowAnimation(int startX, int startY, std::vector<int> rowStops);


    //// Terrain Builder Functions ////
		// IDEA: these should return spriteCollection objects
		// Make it possible to merge sprite collections together so these builder functions can be continually used to build out a collection
		
		//IDEA: make tile class that has special functions for connecting to one another


} // namespace helpers

} // namespace gw