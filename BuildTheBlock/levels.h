#ifndef LEVELS_H
#define LEVELS_H

#include "level.h"
#include <unordered_map>
#include <string>

namespace levels
{
	extern std::unordered_map<std::string, Level> levelMap;
}

#endif