#include "GameViewModel.h"

GameViewModel::GameViewModel(QObject* parent) :
	QObject(parent), m_game{ std::make_unique<Game>() }
{
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

	const auto previousState = GetGameState();
	const auto previousPlayer = GetCurrentPlayer();

	const bool success = m_game->PlayMove({ row, column });

	if (success)
	{
		emit CellChanged(row, column, GetCellState(row, column));

		const auto newState = GetGameState();

		if (newState != previousState)
			emit GameStateChanged(newState);

		const auto newPlayer = GetCurrentPlayer();

		if (newPlayer != previousPlayer && !IsGameOver())
			emit CurrentPlayerChanged(newPlayer);
	}

	return success;
}

void GameViewModel::ResetGame()
{
	m_game = std::make_unique<Game>();

	emit GameReset();
	NotifyAllCellsChanged();
	emit GameStateChanged(GetGameState());
	emit CurrentPlayerChanged(GetCurrentPlayer());
}

void GameViewModel::NotifyCellChanged(uint8_t row, uint8_t column)
{
	emit CellChanged(row, column, GetCellState(row, column));
}

void GameViewModel::NotifyAllCellsChanged()
{
	for (uint8_t row = 0; row < 3; ++row)
	{
		for (uint8_t col = 0; col < 3; ++col)
		{
			NotifyCellChanged(row, col);
		}
	}
}