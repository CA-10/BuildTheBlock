#ifndef GAME_RENDERING_H
#define GAME_RENDERING_H

#include "raylib.h"
#include "colours.h"
#include "constants.h"
#include <unordered_map>
#include <string>
#include "levelTracker.h"

extern std::unordered_map<std::string, Texture2D> texturesMap;

void loadTextures();
void renderPieces();
void renderGrid();
void unloadTextures();

#endif