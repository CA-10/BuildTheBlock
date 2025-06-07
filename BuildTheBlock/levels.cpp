#include "levels.h"

/*
 * 1 = Roadworks
 * 2 = Passenger
 * 3 = Car
 * 4 = Destination
 */

namespace levels
{
	Level level1 = Level{ 1, "Level 1", 4, 4, 90, {
		{3, 0, 0, 2},
		{1, 0, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 1, 4},
	} };
}