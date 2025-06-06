#include "level.h"

Level::Level()
{
	levelNumber = 0;
	levelName = "NA";
	gridCellWidth = 0;
	gridCellHeight = 0;
}

Level::Level(int levelNumber, std::string levelName, int gridCellWidth, int gridCellHeight)
{
	this->levelNumber = levelNumber;
	this->levelName = levelName;
	this->gridCellWidth = gridCellWidth;
	this->gridCellHeight = gridCellHeight;
}