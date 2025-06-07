#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

struct Level
{
	int levelNumber;
	std::string levelName;
	int gridCellWidth;
	int gridCellHeight;
	std::vector<std::vector<int>> levelGrid;
	int carRotation;

	Level();
	Level(int levelNumber, std::string levelName, int gridCellWidth, int gridCellHeight, int carRotation, std::vector<std::vector<int>> levelGrid);
};

#endif