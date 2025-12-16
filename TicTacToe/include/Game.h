#pragma once

#include "Board.h"
#include "interfaces/IListener.h"


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

	class Game
	{
	public:
		Game();
		~Game() = default;
		GameDataConstRef GetData() const;
		bool PlayMove(const Position& pos);

		void AddListener(IListenerWeakPtr listener);
		void RemoveListener(IListenerWeakPtr listener);

		void Reset();
	private:
		GameData m_data;
		ListenerVector m_listeners;

		void NotifyCellChanged(const Position& pos, std::optional<Symbol> newState);
		void NotifyCurrentPlayerChanged(Symbol newPlayer);
		void NotifyGameStateChanged(GameState newState);
		void NotifyGameReset();
	};
}