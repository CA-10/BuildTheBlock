#include "level.h"

Level::Level()
{
	levelNumber = 0;
	levelName = "NA";
	gridCellWidth = 0;
	gridCellHeight = 0;
	carRotation = 0;
	levelGrid = std::vector<std::vector<int>>();
}

Level::Level(int levelNumber, std::string levelName, int gridCellWidth, int gridCellHeight, int carRotation, std::vector<std::vector<int>> levelGrid)
{
	this->levelNumber = levelNumber;
	this->levelName = levelName;
	this->gridCellWidth = gridCellWidth;
	this->gridCellHeight = gridCellHeight;
	this->carRotation = carRotation;
	this->levelGrid = levelGrid;
}