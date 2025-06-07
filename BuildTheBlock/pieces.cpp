#include "pieces.h"

namespace pieces
{
	std::unordered_map<std::string, Piece> piecesMap = std::unordered_map<std::string, Piece>
	{
		{ "purple", Piece{
			std::vector<std::vector<int>>{
				{ 0, 0, 1 },
				{ 1, 1, 1 },
			},
			PURPLE
		} },

		{ "green", Piece{
			std::vector<std::vector<int>>{
				{ 0, 1, 1 },
				{ 1, 1, 1 },
			},
			GREEN
		} },
	};
}