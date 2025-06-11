#include "levels.h"

/*
 * 1 = Roadworks
 * 2 = Passenger
 * 3 = Car
 * 4 = Destination
 * 5 = Tunnel
 */

namespace levels
{
	std::unordered_map<std::string, Level> levelMap = std::unordered_map<std::string, Level>
	{
		{
			"level1", Level{ 1, "Level 1", 4, 4, 90, 
				{
					 {3, 0, 0, 2},
					 {1, 0, 1, 0},
					 {0, 0, 0, 0},
					 {0, 0, 1, 4},
				},

				{
					 {0, 0, 0, 0},
					 {1, 1, 1, 0},
					 {1, 1, 1, 0},
					 {1, 1, 1, 0},
				},

				{
					"purple", "green"
				}
			},
		},

		{
			"level2", Level{ 2, "Level 2", 4, 4, 90,
				{
					 {3, 0, 0, 2},
					 {1, 0, 1, 0},
					 {0, 0, 0, 4},
					 {0, 0, 0, 1},
				},

				{
					 {0, 0, 0, 0},
					 {1, 1, 1, 0},
					 {1, 1, 1, 0},
					 {1, 1, 1, 0},
				},

				{
					"purple", "blue"
				}
			},
		},
	};
}