#ifndef LEVEL_H
#define LEVEL_H

#include <string>

struct Level
{
	int levelNumber;
	std::string levelName;
	int gridCellWidth;
	int gridCellHeight;

	Level();
	Level(int levelNumber, std::string levelName, int gridCellWidth, int gridCellHeight);
};

#endif