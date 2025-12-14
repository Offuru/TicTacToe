#pragma once

#include "Board.h"

namespace tictactoe
{
	using std::uint8_t;

	enum class GameState : uint8_t
	{
		WaitingForMove,
		XWins,
		OWins,
		Draw,
	};

	struct GameData
	{
		BoardPtr m_board;
		GameState m_state;
		Symbol currentPlayer;
	};

	using GameDataRef = std::reference_wrapper<GameData>;
	using GameDataConstRef = std::reference_wrapper<const GameData>;

	class Game
	{
	public:
		Game();
		GameDataConstRef GetData() const;
		bool PlayMove(const Position& pos);

	private:
		GameData m_data;
	};
}