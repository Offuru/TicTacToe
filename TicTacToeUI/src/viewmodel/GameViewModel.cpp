#include "include/viewmodel/GameViewModel.h"

GameViewModel::GameViewModel(QObject* parent) :
	QObject(parent), m_game{ std::make_unique<Game>() }
{
	m_game->AddListener(this);
}

GameViewModel::~GameViewModel()
{
	if (m_game)
		m_game->RemoveListener(this);
}

QString GameViewModel::GetCurrentPlayerString() const
{
	const auto& data = m_game->GetData().get();
	return QString::fromStdString(data.currentPlayer == Symbol::X ? "X" : "O");
}

Symbol GameViewModel::GetCurrentPlayer() const
{
	return m_game->GetData().get().currentPlayer;
}

GameState GameViewModel::GetGameState() const
{
	return m_game->GetData().get().m_state;
}

QString GameViewModel::GetGameStateString() const
{
	const auto& state = m_game->GetData().get().m_state;
	switch (state)
	{
	case GameState::WaitingForMove:
		return "Waiting for Move";
	case GameState::XWins:
		return "X Wins";
	case GameState::OWins:
		return "O Wins";
	case GameState::Draw:
		return "Draw";
	default:
		return "Unknown State";
	}
}

std::optional<Symbol> GameViewModel::GetCellState(uint8_t row, uint8_t column) const
{
	return m_game->GetData().get().m_board->operator[]({ row, column });
}

bool GameViewModel::IsGameOver() const
{
	return m_game->GetData().get().m_state != GameState::WaitingForMove;
}

bool GameViewModel::PlayMove(uint8_t row, uint8_t column)
{
	if (row > 2 || column > 2 || row < 0 || column < 0)
		return false;

	return m_game->PlayMove({ row, column });
}

void GameViewModel::ResetGame()
{
	m_game->Reset();
}

void GameViewModel::OnCellChanged(const Position& pos, std::optional<Symbol> newState)
{
	emit CellChanged(pos.first, pos.second, newState);
}

void GameViewModel::OnCurrentPlayerChanged(Symbol newPlayer)
{
	emit CurrentPlayerChanged(newPlayer);
}

void GameViewModel::OnGameStateChanged(GameState newState)
{
	emit GameStateChanged(newState);
}

void GameViewModel::OnGameReset()
{
	emit GameReset();

	for (uint8_t row = 0; row < 3; ++row)
	{
		for (uint8_t col = 0; col < 3; ++col)
		{
			emit CellChanged(row, col, std::nullopt);
		}
	}
}
