export module game;

import std;

import board;

namespace tictactoe
{
	using std::uint8_t;

	export enum class GameState : uint8_t
	{
		WaitingForMove,
		XWins,
		OWins,
		Draw,
	};

	export struct GameData
	{
		BoardPtr m_board;
		GameState m_state;
		Symbol currentPlayer;
	};

	export using GameDataRef = std::reference_wrapper<GameData>;
	export using GameDataConstRef = std::reference_wrapper<const GameData>;

	export class Game
	{
	public:
		Game();
		GameDataConstRef GetData() const;
		bool PlayMove(const Position& pos);

	private:
		GameData m_data;
	};
}