//module game;

#include "Game.h"

namespace tictactoe
{
	Game::Game() : m_data
	{
		std::make_unique<Board>(),
		GameState::WaitingForMove,
		Symbol::X
	}
	{
	}

	GameDataConstRef Game::GetData() const
	{
		return m_data;
	}

	bool Game::PlayMove(const Position& pos)
	{
		if (m_data.m_state != GameState::WaitingForMove)
			return false;

		if (m_data.m_board->operator[](pos).has_value())
			return false;

		m_data.m_board->operator[](pos) = m_data.currentPlayer;

		auto winner = m_data.m_board->CheckWinner();

		if (winner.has_value())
			m_data.m_state = (winner.value() == Symbol::X) ? GameState::XWins : GameState::OWins;

		else if (m_data.m_board->IsFull())
			m_data.m_state = GameState::Draw;
		else
			m_data.currentPlayer = (m_data.currentPlayer == Symbol::X) ? Symbol::O : Symbol::X;

		return true;
	}
}