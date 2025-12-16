//module game;

#include "include/Game.h"
#include <algorithm>

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
		NotifyCellChanged(pos, m_data.currentPlayer);

		auto winner = m_data.m_board->CheckWinner();

		if (winner.has_value())
		{
			m_data.m_state = (winner.value() == Symbol::X) ? GameState::XWins : GameState::OWins;
			NotifyGameStateChanged(m_data.m_state);
		}

		else if (m_data.m_board->IsFull())
		{
			m_data.m_state = GameState::Draw;
			NotifyGameStateChanged(m_data.m_state);
		}
		else
		{
			m_data.currentPlayer = (m_data.currentPlayer == Symbol::X) ? Symbol::O : Symbol::X;
			NotifyCurrentPlayerChanged(m_data.currentPlayer);
		}

		return true;
	}

	void Game::AddListener(IListenerWeakPtr listener)
	{
		if (listener)
		{
			m_listeners.push_back(listener);
		}
	}

	void Game::RemoveListener(IListenerWeakPtr listener)
	{
		m_listeners.erase(
			std::remove(
				m_listeners.begin(),
				m_listeners.end(),
				listener
			),
			m_listeners.end()
		);
	}

	void Game::Reset()
	{
		m_data.m_board = std::make_unique<Board>();
		m_data.m_state = GameState::WaitingForMove;
		m_data.currentPlayer = Symbol::X;

		NotifyGameReset();
		NotifyGameStateChanged(m_data.m_state);
		NotifyCurrentPlayerChanged(m_data.currentPlayer);
	}

	void Game::NotifyCellChanged(const Position& pos, std::optional<Symbol> newState)
	{
		for (auto listener : m_listeners)
		{
			if (listener)
			{
				listener->OnCellChanged(pos, newState);
			}
		}
	}

	void Game::NotifyCurrentPlayerChanged(Symbol newPlayer)
	{
		for (auto listener : m_listeners)
		{
			if (listener)
			{
				listener->OnCurrentPlayerChanged(newPlayer);
			}
		}
	}

	void Game::NotifyGameStateChanged(GameState newState)
	{
		for (auto listener : m_listeners)
		{
			if (listener)
			{
				listener->OnGameStateChanged(newState);
			}
		}
	}

	void Game::NotifyGameReset()
	{
		for (auto listener : m_listeners)
		{
			if (listener)
			{
				listener->OnGameReset();
			}
		}
	}
}