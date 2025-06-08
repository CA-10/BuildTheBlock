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
	int carRotation;
	std::vector<std::vector<int>> levelGrid;
	std::vector<std::vector<int>> solutionGrid;
	std::vector<std::string> levelPieces;

	Level();
	Level(int levelNumber, std::string levelName, int gridCellWidth, int gridCellHeight, int carRotation, std::vector<std::vector<int>> levelGrid, std::vector<std::vector<int>> solutionGrid, std::vector<std::string> levelPieces);
};

#endif