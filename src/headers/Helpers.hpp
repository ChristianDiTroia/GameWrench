#pragma once

#include <vector>

#include "Vector2f.hpp"

namespace gw
{

namespace helpers 
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// Animation Builders
////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Builds an animation vector for a single row on a sprite sheet
	/// </summary>
	/// <param name="row">The row for all the subsprites</param>
	/// <param name="column">The column of the first subsprite</param>
	/// <param name="endColumn">The column of the last subsprite</param>
	/// <returns>Vector of subsprite (row, col) coordinates for the animation</returns>
	std::vector<gw::Vector2f> rowAnimation(int row, int column, int endColumn);

	/// <summary>
	/// Builds an animation vector for multiple rows on a sprite sheet
	/// </summary>
	/// <param name="startRow">The row of the first subsprite</param>
	/// <param name="startCol">The column of the first subsprite</param>
	/// <param name="rowStops">The columns of the last subsprite on each row</param>
	/// <returns>Vector of (row, col) subsprite coordinates for the animation</returns>
	std::vector<gw::Vector2f> multiRowAnimation(int startRow, int startCol, 
		std::vector<int> rowStops);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Terrain Builders
////////////////////////////////////////////////////////////////////////////////////////////////////

		// IDEA: these should return spriteCollection objects
		// Make it possible to merge sprite collections together so these builder functions can be continually used to build out a collection
		
		//IDEA: make tile class that has special functions for connecting to one another


} // namespace helpers

} // namespace gw