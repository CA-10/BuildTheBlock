#ifndef PIECES_H
#define PIECES_H

#include "piece.h"
#include <unordered_map>
#include <string>

namespace pieces
{
	extern std::unordered_map<std::string, Piece> piecesMap;
}

#endif