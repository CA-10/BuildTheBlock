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
			PURPLE,
			Vector2{30, 30}
		} },

		{ "green", Piece{
			std::vector<std::vector<int>>{
				{ 0, 1, 1 },
				{ 1, 1, 1 },
			},
			GREEN,
			Vector2{30, 30}
		} },
	};
}